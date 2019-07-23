void Event_Logic() {

    //Events are one shot
    Event = EVENT_NO_EVENT;

    Button_Pressed_Check();
    Failed_TimeOut_Check();
}

void Button_Pressed_Check() {
    if(((Button_A_Read != Previous_Button_A_Read)&&(Button_A_Read != NOTHING_PRESSED) ) || ((Button_B_Read != Previous_Button_B_Read)&&(Button_B_Read != NOTHING_PRESSED) ))
        Event = BUTTON_PRESSED;
}

void Failed_TimeOut_Check() {
    switch(CurrentState) {
        case STATE_INITIALIZATION :
            Init_Allowance_Count++;
            if (InitializationComplete == true) {
                Event = EVENT_INIT_PASSED;
            }
            else if (Init_Allowance_Count == INIT_MAX_ALLOWANCE) {
                Init_Allowance_Count = 0;
                Event = EVENT_INIT_FAILED;
            }
        break;
        default:
            //Do Nothing
        break;
    }
}
