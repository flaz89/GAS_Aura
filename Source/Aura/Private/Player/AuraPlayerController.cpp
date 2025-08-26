// Copyright Flaz89.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true; // it defines if this entity updates the server in a networking context
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CursorTrace();
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

/*
 ************************************** INPUTS
 */


void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

/* Callback function for player movement.
 * Need to get the forward direction of the controller in order to add the correct movement input
 */
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();	// transform InputActionValue into FVector2D
	const FRotator Rotation = GetControlRotation();							// extract controller rotation (includes camera rotation)
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);			// created new rotator just with Yaw from Rotation

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // extract normalized forward vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);	// extract normalized forward vector 

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);	// cause is linked to W/S key that's why Y
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);	// cause is linked to A/D key that's why X
	}
}



void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();

	/*
	 * Highlight scenarios:
	 * A. LastActor == nullptr && CurrentActor == nullptr --> return
	 * B. LastActor == nullptr && CurrentActor is valid --> highlight CurrentActor
	 * C. LastActor is valid && CurrentActor == nullptr --> unhighlight LastActor
	 * D. LastActor is valid && CurrentActor is valid --> unhighlight LastActor, highlight CurrentActor
	 * E. LastActor is valid && CurrentActor is valid && LastActor == CurrentActor
	 */
	if (LastActor == nullptr)
	{
		if (CurrentActor != nullptr) // Case B
		{
			CurrentActor->HighlightActor(); 
		}
		// Case A
	}
	else
	{
		if (CurrentActor == nullptr) // Case C
		{
			LastActor->UnHighlightActor(); 
		}
		else
		{
			if (LastActor != CurrentActor) // Case D
			{
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			}
			// Case E
		}
	}
	
}
