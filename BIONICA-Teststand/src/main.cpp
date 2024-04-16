/**
 * ESP32 position motion control example with magnetic sensor
 */
#include <Arduino.h>
#include <SimpleFOC.h>
#include <Adafruit_NeoPixel.h>
#include <../lib/config.h>
#include <../lib/statusled.h>
#include <../lib/motorFunctions.h>





float x = 0.0;
float y = 0.0;

// instantiate the commander
Commander command = Commander(Serial);
void doTargetA(char* cmd) { command.scalar(&target_angleA, cmd); }
void doTargetB(char* cmd) { command.scalar(&target_angleB, cmd); }
void onMotor0(char* cmd){ command.motor(&motor0,cmd); }
void onMotor1(char* cmd){ command.motor(&motor1,cmd); }





void setup() {

    xTaskCreate(
        StatusLED,
        "StatusLED",
        100000,
        NULL,
        1,
        NULL);

    current_state = SETUP;

    setupMotor0();
    setupMotor1();   
    
    
    

    
    // use monitoring with serial
    Serial.begin(115200);
    // comment out if not needed
    motor0.useMonitoring(Serial);
    motor1.useMonitoring(Serial);

    current_state = INITIALISING;
    // initialize motor
    motor0.init();
    motor1.init();
    // align sensor and start FOC
    motor0.initFOC();
    motor1.initFOC();


    // add target command T
    command.add('A', doTargetA, "target angle Motor A");
    command.add('B', doTargetB, "target angle Motor B");
    command.add('M',onMotor0,"my motor0 motion");
    command.add('N',onMotor1,"my motor1 motion");
    command.verbose = VerboseMode::machine_readable;

    //command.add('H', newZeroPos, "set new Zero-Position");

    Serial.println(F("Motor ready."));

    current_state = HOMEING;

    Serial.println(F("Please home all motors manually"));


    motor0.disable();
    motor1.disable();
    status.clear();
    delay(10000);
    motor0.sensor_offset = motor0.shaft_angle;
    motor1.sensor_offset = motor1.shaft_angle;
    motor0.enable();
    motor1.enable();
    current_state = RUNNING;

    xTaskCreate(
        taskM0,
        "Motor Zero Loop",
        100000,
        NULL,
        1,
        NULL);

    xTaskCreate(
        taskM1,
        "Motor One Loop",
        100000,
        NULL,
        1,
        NULL);
}



void moveToPos(double x, double y, double z){
    double b = atan2(y, x) * (180 / PI);
    double l = sqrt(x * x + y * y);
    double h = sqrt(l * l + z * z);
    double phi = atan(z / l) * (180 / PI);
    double theta = acos((h / 2) / 100) * (180 / PI);

    target_angleA = 180 * PI / 180 * 21.77; //((phi + theta) * PI / 180)*21.77;
    target_angleB = ((phi - theta) * PI / 180)*21.77;
    //Serial.printf("Shoulder Target: %f Knee Target: %f\n",  target_angleA, target_angleB);
}

void loop() {

    // main FOC algorithm function
    // the faster you run this function the better
    // Arduino UNO loop  ~1kHz
    // Bluepill loop ~10kHz
        
    command.run();
    // Serial.println("STEP1");
    // for (int i = 0; i < 200; i++)
    // {
    //     moveToPos(20.0 + 0.04*i, 20.0, 30.0);
    //     delay(1);
    // }
    // delay(200);
    // Serial.println("STEP2");
    // for (int i = 0; i < 200; i++)
    // {
    //     moveToPos(100.0, 20.0 + 0.04*i, 30.0);
    //     delay(1);
    // }
    // delay(200);
    // Serial.println("STEP3");
    // for (int i = 0; i < 200; i++)
    // {
    //     moveToPos(100.0, 100.0 - 0.04*i, 30.0);
    //     delay(1);
    // }
    // delay(200);
    // Serial.println("STEP4");
    // for (int i = 0; i < 200; i++)
    // {
    //     moveToPos(100.0 - 0.04*i, 20.0, 30.0);
    //     delay(1);
    // }
    // delay(200);

    //moveToPos(10.0, 10.0, 10.0);
    target_angleA = 0 * PI / 180 * 21.77;
    target_angleB = -40 * PI / 180 * 21.77;
    Serial.printf("Shoulder Angle: %f, Knee Angle: %F \n\n", motor0.shaft_angle, motor1.shaft_angle);
    delay(2000);
    target_angleA = 150 * PI / 180 * 21.77;
    target_angleB = -135 * PI / 180 * 21.77;
    Serial.printf("Shoulder Angle: %f, Knee Angle: %F \n\n", motor0.shaft_angle, motor1.shaft_angle);
    delay(2000);
}