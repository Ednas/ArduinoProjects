//////////////////////////////////////////////////
//
//              Tilt Color Demo for
//      Tessellation PCB from HackerBox 0059
//
//                    uuuuuuu
//                uu$$$$$$$$$$$uu
//             uu$$$$$$$$$$$$$$$$$uu
//            u$$$$$$$$$$$$$$$$$$$$$u
//           u< WWW.HACKERBOXES.COM >u
//          u$$$$$$$$$$$$$$$$$$$$$$$$$u
//          u$$$$$$$$$$$$$$$$$$$$$$$$$u
//          u$$$$$$"   "$$$"   "$$$$$$u
//          "$$$$"      u$u       $$$$"
//           $$$u       u$u       u$$$
//           $$$u      u$$$u      u$$$
//            "$$$$uu$$$   $$$uu$$$$"
//             "$$$$$$$"   "$$$$$$$"
//               u$$$$$$$u$$$$$$$u
//                u$"$"$"$"$"$"$u
//     uuu        $$u$ $ $ $ $u$$       uuu
//    u$$$$        $$$$$u$u$u$$$       u$$$$
//     $$$$$uu      "$$$$$$$$$"     uu$$$$$$
//   u$$$$$$$$$$$uu    """""    uuuu$$$$$$$$$$
//   $$$$"""$$$$$$$$$$uuu   uu$$$$$$$$$"""$$$"
//    """      ""$$$$$$$$$$$uu ""$"""
//              uuuu ""$$$$$$$$$$uuu
//     u$$$uuu$$$$$$$$$uu ""$$$$$$$$$$$uuu$$$
//     $$$$$$$$$$""""           ""$$$$$$$$$$$"
//      "$$$$$"                      ""$$$$""
//        $$$"                         $$$$"
//
//
// ADXL345 I2C code modified from milesburton.com
//               which was modified from SparkFun
// LED control uses FastLED Library
//////////////////////////////////////////////////

#include <Wire.h>
#include <FastLED.h>

#define NUM_LEDS 6
#define DATA_PIN 25
CRGB leds[NUM_LEDS];

// ADXL345 I2C address is 0x53(83)
#define Addr 0x53

// ADXL345 I2C Pins
const uint8_t scl = 16;
const uint8_t sda = 17; 

float xAccl, yAccl, zAccl;

void ReadADXL()
{
  unsigned int data[6];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select bandwidth rate register
  Wire.write(0x2C);
  // Normal mode, Output data rate = 100 Hz
  Wire.write(0x0A);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select power control register
  Wire.write(0x2D);
  // Auto-sleep disable
  Wire.write(0x08);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data format register
  Wire.write(0x31);
  // Self test disabled, 4-wire interface, Full resolution, Range = +/-2g
  Wire.write(0x08);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(100);

  for (int i = 0; i < 6; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write((50 + i));
    // Stop I2C transmission
    Wire.endTransmission();

    // Request 1 byte of data
    Wire.requestFrom(Addr, 1);

    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if (Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }

  // Convert the data to 10-bits
  xAccl = (((data[1] & 0x03) * 256) + data[0]);
  if (xAccl > 511)
  {
    xAccl -= 1024;
  }
  yAccl = (((data[3] & 0x03) * 256) + data[2]);
  if (yAccl > 511)
  {
    yAccl -= 1024;
  }
  zAccl = (((data[5] & 0x03) * 256) + data[4]);
  if (zAccl > 511)
  {
    zAccl -= 1024;
  }
}

void setup()
{
  // Initialize LEDs 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); 
  
  // Initialize I2C communication for ADXL345
  Wire.begin(sda, scl);
  
  // Initialize serial communication, set baud rate to 9600
  Serial.begin(9600);
}

void loop()
{
  ReadADXL();
  UpdateLEDs();

  // Output data to serial monitor
  /*
  Serial.print("Acceleration in X-Axis : ");
  Serial.println(xAccl);
  Serial.print("Acceleration in Y-Axis : ");
  Serial.println(yAccl);
  Serial.print("Acceleration in Z-Axis : ");
  Serial.println(zAccl);
  delay(20);
  */
}

void UpdateLEDs()
{
  int r,g,b;

  //changing these mappings from Accl to RGB defines
  //how the LED colors respond to tilt of the PCB
  
  r=(int)xAccl;
  r=abs(r);
  r=r*0.2;
  r=min(50,r);

  g=(int)yAccl;
  g=abs(g);
  g=g*0.2;
  g=min(50,g);
  
  b=(int)zAccl;
  b=abs(b);
  b=b*0.2;
  b=min(50,b);
   
  for (int i=0;i<6;i++)
  {
    leds[i] = CRGB(r,g,b);
  }
  FastLED.show();
}
