#include "Global_Definitions.h" //Global Definitions
#include "Global_Variables.h" //Global Variables
	
void loop() {
    if(CurrentState >= STATE_OPERATIONAL_FOR_INPUT) {
        Input_Processing();
    }
	
    Event_Logic();
    State_Transition_Logic();
    State_Execution_Logic();

    if(CurrentState >= STATE_OPERATIONAL_FOR_OUTPUT) {
        Output_Processing();
    }      
}

void State_Execution_Logic() {
    switch(CurrentState)
    {
    case STATE_POWER_OFF:
        Execute_State_Power_Off();
    break;
	
    case STATE_INITIALIZATION:
        Execute_State_Initialization();
    break;
	
    case STATE_WAIT:
         Execute_State_Wait();
    break;
	
    case STATE_PRINTING:
        Execute_State_Printing();
    break;
	
    case STATE_PRINTING_FAILED:
        Execute_State_Printing_Failed();
    break;

    case STATE_ERROR:
        Execute_State_Error();
    break;

    default:
         //Do Nothing
    break;
    }
}

void Execute_State_Power_Off() {
    //State Does Nothing But Move To Next State After Hold Off Time.
    delay(POWER_UP_HOLD_OFF_TIME);
    RequestedState = STATE_INITIALIZATION;
}

void Execute_State_Initialization() {
    InitializationComplete  = InitializationCompleteCheck();
}

void Execute_State_Wait() {
    if(Event == BUTTON_PRESSED) {
        for (int currentButton = 0; currentButton < NUM_OF_CMC_BUTTONS_IN_REG_A; currentButton++) {
            if((Button_A_Read)&(1<<currentButton)) {
            CMC_Digit_Two = CMC_Digit_One; //Shift Digit Up.
            CMC_Digit_One = currentButton;
        }
    }

        for (int currentButton = 0; currentButton < NUM_OF_CMC_BUTTONS_IN_REG_B; currentButton++) {
            if((Button_B_Read)&(1<<currentButton)) {
                CMC_Digit_Two = CMC_Digit_One; //Shift Digit Up.
                CMC_Digit_One = currentButton + NUM_OF_CMC_BUTTONS_IN_REG_A;
            }
        }
    }
}
		
void Execute_State_Printing_Failed() {
    RequestedState = STATE_WAIT;
}

void Execute_State_Error() {
    //Do Nothing. Can't Exit State.
}

//TO DO: NOT FINISHED. NEED TO CLEAN UP AND ADD SUBSTATES. DELETE PRINTER FOR NOW.
void Execute_State_Printing() {
    switch(CurrentSubstate) {
        case SUBSTATE_INITIAL_ENTRY:
			RequestedSubState = SUBSTATE_VALID_PRINT_CHECK;
		break;
		
		case SUBSTATE_VALID_PRINT_CHECK:
			if(Execute_Substate_Valid_Print_Check())
				RequestedSubState = SUBSTATE_RANDOM_NUMBER;
			else {
				RequestedState = STATE_PRINTING_FAILED;
			}
		break;
		
		case SUBSTATE_RANDOM_NUMBER:
      Execute_Substate_Random_Number(); 
			RequestedSubState = SUBSTATE_LOAD_BITMAP;
		break;
		
		case SUBSTATE_LOAD_BITMAP:
      Execute_Substate_Load_Bitmap();
		  RequestedSubState = SUBSTATE_WAIT_FOR_EXIT;
		break;

    case SUBSTATE_WAIT_FOR_EXIT:
      RequestedState = STATE_WAIT;
    break;
    
		default:
			//Shouldn't be here.
            RequestedSubState = SUBSTATE_INITIAL_ENTRY;
		break;
	}
	
}

void Execute_Substate_Load_Bitmap() {
  Serial.println("Navi Hey Reached the Bitmap heres your ram");
  File WorkingFile = SD.open(String(FolderPath));
  Serial.println(freeRam());
  if(WorkingFile)
  Serial.println("Hey the file opened");
  printer.printBitmap(360, 520, dynamic_cast<Stream*>(&WorkingFile));
  WorkingFile.close();
  printer.feed(2);
  Serial.println("Passed it");
}

bool Execute_Substate_Valid_Print_Check() {
	
	  Serial.println(F("NAVI HEY VALID"));
  Serial.println(String(FolderPath));
  
	if(CMC_Digit_One == NULL) {
     return false;
	}
  else {
      FolderPath[LOCATION_OF_CMC_ONE_BIT] = CMC_Digit_One + ASCII_NUMERAL_OFFSET;
  }
  
  if(CMC_Digit_Two != NULL) {
      FolderPath[LOCATION_OF_CMC_TWO_BIT] = CMC_Digit_Two + ASCII_NUMERAL_OFFSET;    
  }

  FolderPath[START_LOCATION_OF_FILE_PATH] = 0;
FolderPath[START_LOCATION_OF_FILE_PATH+1] = 0;
FolderPath[START_LOCATION_OF_FILE_PATH+2] = 0;
FolderPath[START_LOCATION_OF_FILE_PATH+3] = 1;
 Serial.println("NAVI HEY RAM");
 Serial.println(freeRam());  
  if(SD.exists(FolderPath)) {
      return true;
  }
  else {
      return false;
  }
  
}

void Execute_Substate_Random_Number() {

  if (!firstTimeThrough) {
    firstTimeThrough = true;
    randomSeed(micros());
  }
  
  for (int currentDecimalSpot = 0; currentDecimalSpot < NUM_OF_DECIMALS_IN_FILE_NAME; currentDecimalSpot++) {
     for (int currentDigit = 1; currentDigit < 10; currentDigit++) {
      FolderPath[currentDecimalSpot + START_LOCATION_OF_FILE_PATH] = currentDigit + ASCII_NUMERAL_OFFSET;

      if(!SD.exists(String(FolderPath))) {
        FolderPath[currentDecimalSpot + START_LOCATION_OF_FILE_PATH] = FolderPath[currentDecimalSpot + START_LOCATION_OF_FILE_PATH] - 1; //Subtract one to go back to one that exists.
        break;
      }
     }
  }

  Serial.println(F("NAVI HEY"));
  Serial.println(String(FolderPath));
  
  int upperBound = ((FolderPath[0+ START_LOCATION_OF_FILE_PATH]-ASCII_NUMERAL_OFFSET) * 1000) + ((FolderPath[1+ START_LOCATION_OF_FILE_PATH]-ASCII_NUMERAL_OFFSET) * 100) + ((FolderPath[2+ START_LOCATION_OF_FILE_PATH]-ASCII_NUMERAL_OFFSET) * 10) + ((FolderPath[3+ START_LOCATION_OF_FILE_PATH]-ASCII_NUMERAL_OFFSET) * 1);
  int randomNumber = randomNumber = random(1, upperBound+1);

  FolderPath[0 + START_LOCATION_OF_FILE_PATH] = (randomNumber / 1000) + ASCII_NUMERAL_OFFSET;
  FolderPath[1 + START_LOCATION_OF_FILE_PATH] = ((randomNumber % 1000)/100) + ASCII_NUMERAL_OFFSET;
  FolderPath[2 + START_LOCATION_OF_FILE_PATH] = (((randomNumber % 1000)%100)/10) + ASCII_NUMERAL_OFFSET;
  FolderPath[3 + START_LOCATION_OF_FILE_PATH] = ((((randomNumber % 1000)%100)%10)/1) + ASCII_NUMERAL_OFFSET;
}

bool InitializationCompleteCheck() {
    
    //Check if SD Card exists
    if (!SD.begin(4)) {
       Serial.println(F("Initialization Failed"));
        return false; 
    }
//    else
//    {
//        //Check if Parameter file exists.
//        if (!SD.exists(PathToParametersFile)) {
//            return false;
//        }
//        else {
//            WorkingFile = SD.open(PathToParametersFile);
//			
//            for (int byteNumber = 0; byteNumber < PARAM_BYTES_FOR_DIR_PATH; byteNumber++) {
//                FolderPath[byteNumber] = WorkingFile.read();
//            }
//
//            Width_In_Bytes = WorkingFile.read();
//            Length_In_Bytes = WorkingFile.read();                           
//            WorkingFile.close();
//        }
//    }
    Serial.println(F("Initialization Completed Ok"));
    return true;
}

//Test Code Delete
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
