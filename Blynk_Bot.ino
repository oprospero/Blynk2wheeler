/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs on Sparkfun Blynk Board.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * NOTE: You can select NodeMCU 1.0 (compatible board)
 * in the Tools -> Board menu
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define PT    Serial.print
#define PTL   Serial.println//

#define motor_l1  12
#define motor_l2  5
#define motor_r1  13
#define motor_r2  15


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "733d68ddb50147dfb28e40c0f3f00402";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "mines";
//char pass[] = "prospervan";
char ssid[] = "AndroidAP";
char pass[] = "prospervan";


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(motor_l1,OUTPUT);
  pinMode(motor_l2,OUTPUT);
  pinMode(motor_r1,OUTPUT);
  pinMode(motor_r2,OUTPUT);
}

void left_stop() {
  digitalWrite(motor_l1, LOW);
  digitalWrite(motor_l2, LOW);
}

void left_forward(int pwr) {
  digitalWrite(motor_l1, HIGH);
  digitalWrite(motor_l2, LOW);
//  analogWrite(motor_l1, pwr);
//  motor11.low();
//  motor12.high();
}
void left_reverse() {
  digitalWrite(motor_l1, LOW);
  digitalWrite(motor_l2, HIGH);
//  analogWrite(motor_l2, spd);
//  motor12.low();
//  motor11.high();
}

void right_stop() {
  digitalWrite(motor_r1, LOW);
  digitalWrite(motor_r2, LOW);
}

void right_forward(int pwr) {
  
  digitalWrite(motor_r1, HIGH);
  digitalWrite(motor_r2, LOW);
//  analogWrite(motor_r1, pwr);
//  motor21.low();
//  motor22.high();
}
void right_reverse() {
  digitalWrite(motor_r1, LOW);
  digitalWrite(motor_r2, HIGH);
//  motor22.low();
//  motor21.high();
}

void drive_left_wheel(int pwr) {
  if (pwr > -100 && pwr < 100)
    left_stop();
  else if (pwr > 0)
    left_forward(pwr);
  else
    left_reverse();
}

void drive_right_wheel(int pwr) {
  if (pwr > -100 && pwr < 100)
    right_stop();
  else if (pwr > 0)
    right_forward(pwr);
  else
    right_reverse();
  
}

void bot_move(int x, int y) {
  int spd = y - 512;
  int rot = (x - 512);

//  PT(F("spd: "));PTL(spd);
//  PT(F("rot: "));PTL(rot);
  
  int pwr_left_wheel = spd - rot;
  int pwr_right_wheel = spd + rot;
  
  PT(F("pl: "));PTL(pwr_left_wheel);
  PT(F("pr: "));PTL(pwr_right_wheel);

  drive_left_wheel(pwr_left_wheel);
  drive_right_wheel(pwr_right_wheel);
}



BLYNK_WRITE(V1)
{
  int x = param[0].asInt(); // getting first value
  int y = param[1].asInt(); // getting second value
//  PT(F("x: "));PTL(x);
//  PT(F("y: "));PTL(y);

  bot_move(x,y);

  
}

void loop()
{
  Blynk.run();
}

