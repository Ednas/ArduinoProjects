//////////////////////////////////////////////////
//
//                Hack-O-Lantern 
//          RGB LED and Audio Spooktacular  
//   DigiSpark USB Hardware from HackerBox 0059
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
// LED code Thanks to Adafruit_NeoPixel Library
//////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>

// Two pixels on pin zero.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, 0, NEO_GRB + NEO_KHZ800);

int speakerPin = 2;
int numTones = 120; 
int cs6 = 1109; 
int fs5 = 740;
int d6 = 1175;
int c6 = 1047;
int f5 = 698;
int b5 = 988;
int e5 = 659;
int bf5 = 932;
int ef5 = 622;
int b4 = 494;
int g5 = 784;

int tones[] = { c6,  f5,  f5,  c6,  f5,  f5,  c6,  f5, cs6,  f5,
                cs6, fs5, fs5, cs6, fs5, fs5, cs6, fs5,  d6, fs5,
                cs6, fs5, fs5, cs6, fs5, fs5, cs6, fs5,  d6, fs5,
                 c6,  f5,  f5,  c6,  f5,  f5,  c6,  f5, cs6,  f5,
                 c6,  f5,  f5,  c6,  f5,  f5,  c6,  f5, cs6,  f5,
                 b5,  e5,  e5,  b5,  e5,  e5,  b5,  e5,  c6,  e5,
                 b5,  e5,  e5,  b5,  e5,  e5,  b5,  e5,  c6,  e5,
                bf5, ef5, ef5, bf5, ef5, ef5, bf5, ef5,  b5, ef5,
                bf5, ef5, ef5, bf5, ef5, ef5, bf5, ef5,  b5, ef5,
                 b5,  e5,  e5,  b5,  e5,  e5,  b5,  e5,  c6,  e5,
                 b5,  e5,  e5,  b5,  e5,  e5,  b5,  e5,  c6,  e5,
                bf5, ef5, ef5, bf5, ef5, ef5, bf5, ef5,  b5, ef5,
                bf5, ef5, ef5, bf5, ef5, ef5, bf5, ef5,  b5, ef5};

void setup() 
{
  strip.begin();
  pinMode(speakerPin, OUTPUT);
}

void loop()
{
  for (int c=0; c < numTones; c++)
  {
    playTone(tones[c],200);
    updateLEDs();
  }
}

//LED colors/brightness
// red(r) is random 0..30 to keep it dim
// green(g) is half of red (to make orange)
// random(2) is ONE or ZERO 50/50% of the time
//   multiply that into g for 50/50 red/orange
void updateLEDs()
{
  int i, r, g;
  for(i=0; i<=1; i++)
  {
    r=random(30);
    g=0.5*r;
    g=g*random(2);
    strip.setPixelColor(i, strip.Color(r, g ,0));
  }
  strip.show();
}

void playTone(int tone, int duration) 
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
  delayMicroseconds(20000);
}
