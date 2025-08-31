// Copyright Flaz89.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere -> SetupAttachment(GetRootComponent());
	Sphere-> OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere-> OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
	

}
/*
 * OnComponentBeginOverlap() delegate we call OnOverlap() callback function and we check if OtherActor has AbilitySystemInterface (AuraBaseCharacter)
 * has, and if yes we want to extract attribute system from it
 */
void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface -> GetAbilitySystemComponent() -> GetAttributeSet(UAuraAttributeSet::StaticClass()));
		// const_cast just to force mutability as exercise
		UAuraAttributeSet* MutableAuraAttribuetSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttribuetSet -> SetHealth(AuraAttributeSet -> GetHealth() + 25.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}


