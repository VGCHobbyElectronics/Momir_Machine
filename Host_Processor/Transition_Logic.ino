
void State_Transition_Logic() {
    PreviousState = CurrentState;

    //Reset Requested State if it's been done.
    if (RequestedState == CurrentState) {
        RequestedState = NULL_REQUESTED;
    }
    if (RequestedSubState == CurrentSubstate) {
        RequestedSubState = NULL_REQUESTED;
    }

    switch(CurrentState) {
        case STATE_POWER_OFF:
            Transition_State_Power_Off();
        break;
        case STATE_INITIALIZATION:
            Transition_State_Initialization();
        break;
        case STATE_WAIT:
            Transition_State_Wait();
        break;
        case STATE_PRINTING:
            Transition_State_Printing();
            Transition_Substates_Printing();
        break;
        case STATE_PRINTING_FAILED:
            Transition_State_Printing_Failed();
        break;
        case STATE_ERROR:
            //Do Nothing, No Transition from Error State.
        break;
        default:
            //Should Never Happen.
        break;
   }
}

void Transition_State_Power_Off() {
    switch (RequestedState) {
        case STATE_INITIALIZATION:
            CurrentState = STATE_INITIALIZATION;
        break;
        default:
            //Do Nothing
        break;
    }
}

void Transition_State_Initialization() {
    switch(Event) {
        case EVENT_INIT_PASSED:
            CurrentState = STATE_WAIT;
        break;
        case EVENT_INIT_FAILED:
            CurrentState = STATE_ERROR;
        break;
        default:
            //Do Nothing
        break;
    }
}

void Transition_State_Wait() {
    switch(Event) {
        case BUTTON_PRESSED:
            if (Start_Button_Pressed) {
                CurrentState = STATE_PRINTING;
				CurrentSubstate = SUBSTATE_INITIAL_ENTRY;
			}
        break;
        default:
            //Do Nothing
        break;
    }
}

void Transition_State_Printing() {
    switch(RequestedState) {
        case STATE_WAIT:
            if(StartTime == 0) {
                StartTime = millis();
            }
            else if ((millis() - StartTime) < PRINT_FINISHED_HOLD_OFF_TIME) {
                //Do Nothing. Waiting.
            }
            else {
                CurrentState = STATE_WAIT;
                StartTime = 0; //Reset Counter for Next Use.
                CMC_Digit_One = NULL;
                CMC_Digit_Two = NULL;
            }
        break;
        case STATE_PRINTING_FAILED:
            CurrentState = STATE_PRINTING_FAILED;
        break;
        default:
            //Do Nothing
        break;
    }
}

void Transition_Substates_Printing() {
	switch(RequestedSubState) {
        case SUBSTATE_VALID_PRINT_CHECK:
			CurrentSubstate = SUBSTATE_VALID_PRINT_CHECK;
		break;
		case SUBSTATE_RANDOM_NUMBER:
            CurrentSubstate = SUBSTATE_RANDOM_NUMBER;
		break;
		case SUBSTATE_LOAD_BITMAP:
            CurrentSubstate = SUBSTATE_LOAD_BITMAP;
		break;
		case SUBSTATE_DATA_TRANS_TO_PRINT:
		    CurrentSubstate = SUBSTATE_DATA_TRANS_TO_PRINT;
		break;
    case SUBSTATE_WAIT_FOR_EXIT:
        CurrentSubstate = SUBSTATE_WAIT_FOR_EXIT;
    break;
    }
}

void Transition_State_Printing_Failed() {
    switch(RequestedState) {
        case STATE_WAIT:
            if(StartTime == 0) {
                StartTime = millis();
			}
            else if ((millis() - StartTime) < PRINT_FAILED_HOLD_OFF_TIME) {
                //Do Nothing. Waiting.
            }
            else {
                CurrentState = STATE_WAIT;
                StartTime = 0; //Reset Counter for Next Use.
                CMC_Digit_One = NULL;
                CMC_Digit_Two = NULL;
            }
        default:
            //Do Nothing
        break;
    }
}
