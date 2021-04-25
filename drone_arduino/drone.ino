/*
 * Pinos
 * D0 - Trig pin
 * D1 e D2 - I2C com o 6050 e câmera
 * D3, D4, D5, D6 - PWM motores
 * D7 - Echo pin
 * D8
 * 
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#ifndef APSSID
#define APSSID "drone"
#define APPSK  "31415926"
#endif

//#include <Pixy2.h>
//
//Pixy2 pixy;
#include <Pixy2I2C.h>
Pixy2I2C pixy;

const char *ssid = APSSID;
const char *password = APPSK;

WebSocketsServer webSocket(81);    // create a websocket server on port 81
WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;

ESP8266WebServer server(80);

unsigned long tempo = 0;
unsigned long tMPU = 0;
unsigned long tDistancia = 0;

const int trigPin = 16;  //D0
const int echoPin = 13;  //D7

long duration;
int dist;

float pitch=0, roll=0;

float ang=0, angX=0, angY=0, angZ=0;

float temperatura=0;

float acc[3], gyr[3];

// Lâmpada da câmera
boolean luz = false;

void setup()
{
  Serial.begin(115200);
  Serial.print("Configurando servidor...\n");

  startAP();
  startWS();
  startMPU();

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.print("Configurando câmera...\n");

  startCamera();
  Serial.println("Câmera online");
  
  tempo = millis();
  tMPU = millis();
  tDistancia = millis();
}

void loop()
{
  server.handleClient();
  webSocket.loop();

  if(millis() - tMPU >= 10) {
    tMPU = millis();
    getMPU();
    cFilter(acc, gyr);
    Serial.print(pitch*180/PI);
    Serial.print("  ");
    Serial.println(roll*180/PI);
  }
  
//  camera();
//  distancia();
//  atualizaPagina();
}
