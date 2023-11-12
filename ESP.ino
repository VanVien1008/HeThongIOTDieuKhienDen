#include <SerialCommand.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>


SerialCommand SCmd;

#define Rx D0
#define Tx D1
SoftwareSerial mySerial(Rx, Tx);


#define WIFI_SSID "Y26 Lofi Chill 2" 
#define WIFI_PASS "y26xinchao"
#define FIREBASE_HOST "dencuatudong-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zD5mHPvCjGfcgPJjMKdrXNLhTjeLVplJUEyId6D2"

int ENA = 4;
int IN1 = 0;
int IN2 = 2;

int den1;
int den2;
int den3;
int den4;
int den5;
int den6;
int quangTro;
                 

FirebaseData firebaseData;
String path = "/";
FirebaseJson json;


double time_b = 0;
double time_start_1 = 0;
double time_start_2 = 0;
double time_c = 0;
String y;
String x;
int TrangThai = 0;

void setup() {
  mySerial.begin(9600);
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if (!Firebase.beginStream(firebaseData, path)) {
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println();
  }

  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
   SCmd.readSerial();
   if (Firebase.getString(firebaseData, path + "Cua/reset")) y = firebaseData.stringData();
  if (y == "1") {
    
    mySerial.println("den1 0");
    mySerial.println("den2 0");
    mySerial.println("den3 0");
    mySerial.println("den4 0");
    mySerial.println("den5 0");
    mySerial.println("den6 0");
    den1 = 0;
    den2 = 0;
    den3 = 0;
    den4 = 0;
    den5 = 0;
    den6 = 0;
    Firebase.setString(firebaseData, path + "Cua/reset", "0");
    
  }
  
   if (Firebase.getString(firebaseData, path + "Cua/TrangThai")) x = firebaseData.stringData();
  if (x == "1") {
    mySerial.println("TrangThai 1");
    TrangThai = 1;
  }
  else{
    mySerial.println("TrangThai 0");
    TrangThai = 0;
  }

if(TrangThai == 0 ){
  // put your main code here, to run repeatedly:
  
if(den1 == 1){
  Firebase.setString(firebaseData, path + "Cua/den1", "1");
}
else{
  Firebase.setString(firebaseData, path + "Cua/den1", "0");
}
   
   if(den2 == 1){
  Firebase.setString(firebaseData, path + "Cua/den2", "1");
}
else{
  Firebase.setString(firebaseData, path + "Cua/den2", "0");
}
if(den3 == 1){
  Firebase.setString(firebaseData, path + "Cua/den3", "1");
}
else{
  Firebase.setString(firebaseData, path + "Cua/den3", "0");
}
if(den4 == 1){
  Firebase.setString(firebaseData, path + "Cua/den4", "1");
}
else{
  Firebase.setString(firebaseData, path + "Cua/den4", "0");
}
if(den5 == 1){
  Firebase.setString(firebaseData, path + "Cua/den5", "1");
}
else{
  Firebase.setString(firebaseData, path + "Cua/den5", "0");
}
if(den6 == 1){
  Firebase.setString(firebaseData, path + "Cua/den6", "1");
}
else{
  Firebase.setString(firebaseData, path + "Cua/den6", "0");
}
}
  
  else{
  dieuKhienDen();
  //   Serial.print(TrangThai);
  Serial.print(den1); 
  Serial.print(den2);
  Serial.print(den3);
  Serial.print(den4);
  Serial.print(den5);
  Serial.println(den6);
  }
}

void dieuKhienDen(){
  
  String x1, x2, x3, x4, x5, x6;
  if (Firebase.getString(firebaseData, path + "Cua/den1")) x1 = firebaseData.stringData();
  if (x1 == "1") {
    mySerial.println("den1 1");
    den1 = 1;
  }
  else{
    mySerial.println("den1 0");
    den1 = 0;
  }

  if (Firebase.getString(firebaseData, path + "Cua/den2")) x2 = firebaseData.stringData();
  if (x2 == "1") {
    mySerial.println("den2 1");
    den2 = 1;
  }
  else{
    mySerial.println("den2 0");
    den2 = 0;
  }

  if (Firebase.getString(firebaseData, path + "Cua/den3")) x3 = firebaseData.stringData();
  if (x3 == "1") {
    mySerial.println("den3 1");
    den3 = 1;
  }
  else{
    mySerial.println("den3 0");
    den3 = 0;
  }

  if (Firebase.getString(firebaseData, path + "Cua/den4")) x4 = firebaseData.stringData();
  if (x4 == "1") {
    mySerial.println("den4 1");
    den4 = 1;
  }
  else{
    mySerial.println("den4 0");
    den4 = 0;
  }

  if (Firebase.getString(firebaseData, path + "Cua/den5")) x5 = firebaseData.stringData();
  if (x5 == "1") {
    mySerial.println("den5 1");
    den5 = 1;
  }
  else{
    mySerial.println("den5 0");
    den5 = 0;
  }

  if (Firebase.getString(firebaseData, path + "Cua/den6")) x6 = firebaseData.stringData();
  if (x6 == "1") {
    mySerial.println("den6 1");
    den6 = 1;
  }
  else{
    mySerial.println("den6 0");
    den6 = 0;
  }
}

void trangThaiDen1() {
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  den1 = val;
}
void trangThaiDen2() {
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  den2 = val;
}
void trangThaiDen3() {
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  den3 = val;
}
void trangThaiDen4() {
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  den4 = val;
}
void trangThaiDen5() {
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  den5 = val;
}
void trangThaiDen6() {
  int val;
  char *arg;
  arg = SCmd.next();
  val = atof(arg);
  den6 = val;
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}