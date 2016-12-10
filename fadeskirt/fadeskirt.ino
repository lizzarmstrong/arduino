#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(11, 6, NEO_GRB + NEO_KHZ800);

uint8_t colours[][3] = {
  {200, 0, 200},
  {100, 0, 200},
  {200, 0, 100},
  {200, 200, 200},
  {100, 100, 200},
  {0, 200, 50},
  {0, 200, 200},
  {0, 100, 200},
  {0, 200, 100}
};



#define FAVCOLOURS sizeof(colours) / 3

void setup() {
  strip.begin();
  strip.show();

}

void loop() {
  randomizeFade();
}

void randomizeFade() {
  int howmany = random(1, 6);
  int randomPixels[howmany];
  int colourChoices[howmany];
  int wait = 50;
  
  
  for(int i=0; i < howmany; i++) {
    randomPixels[i] = random(strip.numPixels());
    colourChoices[i] = random(FAVCOLOURS);
  }
  for(int y=0; y<5; y++) {
    // each step
    for(int x=0; x < howmany; x++) {
      int j = randomPixels[x];
      int c = colourChoices[x];
      int red = colours[c][0];
      int green = colours[c][1];
      int blue = colours[c][2];

      int r = red * (y + 1); r /= 5;
      int g = green * (y + 1); g /= 5;
      int b = blue * (y + 1) ; b /= 5;
  
      strip.setPixelColor(j, strip.Color(r, g, b));
    }
    strip.show();
    delay(wait);
  }

  for(int y=5; y >= 0; y--) {
    // each step
    for(int x=0; x < howmany; x++) {
      int j = randomPixels[x];
      int c = colourChoices[x];
      int red = colours[c][0];
      int green = colours[c][1];
      int blue = colours[c][2];

      int r = red * y; r /= 5;
      int g = green * y; g /= 5;
      int b = blue * y; b /= 5;
      strip.setPixelColor(j, strip.Color(r, g, b));
    }
    strip.show();
    delay(wait);
  }
  
//  // fade in in 5 steps
//  for (uint16_t x=0; x < 5; x++) {
//    // set each pixel
//    for(int z=0; z<5; z++) {  
//      int j = randomPixels[z][0];
//      int c = randomPixels[z][1];
//      int red = colours[c][0];
//      int green = colours[c][1];
//      int blue = colours[c][2];
//
//      Serial.println("-------------");
//      Serial.println("Pixel "); Serial.println(j);
//      Serial.println("red "); Serial.println(red);
//      Serial.println("green "); Serial.println(green);
//      Serial.println("blue "); Serial.println(blue);
//      
//      Serial.println("Setting pixel");
////      int r = pixelRed * (x+1); r /= 5;
////      int g = pixelGreen * (x+1); r /= 5;
////      int b = pixelBlue * (x+1); r /= 5;
//      strip.setPixelColor(j, strip.Color(red, green, blue));
//    }
//    strip.show();
//    delay(1000);
//  }

//  // for each pixel
//  for(uint16_t i=0; i<5; i++) {  
//    int j = randomPixels[i];
//    strip.setPixelColor(j[0], strip.Color(j[1], j[2], j[3]));
//  }
//
//  strip.show();
//  delay(1000);

////   reset each pixel
//  for(uint16_t w=0; w<5; w++) {
//    int j = randomPixels[w];
//    strip.setPixelColor(j, strip.Color(0,0,0));
//  }
//
//  strip.show();
//  delay(1000);
}

