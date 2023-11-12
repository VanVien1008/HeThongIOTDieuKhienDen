#include <SoftwareSerial.h>
#include <SerialCommand.h>

#define Rx 2
#define Tx 3
SoftwareSerial mySerial(Rx, Tx);
SerialCommand SCmd;

int ledNTrai = 11;
int ledNGiua = 9;
int ledNPhai = 7;
int ledLTrai = 12;
int ledLGiua = 10;
int ledLPhai = 8;
int pirSensorTrai = 4;
int pirSensorPhai = 5;
char quangTroSTR[3];
char message[14];

int trangThaiLed = 0;
int trangThai = 0;
long long int startTime[6];
long long int timeTruyen = 0;

int trangThaiDen1Moi = 0;
int trangThaiDen2Moi = 0;
int trangThaiDen3Moi = 0;
int trangThaiDen4Moi = 0;
int trangThaiDen5Moi = 0;
int trangThaiDen6Moi = 0;

int trangThaiDen1Cu = 0;
int trangThaiDen2Cu = 0;
int trangThaiDen3Cu = 0;
int trangThaiDen4Cu = 0;
int trangThaiDen5Cu = 0;
int trangThaiDen6Cu = 0;

int trangThaiSensorTrai;
int trangThaiSensorPhai;
int nguongAnhSang = 30;
int quangTro;  // biến lưu trữ thời điểm bắt đầu bật đèn
unsigned long timeDelay = 15000;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);

  SCmd.addCommand("TrangThai", trangThaiHeThong);
  SCmd.addCommand("den1", den1);
  SCmd.addCommand("den2", den2);
  SCmd.addCommand("den3", den3);
  SCmd.addCommand("den4", den4);
  SCmd.addCommand("den5", den5);
  SCmd.addCommand("den6", den6);


  pinMode(ledNTrai, OUTPUT);
  pinMode(ledNGiua, OUTPUT);
  pinMode(ledNPhai, OUTPUT);
  pinMode(ledLGiua, OUTPUT);
  pinMode(ledLPhai, OUTPUT);
  pinMode(ledLTrai, OUTPUT);
  pinMode(pirSensorTrai, INPUT);
  pinMode(pirSensorPhai, INPUT);
}

void truyenTrangThaiDen() {
   sprintf(quangTroSTR, "%d", quangTro);
   strcpy(message, "GiaTriQuang ");
   strcat(message, quangTroSTR);
  if(trangThaiDen1Moi != trangThaiDen1Cu){
    if(trangThaiDen1Cu == 1){
      mySerial.println("den1 1");
    }
    else
      mySerial.println("den1 0");

    trangThaiDen1Moi = trangThaiDen1Cu;
  }
  if(trangThaiDen2Moi != trangThaiDen2Cu){
    if(trangThaiDen2Cu == 1){
      mySerial.println("den2 1");
    }
    else
      mySerial.println("den2 0");
      trangThaiDen2Moi = trangThaiDen2Cu;
  }
  if(trangThaiDen3Moi != trangThaiDen3Cu){
    if(trangThaiDen3Cu == 1){
      mySerial.println("den3 1");
    }
    else
      mySerial.println("den3 0");
      trangThaiDen3Moi = trangThaiDen3Cu;
  }
  if(trangThaiDen4Moi != trangThaiDen4Cu){
    if(trangThaiDen4Cu == 1){
      mySerial.println("den4 1");
    }
    else
      mySerial.println("den4 0");
      trangThaiDen4Moi = trangThaiDen4Cu;
  }
  if(trangThaiDen5Moi != trangThaiDen5Cu){
    if(trangThaiDen5Cu == 5){
      mySerial.println("den5 1");
    }
    else
      mySerial.println("den5 0");
      trangThaiDen5Moi = trangThaiDen5Cu;
  }
  if(trangThaiDen6Moi != trangThaiDen6Cu){
    if(trangThaiDen6Cu == 1){
      mySerial.println("den6 1");
    }
    else
      mySerial.println("den6 0");
      trangThaiDen6Moi = trangThaiDen6Cu;
  }
 
}

void loop() {
  SCmd.readSerial();
  if(trangThai == 0){


  // put your main code here, to run repeatedly:
  quangTro = analogRead(A0);
  trangThaiSensorPhai = digitalRead(pirSensorPhai);
  trangThaiSensorTrai = digitalRead(pirSensorTrai);

  // trangThai = digitalRead(PIRsensor);
  //Serial.println(trangThai);
  Serial.println(quangTro);
 // truyenTrangThaiDen();

  if (150 < quangTro < 400) {
    trangThaiLed = 2;
  }
  if (quangTro < 150) {
    trangThaiLed = 1;
  }
  if (quangTro > 400) {
    trangThaiLed = 0;
  }

  if (trangThaiLed == 2) {
    if (trangThaiSensorPhai == 1) {

      digitalWrite(ledNPhai, HIGH);
      trangThaiDen1Cu = 1;
      startTime[0] = millis();
    }

    if (trangThaiSensorTrai == 1) {
      digitalWrite(ledNTrai, HIGH);
      trangThaiDen3Cu = 1;
      startTime[1] = millis();
    }

    if (trangThaiSensorPhai == 1 && trangThaiSensorTrai == 1) {
      digitalWrite(ledNGiua, HIGH);
      trangThaiDen2Cu = 1;
      startTime[2] = millis();
    }
  }

  if (trangThaiLed == 1) {
    if (trangThaiSensorPhai == 1) {
      digitalWrite(ledLPhai, HIGH);
      trangThaiDen4Cu = 1;
      startTime[3] = millis();
    }

    if (trangThaiSensorTrai == 1) {
      digitalWrite(ledLTrai, HIGH);
      trangThaiDen6Cu = 1;
      startTime[4] = millis();
    }

    if (trangThaiSensorPhai == 1 && trangThaiSensorTrai == 1) {
      digitalWrite(ledLGiua, HIGH);
      trangThaiDen5Cu = 1;
      startTime[5] = millis();
    }
  }


  for (int i = 0; i < 6; i++) {
    if (millis() - startTime[i] > timeDelay) {
      if (i == 0) {
        digitalWrite(ledNPhai, LOW);
        trangThaiDen1Cu = 0;
      }
      if (i == 1) {
        digitalWrite(ledNTrai, LOW);
        trangThaiDen3Cu = 0;
      }
      if (i == 2) {
        digitalWrite(ledNGiua, LOW);
        trangThaiDen2Cu = 0;
      }

      if (i == 3) {
        digitalWrite(ledLPhai, LOW);
        trangThaiDen4Cu = 0;
      }

      if (i == 4) {
        digitalWrite(ledLTrai, LOW);
        trangThaiDen6Cu = 0;
      }

      if (i == 5) {
        digitalWrite(ledLGiua, LOW);
        trangThaiDen5Cu = 0;
      }
    }
  }
  if(trangThaiDen1Moi != trangThaiDen1Cu){
    if(trangThaiDen1Cu == 1){
      mySerial.println("den1 1");
    }
    else
      mySerial.println("den1 0");

    trangThaiDen1Moi = trangThaiDen1Cu;
  }
  if(trangThaiDen2Moi != trangThaiDen2Cu){
    if(trangThaiDen2Cu == 1){
      mySerial.println("den2 1");
    }
    else
      mySerial.println("den2 0");
      trangThaiDen2Moi = trangThaiDen2Cu;
  }
  if(trangThaiDen3Moi != trangThaiDen3Cu){
    if(trangThaiDen3Cu == 1){
      mySerial.println("den3 1");
    }
    else
      mySerial.println("den3 0");
      trangThaiDen3Moi = trangThaiDen3Cu;
  }
  if(trangThaiDen4Moi != trangThaiDen4Cu){
    if(trangThaiDen4Cu == 1){
      mySerial.println("den4 1");
    }
    else
      mySerial.println("den4 0");
      trangThaiDen4Moi = trangThaiDen4Cu;
  }
  if(trangThaiDen6Moi != trangThaiDen6Cu){
    if(trangThaiDen6Cu == 1){
      mySerial.println("den6 1");
    }
    else
      mySerial.println("den6 0");
      trangThaiDen6Moi = trangThaiDen6Cu;
  }
   if(trangThaiDen5Moi != trangThaiDen5Cu){
    if(trangThaiDen5Cu == 1){
      mySerial.println("den5 1");
    }
    else
      mySerial.println("den5 0");
      trangThaiDen5Moi = trangThaiDen5Cu;
    }
  }

}

void den1(){
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  if(val == 1 && trangThai == 1){
    digitalWrite(ledNTrai , HIGH);
  }
  else if(val == 0 && trangThai == 1){
    digitalWrite(ledNTrai , LOW);
  }
}

void den2(){
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  if(val == 1 && trangThai == 1){
    digitalWrite(ledNGiua , HIGH);
  }
  else if(val == 0 && trangThai == 1){
    digitalWrite(ledNGiua , LOW);
  }
}

void den3(){
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  if(val == 1 && trangThai == 1){
    digitalWrite(ledNPhai , HIGH);
  }
  else if(val == 0 && trangThai == 1){
    digitalWrite(ledNPhai , LOW);
  }
}

void den4(){
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  if(val == 1 && trangThai == 1){
    digitalWrite(ledLTrai , HIGH);
  }
  else if(val == 0 && trangThai == 1){
    digitalWrite(ledLTrai , LOW);
  }
}

void den5(){
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  if(val == 1 && trangThai == 1){
    digitalWrite(ledLGiua , HIGH);
  }
  else if(val == 0 && trangThai == 1){
    digitalWrite(ledLGiua , LOW);
  }
}

void den6(){
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  if(val == 1 && trangThai == 1){
    digitalWrite(ledLPhai , HIGH);
  }
  else if(val == 0 && trangThai == 1){
    digitalWrite(ledLPhai , LOW);
  }
}

void trangThaiHeThong(){
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  if(val == 1){
    trangThai = 1;
  }
  else{
    trangThai = 0;
  }
}