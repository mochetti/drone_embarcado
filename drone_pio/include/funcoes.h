/*
 * Pinos
 * D0 - Trig pin
 * D1 e D2 - I2C com o 6050 e câmera
 * D3, D4, D5, D6 - PWM motores
 * D7 - Echo pin
 * D8
 * 
 */

// Servidor
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <FS.h>
#include "LittleFS.h"

// MPU
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Câmera
#include <Pixy2I2C.h>

#include <Arduino.h>

// Variáveis globais
extern Adafruit_MPU6050 mpu;
extern Pixy2I2C pixy;

extern WebSocketsServer webSocket;    // create a websocket server on port 81
extern WiFiEventHandler stationConnectedHandler;
extern WiFiEventHandler stationDisconnectedHandler;

extern ESP8266WebServer server;

extern const int trigPin;  //D0
extern const int echoPin;  //D7

extern long duration;
extern int dist;

extern float pitch, roll;

extern float ang, angX, angY, angZ;

extern float temperatura;

extern float acc[3], gyr[3];

// Offsets da linha em metros
extern float offX, offY;

// Offsets para calibração do MPU6050
// offAcelX, offAcelY, offAcelZ, offGyroX, offGyroY, offGyroZ;
extern float offsets[6];

// Lâmpada da câmera
extern boolean luz;

extern String macToString(const unsigned char*);

// Funções
void startAP();
void startWS();
void startMPU();
void startCamera();
void luzCamera();
void camera();
void distancia();
void atualizaPagina();
void getMPU();
void calibra();
void cFilter(float[3], float[3]);
void handleRoot();
void conexaoCliente(const WiFiEventSoftAPModeStationConnected&);
void desconexaoCliente(const WiFiEventSoftAPModeStationDisconnected&);
void webSocketEvent(uint8_t, WStype_t, uint8_t *, size_t);