#include "PS2X_lib.h"  //for v1.6
#include "Servo.h"


/******************************************************************
   set pins connected to PS2 controller:
     - 1e column: original
     - 2e colmun: Stef?
   replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        8  //14    
#define PS2_CMD        2  //15
#define PS2_SEL        10  //16
#define PS2_CLK        11  //17

/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
#define pressures   false
#define rumble      true
//#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

/*-------------------------Servo----------------------------*/

#define baseServoPin 9
#define elbowServoPin 5
#define shoulderServoPin 6
#define gripperServoPin 3
#define DRE_STEP 3
//Find max value for servo
Servo baseServo;  //0-180 baseServo
Servo elbowServo;  // 20-180 elbowServo
Servo shoulderServo;  //50-145  shoulderServo
Servo gripperServo;  //90-150 gripperServo

const int SERVO_DELAY = 10;
const int MAX_SIZE_ARR = 20;
const int num_servo = 4;
byte scripts[MAX_SIZE_ARR][num_servo] = {{90,90,90,90}};
int arr_size = 1;
