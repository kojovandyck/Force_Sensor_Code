#define WINDOW_SIZE 5
int INDEX = 0;
float SUM_Angle = 0;
float READINGS_Angle[WINDOW_SIZE];
float AVERAGED_Angle = 0;
float SUM_Force = 0;
float READINGS_Force[WINDOW_SIZE];
float AVERAGED_Force = 0;

int AATsin = 0;
int AATcos = 0;
float AATangle = 0.0;
int n = 0 ;
int i = 0 ;

float cf = 8.6; // calibration factor
float ffsdata = 0;
int offset = 0; // offset value
float ffs_V;
float ffs_R;
float ffs_C;
float Force;

#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 8 // Popular NeoPixel size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int onBits = 0;
float maxValue = 20; // warning value

void setup() {
  Serial.begin (115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  AATsin = analogRead(0) - 512;
  AATcos = analogRead(1) - 512;
  AATangle = (atan2(AATcos, AATsin) / (3.1416)) * 180.0;

  ffsdata = analogRead(5);
  ffs_V = ffsdata * 5.0 / 1023.0;
  ffs_R = 10 * (5 / ffs_V - 1.0);
  ffs_C = 1.0 / ffs_R;
  Force = (ffs_C * 100) + 0;

  if (n == 0) {
    SUM_Angle -= READINGS_Angle[INDEX];
    SUM_Force -= READINGS_Force[INDEX];
    READINGS_Angle[INDEX] = AATangle;
    READINGS_Force[INDEX] = Force;
    SUM_Angle += AATangle;
    SUM_Force += Force;
    INDEX = (INDEX + 1) % WINDOW_SIZE;
    AVERAGED_Angle = SUM_Angle / WINDOW_SIZE;
    AVERAGED_Force = SUM_Force / WINDOW_SIZE;
    Serial.print("Angle value ");
    Serial.print(AVERAGED_Angle);
    Serial.print("  ");
    Serial.print("Force value ");
    Serial.print(AVERAGED_Force);
    Serial.print("ffsdata ");
    Serial.println(ffsdata);
    pixels.clear(); // Set all pixel colors to 'off'
    onBits = (int) (AVERAGED_Force) / maxValue * NUMPIXELS;
    if (onBits > 8) {
      for (int i = 0; i < 8; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(254, 0 , 0));
      }
    } else {
      switch (onBits) {
        case 8:
          pixels.setPixelColor(7, pixels.Color(254, 0 , 0));
        case 7:
          pixels.setPixelColor(6, pixels.Color(254, 0 , 0));
        case 6:
          pixels.setPixelColor(5, pixels.Color(254, 254 , 0));
        case 5:
          pixels.setPixelColor(4, pixels.Color(254, 254 , 0));
        case 4:
          pixels.setPixelColor(3, pixels.Color(0, 254 , 0));
        case 3:
          pixels.setPixelColor(2, pixels.Color(0, 254 , 0));
        case 2:
          pixels.setPixelColor(1, pixels.Color(0, 254 , 0));
        case 1:
          pixels.setPixelColor(0, pixels.Color(0, 254 , 0));
      }
    }
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
n++;
n %= 200;
}
