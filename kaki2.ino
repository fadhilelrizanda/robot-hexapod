#include "DynamixelMotor.h"

//13,14,15 SEDANG DIGUNAKAN

const float cx = 2.5; //coxa
const float fm = 4.7; //femur
const float tb = 9; // tibia

float L, L1;
float alpha, alpha1, alpha2, beta, gama;

enum Dir {
  stop1, stop2, Forward, CW2, CCW2, CW4, CCW4, CW7, CCW7, CW10, CCW10, CW13,
  CCW13, CW15, CCW15, CW18, CCW18, CW30, CCW30, CW90, CCW90, CWawal, CCWawal, stepForward, CW90sekali, CCW90sekali, CW90sekali2
};

Dir dir;
uint8_t state = 50;

int i = 0;
int j = 0;
int k = 0;
int p = 0;

bool logic = false;
bool probe = false;

int once = 0;
int once2 = 0;
int once3 = 0;

float rotate_value;

const uint8_t id[20] = {20, //id 20 tidak di gunakan hanya sebagai penutup array 0
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18
                       };

int position[20] = {};

int16_t speed = 512;

const long unsigned int baudrate = 1000000;

HardwareDynamixelInterface interface(Serial1, PB13);

DynamixelMotor motor1(interface, id[1]); DynamixelMotor motor2(interface, id[2]); DynamixelMotor motor3(interface, id[3]);
DynamixelMotor motor4(interface, id[4]); DynamixelMotor motor5(interface, id[5]); DynamixelMotor motor6(interface, id[6]);
DynamixelMotor motor7(interface, id[7]); DynamixelMotor motor8(interface, id[8]); DynamixelMotor motor9(interface, id[9]);
DynamixelMotor motor10(interface, id[10]); DynamixelMotor motor11(interface, id[11]); DynamixelMotor motor12(interface, id[12]);
DynamixelMotor motor13(interface, id[13]); DynamixelMotor motor14(interface, id[14]); DynamixelMotor motor15(interface, id[15]);
DynamixelMotor motor16(interface, id[16]); DynamixelMotor motor17(interface, id[17]); DynamixelMotor motor18(interface, id[18]);

DynamixelMotor motor20(interface, id[20]); //motor 20 tidak di gunakan hanya sebagai penutup array 0

DynamixelMotor* motors[] = {  &motor20, //motor 20 tidak di gunakan hanya sebagai penutup array 0
                              &motor1, &motor2, &motor3,
                              &motor4, &motor5, &motor6,
                              &motor7, &motor8, &motor9,
                              &motor10, &motor11, &motor12,
                              &motor13, &motor14, &motor15,
                              &motor16, &motor17, &motor18,
                           };



float setMotor(int ID_Motor, float deg) {
  //ID = numberMotor(ID);
  //convert val to degree in dynamixcel
  float val;
  int cal =  48;
  val = (1024.00 / 300.00) * deg;
  motors[ID_Motor]->goalPosition(val);
  //  position[ID] = setDeg(value);
  Serial.print("Fun : ");
  Serial.println(val);
  return position[ID_Motor];
}


void setup()
{
  Serial.begin(9600);
  interface.begin(baudrate);
  delay(100);


  //Initialization dynamixel
  uint8_t status1 = motor1.init(); uint8_t status2 = motor2.init(); uint8_t status3 = motor3.init();
  uint8_t status4 = motor4.init(); uint8_t status5 = motor5.init(); uint8_t status6 = motor6.init();
  uint8_t status7 = motor7.init(); uint8_t status8 = motor8.init(); uint8_t status9 = motor9.init();

  uint8_t status10 = motor10.init(); uint8_t status11 = motor11.init(); uint8_t status12 = motor12.init();
  uint8_t status13 = motor13.init(); uint8_t status14 = motor14.init(); uint8_t status15 = motor15.init();
  uint8_t status16 = motor16.init(); uint8_t status17 = motor17.init(); uint8_t status18 = motor18.init();

  motor1.enableTorque();  motor2.enableTorque();  motor3.enableTorque();
  motor4.enableTorque();  motor5.enableTorque();  motor6.enableTorque();
  motor7.enableTorque();  motor8.enableTorque();  motor9.enableTorque();

  motor10.enableTorque();  motor11.enableTorque();  motor12.enableTorque();
  motor13.enableTorque();  motor14.enableTorque();  motor15.enableTorque();
  motor16.enableTorque();  motor17.enableTorque();  motor18.enableTorque();

  //set speed
  motor1.speed(speed);  motor2.speed(speed);  motor3.speed(speed);
  motor4.speed(speed);  motor5.speed(speed);  motor6.speed(speed);
  motor7.speed(speed);  motor8.speed(speed);  motor9.speed(speed);

  motor10.speed(speed);  motor11.speed(speed);  motor12.speed(speed);
  motor13.speed(speed);  motor14.speed(speed);  motor15.speed(speed);
  motor16.speed(speed);  motor17.speed(speed);  motor18.speed(speed);

  //set CW and CCW
  motor1.jointMode(0, 1023);  motor2.jointMode(0, 1023);  motor3.jointMode(0, 1023);
  motor4.jointMode(0, 1023);  motor5.jointMode(0, 1023);  motor6.jointMode(0, 1023);
  motor7.jointMode(0, 1023);  motor8.jointMode(0, 1023);  motor9.jointMode(0, 1023);

  motor10.jointMode(0, 1023);  motor11.jointMode(0, 1023);  motor12.jointMode(0, 1023);
  motor13.jointMode(0, 1023);  motor14.jointMode(0, 1023);  motor15.jointMode(0, 1023);
  motor16.jointMode(0, 1023);  motor17.jointMode(0, 1023);  motor18.jointMode(0, 1023);

  delay(500);
}
bool state_stop = false;

void trajectory(float start_x, float start_y, float end_x, float end_y, float start_z, float max_z, int interval)
{
  Serial.println("start");
  float step_x = (end_x - start_x) / interval;
  float step_y = (end_y - start_y) / interval;
  float step_z = (max_z / (interval / 2));
  bool down = false;
  float x = start_x;
  float y = start_y;
  float z = start_z;
  for (int i = 0; i < interval; i++)
  {
    trigono_xyz(x, y, z );
    setMotor(13, gama);
    setMotor(14, alpha);
    setMotor(15, beta);
    x = x + step_x;
    y = y + step_y;

    if (i >= (interval / 2))
    {
      z = z - step_z;
    }
    else
    {
      z = z + step_z;
    }

    delay(10);
    Serial.print("x :");
    Serial.println(x);
    Serial.print("y :");
    Serial.println(y);
    Serial.print("z :");
    Serial.println(z);
  }

}

void loop()
{
//    trigono_xyz(9, 9, 6);
//  trigono_xyz(9, 9, 6);
//  setMotor(1, gama);
//  setMotor(2, alpha);
//  setMotor(3, beta);
//
//  setMotor(4, gama);
//  setMotor(5, alpha);
//  setMotor(6, beta);
//
//  setMotor(7, gama);
//  setMotor(8, alpha);
//  setMotor(9, beta);
//
//  setMotor(10, gama);
//  setMotor(11, alpha);
//  setMotor(12, beta);
////
////  setMotor(13, gama);
////  setMotor(14, alpha);
////  setMotor(15, beta);
//
//  setMotor(16, gama);
//  setMotor(17, alpha);
//  setMotor(18, beta);

//  delay(500);


  trajectory(9, 9, 3, 12, 6, 10, 20);  
  delay(200);

  //    trigono_xyz(9, 9, 6);
  //    setMotor(13, gama);
  //    setMotor(14, alpha);
  //    setMotor(15, beta);
  //    delay(1000);
  //    trigono_xyz(11, 5, 6); // belakang
  //    setMotor(13, gama);
  //    setMotor(14, alpha);
  //    setMotor(15, beta);
  //    delay(1000);


}
