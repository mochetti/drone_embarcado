void startMPU() {
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(100);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

}

void getMPU() {  
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // offsets
  //  -2340  -182  1503  295 116 24

  acc[0] = a.acceleration.x - 0.66;
  acc[1] = a.acceleration.y + 0.2;
  acc[2] = a.acceleration.z + 1.31;

  gyr[0] = g.gyro.x + 0.16;
  gyr[1] = g.gyro.y + 0.06;
  gyr[2] = g.gyro.z + 0.01;

  temperatura = temp.temperature;

  /* Print out the values */
//  Serial.print("Acceleration X: ");
//  Serial.print(a.acceleration.x);
//  Serial.print(", Y: ");
//  Serial.print(a.acceleration.y);
//  Serial.print(", Z: ");
//  Serial.print(a.acceleration.z);
//  Serial.println(" m/s^2");
//
//  Serial.print("Rotation X: ");
//  Serial.print(g.gyro.x);
//  Serial.print(", Y: ");
//  Serial.print(g.gyro.y);
//  Serial.print(", Z: ");
//  Serial.print(g.gyro.z);
//  Serial.println(" rad/s");
//
//  Serial.print("Temperature: ");
//  Serial.print(temp.temperature);
//  Serial.println(" degC");
//
//  Serial.println("");
}

//#define ACCELEROMETER_SENSITIVITY 8192.0
//#define GYROSCOPE_SENSITIVITY 65.536 

void cFilter(float accData[3], float gyrData[3])
{
    float pitchAcc, rollAcc;
    float dt = 0.01;               
 
    // Integrate the gyroscope data -> int(angularSpeed) = angle
    pitch += gyrData[0] * dt; // Angle around the X-axis
    roll -= gyrData[1] * dt;    // Angle around the Y-axis
 
    // Compensate for drift with accelerometer data if !bullshit
    // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
    int forceMagnitudeApprox = abs(accData[0]) + abs(accData[1]) + abs(accData[2]);
//    Serial.println(forceMagnitudeApprox);
    if (forceMagnitudeApprox > -20 && forceMagnitudeApprox < 20)
    {
  // Turning around the X axis results in a vector on the Y-axis
        pitchAcc = atan2f(accData[1], accData[2]);
        pitch = pitch * 0.98 + pitchAcc * 0.02;
 
  // Turning around the Y axis results in a vector on the X-axis
        rollAcc = atan2f(accData[0], accData[2]);
        roll = roll * 0.98 + rollAcc * 0.02;
    }
} 
