// Copyright Flaz89.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"


/*
 * Being a base class for characters used in this progect we set it as "Abstract" preventing to instanciate
 * in UE editor and removing "Input function" and "Tick function" 
 */

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	
	//Ability System Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

public:	
	//virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
