// Copyright Epic Games, Inc. All Rights Reserved.

#include "HWProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Target.h"
#include "HWCharacter.h"
#include "HWGameStateBase.h"
#include "HWGameInstance.h"
#include "Components/SphereComponent.h"
#include "SAICharacter.h"

AHWProjectile::AHWProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AHWProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AHWProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherComp->GetName()));
	if (OtherActor != this && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
		Destroy();
	}

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp->GetName() == "Box")) {
		ASAICharacter* target = Cast<ASAICharacter>(OtherActor);
		target->CurrentHealth -= 1;
		if (!target->CurrentHealth) {
			GetWorld()->GetAuthGameMode()->GetGameState<AHWGameStateBase>()->addScore(target->score);
			GetGameInstance<UHWGameInstance>()->addGoal(target->score);
			target->Destroy();
		}
		Destroy();
	}
	
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp->GetName() == "Mesh"))
	{
		ATarget* target = Cast<ATarget>(OtherActor);
		GetWorld()->GetAuthGameMode()->GetGameState<AHWGameStateBase>()->addScore(target->score);
		GetGameInstance<UHWGameInstance>()->addGoal(target->score);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %d"), GetWorld()->GetAuthGameMode()->GetGameState<AHWGameStateBase>()->getScore()));
		target->Destroy();
		Destroy();
	}
	
}