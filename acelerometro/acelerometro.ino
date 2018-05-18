digitalWrite(LED_BUILTIN, HIGH);#include <MPU6050_tockn.h>
#include <Wire.h>
float ax = 0, ay = 0, az = 0, axx = 0, ayy = 0, azz = 0;
float mov = 0;
MPU6050 mpu6050(Wire);
bool ciclo = true;
long timer = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();
  ax = abs(mpu6050.getAngleX());
  ay = abs(mpu6050.getAngleY());
  az = abs(mpu6050.getAngleZ());
  delay(250);
  mpu6050.update();
  axx = abs(mpu6050.getAngleX());
  ayy = abs(mpu6050.getAngleY());
  azz = abs(mpu6050.getAngleZ());
  delay(250);
  mov = abs(ax - axx) + abs(ay - ayy) + abs(az - azz);
  if (mov > 5) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
    digitalWrite(LED_BUILTIN, LOW);
  //  Serial.print("\nmov: ");Serial.print(mov);
  //  Serial.print("\ty: ");Serial.print(ay);
  //  Serial.print("\tz: ");Serial.print(az);
  //  Serial.print("\nxx: ");Serial.print(axx);
  //  Serial.print("\tyy: ");Serial.print(ayy);
  //  Serial.print("\tzz: ");Serial.print(azz);
  //    Serial.print("angleX : "); Serial.print(anguloX);
  //    Serial.print("\tangleY : "); Serial.print(anguloY);
  //    Serial.print("\tangleZ : "); Serial.println(anguloZ);
  //    digitalWrite(LED_BUILTIN, LOW);

  //  Serial.println("=======================================================\n");
  //  timer = millis();

}
