

void Input_Processing() {
    Previous_Button_A_Read = Button_A_Read;
    Previous_Button_B_Read = Button_B_Read;
    Button_A_Read = Unpack_Buttons(REG_BUTTONS_A_ADDRESS); //Buttons have a priority scheme, highest first in case two are pressed at once.
    Button_B_Read = Unpack_Buttons(REG_BUTTONS_B_ADDRESS); //Buttons have a priority scheme, highest first in case two are pressed at once.

    if ((Button_B_Read)&(1<<START_BUTTON_LOCATION)) {
        Start_Button_Pressed = true;
    }
    else
    {
        Start_Button_Pressed = false;
    }
}

byte Unpack_Buttons(byte Data_Address) {
    byte data = I2C_Read_Byte(I2C_BUTTON_MACHINE_ADDRESS, Data_Address);
    if(data != INVALID_REGISTER_READ_VALUE) {
        return data;
    }
    else {
        return INVALID_REGISTER_SAFE_VALUE;
    }
}

void Output_Processing() {
    Pack_LED(REG_LED_A_ADDRESS, CMC_Digit_One);
    Pack_LED(REG_LED_B_ADDRESS, CMC_Digit_Two);
}

void Pack_LED(byte Data_Address, int CMC_Digit) {
    int Printing_Counter = (millis() / PRINTING_PATTERN_TIME)% NUMBER_OF_PERIMETER_LEDs;
    byte Printing_Active_LED = 1 << Printing_Counter;

    int Failed_Counter = (millis() / FAILED_PATTERN_TIME) % NUMBER_OF_FAILED_PATTERNS;
    byte Failed_Active_LEDs = NO_LEDS_ON;

    if(Failed_Counter)
    {
        Failed_Active_LEDs = FAILED_LED_PATTERN;
    }
    else
    {
        //Do Nothing
    }

    switch(CurrentState) {
		
    case STATE_WAIT:
        I2C_Write_Byte (I2C_LED_MACHINE_ADDRESS, Data_Address, LED_MAPPING_ARRAY[CMC_Digit]);
    break;
    case STATE_PRINTING:
        I2C_Write_Byte (I2C_LED_MACHINE_ADDRESS, Data_Address, Printing_Active_LED);
    break;
    case STATE_PRINTING_FAILED:
        I2C_Write_Byte (I2C_LED_MACHINE_ADDRESS, Data_Address, Failed_Active_LEDs);
    break;
    case STATE_ERROR:
        I2C_Write_Byte (I2C_LED_MACHINE_ADDRESS, Data_Address, Failed_Active_LEDs);
    break;
    default:
        //Do Nothing...
    break;
    }
}

byte I2C_Read_Byte (byte Device_Address, byte Data_Address) {
    //First Write the Data Register Address
    Wire.beginTransmission(Device_Address);
    Wire.write(Data_Address);
    Wire.endTransmission();
    delay(1);
    //Next Read A Byte
    Wire.requestFrom(Device_Address, ONE_BYTE);
    if (Wire.available() > 0)
    {
    return Wire.read();
    }
    else
    {
    return INVALID_REGISTER_READ_VALUE;
    }
}

void I2C_Write_Byte (byte Device_Address, byte Read_Address, byte data) {
    //Begin a transmission with device
    Wire.beginTransmission(Device_Address);
    //First Write the Data Register Address
    Wire.write(Read_Address);
    //Next Write the Data Byte
    Wire.write(data);
    //End the transmission
    Wire.endTransmission();
}
