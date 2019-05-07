#include "Servo.h"

//Find max value for servo
Servo baseServo;  //0-180 baseServo
Servo elbowServo;  // 20-180 elbowServo
Servo shoulderServo;  //50-145  shoulderServo
Servo gripperServo;  //90-150 gripperServo

char bluetoothByte;
const int SERVO_DELAY = 10;
const int MAX_SIZE_ARR = 20;
const int num_servo = 4;
byte scripts[MAX_SIZE_ARR][num_servo] = {{90,90,90,90}};
int arr_size = 1;

void setup()
{
  
  Serial.begin (9600);
  Serial.println("Serial Start!");
  baseServo.attach(9);//0-180
  elbowServo.attach(5);//0-80-150
  shoulderServo.attach(6);//0-100
  gripperServo.attach(3);//0-100
  runPos(90,90,90,90);
  
}

void loop()
{
  bluetoothRobotArm();
 
}

void bluetoothRobotArm()
{
  if (Serial.available() > 0)
    bluetoothByte = Serial.read();
  switch (bluetoothByte)
  {
    case '0':
      stopArm();
      break;
    
    case '1':
      vuonRa1Buoc();
      break;
    case '2':
      thuVao1Buoc();
      break;
   
    case '3':
      quayTrai1Buoc();
      break;
    case '4':
      quayPhai1Buoc();
      break;
    
    case '5':
      nangLen1Buoc();
      break;
    case '6':
      haXuong1Buoc();
      break;
    
    case '7':
      kep1Buoc();
      break;
    case '8':
      moRa1Buoc();
      break;
    
    case '9':
      runPos(90,90,90,90);
      break;
    case 'n':
      initNewScripts();
      delay(10);
    case 'r':
      runScripts();
      break;
    case 's':
      addScriptToArr(baseServo.read(),elbowServo.read(),shoulderServo.read(),gripperServo.read());
      delay(10);
      //error occur when not delay
      break;
  }
}
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
    quayPhaiTuTu(basePos);
  }else
    quayTraiTuTu(basePos);
    
  //ELBOW
  if(elbowServo.read() > elbowPos){
     haXuongTuTu(elbowPos);
  }else
     nangLenTuTu(elbowPos);
  //SHOULDER
  if(shoulderServo.read() > shoulderPos){
     thuVaoTuTu(shoulderPos);
  }else
     vuonRaTuTu(shoulderPos);
  //GRIPPER
  if(gripperServo.read() > gripperPos){
    kepTuTu(gripperPos);
  }else
    moRaTuTu(gripperPos);
}

void stopArm()
{
  servoPosition(baseServo.read(), elbowServo.read(), shoulderServo.read(), gripperServo.read());
}

void servoPosition (byte servo1, byte servo2, byte servo3, byte servo4)
{
  baseServo.write(servo1);
  elbowServo.write(servo2);
  shoulderServo.write(servo3);
  gripperServo.write(servo4);
}

/*------------------------------GRIPPER---------------------------------------*/
void kep1Buoc()
{
  gripperServo.write(gripperServo.read() - 1);
  delay(SERVO_DELAY);
}


void moRa1Buoc()
{
  gripperServo.write(gripperServo.read() + 1);
  delay(SERVO_DELAY);
}


void moRaTuTu(int pos)
{
  for (int i = gripperServo.read(); i <= pos; i++)
  {
    gripperServo.write(i);
    delay(SERVO_DELAY);
  }
}

void kepTuTu(int pos)
{
  for (int i = gripperServo.read(); i >= pos; i--)
  {
    gripperServo.write(i);
    delay(SERVO_DELAY);
  }
}

/*----------------------------ELBOW----------------------------------------*/
void nangLenTuTu(int pos)
{
  for (int i = elbowServo.read(); i <= pos; i++)
  {
    elbowServo.write(i);
    delay(SERVO_DELAY);
  }
}
void nangLen1Buoc()
{
  elbowServo.write(elbowServo.read() + 1);
  delay(SERVO_DELAY);
}

void haXuongTuTu(int pos)
{
  for (int i = elbowServo.read(); i >= pos; i--)
  {
    elbowServo.write(i);
    delay(SERVO_DELAY);
  }
}
void haXuong1Buoc()
{
  elbowServo.write(elbowServo.read() - 1);
  delay(SERVO_DELAY);
}


/*----------------------------SHOULDER---------------------------------------------*/

void vuonRa1Buoc()
{
  shoulderServo.write(shoulderServo.read() + 1);
  delay(SERVO_DELAY);
}
void vuonRaTuTu(int pos)
{
  for (int i = shoulderServo.read(); i <= pos; i++)
  {
    shoulderServo.write(i);
    delay(SERVO_DELAY);
  }
}


void thuVao1Buoc()
{
  shoulderServo.write(shoulderServo.read() - 1);
  delay(SERVO_DELAY);
}

void thuVaoTuTu(int pos)
{
  for (int i = shoulderServo.read(); i >= pos; i--)
  {
    shoulderServo.write(i);
    delay(SERVO_DELAY);
  }
}


/*--------------------------------BASE--------------------------------------*/


void quayTrai1Buoc()
{
  baseServo.write(baseServo.read() + 1);
  delay(SERVO_DELAY);
}


void quayPhai1Buoc()
{
  baseServo.write(baseServo.read() - 1);
  delay(SERVO_DELAY);
}

void quayTraiTuTu(int pos)
{
  for (int i = baseServo.read(); i <= pos; i++)
  {
    baseServo.write(i);
    delay(SERVO_DELAY);
  }
}
void quayPhaiTuTu(int pos)
{
  for (int i = baseServo.read(); i >= pos; i--)
  {
    baseServo.write(i);
    delay(SERVO_DELAY);
  }
}
/*--------------------------------------------------------------------------*/
