///////////////////////////////////
//////////DEFINITIONS//////////////
///////////////////////////////////

//I2C ADDRESS AND REGISTER DEFINITIONS
    #define I2C_LED_MACHINE_ADDRESS       8u
    #define REG_LED_A_ADDRESS             0x00  //This were mismapped on slave device. Easier to Fix here.
    #define REG_LED_B_ADDRESS             0x01 //This were mismapped on slave device. Easier to Fix here.
	
    #define I2C_BUTTON_MACHINE_ADDRESS    9u
        #define REG_BUTTONS_A_ADDRESS     0x00 
        #define REG_BUTTONS_B_ADDRESS     0x01
        #define REG_DEVICE_READY_ADDRESS  0x10
        #define REG_DEBOUNCE_TIME         0x11
		
    #define INVALID_REGISTER_READ_VALUE   0xFF //Not all buttons are likely pressed at once.
    #define INVALID_REGISTER_SAFE_VALUE   0x00 //Return nothing pressed if I2C has failed.

//STATE DEFINITIONS
    #define NULL_REQUESTED                -1
    #define STATE_POWER_OFF               0u
    #define STATE_INITIALIZATION          1u
    #define STATE_WAIT                    2u
    #define STATE_PRINTING                3u
    #define STATE_PRINTING_FAILED         4u
    #define STATE_ERROR                   5u
    #define STATE_OPERATIONAL_FOR_INPUT   2u
    #define STATE_OPERATIONAL_FOR_OUTPUT  1u

//SUBSTATE DEFINITIONS
    #define SUBSTATE_INITIAL_ENTRY        0u
    #define SUBSTATE_VALID_PRINT_CHECK    1u
    #define SUBSTATE_RANDOM_NUMBER        2u
    #define SUBSTATE_LOAD_BITMAP          3u
    #define SUBSTATE_DATA_TRANS_TO_PRINT  4u
    #define SUBSTATE_WAIT_FOR_EXIT        5u

//EVENT DEFINITIONS
    #define EVENT_NO_EVENT                0u
    #define EVENT_INIT_PASSED             1u
    #define EVENT_INIT_FAILED             2u
    #define BUTTON_PRESSED                3u
	
//BUTTON DEFINITIONS
    #define NUM_OF_CMC_BUTTONS_IN_REG_A   8u
    #define NUM_OF_CMC_BUTTONS_IN_REG_B   2u
    #define START_BUTTON_LOCATION         2u
    #define NOTHING_PRESSED               0u
    #define NO_LEDS_ON                    0u
    #define FAILED_PATTERN_TIME           250u
    #define NUMBER_OF_FAILED_PATTERNS     2u
    #define FAILED_LED_PATTERN            113u	
	
//TRANSITION DEFINITIONS
    #define POWER_UP_HOLD_OFF_TIME        1000u
    #define PRINT_FINISHED_HOLD_OFF_TIME  5000u
    #define PRINT_FAILED_HOLD_OFF_TIME    2500u
    #define INIT_MAX_ALLOWANCE            3u

//LED DEFINITIONS
    #define NUMBER_OF_PERIMETER_LEDs      6u
    #define PRINTING_PATTERN_TIME         250u

//MISC DEFINITIONS
    #define ONE_BYTE                      1u

//CMC DEFINITIONS
    #define NULL                          10u
    #define INVALID_CMC                   -1

//SD CARD DEFINITIONS
    #define PARAM_BYTES_FOR_DIR_PATH      7u
    #define LOCATION_OF_CMC_TWO_BIT       8u
    #define LOCATION_OF_CMC_ONE_BIT       9u
    #define START_LOCATION_OF_FILE_PATH   11u
    #define FILE_EXTENSION                ".txt"
    #define ASCII_NUMERAL_OFFSET          48u
    #define BYTES_FOR_CMC_FOLDER_PATH     10u  
    #define NUM_OF_DECIMALS_IN_FILE_NAME  4u

//PIN DEFINITIONS
    #define RX_PIN                        5u //Green Wure
    #define TX_PIN                        6u //Yellow Wire
