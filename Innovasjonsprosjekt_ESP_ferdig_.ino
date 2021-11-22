// inkluderer bibliotekene som trengs for å få buzzer og servomotor til å fungere
#include <ESP32Tone.h>
#include "pitches.h"
#include <ESP32Servo.h> 

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Eggan";
const char* password = "12345678";
int b1kj = 0;
int b2kj = 0;
int b3kj = 0;
int b4kj = 0;
int b5kj = 0;

// ultralydssensor
int trigPin = 25; // trigger pin
int echoPin = 33; // echo pin

// buzzer
int tempo = 150; 

int buzzer = 26;

int melody[] = { // pacman melodi
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

// 2 servomotorer: servo1 og servo2
static const int servo1Pin = 14;
static const int servo2Pin = 18;
Servo servo1;
Servo servo2;



void setup() {
  // servo kode
  {
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
  }
  // ultralydssensor
  {
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }
  //Wifi start
    WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
 if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    String serverPath = "https://gruppe4.innovasjon.ed.ntnu.no/innovapp/esp";
    http.begin(serverPath.c_str());
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        char json[500];
        payload.replace(" ", "");
        payload.trim();
        //payload.remove(0,1);
        payload.toCharArray(json, 500);
        Serial.println(payload);
        StaticJsonDocument<200> doc;
        deserializeJson(doc, json);
        int b1 = doc["b1"];
        int b2 = doc["b2"];
        int b3 = doc["b3"];
        int b4 = doc["b4"];
        int b5 = doc["b5"];
        Serial.println(b1);
        Serial.println(b2);
        Serial.println(b3);
        Serial.println(b4);
        Serial.println(b5);
        if (b1 == 1 and b1kj == 0){
          b1kj = 1;
         int randomnum = random(1, 4);

  // ultralydssensor kode
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;

  // if-setning for ultralydssensoren som starter random-funksjonen og en ny if-setning,
  // dersom avstanden den registrerer en bevegelse mellom 2 og 10 cm.
  if(distance > 12) Serial.println("Out of range");
  //legg inn lyd til hvis ikke registrering av hånd her !!!
  else
  {if (randomnum == 1){ // setter i gang buzzeren hvis det randome nummeret = 1
      for (int thisNote = 0; thisNote < notes * 2; thisNote =
      thisNote + 2) {
      divider = melody[thisNote + 1];
      if (divider > 0) {
      noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
      }
    tone(buzzer, melody[thisNote], noteDuration*0.98);
    delay(noteDuration);
    noTone(buzzer);
    
    }
    Serial.println("buzzer");
    }
   else if (randomnum == 2) { // setter i gang servo1 hvis det randome nummeret = 2
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo1.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo1.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 1");
   }
   else if (randomnum == 3) { // setter i gang servo2 hvis det randome nummeret = 3
     for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo2.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo2.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 2");
   }
    }
        }
       if (b2 == 1 and b2kj == 0){
                  b2kj = 1;
         int randomnum = random(1, 4);

  // ultralydssensor kode
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;

  // if-setning for ultralydssensoren som starter random-funksjonen og en ny if-setning,
  // dersom avstanden den registrerer en bevegelse mellom 2 og 10 cm.
  if(distance>12) Serial.println("Out of range");
  //legg inn lyd til hvis ikke registrering av hånd her !!!
  else
  {if (randomnum == 1){ // setter i gang buzzeren hvis det randome nummeret = 1
      for (int thisNote = 0; thisNote < notes * 2; thisNote =
      thisNote + 2) {
      divider = melody[thisNote + 1];
      if (divider > 0) {
      noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
      }
    tone(buzzer, melody[thisNote], noteDuration*0.98);
    delay(noteDuration);
    noTone(buzzer);
    
    }
    Serial.println("buzzer");
    }
   else if (randomnum == 2) { // setter i gang servo1 hvis det randome nummeret = 2
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo1.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo1.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 1");
   }
   else if (randomnum == 3) { // setter i gang servo2 hvis det randome nummeret = 3
     for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo2.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo2.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 2");
   }
    }
       }
       if (b3 == 1 and b3kj == 0) {
                  b3kj = 1;
         int randomnum = random(1, 4);

  // ultralydssensor kode
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;

  // if-setning for ultralydssensoren som starter random-funksjonen og en ny if-setning,
  // dersom avstanden den registrerer en bevegelse mellom 2 og 10 cm.
  if(distance>12) Serial.println("Out of range");
  //legg inn lyd til hvis ikke registrering av hånd her !!!
  else
  {if (randomnum == 1){ // setter i gang buzzeren hvis det randome nummeret = 1
      for (int thisNote = 0; thisNote < notes * 2; thisNote =
      thisNote + 2) {
      divider = melody[thisNote + 1];
      if (divider > 0) {
      noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
      }
    tone(buzzer, melody[thisNote], noteDuration*0.98);
    delay(noteDuration);
    noTone(buzzer);
    
    }
    Serial.println("buzzer");
    }
   else if (randomnum == 2) { // setter i gang servo1 hvis det randome nummeret = 2
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo1.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo1.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 1");
   }
   else if (randomnum == 3) { // setter i gang servo2 hvis det randome nummeret = 3
     for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo2.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo2.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 2");
   }
    }
       }
       if (b4 == 1 and b4kj == 0) {
                  b4kj = 1;
         int randomnum = random(1, 4);

  // ultralydssensor kode
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;

  // if-setning for ultralydssensoren som starter random-funksjonen og en ny if-setning,
  // dersom avstanden den registrerer en bevegelse mellom 2 og 10 cm.
  if(distance>12) Serial.println("Out of range");
  //legg inn lyd til hvis ikke registrering av hånd her !!!
  else
  {if (randomnum == 1){ // setter i gang buzzeren hvis det randome nummeret = 1
      for (int thisNote = 0; thisNote < notes * 2; thisNote =
      thisNote + 2) {
      divider = melody[thisNote + 1];
      if (divider > 0) {
      noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
      }
    tone(buzzer, melody[thisNote], noteDuration*0.98);
    delay(noteDuration);
    noTone(buzzer);
    
    }
    Serial.println("buzzer");
    }
   else if (randomnum == 2) { // setter i gang servo1 hvis det randome nummeret = 2
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo1.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo1.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 1");
   }
   else if (randomnum == 3) { // setter i gang servo2 hvis det randome nummeret = 3
     for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo2.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo2.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 2");
   }
    }
       }
       if (b5 == 1 and b5kj == 0) {
                  b5kj = 1;
         int randomnum = random(1, 4);

  // ultralydssensor kode
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) /29.1;

  // if-setning for ultralydssensoren som starter random-funksjonen og en ny if-setning,
  // dersom avstanden den registrerer en bevegelse mellom 2 og 10 cm.
  if(distance>12) Serial.println("Out of range");
  //legg inn lyd til hvis ikke registrering av hånd her !!!
  else
  {if (randomnum == 1){ // setter i gang buzzeren hvis det randome nummeret = 1
      for (int thisNote = 0; thisNote < notes * 2; thisNote =
      thisNote + 2) {
      divider = melody[thisNote + 1];
      if (divider > 0) {
      noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
      }
    tone(buzzer, melody[thisNote], noteDuration*0.98);
    delay(noteDuration);
    noTone(buzzer);
    
    }
    Serial.println("buzzer");
    }
   else if (randomnum == 2) { // setter i gang servo1 hvis det randome nummeret = 2
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo1.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo1.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 1");
   }
   else if (randomnum == 3) { // setter i gang servo2 hvis det randome nummeret = 3
     for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
   servo2.write(posDegrees);
   delay(2);
   }
   for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
   servo2.write(posDegrees);
   delay(2);
   }
   Serial.println("servo 2");
   }
    }
       }
      }
     else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
     delay(1000);
  }
  else{
     Serial.println("WiFi Disconnected");
  }
}
