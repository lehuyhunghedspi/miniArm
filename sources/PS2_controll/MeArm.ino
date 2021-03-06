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

void loop() {
  /* You must Read Gamepad to get new values and set vibration values
     ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
     if you don't enable the rumble, use ps2x.read_gamepad(); with no values
     You should call this at least once a second
  */
  if (error == 1) //skip loop if no controller found
    return;

  if (type == 2) { //Guitar Hero Controller
    ps2x.read_gamepad();          //read controller

    if (ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if (ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if (ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if (ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if (ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed");

    if (ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");

    if (ps2x.Button(UP_STRUM))         //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if (ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");

    if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");

    if (ps2x.Button(ORANGE_FRET)) {    // print stick value IF TRUE
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
    }
  }




  
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

    if( ps2x.ButtonDataByte()!= 65535 ){
  
      if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
        Serial.println("Start is being held");
      if (ps2x.Button(PSB_SELECT))
        Serial.println("Select is being held");
  
      if (ps2x.Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
        Serial.print("Up held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
        upOneStep();
      }
      
      if (ps2x.Button(PSB_PAD_RIGHT)) {
        Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
        turnRightOneStep(); 
      }
      
      if (ps2x.Button(PSB_PAD_LEFT)) {
        Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
        turnLeftOneStep();
      }
  
      if (ps2x.Button(PSB_PAD_DOWN)) {
        Serial.print("DOWN held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
         downOneStep();
      }
    }
    
    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState() && ps2x.ButtonDataByte()!= 65535 ) { //will be TRUE if any button changes state (on to off, or off to on)
      
      if (ps2x.Button(PSB_L3) )
        Serial.println("L3 pressed");
      if (ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      
      if (ps2x.Button(PSB_L2)){
        Serial.println("L2 pressed");
        openGripperSlowly(150);
      }
      
      if (ps2x.Button(PSB_R2)){
        Serial.println("R2 pressed");
        closeGripperSlowly(90);
      }
      
      if (ps2x.Button(PSB_TRIANGLE)){
        Serial.println("Triangle pressed");
        runScripts();
      }
    }
    
    if(ps2x.ButtonDataByte()!= 65535 ){
      if ( ps2x.ButtonPressed(PSB_CIRCLE)){//will be TRUE if button was JUST pressed
        Serial.println("Circle just pressed");
        Serial.println(ps2x.ButtonDataByte());
        runPos(90,90,90,90);
      }
      
      if ( ps2x.NewButtonState(PSB_CROSS) && ps2x.ButtonDataByte()){
        //will be TRUE if button was JUST pressed OR released
        Serial.println(ps2x.ButtonDataByte());
        Serial.println("X just changed");
        initNewScripts();
        delay(10);
      }
      
      if (ps2x.ButtonReleased(PSB_SQUARE)){             //will be TRUE if button was JUST released
         Serial.println(ps2x.ButtonDataByte());
        Serial.println("Square just released");
        addScriptToArr(baseServo.read(),elbowServo.read(),shoulderServo.read(),gripperServo.read());
        delay(10);
      }
      
      if (ps2x.Button(PSB_L1)) { //print stick values if either is TRUE
        Serial.print("Stick Values PSB_L1");
        /*
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC);
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC);
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC);
        */
        longerOneStep();
      }
      
      if(ps2x.Button(PSB_R1)){ //print stick values if either is TRUE
        Serial.print("Stick Values PSB_R1");
        /*
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC);
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC);
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC);
        */
        shorterOneStep();
      }
    }
  }
  delay(50);
}

/*--------------------------Save/Run script-------------------------*/

void initNewScripts(){
  arr_size = 0;
}

void addScriptToArr(byte basePos,byte elbowPos,byte shoulderPos,byte gripperPos){
  if(arr_size < MAX_SIZE_ARR){
    scripts[arr_size][0] = basePos;
    scripts[arr_size][1] = elbowPos;
    scripts[arr_size][2] = shoulderPos;
    scripts[arr_size][3] = gripperPos;
    arr_size++;
  }
}

void runScripts(){
  for(int i = 0; i < arr_size; i++){
    runPos(scripts[i][0],
           scripts[i][1],
           scripts[i][2],
           scripts[i][3]);       
  }
}


void runPos(int basePos,int elbowPos,int shoulderPos,int gripperPos){
  //BASE 
  if(baseServo.read()> basePos){
    turnRightSlowly(basePos);
  }else
    turnLeftSlowly(basePos);
  
  //ELBOW
  if(elbowServo.read() > elbowPos){
     downSlowly(elbowPos);
  }else
     upSlowly(elbowPos);
  
  //SHOULDER
  if(shoulderServo.read() > shoulderPos){
     shorterSlowly(shoulderPos);
  }else
     longerSlowly(shoulderPos);
  //GRIPPER
  
  if(gripperServo.read() > gripperPos){
    closeGripperSlowly(gripperPos);
  }else
    openGripperSlowly(gripperPos);
    
}

/*--------------------------------BASE------------------------------*/

void turnLeftOneStep()
{
  baseServo.write(baseServo.read() + DRE_STEP);
  delay(SERVO_DELAY);
}


void turnRightOneStep()
{
  baseServo.write(baseServo.read() - DRE_STEP);
  delay(SERVO_DELAY);
}


void turnLeftSlowly(int pos)
{
  for (int i = baseServo.read(); i <= pos; i++)
  {
    baseServo.write(i);
    delay(SERVO_DELAY);
  }
}

void turnRightSlowly(int pos)
{
  for (int i = baseServo.read(); i >= pos; i--)
  {
    baseServo.write(i);
    delay(SERVO_DELAY);
  }
}

/*----------------------------ELBOW----------------------------------------*/

void upOneStep()
{
  elbowServo.write(elbowServo.read() + DRE_STEP);
  delay(SERVO_DELAY);
}
void downOneStep()
{
  elbowServo.write(elbowServo.read() - DRE_STEP);
  delay(SERVO_DELAY);
}

void upSlowly(int pos)
{
  for (int i = elbowServo.read(); i <= pos; i++)
  {
    elbowServo.write(i);
    delay(SERVO_DELAY);
  }
}

void downSlowly(int pos)
{
  for (int i = elbowServo.read(); i >= pos; i--)
  {
    elbowServo.write(i);
    delay(SERVO_DELAY);
  }
}

/*----------------------------SHOULDER---------------------------------------------*/
void longerOneStep()
{
  shoulderServo.write(shoulderServo.read() + DRE_STEP);
  delay(SERVO_DELAY);
}

void shorterOneStep()
{
  shoulderServo.write(shoulderServo.read() - DRE_STEP);
  delay(SERVO_DELAY);
}

void longerSlowly(int pos)
{
  for (int i = shoulderServo.read(); i <= pos; i++)
  {
    shoulderServo.write(i);
    delay(SERVO_DELAY);
  }
}

void shorterSlowly(int pos)
{
  for (int i = shoulderServo.read(); i >= pos; i--)
  {
    shoulderServo.write(i);
    delay(SERVO_DELAY);
  }
}
/*------------------------------GRIPPER---------------------------------------*/

void openGripper(){
  gripperServo.write(150);
  delay(SERVO_DELAY);
}

void closeGripper(){
  gripperServo.write(90);
   delay(SERVO_DELAY);
}

void openGripperSlowly(int pos)
{
  for (int i = gripperServo.read(); i <= pos; i++)
  {
    gripperServo.write(i);
    delay(SERVO_DELAY);
  }
}

void closeGripperSlowly(int pos)
{
  for (int i = gripperServo.read(); i >= pos; i--)
  {
    gripperServo.write(i);
    delay(SERVO_DELAY);
  }
}
