#include <Wire.h> //For I2C
#include <SPI.h> //For SD Card
#include <SD.h> //For SD Card
#include "Adafruit_Thermal.h" //For Thermal Receipt Printer
#include "SoftwareSerial.h" // For Thermal Receipt Printer

/**********************
	    VARIABLES
**********************/
	//State and Event Variables
	byte CurrentState = STATE_POWER_OFF;
	byte PreviousState = STATE_POWER_OFF;
	byte RequestedState = NULL_REQUESTED;
	byte CurrentSubstate = SUBSTATE_INITIAL_ENTRY;
	byte RequestedSubState = NULL_REQUESTED;	
	byte Event = EVENT_NO_EVENT;
	unsigned long StartTime = 0; //Needs to avoid millis rollover. 49 days is fine.

  //SD CARD VARIABLES
  const char PathToParametersFile[] = "param.txt";
  char FolderPath[] = "VER_002/00/0000.txt";
  bool firstTimeThrough = false;
  
  //TEST CODE
  SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
  Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
  
	//MISC VARIABLES
	bool InitializationComplete = false;
	byte Init_Allowance_Count = 0;
	byte CMC_Digit_One = NULL;
	byte CMC_Digit_Two = NULL;
	bool Start_Button_Pressed = false;
	byte Button_A_Read = 0;
	byte Button_B_Read = 0;
	byte Previous_Button_A_Read = 0;
	byte Previous_Button_B_Read = 0;
	int Print_Hold_Off_Counter = 0;
  
	const byte LED_MAPPING_ARRAY[11] {63,6,91,79,102,109,125,7,127,103,64};
		//0,1,2,3,4,5,6,7,8,9,-(Null).
		
