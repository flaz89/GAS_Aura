// Copyright Flaz89.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true; // it defines if this entity update the server in a networking context
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	// Set the Subsystem with Mapping context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	// Set shown mouse cursor and its behavior
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
