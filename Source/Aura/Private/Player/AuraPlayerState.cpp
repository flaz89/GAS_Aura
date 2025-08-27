// Copyright Flaz89.


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// this defines how many times in a second an object (PlayerState in this case) sends data to server, 100.f means 100Hz updating server each 10 milliseconds(ms)
	SetNetUpdateFrequency(100.f);  
}
