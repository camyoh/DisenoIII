/*******************VARIABLES DE LAS NOTAS MUSICALES****************************/
// Definición de las frecuencias de las notas.
#define DO1 33
#define DO1S 35
#define RE1 37
#define RE1S 39
#define MI1 41
#define FA1 44
#define FA1S 46
#define SOL1 49
#define SOL1S 52
#define LA1 55
#define LA1S 58
#define SI1 62
#define DO2 65
#define DO2S 69
#define RE2 73
#define RE2S 78
#define MI2 82
#define FA2 87
#define FA2S 93
#define SOL2 98
#define SOL2S 104
#define LA2 110
#define LA2S 117
#define SI2 123
#define DO3 131
#define DO3S 139
#define RE3 147
#define RE3S 156
#define MI3 165
#define FA3 175
#define FA3S 185
#define SOL3 196
#define SOL3S 208
#define LA3 220
#define LA3S 233
#define SI3 247
#define DO4 262
#define DO4S 277
#define RE4 294
#define RE4S 311
#define MI4 330
#define FA4 349
#define FA4S 370
#define SOL4 392
#define SOL4S 415
#define LA4 440
#define LA4S 466
#define SI4 494
#define DO5 523
#define DO5S 554
#define RE5 587
#define RE5S 622
#define MI5 659
#define FA5 698
#define FA5S 740
#define SOL5 784
#define SOL5S 831
#define LA5 880
#define LA5S 932
#define SI5 988
#define DO6 1047
#define DO6S 1109
#define RE6 1175
#define RE6S 1245
#define MI6 1319
#define FA6 1397
#define FA6S 1480
#define SOL6 1568
#define SOL6S 1661
#define LA6 1760
#define LA6S 1865
#define SI6 1976
#define DO7 2093
#define DO7S 2217
#define RE7 2349
#define RE7S 2489
#define MI7 2637
#define FA7 2794
#define FA7S 2960
#define SOL7 3136
#define SOL7S 3322
#define LA7 3520
#define LA7S 3729
#define SI7 3951
#define redondap 288
#define redonda 192
#define blancap 144
#define blanca 96
#define negrap 72
#define negra 48
#define corcheap 36
#define corchea 24
#define semicorcheap 18
#define tresillo 16
#define semicorchea 12
#define fusap 9
#define fusa 6
#define semifusa 3
/************************************************************/
/**************variables de los leds***************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6
#define NUM_LEDS 2
#define BRIGHTNESS 50
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
/****************************************************************/
/**************variables del acelerometro*************************/
#include <MPU6050_tockn.h>
#include <Wire.h>
float ax = 0, ay = 0, az = 0, axx = 0, ayy = 0, azz = 0;
float mov = 0;
MPU6050 mpu6050(Wire);
bool ciclo = true;
long timer = 0;
/******************************************************************/

void navidad(int pin, int nota, int duracion, int tiempo) {
  int tiempot = duracion * tiempo;
  tone(pin, nota, duracion);

  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.setBrightness(100);
  strip.begin();
  strip.show();

  delay(tiempot);
}
void cancion() {
  int tempo = 5;
  navidad(8, DO1, negra, tempo);
  navidad(8, RE2, negra, tempo);
  navidad(8, MI3, negra, tempo);
  navidad(8, FA4, negra, tempo);
  navidad(8, SOL5, negra, tempo);
  navidad(8, LA6, negra, tempo);
  navidad(8, SI7, negra, tempo);
}
const int motor = 9;
void setup() {
  /*****************configuracion de los leds*********************/
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.setPixelColor(1, strip.Color(255, 0, 0));
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  /*****************************************************************/
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  mpu6050.update();
  ax = abs(mpu6050.getAngleX());
  ay = abs(mpu6050.getAngleY());
  az = abs(mpu6050.getAngleZ());
  delay(50);
  mpu6050.update();
  axx = abs(mpu6050.getAngleX());
  ayy = abs(mpu6050.getAngleY());
  azz = abs(mpu6050.getAngleZ());
  delay(50);
  mov = abs(ax - axx) + abs(ay - ayy) + abs(az - azz);
  if (mov > 10) {
    //digitalWrite(LED_BUILTIN, HIGH);
    //cancion();
    digitalWrite(motor, HIGH);//prende el motor
    //Serial.print("\nmov: ");Serial.print(mov);
    navidad(8, SI7, redondap, 5);
    digitalWrite(motor, LOW);//apaga el motor
  }
  else
  {
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.setPixelColor(1, strip.Color(255, 0, 0));
    strip.setBrightness(50);
    strip.begin();
    strip.show();
  }
  //digitalWrite(LED_BUILTIN, LOW);
  Serial.print("\nmov: "); Serial.print(mov);
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


