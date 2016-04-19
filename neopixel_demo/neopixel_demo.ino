#include <Adafruit_NeoPixel.h>

#define PIN 4  //2015-05-11 changed from pin 1 to pin 4 for ease of connection

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs) 2015-05-10 vm we're using Flora neopixels v2
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//2015-05-10  changed parameter 1 to 6 for 6 neopixels in daffodils
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);

uint8_t myColors[][3] = {{232, 100, 255},  // purple
                         {200, 200, 20},   // yellow
                         {30, 200, 200},   // blue
                         {(0,255,255)},    // cyan
                         {(255,69,0)},     // orange red
                         {(0,255,0)},      // lime
                         {(255,0,255)},    // magenta
                         {(255,0,0)},      // red
                          };

#define FAVCOLORS sizeof(myColors) / 3

void setup() {
  strip.begin();
  strip.setBrightness(40);
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  flashRandom(5, 2);  // first number is 'wait' delay, shorter num == shorter twinkle 2015-05-08 vm changed this to 15 from 5--better for flowers
  //flashRandom(15, 4);  // second number is how many neopixels to simultaneously light up 2015-05-08 vm changed this to 2-4-3 from 1-3-2 for grins
  //flashRandom(15, 3);

}

void flashRandom(int wait, uint8_t howmany) {

  for(uint16_t i=0; i<howmany; i++) {
    // pick a random favorite color!
    int c = random(FAVCOLORS);
    int red = myColors[c][0];
    int green = myColors[c][1];
    int blue = myColors[c][2];

    // get a random pixel from the list
    int j = random(strip.numPixels());
  
    // now we will 'fade' it in 5 steps
    for (int x=0; x < 5; x++) {
      int r = red * (x+1); r /= 5;
      int g = green * (x+1); g /= 5;
      int b = blue * (x+1); b /= 5;
    
      strip.setPixelColor(j, strip.Color(r, g, b));
      strip.show();
      delay(200);
    }
    // & fade out in 5 steps
//    for (int x=5; x >= 0; x--) {
//      int r = red * x; r /= 5;
//      int g = green * x; g /= 5;
//      int b = blue * x; b /= 5;
//    
//      strip.setPixelColor(j, strip.Color(r, g, b));
//      strip.show();
//      delay(wait);
//    }
  }
  // LEDs will be off when done (they are faded to 0)

}
