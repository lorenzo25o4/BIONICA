//Pin-Config
#define PolePairs 7
#define MotorKV 140
#define PhaseResistance 22.0
#define GearRatio 21.77

//motor0
#define M0VoltageLimit 14
#define M0CurrentLimit 0.4
#define M0CurrentP 20
#define M0CurrentI 0
#define M0CurrentD 0
#define M0VelocityP 0.025
#define M0VelocityI 1.4
#define M0VelocityD 0
#define M0AngleP 8
#define M0AngleVelocityLimit 41

//driver0
#define M0DriverEnable 14
#define M0IN1 7
#define M0IN2 8
#define M0IN3 9
#define D0VoltagePowerSupply 12

//sensor0
#define SCL0 2
#define SDA0 3
#define S0Freq 400000L

//motor1
#define M1VoltageLimit 14
#define M1CurrentLimit 0.4
#define M1CurrentP 20
#define M1CurrentI 0
#define M1CurrentD 0
#define M1VelocityP 0.025
#define M1VelocityI 1.4
#define M1VelocityD 0
#define M1AngleP 8
#define M1AngleVelocityLimit 70

//driver1
#define M1DriverEnable 16
#define M1IN1 18
#define M1IN2 35
#define M1IN3 36
#define D1VoltagePowerSupply 12

//sensor0
#define SCL1 6
#define SDA1 12
#define S1Freq 400000L


//RGB-LED Status
#define RUNNING 0
#define RUNNING_COLOR 0x00000F00 //green
#define RUNNING_FREQ 3

#define ERROR 1
#define ERROR_COLOR 0x00FF0000  //red
#define ERROR_FREQ 10 //Hz

#define SETUP 2
#define SETUP_COLOR 0x00880088 //purple

#define INITIALISING 3
#define INITIALISING_COLOR 0x00FF4400 //amber

#define HOMEING 4
#define HOMEING_COLOR 0x00000088 //blue

#define CANCOMMUNICATION 5
#define CANCOMMUNICATION_COLOR 0x00008800 //green
#define CANCOMMUNICATION_FREQ 4 //Hz