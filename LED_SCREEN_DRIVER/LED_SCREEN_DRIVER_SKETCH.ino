//REG 1000 Address is 0 on I2c. Only 8 bit memory addressesing is used.

#include <Wire.h>

#define ZERO_AVAILABLE_WORDS 0u
#define NUM_OF_OUTPUTS_ELEMENTS 13u
#define MULTIPLEXING_DELAY_US 1000

#define REG_1000_ADDRESS 0u //FOR CONTROLLING LED 1
#define REG_1001_ADDRESS 1u //FOR CONTROLLING LED 2
#define REG_1002_ADDRESS 2u //FOR READING INPUTS

#define LED_1_A_OUTPUT_PIN 5  //D5 Output is connected to LED 1 A.
#define LED_1_B_OUTPUT_PIN 13 //D13 Output is connected to LED 1 B.
#define LED_1_C_OUTPUT_PIN 10 //D10 Output is connected to LED 1 C.
#define LED_1_D_OUTPUT_PIN 9 //D9 Output is connected to LED 1 D.
#define LED_1_E_OUTPUT_PIN 8 //D8 Output is connected to LED 1 E.
#define LED_1_F_OUTPUT_PIN 6 //D6 Output is connected to LED 1 F.
#define LED_1_G_OUTPUT_PIN 11 //D11 Output is connected to LED 1 G.

#define LED_2_A_OUTPUT_PIN 0 //D0 Output is connected to LED 2 A.
#define LED_2_B_OUTPUT_PIN A3 //A3 Output is connected to LED 2 B.
#define LED_2_C_OUTPUT_PIN A1 //A1 Output is connected to LED 2 C.
#define LED_2_D_OUTPUT_PIN A0 //A0 Output is connected to LED 2 D.
#define LED_2_E_OUTPUT_PIN 4 //D4 Output is connected to LED 2 E.
#define LED_2_F_OUTPUT_PIN 1 //D1 Output is connected to LED 2 F.
#define LED_2_G_OUTPUT_PIN A2 //A2 Output is connected to LED 2 G.

#define LED_1_A_ELEMENT_DESIGNATOR 0u
#define LED_1_B_ELEMENT_DESIGNATOR 1u
#define LED_1_C_ELEMENT_DESIGNATOR 2u
#define LED_1_D_ELEMENT_DESIGNATOR 3u
#define LED_1_E_ELEMENT_DESIGNATOR 4u
#define LED_1_F_ELEMENT_DESIGNATOR 5u
#define LED_1_G_ELEMENT_DESIGNATOR 6u

#define LED_2_A_ELEMENT_DESIGNATOR 7u
#define LED_2_B_ELEMENT_DESIGNATOR 8u
#define LED_2_C_ELEMENT_DESIGNATOR 9u
#define LED_2_D_ELEMENT_DESIGNATOR 10u
#define LED_2_E_ELEMENT_DESIGNATOR 11u
#define LED_2_F_ELEMENT_DESIGNATOR 12u
#define LED_2_G_ELEMENT_DESIGNATOR 13u


#define BUTTON_0_INPUT_PIN 2 //D2 Input is spare for button connection.
#define BUTTON_1_INPUT_PIN 3 //D3 Input is spare for button connection.
#define BUTTON_2_INPUT_PIN 7 //D7 Input is spare for button connection.

int outputArray[14] = {LED_1_A_OUTPUT_PIN,
                       LED_1_B_OUTPUT_PIN,
                       LED_1_C_OUTPUT_PIN,
                       LED_1_D_OUTPUT_PIN,
                       LED_1_E_OUTPUT_PIN,
                       LED_1_F_OUTPUT_PIN,
                       LED_1_G_OUTPUT_PIN,
                       LED_2_A_OUTPUT_PIN,
                       LED_2_B_OUTPUT_PIN,
                       LED_2_C_OUTPUT_PIN,
                       LED_2_D_OUTPUT_PIN,
                       LED_2_E_OUTPUT_PIN,
                       LED_2_F_OUTPUT_PIN,
                       LED_2_G_OUTPUT_PIN,};

int multiplex_ID = 0;
byte Data_Read_Address = 0;

typedef struct Reg_1000_Struct
{
  int Led_1_A_Reg : 1;
  int Led_1_B_Reg : 1;
  int Led_1_C_Reg : 1;
  int Led_1_D_Reg : 1;
  int Led_1_E_Reg : 1;
  int Led_1_F_Reg : 1;
  int Led_1_G_Reg : 1;
  int Spare : 1;
};

typedef union Reg_1000_Union
{
  Reg_1000_Struct Bits;
  byte nByte;
}; Reg_1000_Union Reg_1000;

typedef struct Reg_1001_Struct
{
  int Led_2_A_Reg : 1;
  int Led_2_B_Reg : 1;
  int Led_2_C_Reg : 1;
  int Led_2_D_Reg : 1;
  int Led_2_E_Reg : 1;
  int Led_2_F_Reg : 1;
  int Led_2_G_Reg : 1;
  int Spare : 1;
};

typedef union Reg_1001_Union
{
  Reg_1001_Struct Bits;
  byte nByte;
}; Reg_1001_Union Reg_1001;

typedef struct Reg_1002_Struct
{
  int Button_0_Reg : 1;
  int Button_1_Reg : 1;
  int Button_2_Reg : 1;
  int Spare : 5;
};

typedef union Reg_1002_Union
{
  Reg_1002_Struct Bits;
  byte nByte;
}; Reg_1002_Union Reg_1002;

typedef struct Null_Reg_Struct
{
  int Spare: 8;
};

typedef union Null_Reg_Union
{
  Null_Reg_Struct Bits;
  byte nByte;
}; Null_Reg_Union Null_Reg;

void setup() 
{
  setPinModes();
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  initialize_Registers();
}

void loop() {
  setOutputs();
  delayMicroseconds(MULTIPLEXING_DELAY_US);
}

void setOutputs()
{
  if (multiplex_ID < NUM_OF_OUTPUTS_ELEMENTS)
    multiplex_ID++;
  else
    multiplex_ID = 0;

  for(int outputNumber = 0; outputNumber < NUM_OF_OUTPUTS_ELEMENTS; outputNumber++)
  {
    digitalWrite(outputArray[outputNumber], HIGH); //High Clears it since its a common annode display.
  }

  switch(multiplex_ID)
  {
    case LED_1_A_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1000.Bits.Led_1_A_Reg);
    break;
    case LED_1_B_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1000.Bits.Led_1_B_Reg);
    break;
    case LED_1_C_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1000.Bits.Led_1_C_Reg);
    break;
    case LED_1_D_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1000.Bits.Led_1_D_Reg);
    break;
    case LED_1_E_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1000.Bits.Led_1_E_Reg);
    break;
    case LED_1_F_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1000.Bits.Led_1_F_Reg);
    break;
    case LED_1_G_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1000.Bits.Led_1_G_Reg);
    break;
    case LED_2_A_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1001.Bits.Led_2_A_Reg);
    break;
    case LED_2_B_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1001.Bits.Led_2_B_Reg);
    break;
    case LED_2_C_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1001.Bits.Led_2_C_Reg);
    break;
    case LED_2_D_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1001.Bits.Led_2_D_Reg);
    break;
    case LED_2_E_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1001.Bits.Led_2_E_Reg);   
    break;
    case LED_2_F_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1001.Bits.Led_2_F_Reg);     
    break;
    case LED_2_G_ELEMENT_DESIGNATOR:
      digitalWrite(outputArray[multiplex_ID], !Reg_1001.Bits.Led_2_G_Reg);
    break;
    default:
    //Do Nothing
    break;
  }
}

void initialize_Registers()
{
  Reg_1000.nByte = 0; //Bits 7,6,5,4,3,2,1 should be initialized to their OFF State.
  Reg_1001.nByte = 0; //Bits 7,6,5,4,3,2,1 should be initialized to their OFF State.
  Reg_1002.nByte = 0; //Bits 2, 1, and 0 should be initialized to their OFF State.
  Null_Reg.nByte = 0;
}

void setPinModes()
{
  pinMode(LED_1_A_OUTPUT_PIN, OUTPUT);
  pinMode(LED_1_B_OUTPUT_PIN, OUTPUT);
  pinMode(LED_1_C_OUTPUT_PIN, OUTPUT);
  pinMode(LED_1_D_OUTPUT_PIN, OUTPUT);
  pinMode(LED_1_E_OUTPUT_PIN, OUTPUT);
  pinMode(LED_1_F_OUTPUT_PIN, OUTPUT);
  pinMode(LED_1_G_OUTPUT_PIN, OUTPUT);

  pinMode(LED_2_A_OUTPUT_PIN, OUTPUT);
  pinMode(LED_2_B_OUTPUT_PIN, OUTPUT);
  pinMode(LED_2_C_OUTPUT_PIN, OUTPUT);
  pinMode(LED_2_D_OUTPUT_PIN, OUTPUT);
  pinMode(LED_2_E_OUTPUT_PIN, OUTPUT);
  pinMode(LED_2_F_OUTPUT_PIN, OUTPUT);
  pinMode(LED_2_G_OUTPUT_PIN, OUTPUT);

  pinMode(BUTTON_0_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_1_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_INPUT_PIN, INPUT_PULLUP);
}

void receiveEvent(int numBytes)
{
  byte First_Byte_Read = Wire.read();
        Data_Read_Address = First_Byte_Read;
  while(Wire.available() > ZERO_AVAILABLE_WORDS) //Ensures all bytes are read.
  {
    switch(First_Byte_Read) 
    {
      case REG_1000_ADDRESS:
        Reg_1000.nByte = Wire.read();
        break;
      case REG_1001_ADDRESS:
        Reg_1001.nByte = Wire.read();
        break;
      default:
        Wire.read();
        break;
    }
  }
}

void requestEvent()
{
  switch(Data_Read_Address)
  {
    case REG_1002_ADDRESS:
      Reg_1002.Bits.Button_0_Reg = !digitalRead(BUTTON_0_INPUT_PIN); //Opposite because ground is PRESSED.
      Reg_1002.Bits.Button_1_Reg = !digitalRead(BUTTON_1_INPUT_PIN); //Opposite because ground is PRESSED.
      Reg_1002.Bits.Button_2_Reg = !digitalRead(BUTTON_2_INPUT_PIN); //Opposite because ground is PRESSED.
      Wire.write(Reg_1002.nByte);
    break;
    default:
      Wire.write(Null_Reg.nByte);
  }
}
