///////////////蜂鳴器//////////////////////
#include "pitches.h"                 //聲音函式庫
int alert = NOTE_C5 ;                //警報聲響
int alert_hum = NOTE_E1 ; 
///////////////蜂鳴器//////////////////////



//////////////距離感測器///////////////////
const int trig = 12;
const int echo = 11;                  //Echo會送出超音波來回的時間
const int inter_time = 1000;
int time = 0;
//////////////距離感測器///////////////////


//////////////濕度感測器///////////////////
#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

//////////////濕度感測器///////////////////






void setup() {
  Serial.begin(9600);                 //螢幕
  pinMode (trig, OUTPUT);            //觸發高低電位
  pinMode (echo, INPUT);             // 輸入超音波來回的時間給Echo


}




void loop() {
  ////////////////////////////////////////
  float duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH);     //duration = 超音波來回的時間
  distance = (duration/2)/29;          //距離 distance = 超音波來回時間的一半 除  29

  if (distance < 30)
  {
    tone(8, alert, 500);
  }
  ////////////////////////////////////////

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  
  //////////////////////////////////////
  
  Serial.print("Data:");
  Serial.print (time/1000);             //第幾次調查結果
  Serial.print(", d = ");
  Serial.print(distance);
  Serial.println(" cm");
  //////////////////////////////////////
  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("DHT11 TEST  OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

  if (humidity > 92)
  {
    tone(8, alert_hum, 500);                 //濕度太高警報
  }
  /////////////////////////////////////////
  time = time + inter_time;
  delay(inter_time);                   //等待一秒
}
