#include "funcoes.h"

void distancia() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  dist= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  // Serial.print("Distancia(cm): ");
  // Serial.println(dist);
}
