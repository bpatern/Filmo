#define confirm '%'

#define lampon 'A'
#define lampoff 'B'

#define ignore_controlswitch '#'
#define mcopy 'm'

#define forward_continuous 'F'
#define reverse_continuous 'R'
#define stop 'X'

#define forward_single 'f'
#define reverse_single 'r'
#define forward_single_opticalprinter 'g'
#define reverse_single_opticalprinter 'h'

inline bool commandLibrary(char device, char recvd, uint16_t argument = -1)
{
    // std::string rec = recvd;

    if (device == 'e') // engine or motor, doesnt handle command parsing logic, receives commands internally
    {
        if (recvd == lampon)
        {
            ESP_LOGI("serial", "LAMP ON");
            constantLED = 1;
            ledSwitch = 1;
            uart_write_bytes(UART_NUM_2, sendConfirmationResponse(lampon), 64);
        }
        else if (recvd == lampoff)
        {
            ESP_LOGI("serial", "LAMP OFF");
            constantLED = 0;
                        ledSwitch = 0;


            send_LEDC('x');
            uart_write_bytes(UART_NUM_2, sendConfirmationResponse(lampoff), 64);

        } else if (recvd == forward_single)
        {
            xQueueSend(q_singleFrame, &recvd, 2);
            if (argument!=-1)
            {

            }
            ESP_LOGI("serial", "singleFrameFWD");


        } else if (recvd == reverse_single)
        {

            xQueueSend(q_singleFrame, &recvd, 2);
            if (argument!=-1)
            {
                
            }
            ESP_LOGI("serial", "singleFrameREV");
        } else if (recvd == forward_continuous)
        {
            xQueueSend(runMsg, &recvd, 2);
            if (argument!=-1)
            {

            }

        } else if (recvd == reverse_continuous)
        {
            xQueueSend(runMsg, &recvd, 2);
            if (argument!=-1)
            {
                
            }

        } else if (recvd == stop)
        {
            xQueueSend(runMsg, &recvd, 2);
            if (argument!=-1)
            {
                
            }
        } else if (recvd == ignore_controlswitch)
        {
            ignoreControlSwitch++;
            if (ignoreControlSwitch == 1)
            {
                ESP_LOGI("system", "EIKI CONTROL SWITCH DISABLED!!! CAREFUL!!!!!");
            } else if(ignoreControlSwitch > 1)
            {
                ignoreControlSwitch = 0;
                ESP_LOGI("system", "EIKI CONTROL SWITCH ENABLED");
            }
        } else if (recvd == mcopy)
        {
            ignoreControlSwitch = 1;
            uart_write_bytes(UART_NUM_2, sendConfirmationResponse(mcopy), 64);

        } 
        else if (recvd == forward_single_opticalprinter)
        {
                     xQueueSend(q_singleFrame, &recvd, 2);
   
        }
        else if (recvd == reverse_single_opticalprinter)
        {
                     xQueueSend(q_singleFrame, &recvd, 2);
        }
        else 
        {
            return false;
        }
    }
    // } else if (recvd == 'g')
    // {
    //             ESP_LOGI("serial", "Single Frame FWD");

    // } else if (recvd == 'h')
    // {
    //     ESP_LOGI("serial", "Single Frame REV");
    // } else if (recvd == 'F')
    // {
    //     ESP_LOGI("serial", "Motor FWD");

    // } else if (recvd == 'R')
    // {
    //     ESP_LOGI("serial", "Motor REV");
    // }

    return true;
}

inline const char * sendConfirmationResponse(char message) {
     static char append[1];
     append[0] = confirm;
     append[1] = message;
    static const char *msg = append;
    return msg;
}

// inline void commandString(char received) {
//     if (received[0] == '<')
//     {
//         char* strtokIndx;
//         strtokIndx = strtok(&received, ",");
//         uint8_t commandTemp = (uint8_t)*strtokIndx;
//         strtokIndx = strtok(NULL, ">");
//         uint16_t valueTemp = (uint16_t)*strtokIndx;

//                 ESP_LOGI("serial", "term 1 %u", commandTemp);
//                 ESP_LOGI("serial", "term 2 %u", valueTemp);

//         // commandLibrary((uint8_t)commandTemp, valueTemp);

//     }
// }