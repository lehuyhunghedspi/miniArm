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

void setup() {

  Serial.begin(57600);

  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
  
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }


  /*----------Servo--------*/
  baseServo.attach(baseServoPin);//0-180
  elbowServo.attach(elbowServoPin);//0-80-150
  shoulderServo.attach(shoulderServoPin);//0-100
  gripperServo.attach(gripperServoPin);//0-100
  
}

