// Clock example using a seven segment display & GPS for time.
//
// Must have the Adafruit GPS library installed too!  See:
//   https://github.com/adafruit/Adafruit-GPS-Library
//
// Designed specifically to work with the Adafruit LED 7-Segment backpacks
// and ultimate GPS breakout/shield:
// ----> http://www.adafruit.com/products/881
// ----> http://www.adafruit.com/products/880
// ----> http://www.adafruit.com/products/879
// ----> http://www.adafruit.com/products/878
// ----> http://www.adafruit.com/products/746
//
// Adafruit invests time and resources providing this open source code, 
// please support Adafruit and open-source hardware by purchasing 
// products from Adafruit!
//
// Written by Tony DiCola for Adafruit Industries.
// Released under a MIT license: https://opensource.org/licenses/MIT

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GPS.h>
#include "Adafruit_LEDBackpack.h"

// I2C address of the display.  Stick with the default address of 0x70
// unless you've changed the address jumpers on the back of the display.
#define DISPLAY_ADDRESS   0x70


// Create display and GPS objects.  These are global variables that
// can be accessed from both the setup and loop function below.
Adafruit_7segment clockDisplay = Adafruit_7segment();
SoftwareSerial gpsSerial(8, 7);  // GPS breakout/shield will use a 
                                 // software serial connection with 
                                 // TX = pin 8 and RX = pin 7.
Adafruit_GPS gps(&gpsSerial);
float maxKnots = 0;
int counter=0;
int maxSwitchPin=9;

void setup() {
  // Setup function runs once at startup to initialize the display and GPS.

  // Setup Serial port to print debug output.
  Serial.begin(115200);
  Serial.println("Speedometer starting!");

  i2cScan();

  pinMode(maxSwitchPin,INPUT);

  // Setup the display.
  clockDisplay.begin(DISPLAY_ADDRESS);

  // Setup the GPS using a 9600 baud connection (the default for most
  // GPS modules).
  gps.begin(9600);

  // Configure GPS to onlu output minimum data (location, time, fix).
  gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);

  // Use a 1 hz, once a second, update rate.
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  
  // Enable the interrupt to parse GPS data.
  enableGPSInterrupt();

  
}

void scanner(){
  //Serial.print("Scanning:");
  //Serial.print(counter,DEC);
  //Serial.print(":");
  if(counter % 10 == 0)
  {
    clockDisplay.writeDigitRaw(3,16);
    clockDisplay.writeDigitRaw(4,0);
    //Serial.println("1");
  }
  else if(counter % 10 == 1 || counter % 10 == 9)
  {
    clockDisplay.writeDigitRaw(3,32);
    clockDisplay.writeDigitRaw(4,0);
    //Serial.println("2");
  }
  else if(counter % 10 == 2 || counter % 10 == 8)
  {
    clockDisplay.writeDigitRaw(3,1);
    clockDisplay.writeDigitRaw(4,0);
    //Serial.println("3");
  }
  else if(counter % 10 == 3 || counter % 10 == 7)
  {
    clockDisplay.writeDigitRaw(3,0);
    clockDisplay.writeDigitRaw(4,1);
    //Serial.println("4");
  }
  else if(counter % 10 == 4 || counter % 10 == 6)
  {
    clockDisplay.writeDigitRaw(3,0);
    clockDisplay.writeDigitRaw(4,2);
    //Serial.println("5");
  }
  else if(counter % 10 == 5)
  {
    clockDisplay.writeDigitRaw(3,0);
    clockDisplay.writeDigitRaw(4,4);
    //Serial.println("6");
  }
  clockDisplay.writeDisplay();
  counter++;
  delay(100);
}

void loop() {
  
  // Check if GPS has new data and parse it.
  if (gps.newNMEAreceived()) {
    gps.parse(gps.lastNMEA());

    if(gps.satellites<5)
    {
      Serial.print("Satellites:");
      Serial.println(gps.satellites,DEC);
      scanner();
    }
    else
    {
      float knots = gps.speed;
    
      if(knots>maxKnots){
        maxKnots = knots;
      }
    
      //if(digitalRead(maxSwitchPin)==1){ //max button is down
      //  knots = maxKnots;
      //}
      
      float mph = knots * 1.15078;
    
      int displayValue = (int)mph;

      Serial.print("Speed:");
      Serial.println(displayValue,DEC);
      
      clockDisplay.println(displayValue, DEC);
      clockDisplay.writeDisplay();
      //delay(250);
    }
  }
  else
  {
    //scanner();
  }  
}

SIGNAL(TIMER0_COMPA_vect) {
  // Use a timer interrupt once a millisecond to check for new GPS data.
  // This piggybacks on Arduino's internal clock timer for the millis()
  // function.
  gps.read();
}

void enableGPSInterrupt() {
  // Function to enable the timer interrupt that will parse GPS data.
  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function above
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

void i2cScan()
 {
   byte error, address;
   int nDevices;
   Wire.begin();
  Serial.println("Scanning...");
 
  nDevices = 0;
   for(address = 0; address <= 127; address++ )
  {
     // The i2c_scanner uses the return value of
     // the Write.endTransmisstion to see if
     // a device did acknowledge to the address.
     Wire.beginTransmission(address);
     error = Wire.endTransmission();
 
    if (error == 0)
     {
       Serial.print("I2C device found at address 0x");
       if (address<16)
        Serial.print("0");
       Serial.print(address,HEX);
       Serial.println(" !");
 
      nDevices++;
     }
     else if (error==4)
    {
       Serial.print("Unknow error at address 0x");
       if (address<16)
        Serial.print("0");
       Serial.println(address,HEX);
     }
   }
   if (nDevices == 0)
     Serial.println("No I2C devices found\n");
   else
     Serial.println("done\n");
 
  //delay(8000);           // wait 8 seconds for next scan
 }

