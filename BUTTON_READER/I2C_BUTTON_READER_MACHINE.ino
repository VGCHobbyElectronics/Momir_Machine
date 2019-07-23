#include <Wire.h>

#define ZERO_AVAILABLE_WORDS 0u
byte Data_Read_Address = 0;

#define REG_BUTTONS_A_ADDRESS 0x00u
#define REG_BUTTONS_B_ADDRESS 0x01u
#define REG_DEVICE_READY_ADDRESS 0x10u
#define REG_DEBOUNCE_TIME_ADDRESS 0x11u

#define DEVICE_READY_DEFAULT_VALUE 0xAAu
#define DEBOUNCE_TIME_DEFAULT_VALUE 50u

#define BUTTON_0_INPUT_PIN 1
#define BUTTON_1_INPUT_PIN 2
#define BUTTON_2_INPUT_PIN 5
#define BUTTON_3_INPUT_PIN 7
#define BUTTON_4_INPUT_PIN 8
#define BUTTON_5_INPUT_PIN A3
#define BUTTON_6_INPUT_PIN A2
#define BUTTON_7_INPUT_PIN 13

#define BUTTON_8_INPUT_PIN 10
#define BUTTON_9_INPUT_PIN 9
#define BUTTON_10_INPUT_PIN 0
#define BUTTON_11_INPUT_PIN 3 //Spare
#define BUTTON_12_INPUT_PIN 4 //Spare
#define BUTTON_13_INPUT_PIN 6 //Spare
#define BUTTON_14_INPUT_PIN 11 //Spare
#define BUTTON_15_INPUT_PIN 12 //Spare

int InputArrayDataPins[16] = {BUTTON_0_INPUT_PIN,
                      BUTTON_1_INPUT_PIN,
                      BUTTON_2_INPUT_PIN,
                      BUTTON_3_INPUT_PIN,
                      BUTTON_4_INPUT_PIN,
                      BUTTON_5_INPUT_PIN,
                      BUTTON_6_INPUT_PIN,
                      BUTTON_7_INPUT_PIN,
                      BUTTON_8_INPUT_PIN,
                      BUTTON_9_INPUT_PIN,
                      BUTTON_10_INPUT_PIN,
                      BUTTON_11_INPUT_PIN,
                      BUTTON_12_INPUT_PIN,
                      BUTTON_13_INPUT_PIN,
                      BUTTON_14_INPUT_PIN,
                      BUTTON_15_INPUT_PIN,};

uint32_t InputArrayMSCounters[16] = {0};
uint32_t previousMS;
uint32_t deltaMS;
bool InputArrayDebounced[16] = {0};

typedef struct Reg_Buttons_A_Struct
{
  int Button_00_Bit : 1;
  int Button_01_Bit : 1;
  int Button_02_Bit : 1;
  int Button_03_Bit : 1;
  int Button_04_Bit : 1;
  int Button_05_Bit : 1;
  int Button_06_Bit : 1;
  int Button_07_Bit : 1;
};

typedef union Reg_Buttons_A_Union
{
  Reg_Buttons_A_Struct Bits;
  byte nByte;
}; Reg_Buttons_A_Union Reg_Buttons_A;

typedef struct Reg_Buttons_B_Struct
{
  int Button_08_Bit : 1;
  int Button_09_Bit : 1;
  int Button_10_Bit : 1;
  int Button_11_Bit : 1; //Spare
  int Button_12_Bit : 1; //Spare
  int Button_13_Bit : 1; //Spare
  int Button_14_Bit : 1; //Spare
  int Button_15_Bit : 1; //Spare
};

typedef union Reg_Buttons_B_Union
{
  Reg_Buttons_B_Struct Bits;
  byte nByte;
}; Reg_Buttons_B_Union Reg_Buttons_B;

typedef struct Reg_Device_Ready_Struct
{
  int Device_Ready : 8;
};

typedef union Reg_Device_Ready_Union
{
  Reg_Device_Ready_Struct Bits;
  byte nByte;
}; Reg_Device_Ready_Union Reg_Device_Ready;

typedef struct Reg_Debounce_Time_Struct
{
  int Debounce_Time : 8;
};

typedef union Reg_Debounce_Time_Union
{
  Reg_Debounce_Time_Struct Bits;
  byte nByte;
}; Reg_Debounce_Time_Union Reg_Debounce_Time;

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
  Wire.begin(9);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  initialize_Registers();
  previousMS = millis();
}

void loop() 
{
  setInputs();
}

void setInputs()
{
  deltaMS = millis() - previousMS;
  previousMS = millis();
  
  for(int currentInput = 0; currentInput < sizeof(InputArrayDebounced); currentInput++)
  {
    if(!digitalRead(InputArrayDataPins[currentInput]))
    {
      if((InputArrayMSCounters[currentInput]+deltaMS)<= UINT32_MAX)
      {
        InputArrayMSCounters[currentInput] = InputArrayMSCounters[currentInput]+deltaMS;
      }
      else
      {
        InputArrayMSCounters[currentInput] = UINT32_MAX;
      }
    }
    else
    {
    InputArrayMSCounters[currentInput] = 0;
    }

    if(InputArrayMSCounters[currentInput]>=Reg_Debounce_Time.Bits.Debounce_Time)
    {
    InputArrayDebounced[currentInput] = true;    
    }

    else
    {
    InputArrayDebounced[currentInput] = false;
    }
  }
  
}

void initialize_Registers()
{
  Reg_Buttons_A.nByte = 0;
  Reg_Buttons_B.nByte = 0; 
  Reg_Device_Ready.Bits.Device_Ready = DEVICE_READY_DEFAULT_VALUE;
  Reg_Debounce_Time.Bits.Debounce_Time = DEBOUNCE_TIME_DEFAULT_VALUE;
  Null_Reg.nByte = 0;
}

void setPinModes()
{
  pinMode(BUTTON_0_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_1_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_4_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_5_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_6_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_7_INPUT_PIN, INPUT_PULLUP);

  pinMode(BUTTON_8_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_9_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_10_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_11_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_12_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_13_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_14_INPUT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_15_INPUT_PIN, INPUT_PULLUP);
}

void receiveEvent(int numBytes)
{
  byte First_Byte_Read = Wire.read();
  Data_Read_Address = First_Byte_Read;
  
  while(Wire.available() > ZERO_AVAILABLE_WORDS) //Ensures all bytes are read.
  {
    switch(First_Byte_Read) 
    {
      case REG_DEBOUNCE_TIME_ADDRESS:
        Reg_Debounce_Time.nByte = Wire.read();
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
    case REG_BUTTONS_A_ADDRESS:
       Reg_Buttons_A.Bits.Button_00_Bit = InputArrayDebounced[0];
       Reg_Buttons_A.Bits.Button_01_Bit = InputArrayDebounced[1];
       Reg_Buttons_A.Bits.Button_02_Bit = InputArrayDebounced[2];
       Reg_Buttons_A.Bits.Button_03_Bit = InputArrayDebounced[3];
       Reg_Buttons_A.Bits.Button_04_Bit = InputArrayDebounced[4];
       Reg_Buttons_A.Bits.Button_05_Bit = InputArrayDebounced[5];
       Reg_Buttons_A.Bits.Button_06_Bit = InputArrayDebounced[6];
       Reg_Buttons_A.Bits.Button_07_Bit = InputArrayDebounced[7];
       Wire.write(Reg_Buttons_A.nByte);
    break;
    case REG_BUTTONS_B_ADDRESS:
       Reg_Buttons_B.Bits.Button_08_Bit = InputArrayDebounced[8];
       Reg_Buttons_B.Bits.Button_09_Bit = InputArrayDebounced[9];
       Reg_Buttons_B.Bits.Button_10_Bit = InputArrayDebounced[10];
       Reg_Buttons_B.Bits.Button_11_Bit = InputArrayDebounced[11];
       Reg_Buttons_B.Bits.Button_12_Bit = InputArrayDebounced[12];
       Reg_Buttons_B.Bits.Button_13_Bit = InputArrayDebounced[13];
       Reg_Buttons_B.Bits.Button_14_Bit = InputArrayDebounced[14];
       Reg_Buttons_B.Bits.Button_15_Bit = InputArrayDebounced[15];
       Wire.write(Reg_Buttons_B.nByte);
    break;
    case REG_DEVICE_READY_ADDRESS:
       Wire.write(Reg_Device_Ready.nByte);
    break;
    case REG_DEBOUNCE_TIME_ADDRESS:
       Wire.write(Reg_Debounce_Time.nByte);
    break;
    default:
      Wire.write(Null_Reg.nByte);
    break;
  }
}
