Adafruit_NeoPixel status(1, 47, NEO_RGB + NEO_KHZ800);
int8_t current_state = SETUP;

void StatusLED(void * parameter)
{
    status.begin();
    bool toggle = false;
    uint16_t freq = 1;
    for(;;)
    {
        switch (current_state)
        {
        case RUNNING:
                status.clear();
                (toggle) ? status.setPixelColor(0, RUNNING_COLOR) : status.clear();
                toggle = !toggle;
                freq = RUNNING_FREQ;
            break;
        case SETUP:
                status.clear();
                status.setPixelColor(0, SETUP_COLOR);
                freq = 1;
                break;
        case ERROR:
                status.clear();
                (toggle) ? status.setPixelColor(0, ERROR_COLOR) : status.clear();
                toggle = !toggle;
                freq = ERROR_FREQ;
            break;
        case INITIALISING:
                status.clear();
                status.setPixelColor(0, INITIALISING_COLOR);
                freq = 1;
            break;
        case HOMEING:
                status.clear();
                status.setPixelColor(0, HOMEING_COLOR);
                freq = 1;
            break;
        case CANCOMMUNICATION:
                status.clear();
                (toggle) ? status.setPixelColor(0, CANCOMMUNICATION_COLOR) : status.clear();
                toggle = !toggle;
                freq = CANCOMMUNICATION_FREQ;
            break;
                                                                                                            
        default:
            break;
        }
        status.show();
        vTaskDelay(1000/freq);
    }
}