#include "funcoes.h"

Adafruit_MPU6050 mpu;

Pixy2I2C pixy;

WebSocketsServer webSocket(81);    // create a websocket server on port 81
WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;

ESP8266WebServer server(80);

unsigned long tPagina, tCamera = 0, tMPU = 0, tDistancia = 0;

const int trigPin = 16;  //D0
const int echoPin = 13;  //D7

long duration;
int dist;

float pitch=0, roll=0;

float ang=0, angX=0, angY=0, angZ=0;

float temperatura=0;

float acc[3], gyr[3];

float offX, offY;

// offAcelX, offAcelY, offAcelZ, offGyroX, offGyroY, offGyroZ;
float offsets[] = {-0.66, 0.2, 1.31, 0.16, 0.06, 0.01};

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
  
  tPagina = millis();
  tCamera = millis();
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
  }

  if(millis() - tCamera >= 10) {
    tCamera = millis();
    camera();
  }

  if(millis() - tDistancia >= 50) {
    tDistancia = millis();
    distancia();
  }
  
  if(millis() - tPagina >= 100) {
    tPagina = millis();
    atualizaPagina();
  }
}
