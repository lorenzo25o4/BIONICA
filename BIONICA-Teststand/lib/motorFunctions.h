

MagneticSensorI2C sensor0 = MagneticSensorI2C(AS5600_I2C);
MagneticSensorI2C sensor1 = MagneticSensorI2C(AS5600_I2C);


BLDCMotor motor0 = BLDCMotor(PolePairs, PhaseResistance, MotorKV * 1.6);
BLDCDriver3PWM driver0 = BLDCDriver3PWM(M0IN1, M0IN2, M0IN3, M0DriverEnable);

BLDCMotor motor1 = BLDCMotor(PolePairs, PhaseResistance, MotorKV * 1.6);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(M1IN1, M1IN2, M1IN3, M1DriverEnable);


// angle set point variable
float target_angleA = 0;
float target_angleB = 0;

void taskM0(void * parameter)
{
    for(;;)
    {
        motor0.loopFOC();
        motor0.move(target_angleA);
        motor0.monitor();
    }
}

void taskM1(void * parameter)
{
    for(;;)
    {
        motor1.loopFOC();
        motor1.move(target_angleB);
        
    }
}

void setupMotor0()
{
    //Start I2C_0 for AS5600
    Wire.begin(SDA0, SCL0, S0Freq);
    //Initialise AS5600 on I2C_0
    sensor0.init(&Wire);
    //Link AS5600 to Motor_0
    motor0.linkSensor(&sensor0);

    driver0.voltage_power_supply = D0VoltagePowerSupply;
    driver0.init();
    motor0.linkDriver(&driver0);

    motor0.foc_modulation = FOCModulationType::SinePWM;
    motor0.controller = MotionControlType::angle;

    motor0.PID_velocity.P = M0VelocityP;
    motor0.PID_velocity.I = M0VelocityI;
    motor0.PID_velocity.D = M0VelocityD;
    // motor0.voltage_limit = M0VoltageLimit;
    motor0.PID_current_q.P = M0CurrentP;
    motor0.PID_current_q.I = M0CurrentI;
    motor0.PID_current_q.D = M0CurrentD;

    motor0.current_limit = M0CurrentLimit;

    motor0.LPF_velocity.Tf = 0.01f;
    motor0.P_angle.P = M0AngleP;
    motor0.velocity_limit = M0AngleVelocityLimit;
    motor0.useMonitoring(Serial);
    motor0.monitor_start_char = 'M';
    motor0.monitor_end_char = 'M';
}

void setupMotor1()
{
    Wire1.begin(SDA1, SCL1, S1Freq);
    // initialise magnetic sensor hardware
    sensor1.init(&Wire1);
    // link the motor to the sensor
    motor1.linkSensor(&sensor1);
    // driver config
    // power supply voltage [V]
    driver1.voltage_power_supply = D1VoltagePowerSupply;
    driver1.init();
    // link the motor and the driver
    motor1.linkDriver(&driver1);
    // choose FOC modulation (optional)
    motor1.foc_modulation = FOCModulationType::SinePWM;
    // set motion control loop to be used
    motor1.controller = MotionControlType::angle;
    // contoller configuration
    // default parameters in defaults.h
    // velocity PI controller parameters
    motor1.PID_velocity.P = M1VelocityP;
    motor1.PID_velocity.I = M1VelocityI;
    motor1.PID_velocity.D = M1VelocityD;

    motor1.PID_current_q.P = M1CurrentP;
    motor1.PID_current_q.I = M1CurrentI;
    motor1.PID_current_q.D = M1CurrentD;
    // // maximal voltage to be set to the motor
    // motor1.voltage_limit = M1VoltageLimit;

    motor1.current_limit = M1CurrentLimit;
    // velocity low pass filtering time constant
    // the lower the less filtered
    motor1.LPF_velocity.Tf = 0.01f;
    // angle P controller
    motor1.P_angle.P = M1AngleP;
    // maximal velocity of the position control
    motor1.velocity_limit = M1AngleVelocityLimit;

    motor1.useMonitoring(Serial);
    motor1.monitor_start_char = 'N';
    motor1.monitor_end_char = 'N';
}


//to check if the provided angle is physicaly possible to reach 
void checkAngle()
{

}