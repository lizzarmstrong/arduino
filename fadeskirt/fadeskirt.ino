#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel strip = Adafruit_NeoPixel(11, 6, NEO_GRB + NEO_KHZ800);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

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

    Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!accel.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }

  
  strip.begin();
  strip.show();

}

void loop() {

  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
  Serial.print("Accel X: "); Serial.print(event.acceleration.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print(event.acceleration.y);       Serial.print(" ");
  Serial.print("Z: "); Serial.print(event.acceleration.z);     Serial.print(" ");

  // Get the magnitude (length) of the 3 axis vector
  // http://en.wikipedia.org/wiki/Euclidean_vector#Length
  double storedVector = event.acceleration.x*event.acceleration.x;
  storedVector += event.acceleration.y*event.acceleration.y;
  storedVector += event.acceleration.z*event.acceleration.z;
  storedVector = sqrt(storedVector);
  Serial.print("Len: "); Serial.println(storedVector);
  
  // wait a bit
  delay(100);
  
  // get new data!
  accel.getEvent(&event);
  double newVector = event.acceleration.x*event.acceleration.x;
  newVector += event.acceleration.y*event.acceleration.y;
  newVector += event.acceleration.z*event.acceleration.z;
  newVector = sqrt(newVector);
  Serial.print("New Len: "); Serial.println(newVector);

  Serial.print("Difference: "); Serial.println(abs(newVector - storedVector));
  
  
  if(abs(newVector - storedVector) > 3) {
    randomizeFade(10);
  } else if (abs(newVector - storedVector) < 1) {
    randomizeFade(100);
  } else {
    randomizeFade(50);
  }
}

void randomizeFade(int wait) {
  int howmany = random(1, 6);
  int randomPixels[howmany];
  int colourChoices[howmany];
  
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
}

