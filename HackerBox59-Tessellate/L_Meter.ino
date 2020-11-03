// HackerBox 0059 Inductance Meter
//
// Design and code inspired by: 
// http://electronoobs.com/eng_arduino_tut10_3.php
//
// Theory of operation:
// The MCU drives the "kickpin" high to charge the LC tank
// circuit up.  L is the unknown Inductor and C is the 1uF
// Capacitor.  When kickpin in released to low by the MCU,
// the LC tank will ring at a frequency determined by L and C.
// This frequency can be measured by turning the ringing
// sinusoid into square pulses using a fast comparator IC.
// The square pulses are read into the MCU at sensepin and
// the measured pulse frequency allows us to calculate L. 

// Set these two pins to those connected to the meter circuit
#define kickpin  27
#define sensepin 26

double pulse, frequency, capacitance, inductance;
void setup(){
  Serial.begin(9600);
  pinMode(sensepin, INPUT);
  pinMode(kickpin, OUTPUT);
  Serial.println("~~ Inductance Meter ~~");
  delay(200);
}
void loop()
{
  digitalWrite(kickpin, HIGH);
  delay(10); //let the tank charge up
  digitalWrite(kickpin,LOW);
  delayMicroseconds(50); //let ringing stabalize
  
  pulse = pulseIn(sensepin,HIGH,5000);
  if(pulse > 0.1)
  { 
    //actual measurement(not a timeout)
    capacitance = 1.E-6; // 1uF
    frequency = 1.E6/(2*pulse);
    inductance = 1./(capacitance*frequency*frequency*4.*3.14159*3.14159);
    inductance *= 1E6;

    //Serial output
    Serial.print("High for uS:");
    Serial.print( pulse );
    Serial.print("\tfrequency Hz:");
    Serial.print( frequency );
    Serial.print("\tinductance uH:");
    Serial.println( inductance );
    delay(10);
  }
  else
  {
    Serial.println("timeout");
  }
}
