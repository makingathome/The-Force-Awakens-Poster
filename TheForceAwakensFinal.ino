#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// By Steve Moseley at MakingAtHome.com

// Set Variables

// Set count for selection
int COUNT = 0;
int COUNT1 = 0;
int COUNT2 = 0;
int COUNT3 = 0;
int COUNT4 = 0;
int COUNT5 = 0;
int COUNT6 = 0;
int COUNT7 = 0;
int COUNT8 = 0;

int COUNTa = -1;
int COUNTb = -1;
int COUNTc = -1;

long randNumber;

int FADECOUNT = 0;
int FLASHCOUNT = 0;

// MODE is the mode of the display: 1 motion color, 2 on color, 3 motion white, 4 on white, 5 motion sabers, 6 on sabers, 7 motion rainbow, 8 on rainbow
int MODE = 1;

// BR is the brightness of the LEDs, cycle through 100, 150, 200, 250, 50 back to 100
int BR = 250;
// BRPLUS is the brightness increase for button 2 press
int BRPLUS = 50;
// BRMIN is the min brightness level
int BRMIN = 50;
// BRMAX is the max brightness level
int BRMAX = 250;

// LENGTH is the length in seconds that the poster stays on after motion sensor tripping
int LENGTH = 10;
// LENGTHPLUS is the length increase fro a button 3 press
int LENGTHPLUS = 10;
// LENGTHMIN is the min length for the duration
int LENGTHMIN = 10;
// LENGTHMAX is the max length for the duration
int LENGTHMAX = 50;

// Delay for animation timing
int DUR = 50;

// Button Variables
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

// Set the number of the pushbutton pins
const int buttonPinA = 32; // Left Button
const int buttonPinB = 34; // Middle Button
const int buttonPinC = 36; // Right Button

// PIR Sensor variables
int Sensor = 30; // The word "Sensor" can know be used throughout the program and will always reference pin 30
int val = LOW; // "val" will be a variable used to store the state (HIGH or LOW) of the sensor

#define PIN22
// Strip a This is everything except the lightsabers
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip_a = Adafruit_NeoPixel(123, 22, NEO_RGBW + NEO_KHZ800);

#define PIN24
// Strip b FINN This is the strip of 17 for Finns lightsaber
Adafruit_NeoPixel strip_b = Adafruit_NeoPixel(17, 24, NEO_RGBW + NEO_KHZ800);

#define PIN26
// Strip c KYLO This is the strip of 24 for Kylo's light saber and 8 more for the side exhaust
Adafruit_NeoPixel strip_c = Adafruit_NeoPixel(32, 26, NEO_RGBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

//-----------------------------------------------------------------------------------------

void setup() {

  // pinMode(Sensor, INPUT); // And this tells the program that Sensor (pin 30) will be used for input
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinA, INPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(buttonPinC, INPUT);

  strip_a.begin();
  strip_a.show(); // Initialize all pixels to 'off'
  strip_b.begin();
  strip_b.show(); // Initialize all pixels to 'off'
  strip_c.begin();
  strip_c.show(); // Initialize all pixels to 'off'

pinMode(Sensor, INPUT); // And this tells the program that Sensor (pin 30) will be used for input

// Menu to go to correct MODE -----------------------------------------------------------------------------------------
MENU:

// Out of counting and sending to MODE section
if (MODE >= 9){
  MODE = 1;
  goto MODE1;
}
else if (MODE == 1){
  goto MODE1;
}
else if (MODE == 2){
  goto MODE2;
}
else if (MODE == 3){
  goto MODE3;
}
else if (MODE == 4){
  goto MODE4;
}
else if (MODE == 5){
  goto MODE5;
}
else if (MODE == 6){
  goto MODE6;
}
else if (MODE == 7){
  goto MODE7;
}
else if (MODE == 8){
  goto MODE8;
}


// ---------------------------------------------------------------
// Mode 1 - Motion Color ----------------------------------------- GOOD
MODE1:

  flashled();

MODE1A:

  buttons1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }
 

val = digitalRead(Sensor); // To determine if "val" is HIGH or LOW this checks the state of the Sensor (pin 30)
if (val != HIGH) goto MODE1A;

// Finn turn on
  finnon1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

  buttons1();
  
// set count1 to 0
COUNT1 = 0;

// Repeat Finn On 5 times
while(COUNT1 < 5){
  finnonly1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }
  
  buttons1();

 COUNT1++;
}

// Finn on Kylo Turns On
  finnkyloin1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

  buttons1();

// set count1 to 0
COUNT1 = 0;

// Repeat Finn and Kylo on 5 times
while(COUNT1 < 5){
  kylofinn1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

  buttons1();
  
 COUNT1++;
}

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }
  
  buttons1();

  rou3();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

  buttons1();

  rou4();
  
// set count1 to 0
COUNT1 = 0;

while(COUNT1 < LENGTH){

randNumber = random(10);
if (randNumber <= 3){
  rou5();
}
else {
  rou6();
}

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }


// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }


  buttons1();

  staticupdate1();

  COUNT1++;
}

// Fade out everything except light sabers
  rou8();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

  buttons1();

// set count1 to 0
COUNT1 = 0;

// Repeat Finn and Kylo on 5 times
while(COUNT1 < 5){
  kylofinn1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }
  
  buttons1();

 COUNT1++;
}

// Finn on Kylo Turns Off
  finnkylooff1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

  buttons1();

// set count1 to 0
COUNT1 = 0;

// Repeat Finn On 5 times
while(COUNT1 < 5){
  finnonly1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 2;
  goto MENU;
  }

  buttons1();

 COUNT1++;
}

// Finn Turns Off
  finnoff1();

  stripsoff();

  goto MODE1A;



// ---------------------------------------------------------------
// Mode 2 - On Color ---------------------------------------------
MODE2:

  flashled();

MODE2A:

  buttons1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 3;
  goto MENU;
  }

  rou3();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 3;
  goto MENU;
  }

  buttons1();

  rou4();
  
MODE2B:

// set count1 to 0
COUNT2 = 0;

while(COUNT2 < LENGTH){

randNumber = random(10);
if (randNumber <= 3){
  rou5();
}
else {
  rou6();
}


// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }
 

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 3;
  goto MENU;
  }

  buttons1();

  COUNT2++;
}

  goto MODE2B;



// ---------------------------------------------------------------
// Mode 3 - Motion White -----------------------------------------
MODE3:

  flashled();

MODE3A:

  buttons1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 4;
  goto MENU;
  }

// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }
 
val = digitalRead(Sensor); // To determine if "val" is HIGH or LOW this checks the state of the Sensor (pin 30)
if (val != HIGH) goto MODE3A;
else stripsfadein();  // Fade strips in from off to BR

// set count3 to 0
COUNT3 = 0;

while(COUNT3 < LENGTH){
  // Check buttons LENGTH times in a loop

stripson();  // Turn all strips on

  buttons1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 4;
  goto MENU;
  }

  delay (500);

// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }

  COUNT3++;
}

  stripsfadeout();

  stripsoff();

  goto MODE3A;



// ---------------------------------------------------------------
// Mode 4 - On White ---------------------------------------------
MODE4:

  flashled();

MODE4A:

  buttons1();


// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 5;
  goto MENU;
  }

stripson();  // Turn all strips on

// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }

  delay (200);

  goto MODE4A;



// ---------------------------------------------------------------
// Mode 5 - Motion Light Sabers Only -----------------------------
MODE5:

  flashled();

MODE5A:

  buttons1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 6;
  goto MENU;
  }


// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }


val = digitalRead(Sensor); // To determine if "val" is HIGH or LOW this checks the state of the Sensor (pin 30)
if (val != HIGH) goto MODE5A;


// Finn turn on
  finnon1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 6;
  goto MENU;
  }

  buttons1();
  
// set count5 to 0
COUNT5 = 0;

// Repeat Finn On 5 times
while(COUNT5 < 5){
  finnonly1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 6;
  goto MENU;
  }
  
  buttons1();

 COUNT5++;
}

// Finn on Kylo Turns On
  finnkyloin1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 6;
  goto MENU;
  }

  buttons1();

// set count5 to 0
COUNT5 = 0;

// Repeat Finn and Kylo on 5 times
while(COUNT5 < LENGTH){
  kylofinn1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 6;
  goto MENU;
  }

  buttons1();
  
 COUNT5++;
}

// Finn on Kylo Turns Off
  finnkylooff1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 6;
  goto MENU;
  }

  buttons1();

// set count5 to 0
COUNT5 = 0;

// Repeat Finn On 5 times
while(COUNT5 < 5){
  finnonly1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 6;
  goto MENU;
  }

  buttons1();


// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }


 COUNT5++;
}

// Finn Turns Off
  finnoff1();

  stripsoff();

  goto MODE5A;



// ---------------------------------------------------------------
// Mode 6 - On Light Sabers Only --------------------------------- 

MODE6:

  flashled();

MODE6A:

  buttons1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 7;
  goto MENU;
  }

// set count6 to 0
COUNT6 = 0;

// Repeat Finn and Kylo on 5 times
while(COUNT6 < LENGTH){
  kylofinn1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 7;
  goto MENU;
  }

  buttons1();


// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }


 COUNT6++;
}

  goto MODE6A;



// ---------------------------------------------------------------
// Mode 7 - Motion Rainbow ---------------------------------------
MODE7:

  flashled();

MODE7A:

  buttons1();

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 8;
  goto MENU;
  }


// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }


val = digitalRead(Sensor); // To determine if "val" is HIGH or LOW this checks the state of the Sensor (pin 30)
if (val != HIGH) goto MODE7A;

// set count5 to 0
COUNT7 = 0;

// Repeat
while(COUNT7 < LENGTH/2){

// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 8;
  delay (1000);
  goto MENU;
  }

  buttons1();

  rainbowsabers(40);

 COUNT7++;
}

  stripsoff();
  
  goto MODE7A;



// ---------------------------------------------------------------
// Mode 8 - On Rainbow  ------------------------------------------
MODE8:

  flashled();

MODE8A:

  buttons1();


// Reset when all three buttons are pressed
if (digitalRead(buttonPinA) == HIGH && digitalRead(buttonPinB) == HIGH && digitalRead(buttonPinC) == HIGH){
  MODE = 1;
  LENGTH = 10;
  BR = 250;
  goto MENU;
  }


// MODE button check
if (digitalRead(buttonPinA) == HIGH){
  MODE = 1;
  delay (1500);
  goto MENU;
  }

  rainbowsabers(40);

  delay (500);
    
  goto MODE8A;



// ---------------------------------------------------------------
// END OF MODES 
// ---------------------------------------------------------------


pinMode(Sensor, INPUT); // And this tells the program that Sensor (pin 30) will be used for input

  // theaterChase(strip_b.Color(250, 0, 0), 60); // Green

  rainbow(1);


if (MODE == 1)colorWipeb(strip_b.Color(100, 0, 0, 0), 0); // Green - Left Button
else if (MODE == 2)colorWipeb(strip_b.Color(0, 100, 0, 0), 0); // Red - Middle Button
else if (MODE == 3)colorWipeb(strip_b.Color(0, 0, 100, 0), 0); // Blue - Right Button
else if (MODE == 4)colorWipeb(strip_b.Color(0, 0, 0, 100), 0); // White - Motion Sensor


// val = digitalRead(Sensor); // To determine if "val" is HIGH or LOW this checks the state of the Sensor (pin 30)
// if (val == HIGH)colorWipeb(strip_b.Color(0, 0, 0, 100), 5); // White
// if (val == LOW)colorWipeb(strip_b.Color(0, 0, 0, 0), 5); // Off


// if (digitalRead(buttonPinA) == HIGH)colorWipeb(strip_b.Color(100, 0, 0, 0), 5); // Green - Left Button
// if (digitalRead(buttonPinB) == HIGH)colorWipeb(strip_b.Color(0, 100, 0, 0), 5); // Red - Middle Button
// if (digitalRead(buttonPinC) == HIGH)colorWipeb(strip_b.Color(0, 0, 100, 0), 5); // Blue - Right Button


// MODE is the mode of the display: 1 motion color, 2 motion white, 3 on color, 4 on white, 5 motion rainbow, 6 motion light sabers only
// int MODE = 1;
// BR is the brightness of the LEDs, cycle through 100, 150, 200, 250, 50 back to 100
// int BR = 100;
// LENGTH is the length in seconds that the poster stays on after motion sensor tripping
// int LENGTH = 15;

}


// ---------------------------------------------------------------
// Start of the reference loops
// ---------------------------------------------------------------

void brightcheck1() {


// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, 0);
  COUNTb++;
}

  strip_b.show();


// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, BR, 0, 0);
  COUNTb++;
}

  strip_b.show();
  delay (500);
  

// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, 0);
  COUNTb++;
}

  strip_b.show();
  
}


// ============================================================================

void lengthcheck1() {


// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, 0);
  COUNTb++;
}

  strip_b.show();


// set count to -1
  COUNTb = -1;
while(COUNTb < LENGTH/5){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, BR, 0, 0);
  COUNTb++;
}

  strip_b.show();
  delay (1000);
  

// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, 0);
  COUNTb++;
}

  strip_b.show();
  
}


// ============================================================================

void flashled() {

  delay (500);
  stripsoff();  // Turn all strips off

// set flashcount to 0
FLASHCOUNT = 0;

while(FLASHCOUNT < MODE){
  // Flash lights MODE times to inticate the mode that is active

  delay (200);
  stripson();  // Turn all strips on
  delay (200);
  stripsoff();  // Turn all strips off

  FLASHCOUNT++;
}

  delay (500);

}


// ============================================================================

void stripsfadein() {
// Fade strips in from off to BR over BR steps

// set count from 0 to BR
  FADECOUNT = 0;

while(FADECOUNT < BR){

// set count to -1
  COUNTa = -1;

while(COUNTa < 123){
  // Set pixels to 0
  strip_a.setPixelColor(COUNTa, 0, 0, 0, FADECOUNT);
  COUNTa++;
}

// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, FADECOUNT);
  COUNTb++;
}

// set count to -1
  COUNTc = -1;
while(COUNTc < 32){
  // Set pixels to 0
  strip_c.setPixelColor(COUNTc, 0, 0, 0, FADECOUNT);
  COUNTc++;
}

  strip_a.show();
  strip_b.show();
  strip_c.show();

  FADECOUNT++;
 
  delay(1);

}
  
}


// ============================================================================

void stripsfadeout() {
// Fade strips out from BR to off over BR steps

// set count from BR to 0
  FADECOUNT = BR;

while(FADECOUNT > 0){

// set count to -1
  COUNTa = -1;

while(COUNTa < 123){
  // Set pixels to 0
  strip_a.setPixelColor(COUNTa, 0, 0, 0, FADECOUNT);
  COUNTa++;
}

// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, FADECOUNT);
  COUNTb++;
}

// set count to -1
  COUNTc = -1;
while(COUNTc < 32){
  // Set pixels to 0
  strip_c.setPixelColor(COUNTc, 0, 0, 0, FADECOUNT);
  COUNTc++;
}

  strip_a.show();
  strip_b.show();
  strip_c.show();

  FADECOUNT = FADECOUNT - 1;
 
  delay(5);

}
  
}


// ============================================================================

void stripson() {
// Turn all strips on - WORKS


// set count to -1
  COUNTa = -1;

while(COUNTa < 123){
  // Set pixels to 0
  strip_a.setPixelColor(COUNTa, 0, 0, 0, BR);
  COUNTa++;
}

// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, BR);
  COUNTb++;
}

// set count to -1
  COUNTc = -1;
while(COUNTc < 32){
  // Set pixels to 0
  strip_c.setPixelColor(COUNTc, 0, 0, 0, BR);
  COUNTc++;
}

  strip_a.show();
  strip_b.show();
  strip_c.show();
    
}


// ============================================================================

void stripsoff() {
// Turn all strips off - WORKS

// set count to -1
  COUNTa = -1;

while(COUNTa < 123){
  // Set pixels to 0
  strip_a.setPixelColor(COUNTa, 0, 0, 0, 0);
  COUNTa++;
}

// set count to -1
  COUNTb = -1;
while(COUNTb < 17){
  // Set pixels to 0
  strip_b.setPixelColor(COUNTb, 0, 0, 0, 0);
  COUNTb++;
}

// set count to -1
  COUNTc = -1;
while(COUNTc < 32){
  // Set pixels to 0
  strip_c.setPixelColor(COUNTc, 0, 0, 0, 0);
  COUNTc++;
}

  strip_a.show();
  strip_b.show();
  strip_c.show();
  
}


// ============================================================================


// Strip a colorwipe
// Fill the dots one after the other with a color
void colorWipea(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_a.numPixels(); i++) {
    strip_a.setPixelColor(i, c);
    strip_a.show();
    delay(wait);
  }
}


// Strip b colorwipe
// Fill the dots one after the other with a color
void colorWipeb(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_b.numPixels(); i++) {
    strip_b.setPixelColor(i, c);
    strip_b.show();
    delay(wait);
  }
}


// Strip c colorwipe
// Fill the dots one after the other with a color
void colorWipec(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_c.numPixels(); i++) {
    strip_c.setPixelColor(i, c);
    strip_c.show();
    delay(wait);
  }
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip_c.numPixels(); i++) {
      strip_c.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip_c.show();
    delay(wait);
  }
}


void rainbowsabers(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip_c.numPixels(); i++) {
      strip_b.setPixelColor(i, Wheel((i+j) & 255));
      strip_c.setPixelColor(i, Wheel((i+j) & 255));
    }

  if (digitalRead(buttonPinB) == HIGH)BR = BR + BRPLUS; // Increase Briteness

  // Check BR and if over BRMAX reset to BRMIN
  if (BR > BRMAX){
    BR = BRMIN;
  }



    strip_b.show();
    strip_c.show();
    delay(wait);
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip_a.numPixels(); i++) {
      strip_a.setPixelColor(i, Wheel(((i * 256 / strip_a.numPixels()) + j) & 255));
    }
    strip_a.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip_a.numPixels(); i=i+3) {
        strip_b.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip_b.show();

      delay(wait);

      for (uint16_t i=0; i < strip_b.numPixels(); i=i+3) {
        strip_b.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip_a.numPixels(); i=i+3) {
        strip_a.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip_a.show();

      delay(wait);

      for (uint16_t i=0; i < strip_a.numPixels(); i=i+3) {
        strip_a.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip_a.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip_a.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip_a.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


// ============================================================================
// Button read to update variables


void buttons1(){


// button read
if (digitalRead(buttonPinB) == HIGH && BR + BRPLUS <= BRMAX){
  BR = BR + BRPLUS; // Increase Briteness
  brightcheck1();
  delay (1000);
}

else if (digitalRead(buttonPinB) == HIGH && BR + BRPLUS > BRMAX){
  BR = BRMIN; // Increase Briteness
  brightcheck1();
  delay (1000);
}

else if (digitalRead(buttonPinC) == HIGH && LENGTH + LENGTHPLUS <= LENGTHMAX){
  LENGTH = LENGTH + LENGTHPLUS; // Increase Duration of motion loop
  lengthcheck1();
  delay (1000);
  }

else if (digitalRead(buttonPinC) == HIGH && LENGTH + LENGTHPLUS > LENGTHMAX){
  LENGTH = LENGTHMIN; // Increase Duration of motion loop
  lengthcheck1();
  delay (1000);
  }

}


// ============================================================================
// Show all strips and delay by DUR

  void flash() {
  
  strip_a.show();
  strip_b.show();
  strip_c.show();
  delay (DUR);

  }

// ============================================================================
// Animation Routine



void finnon1() {

// Finn Turning On

  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,0,0);
  strip_b.setPixelColor(2,0,0,0,0);
  strip_b.setPixelColor(3,0,0,0,0);
  strip_b.setPixelColor(4,0,0,0,0);
  strip_b.setPixelColor(5,0,0,0,0);
  strip_b.setPixelColor(6,0,0,0,0);
  strip_b.setPixelColor(7,0,0,0,0);
  strip_b.setPixelColor(8,0,0,0,0);
  strip_b.setPixelColor(9,0,0,0,0);
  strip_b.setPixelColor(10,0,0,0,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,0,0);
  strip_b.setPixelColor(5,0,0,0,0);
  strip_b.setPixelColor(6,0,0,0,0);
  strip_b.setPixelColor(7,0,0,0,0);
  strip_b.setPixelColor(8,0,0,0,0);
  strip_b.setPixelColor(9,0,0,0,0);
  strip_b.setPixelColor(10,0,0,0,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,0,0);
  strip_b.setPixelColor(9,0,0,0,0);
  strip_b.setPixelColor(10,0,0,0,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  flash();

}






void finnkyloin1() {

// Finn On and Kylo turns on
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,0,0,0);
  strip_c.setPixelColor(11,0,0,0,0);
  strip_c.setPixelColor(12,0,0,0,0);
  strip_c.setPixelColor(13,0,0,0,0);
  strip_c.setPixelColor(14,0,0,0,0);
  strip_c.setPixelColor(15,0,0,0,0);
  strip_c.setPixelColor(16,0,0,0,0);
  strip_c.setPixelColor(17,0,0,0,0);
  strip_c.setPixelColor(18,0,0,0,0);
  strip_c.setPixelColor(19,0,0,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,0,0,0);
  strip_c.setPixelColor(6,0,0,0,0);
  strip_c.setPixelColor(7,0,0,0,0);
  strip_c.setPixelColor(8,0,0,0,0);
  strip_c.setPixelColor(9,0,0,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,0,0,0);
  strip_c.setPixelColor(11,0,0,0,0);
  strip_c.setPixelColor(12,0,0,0,0);
  strip_c.setPixelColor(13,0,0,0,0);
  strip_c.setPixelColor(14,0,0,0,0);
  strip_c.setPixelColor(15,0,0,0,0);
  strip_c.setPixelColor(16,0,0,0,0);
  strip_c.setPixelColor(17,0,0,0,0);
  strip_c.setPixelColor(18,0,0,0,0);
  strip_c.setPixelColor(19,0,0,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,0,0,0);
  strip_c.setPixelColor(16,0,0,0,0);
  strip_c.setPixelColor(17,0,0,0,0);
  strip_c.setPixelColor(18,0,0,0,0);
  strip_c.setPixelColor(19,0,0,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();

}







void rou3() {

// 3.0 credits, star wars, star killer, and explosion

  strip_a.setPixelColor(0,0,0,0,BR/10);
  strip_a.setPixelColor(1,0,0,0,BR/10);
  strip_a.setPixelColor(10,0,0,0,BR/10);
  strip_a.setPixelColor(11,0,0,0,BR/10);
  strip_a.setPixelColor(111,BR/20,BR/20,0,0);
  strip_a.setPixelColor(112,BR/20,BR/20,0,0);
  strip_a.setPixelColor(113,BR/20,BR/20,0,0);
  strip_a.setPixelColor(114,BR/20,BR/20,0,0);
  strip_a.setPixelColor(115,BR/20,BR/20,0,0);
  strip_a.setPixelColor(116,BR/20,BR/20,0,0);
  strip_a.setPixelColor(117,BR/20,BR/20,0,0);
  strip_a.setPixelColor(118,BR/20,BR/20,0,0);
  strip_a.setPixelColor(119,BR/20,BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,BR/10);
  strip_a.setPixelColor(120,BR/20,BR/20,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(13,0,0,0,BR/10);
  strip_a.setPixelColor(14,0,0,0,BR/10);
  strip_a.setPixelColor(15,0,0,0,BR/10);
  strip_a.setPixelColor(16,0,0,0,BR/10);
  strip_a.setPixelColor(17,0,0,0,BR/10);
  strip_a.setPixelColor(18,0,0,0,BR/10);
  strip_a.setPixelColor(19,0,0,0,BR/10);
  strip_a.setPixelColor(2,0,0,0,BR/10);
  strip_a.setPixelColor(20,0,0,0,BR/10);
  strip_a.setPixelColor(21,0,0,0,BR/10);
  strip_a.setPixelColor(22,0,0,0,BR/10);
  strip_a.setPixelColor(23,0,0,0,BR/10);
  strip_a.setPixelColor(24,0,0,0,BR/10);
  strip_a.setPixelColor(25,0,0,0,BR/10);
  strip_a.setPixelColor(26,0,0,0,BR/10);
  strip_a.setPixelColor(27,0,0,0,BR/10);
  strip_a.setPixelColor(28,0,0,0,BR/10);
  strip_a.setPixelColor(29,0,0,0,BR/10);
  strip_a.setPixelColor(3,0,0,0,BR/10);
  strip_a.setPixelColor(30,0,0,0,BR/10);
  strip_a.setPixelColor(31,0,0,0,BR/10);
  strip_a.setPixelColor(32,0,0,0,BR/10);
  strip_a.setPixelColor(33,0,0,0,BR/10);
  strip_a.setPixelColor(34,0,0,0,0);
  strip_a.setPixelColor(35,0,0,0,0);
  strip_a.setPixelColor(36,0,0,0,0);
  strip_a.setPixelColor(37,0,0,0,0);
  strip_a.setPixelColor(38,0,0,0,0);
  strip_a.setPixelColor(39,0,0,0,0);
  strip_a.setPixelColor(4,0,0,0,BR/10);
  strip_a.setPixelColor(40,0,0,0,0);
  strip_a.setPixelColor(41,0,0,0,0);
  strip_a.setPixelColor(42,0,0,0,0);
  strip_a.setPixelColor(43,0,0,0,0);
  strip_a.setPixelColor(44,0,0,0,0);
  strip_a.setPixelColor(45,0,0,0,0);
  strip_a.setPixelColor(46,0,0,0,0);
  strip_a.setPixelColor(47,0,0,0,0);
  strip_a.setPixelColor(48,0,0,0,0);
  strip_a.setPixelColor(49,0,0,0,0);
  strip_a.setPixelColor(5,0,0,0,BR/10);
  strip_a.setPixelColor(50,0,0,0,0);
  strip_a.setPixelColor(51,0,0,0,0);
  strip_a.setPixelColor(52,0,0,0,0);
  strip_a.setPixelColor(53,0,0,0,0);
  strip_a.setPixelColor(54,0,0,0,0);
  strip_a.setPixelColor(55,0,0,0,0);
  strip_a.setPixelColor(56,0,0,0,0);
  strip_a.setPixelColor(57,0,0,0,0);
  strip_a.setPixelColor(58,0,0,0,0);
  strip_a.setPixelColor(59,0,0,0,0);
  strip_a.setPixelColor(6,0,0,0,BR/10);
  strip_a.setPixelColor(60,0,0,0,0);
  strip_a.setPixelColor(61,0,0,0,0);
  strip_a.setPixelColor(62,0,0,0,0);
  strip_a.setPixelColor(63,0,0,0,0);
  strip_a.setPixelColor(64,0,0,0,0);
  strip_a.setPixelColor(65,0,0,0,0);
  strip_a.setPixelColor(66,0,0,0,0);
  strip_a.setPixelColor(67,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,BR/10);
  strip_a.setPixelColor(8,0,0,0,BR/10);
  strip_a.setPixelColor(9,0,0,0,BR/10);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,5*BR/8,0,0);
  strip_c.setPixelColor(1,0,5*BR/8,0,0);
  strip_c.setPixelColor(10,0,5*BR/8,0,0);
  strip_c.setPixelColor(11,0,5*BR/8,0,0);
  strip_c.setPixelColor(12,0,5*BR/8,0,0);
  strip_c.setPixelColor(13,0,5*BR/8,0,0);
  strip_c.setPixelColor(14,0,5*BR/8,0,0);
  strip_c.setPixelColor(15,0,5*BR/8,0,0);
  strip_c.setPixelColor(16,0,5*BR/8,0,0);
  strip_c.setPixelColor(17,0,5*BR/8,0,0);
  strip_c.setPixelColor(18,0,5*BR/8,0,0);
  strip_c.setPixelColor(19,0,5*BR/8,0,0);
  strip_c.setPixelColor(2,0,5*BR/8,0,0);
  strip_c.setPixelColor(20,0,5*BR/8,0,0);
  strip_c.setPixelColor(21,0,5*BR/8,0,0);
  strip_c.setPixelColor(22,0,5*BR/8,0,0);
  strip_c.setPixelColor(23,0,5*BR/8,0,0);
  strip_c.setPixelColor(24,0,5*BR/8,0,0);
  strip_c.setPixelColor(25,0,5*BR/8,0,0);
  strip_c.setPixelColor(26,0,5*BR/8,0,0);
  strip_c.setPixelColor(27,0,5*BR/8,0,0);
  strip_c.setPixelColor(28,0,5*BR/8,0,0);
  strip_c.setPixelColor(29,0,5*BR/8,0,0);
  strip_c.setPixelColor(3,0,5*BR/8,0,0);
  strip_c.setPixelColor(30,0,5*BR/8,0,0);
  strip_c.setPixelColor(31,0,5*BR/8,0,0);
  strip_c.setPixelColor(4,0,5*BR/8,0,0);
  strip_c.setPixelColor(5,0,5*BR/8,0,0);
  strip_c.setPixelColor(6,0,5*BR/8,0,0);
  strip_c.setPixelColor(7,0,5*BR/8,0,0);
  strip_c.setPixelColor(8,0,5*BR/8,0,0);
  strip_c.setPixelColor(9,0,5*BR/8,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,BR/5);
  strip_a.setPixelColor(1,0,0,0,BR/5);
  strip_a.setPixelColor(10,0,0,0,BR/5);
  strip_a.setPixelColor(11,0,0,0,BR/5);
  strip_a.setPixelColor(111,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(112,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(113,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(114,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(115,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(116,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(117,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(118,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(119,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,BR/5);
  strip_a.setPixelColor(120,2*BR/20,2*BR/20,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,BR/5);
  strip_a.setPixelColor(14,0,0,0,BR/5);
  strip_a.setPixelColor(15,0,0,0,BR/5);
  strip_a.setPixelColor(16,0,0,0,BR/5);
  strip_a.setPixelColor(17,0,0,0,BR/5);
  strip_a.setPixelColor(18,0,0,0,BR/5);
  strip_a.setPixelColor(19,0,0,0,BR/5);
  strip_a.setPixelColor(2,0,0,0,BR/5);
  strip_a.setPixelColor(20,0,0,0,BR/5);
  strip_a.setPixelColor(21,0,0,0,BR/5);
  strip_a.setPixelColor(22,0,0,0,BR/5);
  strip_a.setPixelColor(23,0,0,0,BR/5);
  strip_a.setPixelColor(24,0,0,0,BR/5);
  strip_a.setPixelColor(25,0,0,0,BR/5);
  strip_a.setPixelColor(26,0,0,0,BR/5);
  strip_a.setPixelColor(27,0,0,0,BR/5);
  strip_a.setPixelColor(28,0,0,0,BR/5);
  strip_a.setPixelColor(29,0,0,0,BR/5);
  strip_a.setPixelColor(3,0,0,0,BR/5);
  strip_a.setPixelColor(30,0,0,0,BR/5);
  strip_a.setPixelColor(31,0,0,0,BR/5);
  strip_a.setPixelColor(32,0,0,0,BR/5);
  strip_a.setPixelColor(33,0,0,0,BR/5);
  strip_a.setPixelColor(34,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(35,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(36,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(37,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(38,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(39,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(4,0,0,0,BR/5);
  strip_a.setPixelColor(40,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(41,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(42,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(43,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(44,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(45,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(46,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(47,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(48,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(49,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(5,0,0,0,BR/5);
  strip_a.setPixelColor(50,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(51,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(52,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(53,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(54,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(55,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(56,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(57,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(58,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(59,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(6,0,0,0,BR/5);
  strip_a.setPixelColor(60,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(61,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(62,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(63,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(64,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(65,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(66,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(67,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(7,0,0,0,BR/5);
  strip_a.setPixelColor(8,0,0,0,BR/5);
  strip_a.setPixelColor(9,0,0,0,BR/5);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,3*(BR/10));
  strip_a.setPixelColor(1,0,0,0,3*(BR/10));
  strip_a.setPixelColor(10,0,0,0,3*(BR/10));
  strip_a.setPixelColor(11,0,0,0,3*(BR/10));
  strip_a.setPixelColor(111,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(112,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(113,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(114,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(115,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(116,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(117,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(118,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(119,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,3*(BR/10));
  strip_a.setPixelColor(120,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,3*(BR/10));
  strip_a.setPixelColor(14,0,0,0,3*(BR/10));
  strip_a.setPixelColor(15,0,0,0,3*(BR/10));
  strip_a.setPixelColor(16,0,0,0,3*(BR/10));
  strip_a.setPixelColor(17,0,0,0,3*(BR/10));
  strip_a.setPixelColor(18,0,0,0,3*(BR/10));
  strip_a.setPixelColor(19,0,0,0,3*(BR/10));
  strip_a.setPixelColor(2,0,0,0,3*(BR/10));
  strip_a.setPixelColor(20,0,0,0,3*(BR/10));
  strip_a.setPixelColor(21,0,0,0,3*(BR/10));
  strip_a.setPixelColor(22,0,0,0,3*(BR/10));
  strip_a.setPixelColor(23,0,0,0,3*(BR/10));
  strip_a.setPixelColor(24,0,0,0,3*(BR/10));
  strip_a.setPixelColor(25,0,0,0,3*(BR/10));
  strip_a.setPixelColor(26,0,0,0,3*(BR/10));
  strip_a.setPixelColor(27,0,0,0,3*(BR/10));
  strip_a.setPixelColor(28,0,0,0,3*(BR/10));
  strip_a.setPixelColor(29,0,0,0,3*(BR/10));
  strip_a.setPixelColor(3,0,0,0,3*(BR/10));
  strip_a.setPixelColor(30,0,0,0,3*(BR/10));
  strip_a.setPixelColor(31,0,0,0,3*(BR/10));
  strip_a.setPixelColor(32,0,0,0,3*(BR/10));
  strip_a.setPixelColor(33,0,0,0,3*(BR/10));
  strip_a.setPixelColor(34,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(35,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(36,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(37,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(38,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(39,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(4,0,0,0,3*(BR/10));
  strip_a.setPixelColor(40,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(41,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(42,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(43,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(44,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(45,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(46,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(47,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(48,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(49,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(5,0,0,0,3*(BR/10));
  strip_a.setPixelColor(50,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(51,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(52,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(53,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(54,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(55,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(56,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(57,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(58,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(59,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(6,0,0,0,3*(BR/10));
  strip_a.setPixelColor(60,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(61,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(62,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(63,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(64,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(65,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(66,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(67,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(7,0,0,0,3*(BR/10));
  strip_a.setPixelColor(8,0,0,0,3*(BR/10));
  strip_a.setPixelColor(9,0,0,0,3*(BR/10));
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,2*(BR/5));
  strip_a.setPixelColor(1,0,0,0,2*(BR/5));
  strip_a.setPixelColor(10,0,0,0,2*(BR/5));
  strip_a.setPixelColor(11,0,0,0,2*(BR/5));
  strip_a.setPixelColor(111,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(112,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(113,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(114,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(115,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(116,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(117,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(118,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(119,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,2*(BR/5));
  strip_a.setPixelColor(120,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,2*(BR/5));
  strip_a.setPixelColor(14,0,0,0,2*(BR/5));
  strip_a.setPixelColor(15,0,0,0,2*(BR/5));
  strip_a.setPixelColor(16,0,0,0,2*(BR/5));
  strip_a.setPixelColor(17,0,0,0,2*(BR/5));
  strip_a.setPixelColor(18,0,0,0,2*(BR/5));
  strip_a.setPixelColor(19,0,0,0,2*(BR/5));
  strip_a.setPixelColor(2,0,0,0,2*(BR/5));
  strip_a.setPixelColor(20,0,0,0,2*(BR/5));
  strip_a.setPixelColor(21,0,0,0,2*(BR/5));
  strip_a.setPixelColor(22,0,0,0,2*(BR/5));
  strip_a.setPixelColor(23,0,0,0,2*(BR/5));
  strip_a.setPixelColor(24,0,0,0,2*(BR/5));
  strip_a.setPixelColor(25,0,0,0,2*(BR/5));
  strip_a.setPixelColor(26,0,0,0,2*(BR/5));
  strip_a.setPixelColor(27,0,0,0,2*(BR/5));
  strip_a.setPixelColor(28,0,0,0,2*(BR/5));
  strip_a.setPixelColor(29,0,0,0,2*(BR/5));
  strip_a.setPixelColor(3,0,0,0,2*(BR/5));
  strip_a.setPixelColor(30,0,0,0,2*(BR/5));
  strip_a.setPixelColor(31,0,0,0,2*(BR/5));
  strip_a.setPixelColor(32,0,0,0,2*(BR/5));
  strip_a.setPixelColor(33,0,0,0,2*(BR/5));
  strip_a.setPixelColor(34,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(35,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(36,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(37,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(38,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(39,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(4,0,0,0,2*(BR/5));
  strip_a.setPixelColor(40,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(41,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(42,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(43,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(44,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(45,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(46,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(47,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(48,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(49,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(5,0,0,0,2*(BR/5));
  strip_a.setPixelColor(50,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(51,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(52,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(53,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(54,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(55,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(56,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(57,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(58,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(59,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(6,0,0,0,2*(BR/5));
  strip_a.setPixelColor(60,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(61,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(62,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(63,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(64,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(65,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(66,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(67,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(7,0,0,0,2*(BR/5));
  strip_a.setPixelColor(8,0,0,0,2*(BR/5));
  strip_a.setPixelColor(9,0,0,0,2*(BR/5));
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,BR/2);
  strip_a.setPixelColor(1,0,0,0,BR/2);
  strip_a.setPixelColor(10,0,0,0,BR/2);
  strip_a.setPixelColor(11,0,0,0,BR/2);
  strip_a.setPixelColor(111,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(112,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(113,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(114,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(115,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(116,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(117,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(118,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(119,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,BR/2);
  strip_a.setPixelColor(120,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(121,0,BR,0,0);
  strip_a.setPixelColor(122,0,BR,0,0);
  strip_a.setPixelColor(13,0,0,0,BR/2);
  strip_a.setPixelColor(14,0,0,0,BR/2);
  strip_a.setPixelColor(15,0,0,0,BR/2);
  strip_a.setPixelColor(16,0,0,0,BR/2);
  strip_a.setPixelColor(17,0,0,0,BR/2);
  strip_a.setPixelColor(18,0,0,0,BR/2);
  strip_a.setPixelColor(19,0,0,0,BR/2);
  strip_a.setPixelColor(2,0,0,0,BR/2);
  strip_a.setPixelColor(20,0,0,0,BR/2);
  strip_a.setPixelColor(21,0,0,0,BR/2);
  strip_a.setPixelColor(22,0,0,0,BR/2);
  strip_a.setPixelColor(23,0,0,0,BR/2);
  strip_a.setPixelColor(24,0,0,0,BR/2);
  strip_a.setPixelColor(25,0,0,0,BR/2);
  strip_a.setPixelColor(26,0,0,0,BR/2);
  strip_a.setPixelColor(27,0,0,0,BR/2);
  strip_a.setPixelColor(28,0,0,0,BR/2);
  strip_a.setPixelColor(29,0,0,0,BR/2);
  strip_a.setPixelColor(3,0,0,0,BR/2);
  strip_a.setPixelColor(30,0,0,0,BR/2);
  strip_a.setPixelColor(31,0,0,0,BR/2);
  strip_a.setPixelColor(32,0,0,0,BR/2);
  strip_a.setPixelColor(33,0,0,0,BR/2);
  strip_a.setPixelColor(34,BR,BR,0,0);
  strip_a.setPixelColor(35,BR,BR,0,0);
  strip_a.setPixelColor(36,BR,BR,0,0);
  strip_a.setPixelColor(37,BR,BR,0,0);
  strip_a.setPixelColor(38,BR,BR,0,0);
  strip_a.setPixelColor(39,BR,BR,0,0);
  strip_a.setPixelColor(4,0,0,0,BR/2);
  strip_a.setPixelColor(40,BR,BR,0,0);
  strip_a.setPixelColor(41,BR,BR,0,0);
  strip_a.setPixelColor(42,BR,BR,0,0);
  strip_a.setPixelColor(43,BR,BR,0,0);
  strip_a.setPixelColor(44,BR,BR,0,0);
  strip_a.setPixelColor(45,BR,BR,0,0);
  strip_a.setPixelColor(46,BR,BR,0,0);
  strip_a.setPixelColor(47,BR,BR,0,0);
  strip_a.setPixelColor(48,BR,BR,0,0);
  strip_a.setPixelColor(49,BR,BR,0,0);
  strip_a.setPixelColor(5,0,0,0,BR/2);
  strip_a.setPixelColor(50,BR,BR,0,0);
  strip_a.setPixelColor(51,BR,BR,0,0);
  strip_a.setPixelColor(52,BR,BR,0,0);
  strip_a.setPixelColor(53,BR,BR,0,0);
  strip_a.setPixelColor(54,BR,BR,0,0);
  strip_a.setPixelColor(55,BR,BR,0,0);
  strip_a.setPixelColor(56,BR,BR,0,0);
  strip_a.setPixelColor(57,BR,BR,0,0);
  strip_a.setPixelColor(58,BR,BR,0,0);
  strip_a.setPixelColor(59,BR,BR,0,0);
  strip_a.setPixelColor(6,0,0,0,BR/2);
  strip_a.setPixelColor(60,BR,BR,0,0);
  strip_a.setPixelColor(61,BR,BR,0,0);
  strip_a.setPixelColor(62,BR,BR,0,0);
  strip_a.setPixelColor(63,BR,BR,0,0);
  strip_a.setPixelColor(64,BR,BR,0,0);
  strip_a.setPixelColor(65,BR,BR,0,0);
  strip_a.setPixelColor(66,BR,BR,0,0);
  strip_a.setPixelColor(67,BR,BR,0,0);
  strip_a.setPixelColor(7,0,0,0,BR/2);
  strip_a.setPixelColor(8,0,0,0,BR/2);
  strip_a.setPixelColor(9,0,0,0,BR/2);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,3*(BR/5));
  strip_a.setPixelColor(1,0,0,0,3*(BR/5));
  strip_a.setPixelColor(10,0,0,0,3*(BR/5));
  strip_a.setPixelColor(11,0,0,0,3*(BR/5));
  strip_a.setPixelColor(111,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(112,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(113,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(114,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(115,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(116,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(117,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(118,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(119,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,3*(BR/5));
  strip_a.setPixelColor(120,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,3*(BR/5));
  strip_a.setPixelColor(14,0,0,0,3*(BR/5));
  strip_a.setPixelColor(15,0,0,0,3*(BR/5));
  strip_a.setPixelColor(16,0,0,0,3*(BR/5));
  strip_a.setPixelColor(17,0,0,0,3*(BR/5));
  strip_a.setPixelColor(18,0,0,0,3*(BR/5));
  strip_a.setPixelColor(19,0,0,0,3*(BR/5));
  strip_a.setPixelColor(2,0,0,0,3*(BR/5));
  strip_a.setPixelColor(20,0,0,0,3*(BR/5));
  strip_a.setPixelColor(21,0,0,0,3*(BR/5));
  strip_a.setPixelColor(22,0,0,0,3*(BR/5));
  strip_a.setPixelColor(23,0,0,0,3*(BR/5));
  strip_a.setPixelColor(24,0,0,0,3*(BR/5));
  strip_a.setPixelColor(25,0,0,0,3*(BR/5));
  strip_a.setPixelColor(26,0,0,0,3*(BR/5));
  strip_a.setPixelColor(27,0,0,0,3*(BR/5));
  strip_a.setPixelColor(28,0,0,0,3*(BR/5));
  strip_a.setPixelColor(29,0,0,0,3*(BR/5));
  strip_a.setPixelColor(3,0,0,0,3*(BR/5));
  strip_a.setPixelColor(30,0,0,0,3*(BR/5));
  strip_a.setPixelColor(31,0,0,0,3*(BR/5));
  strip_a.setPixelColor(32,0,0,0,3*(BR/5));
  strip_a.setPixelColor(33,0,0,0,3*(BR/5));
  strip_a.setPixelColor(4,0,0,0,3*(BR/5));
  strip_a.setPixelColor(5,0,0,0,3*(BR/5));
  strip_a.setPixelColor(6,0,0,0,3*(BR/5));
  strip_a.setPixelColor(7,0,0,0,3*(BR/5));
  strip_a.setPixelColor(8,0,0,0,3*(BR/5));
  strip_a.setPixelColor(9,0,0,0,3*(BR/5));
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,7*(BR/10));
  strip_a.setPixelColor(1,0,0,0,7*(BR/10));
  strip_a.setPixelColor(10,0,0,0,7*(BR/10));
  strip_a.setPixelColor(11,0,0,0,7*(BR/10));
  strip_a.setPixelColor(111,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(112,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(113,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(114,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(115,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(116,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(117,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(118,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(119,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,7*(BR/10));
  strip_a.setPixelColor(120,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,7*(BR/10));
  strip_a.setPixelColor(14,0,0,0,7*(BR/10));
  strip_a.setPixelColor(15,0,0,0,7*(BR/10));
  strip_a.setPixelColor(16,0,0,0,7*(BR/10));
  strip_a.setPixelColor(17,0,0,0,7*(BR/10));
  strip_a.setPixelColor(18,0,0,0,7*(BR/10));
  strip_a.setPixelColor(19,0,0,0,7*(BR/10));
  strip_a.setPixelColor(2,0,0,0,7*(BR/10));
  strip_a.setPixelColor(20,0,0,0,7*(BR/10));
  strip_a.setPixelColor(21,0,0,0,7*(BR/10));
  strip_a.setPixelColor(22,0,0,0,7*(BR/10));
  strip_a.setPixelColor(23,0,0,0,7*(BR/10));
  strip_a.setPixelColor(24,0,0,0,7*(BR/10));
  strip_a.setPixelColor(25,0,0,0,7*(BR/10));
  strip_a.setPixelColor(26,0,0,0,7*(BR/10));
  strip_a.setPixelColor(27,0,0,0,7*(BR/10));
  strip_a.setPixelColor(28,0,0,0,7*(BR/10));
  strip_a.setPixelColor(29,0,0,0,7*(BR/10));
  strip_a.setPixelColor(3,0,0,0,7*(BR/10));
  strip_a.setPixelColor(30,0,0,0,7*(BR/10));
  strip_a.setPixelColor(31,0,0,0,7*(BR/10));
  strip_a.setPixelColor(32,0,0,0,7*(BR/10));
  strip_a.setPixelColor(33,0,0,0,7*(BR/10));
  strip_a.setPixelColor(4,0,0,0,7*(BR/10));
  strip_a.setPixelColor(5,0,0,0,7*(BR/10));
  strip_a.setPixelColor(6,0,0,0,7*(BR/10));
  strip_a.setPixelColor(7,0,0,0,7*(BR/10));
  strip_a.setPixelColor(8,0,0,0,7*(BR/10));
  strip_a.setPixelColor(9,0,0,0,7*(BR/10));
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,4*(BR/5));
  strip_a.setPixelColor(1,0,0,0,4*(BR/5));
  strip_a.setPixelColor(10,0,0,0,4*(BR/5));
  strip_a.setPixelColor(11,0,0,0,4*(BR/5));
  strip_a.setPixelColor(111,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(112,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(113,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(114,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(115,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(116,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(117,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(118,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(119,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,4*(BR/5));
  strip_a.setPixelColor(120,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,4*(BR/5));
  strip_a.setPixelColor(14,0,0,0,4*(BR/5));
  strip_a.setPixelColor(15,0,0,0,4*(BR/5));
  strip_a.setPixelColor(16,0,0,0,4*(BR/5));
  strip_a.setPixelColor(17,0,0,0,4*(BR/5));
  strip_a.setPixelColor(18,0,0,0,4*(BR/5));
  strip_a.setPixelColor(19,0,0,0,4*(BR/5));
  strip_a.setPixelColor(2,0,0,0,4*(BR/5));
  strip_a.setPixelColor(20,0,0,0,4*(BR/5));
  strip_a.setPixelColor(21,0,0,0,4*(BR/5));
  strip_a.setPixelColor(22,0,0,0,4*(BR/5));
  strip_a.setPixelColor(23,0,0,0,4*(BR/5));
  strip_a.setPixelColor(24,0,0,0,4*(BR/5));
  strip_a.setPixelColor(25,0,0,0,4*(BR/5));
  strip_a.setPixelColor(26,0,0,0,4*(BR/5));
  strip_a.setPixelColor(27,0,0,0,4*(BR/5));
  strip_a.setPixelColor(28,0,0,0,4*(BR/5));
  strip_a.setPixelColor(29,0,0,0,4*(BR/5));
  strip_a.setPixelColor(3,0,0,0,4*(BR/5));
  strip_a.setPixelColor(30,0,0,0,4*(BR/5));
  strip_a.setPixelColor(31,0,0,0,4*(BR/5));
  strip_a.setPixelColor(32,0,0,0,4*(BR/5));
  strip_a.setPixelColor(33,0,0,0,4*(BR/5));
  strip_a.setPixelColor(4,0,0,0,4*(BR/5));
  strip_a.setPixelColor(5,0,0,0,4*(BR/5));
  strip_a.setPixelColor(6,0,0,0,4*(BR/5));
  strip_a.setPixelColor(7,0,0,0,4*(BR/5));
  strip_a.setPixelColor(8,0,0,0,4*(BR/5));
  strip_a.setPixelColor(9,0,0,0,4*(BR/5));
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,9*(BR/10));
  strip_a.setPixelColor(1,0,0,0,9*(BR/10));
  strip_a.setPixelColor(10,0,0,0,9*(BR/10));
  strip_a.setPixelColor(11,0,0,0,9*(BR/10));
  strip_a.setPixelColor(111,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(112,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(113,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(114,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(115,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(116,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(117,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(118,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(119,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,9*(BR/10));
  strip_a.setPixelColor(120,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(13,0,0,0,9*(BR/10));
  strip_a.setPixelColor(14,0,0,0,9*(BR/10));
  strip_a.setPixelColor(15,0,0,0,9*(BR/10));
  strip_a.setPixelColor(16,0,0,0,9*(BR/10));
  strip_a.setPixelColor(17,0,0,0,9*(BR/10));
  strip_a.setPixelColor(18,0,0,0,9*(BR/10));
  strip_a.setPixelColor(19,0,0,0,9*(BR/10));
  strip_a.setPixelColor(2,0,0,0,9*(BR/10));
  strip_a.setPixelColor(20,0,0,0,9*(BR/10));
  strip_a.setPixelColor(21,0,0,0,9*(BR/10));
  strip_a.setPixelColor(22,0,0,0,9*(BR/10));
  strip_a.setPixelColor(23,0,0,0,9*(BR/10));
  strip_a.setPixelColor(24,0,0,0,9*(BR/10));
  strip_a.setPixelColor(25,0,0,0,9*(BR/10));
  strip_a.setPixelColor(26,0,0,0,9*(BR/10));
  strip_a.setPixelColor(27,0,0,0,9*(BR/10));
  strip_a.setPixelColor(28,0,0,0,9*(BR/10));
  strip_a.setPixelColor(29,0,0,0,9*(BR/10));
  strip_a.setPixelColor(3,0,0,0,9*(BR/10));
  strip_a.setPixelColor(30,0,0,0,9*(BR/10));
  strip_a.setPixelColor(31,0,0,0,9*(BR/10));
  strip_a.setPixelColor(32,0,0,0,9*(BR/10));
  strip_a.setPixelColor(33,0,0,0,9*(BR/10));
  strip_a.setPixelColor(4,0,0,0,9*(BR/10));
  strip_a.setPixelColor(5,0,0,0,9*(BR/10));
  strip_a.setPixelColor(6,0,0,0,9*(BR/10));
  strip_a.setPixelColor(7,0,0,0,9*(BR/10));
  strip_a.setPixelColor(8,0,0,0,9*(BR/10));
  strip_a.setPixelColor(9,0,0,0,9*(BR/10));
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,BR);
  strip_a.setPixelColor(1,0,0,0,BR);
  strip_a.setPixelColor(10,0,0,0,BR);
  strip_a.setPixelColor(11,0,0,0,BR);
  strip_a.setPixelColor(111,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(112,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(113,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(114,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(115,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(116,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(117,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(118,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(119,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,BR);
  strip_a.setPixelColor(120,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(121,0,0,0,0);
  strip_a.setPixelColor(122,0,0,0,0);
  strip_a.setPixelColor(13,0,0,0,BR);
  strip_a.setPixelColor(14,0,0,0,BR);
  strip_a.setPixelColor(15,0,0,0,BR);
  strip_a.setPixelColor(16,0,0,0,BR);
  strip_a.setPixelColor(17,0,0,0,BR);
  strip_a.setPixelColor(18,0,0,0,BR);
  strip_a.setPixelColor(19,0,0,0,BR);
  strip_a.setPixelColor(2,0,0,0,BR);
  strip_a.setPixelColor(20,0,0,0,BR);
  strip_a.setPixelColor(21,0,0,0,BR);
  strip_a.setPixelColor(22,0,0,0,BR);
  strip_a.setPixelColor(23,0,0,0,BR);
  strip_a.setPixelColor(24,0,0,0,BR);
  strip_a.setPixelColor(25,0,0,0,BR);
  strip_a.setPixelColor(26,0,0,0,BR);
  strip_a.setPixelColor(27,0,0,0,BR);
  strip_a.setPixelColor(28,0,0,0,BR);
  strip_a.setPixelColor(29,0,0,0,BR);
  strip_a.setPixelColor(3,0,0,0,BR);
  strip_a.setPixelColor(30,0,0,0,BR);
  strip_a.setPixelColor(31,0,0,0,BR);
  strip_a.setPixelColor(32,0,0,0,BR);
  strip_a.setPixelColor(33,0,0,0,BR);
  strip_a.setPixelColor(4,0,0,0,BR);
  strip_a.setPixelColor(5,0,0,0,BR);
  strip_a.setPixelColor(6,0,0,0,BR);
  strip_a.setPixelColor(7,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,BR);
  strip_a.setPixelColor(9,0,0,0,BR);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();

}







void rou4() {

// 4.0 Force Awakens

  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,0);
  strip_a.setPixelColor(73,0,0,0,0);
  strip_a.setPixelColor(74,0,0,0,0);
  strip_a.setPixelColor(75,0,0,0,BR/4);
  strip_a.setPixelColor(76,0,0,0,BR/2);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR/2);
  strip_a.setPixelColor(79,0,0,0,BR/4);
  strip_a.setPixelColor(80,0,0,0,0);
  strip_a.setPixelColor(81,0,0,0,0);
  strip_a.setPixelColor(82,0,0,0,0);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,0);
  strip_a.setPixelColor(73,0,0,0,0);
  strip_a.setPixelColor(74,0,0,0,BR/4);
  strip_a.setPixelColor(75,0,0,0,BR/2);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR/2);
  strip_a.setPixelColor(80,0,0,0,BR/4);
  strip_a.setPixelColor(81,0,0,0,0);
  strip_a.setPixelColor(82,0,0,0,0);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,0);
  strip_a.setPixelColor(73,0,0,0,BR/4);
  strip_a.setPixelColor(74,0,0,0,BR/2);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR/2);
  strip_a.setPixelColor(81,0,0,0,BR/4);
  strip_a.setPixelColor(82,0,0,0,0);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,BR/4);
  strip_a.setPixelColor(73,0,0,0,BR/2);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR/2);
  strip_a.setPixelColor(82,0,0,0,BR/4);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(121,0,BR,0,0);
  strip_a.setPixelColor(122,0,BR,0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,BR/4);
  strip_a.setPixelColor(72,0,0,0,BR/2);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR/2);
  strip_a.setPixelColor(83,0,0,0,BR/4);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(70,0,0,0,BR/4);
  strip_a.setPixelColor(71,0,0,0,BR/2);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR/2);
  strip_a.setPixelColor(84,0,0,0,BR/4);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,BR/4);
  strip_a.setPixelColor(70,0,0,0,BR/2);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR/2);
  strip_a.setPixelColor(85,0,0,0,BR/4);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(68,0,0,0,BR/4);
  strip_a.setPixelColor(69,0,0,0,BR/2);
  strip_a.setPixelColor(70,0,0,0,BR);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR);
  strip_a.setPixelColor(85,0,0,0,BR/2);
  strip_a.setPixelColor(86,0,0,0,BR/4);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(68,0,0,0,BR/2);
  strip_a.setPixelColor(69,0,0,0,BR);
  strip_a.setPixelColor(70,0,0,0,BR);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR);
  strip_a.setPixelColor(85,0,0,0,BR);
  strip_a.setPixelColor(86,0,0,0,BR/2);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(121,0,0,0,0);
  strip_a.setPixelColor(122,0,0,0,0);
  strip_a.setPixelColor(68,0,0,0,BR);
  strip_a.setPixelColor(69,0,0,0,BR);
  strip_a.setPixelColor(70,0,0,0,BR);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR);
  strip_a.setPixelColor(85,0,0,0,BR);
  strip_a.setPixelColor(86,0,0,0,BR);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();

}






void rou5() {

// 5.0 all on, tie fighter shots, xwing

  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,BR,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,BR,0,0,0);
  strip_a.setPixelColor(90,BR,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/2,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/2,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR/2,0,0);
  strip_a.setPixelColor(109,0,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,BR/2,0,0,0);
  strip_a.setPixelColor(90,BR,0,0,0);
  strip_a.setPixelColor(91,BR,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/4,BR,0,0);
  strip_a.setPixelColor(99,BR/2,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,BR/4,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,BR/2,0,0,0);
  strip_a.setPixelColor(91,BR,0,0,0);
  strip_a.setPixelColor(92,BR,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,0,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR/2,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,BR/4,BR/2,0,0);
  strip_a.setPixelColor(121,0,BR,0,0);
  strip_a.setPixelColor(122,0,BR,0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,BR/2,0,0,0);
  strip_a.setPixelColor(92,BR,0,0,0);
  strip_a.setPixelColor(93,BR,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,BR/2,0,0,0);
  strip_a.setPixelColor(93,BR,0,0,0);
  strip_a.setPixelColor(94,BR,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(87,BR,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,BR/2,0,0,0);
  strip_a.setPixelColor(94,BR,0,0,0);
  strip_a.setPixelColor(95,BR,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/2,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/2,BR,0,0);
  strip_a.setPixelColor(106,0,BR/2,0,0);
  strip_a.setPixelColor(107,BR/2,BR,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(87,BR/2,0,0,0);
  strip_a.setPixelColor(88,BR,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,BR/2,0,0,0);
  strip_a.setPixelColor(95,BR,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,0,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR,0,0);
  strip_a.setPixelColor(99,BR/2,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,BR/2,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,BR/2,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/2,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,BR/2,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,0,0,0);
  strip_a.setPixelColor(122,0,0,0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,0,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();

}







void rou6() {

// 6.0 All On

  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/2,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/2,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR/2,0,0);
  strip_a.setPixelColor(109,0,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/4,BR,0,0);
  strip_a.setPixelColor(99,BR/2,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,BR/4,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,0,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR/2,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,BR/4,BR/2,0,0);
  strip_a.setPixelColor(121,0,BR,0,0);
  strip_a.setPixelColor(122,0,BR,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/2,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/2,BR,0,0);
  strip_a.setPixelColor(106,0,BR/2,0,0);
  strip_a.setPixelColor(107,BR/2,BR,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,0,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR,0,0);
  strip_a.setPixelColor(99,BR/2,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/2,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,BR/2,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,0,0,0);
  strip_a.setPixelColor(122,0,0,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,0,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();

}







void rou7() {

// 7.0 all on, tie fighter shots, xwing

  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(87,BR,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,BR,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(87,BR/2,0,0,0);
  strip_a.setPixelColor(88,BR,0,0,0);
  strip_a.setPixelColor(89,BR,0,0,0);
  strip_a.setPixelColor(90,BR,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/2,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/2,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR/2,0,0);
  strip_a.setPixelColor(109,0,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,BR/2,0,0,0);
  strip_a.setPixelColor(89,BR/2,0,0,0);
  strip_a.setPixelColor(90,BR,0,0,0);
  strip_a.setPixelColor(91,BR,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/4,BR,0,0);
  strip_a.setPixelColor(99,BR/2,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,BR/4,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,BR/2,0,0,0);
  strip_a.setPixelColor(91,BR,0,0,0);
  strip_a.setPixelColor(92,BR,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,0,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR/2,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,BR/4,BR/2,0,0);
  strip_a.setPixelColor(121,0,BR,0,0);
  strip_a.setPixelColor(122,0,BR,0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,BR/2,0,0,0);
  strip_a.setPixelColor(92,BR,0,0,0);
  strip_a.setPixelColor(93,BR,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,BR/2,0,0,0);
  strip_a.setPixelColor(93,BR,0,0,0);
  strip_a.setPixelColor(94,BR,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(87,BR,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,BR/2,0,0,0);
  strip_a.setPixelColor(94,BR,0,0,0);
  strip_a.setPixelColor(95,BR,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/2,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/2,BR,0,0);
  strip_a.setPixelColor(106,0,BR/2,0,0);
  strip_a.setPixelColor(107,BR/2,BR,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(87,BR/2,0,0,0);
  strip_a.setPixelColor(88,BR,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,BR/2,0,0,0);
  strip_a.setPixelColor(95,BR,0,0,0);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,0,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR,0,0);
  strip_a.setPixelColor(99,BR/2,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,BR/2,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,BR/2,0,0,0);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/2,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(100,BR/2,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(121,0,0,0,0);
  strip_a.setPixelColor(122,0,0,0,0);
  strip_a.setPixelColor(87,0,0,0,0);
  strip_a.setPixelColor(88,0,0,0,0);
  strip_a.setPixelColor(89,0,0,0,0);
  strip_a.setPixelColor(90,0,0,0,0);
  strip_a.setPixelColor(91,0,0,0,0);
  strip_a.setPixelColor(92,0,0,0,0);
  strip_a.setPixelColor(93,0,0,0,0);
  strip_a.setPixelColor(94,0,0,0,0);
  strip_a.setPixelColor(95,0,0,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,0,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();

}







void rou8() {

// 8.0 All Fade Out

  strip_a.setPixelColor(0,0,0,0,BR);
  strip_a.setPixelColor(1,0,0,0,BR);
  strip_a.setPixelColor(10,0,0,0,BR);
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,0,BR/2,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,0,BR/2,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(11,0,0,0,BR);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(111,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(112,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(113,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(114,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(115,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(116,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(117,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(118,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(119,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,BR);
  strip_a.setPixelColor(120,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(13,0,0,0,BR);
  strip_a.setPixelColor(14,0,0,0,BR);
  strip_a.setPixelColor(15,0,0,0,BR);
  strip_a.setPixelColor(16,0,0,0,BR);
  strip_a.setPixelColor(17,0,0,0,BR);
  strip_a.setPixelColor(18,0,0,0,BR);
  strip_a.setPixelColor(19,0,0,0,BR);
  strip_a.setPixelColor(2,0,0,0,BR);
  strip_a.setPixelColor(20,0,0,0,BR);
  strip_a.setPixelColor(21,0,0,0,BR);
  strip_a.setPixelColor(22,0,0,0,BR);
  strip_a.setPixelColor(23,0,0,0,BR);
  strip_a.setPixelColor(24,0,0,0,BR);
  strip_a.setPixelColor(25,0,0,0,BR);
  strip_a.setPixelColor(26,0,0,0,BR);
  strip_a.setPixelColor(27,0,0,0,BR);
  strip_a.setPixelColor(28,0,0,0,BR);
  strip_a.setPixelColor(29,0,0,0,BR);
  strip_a.setPixelColor(3,0,0,0,BR);
  strip_a.setPixelColor(30,0,0,0,BR);
  strip_a.setPixelColor(31,0,0,0,BR);
  strip_a.setPixelColor(32,0,0,0,BR);
  strip_a.setPixelColor(33,0,0,0,BR);
  strip_a.setPixelColor(34,BR,BR,0,0);
  strip_a.setPixelColor(35,BR,BR,0,0);
  strip_a.setPixelColor(36,BR,BR,0,0);
  strip_a.setPixelColor(37,BR,BR,0,0);
  strip_a.setPixelColor(38,BR,BR,0,0);
  strip_a.setPixelColor(39,BR,BR,0,0);
  strip_a.setPixelColor(4,0,0,0,BR);
  strip_a.setPixelColor(40,BR,BR,0,0);
  strip_a.setPixelColor(41,BR,BR,0,0);
  strip_a.setPixelColor(42,BR,BR,0,0);
  strip_a.setPixelColor(43,BR,BR,0,0);
  strip_a.setPixelColor(44,BR,BR,0,0);
  strip_a.setPixelColor(45,BR,BR,0,0);
  strip_a.setPixelColor(46,BR,BR,0,0);
  strip_a.setPixelColor(47,BR,BR,0,0);
  strip_a.setPixelColor(48,BR,BR,0,0);
  strip_a.setPixelColor(49,BR,BR,0,0);
  strip_a.setPixelColor(5,0,0,0,BR);
  strip_a.setPixelColor(50,BR,BR,0,0);
  strip_a.setPixelColor(51,BR,BR,0,0);
  strip_a.setPixelColor(52,BR,BR,0,0);
  strip_a.setPixelColor(53,BR,BR,0,0);
  strip_a.setPixelColor(54,BR,BR,0,0);
  strip_a.setPixelColor(55,BR,BR,0,0);
  strip_a.setPixelColor(56,BR,BR,0,0);
  strip_a.setPixelColor(57,BR,BR,0,0);
  strip_a.setPixelColor(58,BR,BR,0,0);
  strip_a.setPixelColor(59,BR,BR,0,0);
  strip_a.setPixelColor(6,0,0,0,BR);
  strip_a.setPixelColor(60,BR,BR,0,0);
  strip_a.setPixelColor(61,BR,BR,0,0);
  strip_a.setPixelColor(62,BR,BR,0,0);
  strip_a.setPixelColor(63,BR,BR,0,0);
  strip_a.setPixelColor(64,BR,BR,0,0);
  strip_a.setPixelColor(65,BR,BR,0,0);
  strip_a.setPixelColor(66,BR,BR,0,0);
  strip_a.setPixelColor(67,BR,BR,0,0);
  strip_a.setPixelColor(68,0,0,0,BR/2);
  strip_a.setPixelColor(69,0,0,0,BR);
  strip_a.setPixelColor(7,0,0,0,BR);
  strip_a.setPixelColor(70,0,0,0,BR);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR);
  strip_a.setPixelColor(85,0,0,0,BR);
  strip_a.setPixelColor(86,0,0,0,BR/2);
  strip_a.setPixelColor(9,0,0,0,BR);
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,9*(BR/10));
  strip_a.setPixelColor(1,0,0,0,9*(BR/10));
  strip_a.setPixelColor(10,0,0,0,9*(BR/10));
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(11,0,0,0,9*(BR/10));
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(111,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(112,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(113,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(114,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(115,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(116,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(117,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(118,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(119,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,9*(BR/10));
  strip_a.setPixelColor(120,9*BR/20,9*BR/20,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,9*(BR/10));
  strip_a.setPixelColor(14,0,0,0,9*(BR/10));
  strip_a.setPixelColor(15,0,0,0,9*(BR/10));
  strip_a.setPixelColor(16,0,0,0,9*(BR/10));
  strip_a.setPixelColor(17,0,0,0,9*(BR/10));
  strip_a.setPixelColor(18,0,0,0,9*(BR/10));
  strip_a.setPixelColor(19,0,0,0,9*(BR/10));
  strip_a.setPixelColor(2,0,0,0,9*(BR/10));
  strip_a.setPixelColor(20,0,0,0,9*(BR/10));
  strip_a.setPixelColor(21,0,0,0,9*(BR/10));
  strip_a.setPixelColor(22,0,0,0,9*(BR/10));
  strip_a.setPixelColor(23,0,0,0,9*(BR/10));
  strip_a.setPixelColor(24,0,0,0,9*(BR/10));
  strip_a.setPixelColor(25,0,0,0,9*(BR/10));
  strip_a.setPixelColor(26,0,0,0,9*(BR/10));
  strip_a.setPixelColor(27,0,0,0,9*(BR/10));
  strip_a.setPixelColor(28,0,0,0,9*(BR/10));
  strip_a.setPixelColor(29,0,0,0,9*(BR/10));
  strip_a.setPixelColor(3,0,0,0,9*(BR/10));
  strip_a.setPixelColor(30,0,0,0,9*(BR/10));
  strip_a.setPixelColor(31,0,0,0,9*(BR/10));
  strip_a.setPixelColor(32,0,0,0,9*(BR/10));
  strip_a.setPixelColor(33,0,0,0,9*(BR/10));
  strip_a.setPixelColor(34,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(35,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(36,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(37,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(38,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(39,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(4,0,0,0,9*(BR/10));
  strip_a.setPixelColor(40,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(41,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(42,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(43,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(44,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(45,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(46,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(47,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(48,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(49,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(5,0,0,0,9*(BR/10));
  strip_a.setPixelColor(50,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(51,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(52,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(53,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(54,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(55,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(56,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(57,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(58,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(59,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(6,0,0,0,9*(BR/10));
  strip_a.setPixelColor(60,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(61,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(62,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(63,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(64,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(65,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(66,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(67,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(68,0,0,0,BR/4);
  strip_a.setPixelColor(69,0,0,0,BR/2);
  strip_a.setPixelColor(7,0,0,0,9*(BR/10));
  strip_a.setPixelColor(70,0,0,0,BR);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,9*(BR/10));
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR);
  strip_a.setPixelColor(85,0,0,0,BR/2);
  strip_a.setPixelColor(86,0,0,0,BR/4);
  strip_a.setPixelColor(9,0,0,0,9*(BR/10));
  strip_a.setPixelColor(96,0,BR,0,0);
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,4*(BR/5));
  strip_a.setPixelColor(1,0,0,0,4*(BR/5));
  strip_a.setPixelColor(10,0,0,0,4*(BR/5));
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/2,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/2,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR/2,0,0);
  strip_a.setPixelColor(109,0,BR/2,0,0);
  strip_a.setPixelColor(11,0,0,0,4*(BR/5));
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(111,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(112,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(113,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(114,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(115,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(116,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(117,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(118,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(119,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,4*(BR/5));
  strip_a.setPixelColor(120,8*BR/20,8*BR/20,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,4*(BR/5));
  strip_a.setPixelColor(14,0,0,0,4*(BR/5));
  strip_a.setPixelColor(15,0,0,0,4*(BR/5));
  strip_a.setPixelColor(16,0,0,0,4*(BR/5));
  strip_a.setPixelColor(17,0,0,0,4*(BR/5));
  strip_a.setPixelColor(18,0,0,0,4*(BR/5));
  strip_a.setPixelColor(19,0,0,0,4*(BR/5));
  strip_a.setPixelColor(2,0,0,0,4*(BR/5));
  strip_a.setPixelColor(20,0,0,0,4*(BR/5));
  strip_a.setPixelColor(21,0,0,0,4*(BR/5));
  strip_a.setPixelColor(22,0,0,0,4*(BR/5));
  strip_a.setPixelColor(23,0,0,0,4*(BR/5));
  strip_a.setPixelColor(24,0,0,0,4*(BR/5));
  strip_a.setPixelColor(25,0,0,0,4*(BR/5));
  strip_a.setPixelColor(26,0,0,0,4*(BR/5));
  strip_a.setPixelColor(27,0,0,0,4*(BR/5));
  strip_a.setPixelColor(28,0,0,0,4*(BR/5));
  strip_a.setPixelColor(29,0,0,0,4*(BR/5));
  strip_a.setPixelColor(3,0,0,0,4*(BR/5));
  strip_a.setPixelColor(30,0,0,0,4*(BR/5));
  strip_a.setPixelColor(31,0,0,0,4*(BR/5));
  strip_a.setPixelColor(32,0,0,0,4*(BR/5));
  strip_a.setPixelColor(33,0,0,0,4*(BR/5));
  strip_a.setPixelColor(34,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(35,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(36,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(37,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(38,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(39,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(4,0,0,0,4*(BR/5));
  strip_a.setPixelColor(40,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(41,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(42,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(43,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(44,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(45,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(46,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(47,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(48,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(49,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(5,0,0,0,4*(BR/5));
  strip_a.setPixelColor(50,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(51,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(52,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(53,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(54,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(55,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(56,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(57,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(58,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(59,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(6,0,0,0,4*(BR/5));
  strip_a.setPixelColor(60,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(61,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(62,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(63,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(64,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(65,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(66,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(67,10*BR/20,10*BR/20,0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,BR/4);
  strip_a.setPixelColor(7,0,0,0,4*(BR/5));
  strip_a.setPixelColor(70,0,0,0,BR/2);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,4*(BR/5));
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR/2);
  strip_a.setPixelColor(85,0,0,0,BR/4);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,4*(BR/5));
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/4,BR,0,0);
  strip_a.setPixelColor(99,BR/2,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,7*(BR/10));
  strip_a.setPixelColor(1,0,0,0,7*(BR/10));
  strip_a.setPixelColor(10,0,0,0,7*(BR/10));
  strip_a.setPixelColor(100,BR/4,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/2,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,0,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(11,0,0,0,7*(BR/10));
  strip_a.setPixelColor(110,0,BR/2,0,0);
  strip_a.setPixelColor(111,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(112,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(113,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(114,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(115,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(116,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(117,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(118,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(119,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,7*(BR/10));
  strip_a.setPixelColor(120,7*BR/20,7*BR/20,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,7*(BR/10));
  strip_a.setPixelColor(14,0,0,0,7*(BR/10));
  strip_a.setPixelColor(15,0,0,0,7*(BR/10));
  strip_a.setPixelColor(16,0,0,0,7*(BR/10));
  strip_a.setPixelColor(17,0,0,0,7*(BR/10));
  strip_a.setPixelColor(18,0,0,0,7*(BR/10));
  strip_a.setPixelColor(19,0,0,0,7*(BR/10));
  strip_a.setPixelColor(2,0,0,0,7*(BR/10));
  strip_a.setPixelColor(20,0,0,0,7*(BR/10));
  strip_a.setPixelColor(21,0,0,0,7*(BR/10));
  strip_a.setPixelColor(22,0,0,0,7*(BR/10));
  strip_a.setPixelColor(23,0,0,0,7*(BR/10));
  strip_a.setPixelColor(24,0,0,0,7*(BR/10));
  strip_a.setPixelColor(25,0,0,0,7*(BR/10));
  strip_a.setPixelColor(26,0,0,0,7*(BR/10));
  strip_a.setPixelColor(27,0,0,0,7*(BR/10));
  strip_a.setPixelColor(28,0,0,0,7*(BR/10));
  strip_a.setPixelColor(29,0,0,0,7*(BR/10));
  strip_a.setPixelColor(3,0,0,0,7*(BR/10));
  strip_a.setPixelColor(30,0,0,0,7*(BR/10));
  strip_a.setPixelColor(31,0,0,0,7*(BR/10));
  strip_a.setPixelColor(32,0,0,0,7*(BR/10));
  strip_a.setPixelColor(33,0,0,0,7*(BR/10));
  strip_a.setPixelColor(34,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(35,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(36,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(37,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(38,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(39,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(4,0,0,0,7*(BR/10));
  strip_a.setPixelColor(40,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(41,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(42,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(43,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(44,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(45,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(46,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(47,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(48,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(49,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(5,0,0,0,7*(BR/10));
  strip_a.setPixelColor(50,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(51,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(52,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(53,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(54,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(55,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(56,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(57,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(58,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(59,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(6,0,0,0,7*(BR/10));
  strip_a.setPixelColor(60,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(61,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(62,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(63,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(64,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(65,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(66,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(67,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,7*(BR/10));
  strip_a.setPixelColor(70,0,0,0,BR/4);
  strip_a.setPixelColor(71,0,0,0,BR/2);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,7*(BR/10));
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR/2);
  strip_a.setPixelColor(84,0,0,0,BR/4);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,7*(BR/10));
  strip_a.setPixelColor(96,BR/4,BR,0,0);
  strip_a.setPixelColor(97,0,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,0,BR,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,3*(BR/5));
  strip_a.setPixelColor(1,0,0,0,3*(BR/5));
  strip_a.setPixelColor(10,0,0,0,3*(BR/5));
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR/2,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/4,BR,0,0);
  strip_a.setPixelColor(104,BR/2,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR/2,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/4,BR,0,0);
  strip_a.setPixelColor(109,BR/2,BR,0,0);
  strip_a.setPixelColor(11,0,0,0,3*(BR/5));
  strip_a.setPixelColor(110,BR/4,BR/2,0,0);
  strip_a.setPixelColor(111,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(112,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(113,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(114,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(115,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(116,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(117,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(118,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(119,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,3*(BR/5));
  strip_a.setPixelColor(120,6*BR/20,6*BR/20,0,0);
  strip_a.setPixelColor(121,0,BR,0,0);
  strip_a.setPixelColor(122,0,BR,0,0);
  strip_a.setPixelColor(13,0,0,0,3*(BR/5));
  strip_a.setPixelColor(14,0,0,0,3*(BR/5));
  strip_a.setPixelColor(15,0,0,0,3*(BR/5));
  strip_a.setPixelColor(16,0,0,0,3*(BR/5));
  strip_a.setPixelColor(17,0,0,0,3*(BR/5));
  strip_a.setPixelColor(18,0,0,0,3*(BR/5));
  strip_a.setPixelColor(19,0,0,0,3*(BR/5));
  strip_a.setPixelColor(2,0,0,0,3*(BR/5));
  strip_a.setPixelColor(20,0,0,0,3*(BR/5));
  strip_a.setPixelColor(21,0,0,0,3*(BR/5));
  strip_a.setPixelColor(22,0,0,0,3*(BR/5));
  strip_a.setPixelColor(23,0,0,0,3*(BR/5));
  strip_a.setPixelColor(24,0,0,0,3*(BR/5));
  strip_a.setPixelColor(25,0,0,0,3*(BR/5));
  strip_a.setPixelColor(26,0,0,0,3*(BR/5));
  strip_a.setPixelColor(27,0,0,0,3*(BR/5));
  strip_a.setPixelColor(28,0,0,0,3*(BR/5));
  strip_a.setPixelColor(29,0,0,0,3*(BR/5));
  strip_a.setPixelColor(3,0,0,0,3*(BR/5));
  strip_a.setPixelColor(30,0,0,0,3*(BR/5));
  strip_a.setPixelColor(31,0,0,0,3*(BR/5));
  strip_a.setPixelColor(32,0,0,0,3*(BR/5));
  strip_a.setPixelColor(33,0,0,0,3*(BR/5));
  strip_a.setPixelColor(34,0,0,0,0);
  strip_a.setPixelColor(35,0,0,0,0);
  strip_a.setPixelColor(36,0,0,0,0);
  strip_a.setPixelColor(37,0,0,0,0);
  strip_a.setPixelColor(38,0,0,0,0);
  strip_a.setPixelColor(39,0,0,0,0);
  strip_a.setPixelColor(4,0,0,0,3*(BR/5));
  strip_a.setPixelColor(40,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(41,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(42,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(43,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(44,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(45,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(46,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(47,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(48,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(49,15*BR/20,15*BR/20,0,0);
  strip_a.setPixelColor(40,0,0,0,0);
  strip_a.setPixelColor(41,0,0,0,0);
  strip_a.setPixelColor(42,0,0,0,0);
  strip_a.setPixelColor(43,0,0,0,0);
  strip_a.setPixelColor(44,0,0,0,0);
  strip_a.setPixelColor(45,0,0,0,0);
  strip_a.setPixelColor(46,0,0,0,0);
  strip_a.setPixelColor(47,0,0,0,0);
  strip_a.setPixelColor(48,0,0,0,0);
  strip_a.setPixelColor(49,0,0,0,0);
  strip_a.setPixelColor(5,0,0,0,3*(BR/5));
  strip_a.setPixelColor(50,0,0,0,0);
  strip_a.setPixelColor(51,0,0,0,0);
  strip_a.setPixelColor(52,0,0,0,0);
  strip_a.setPixelColor(53,0,0,0,0);
  strip_a.setPixelColor(54,0,0,0,0);
  strip_a.setPixelColor(55,0,0,0,0);
  strip_a.setPixelColor(56,0,0,0,0);
  strip_a.setPixelColor(57,0,0,0,0);
  strip_a.setPixelColor(58,0,0,0,0);
  strip_a.setPixelColor(59,0,0,0,0);
  strip_a.setPixelColor(6,0,0,0,3*(BR/5));
  strip_a.setPixelColor(60,0,0,0,0);
  strip_a.setPixelColor(61,0,0,0,0);
  strip_a.setPixelColor(62,0,0,0,0);
  strip_a.setPixelColor(63,0,0,0,0);
  strip_a.setPixelColor(64,0,0,0,0);
  strip_a.setPixelColor(65,0,0,0,0);
  strip_a.setPixelColor(66,0,0,0,0);
  strip_a.setPixelColor(67,0,0,0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,3*(BR/5));
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,BR/4);
  strip_a.setPixelColor(72,0,0,0,BR/2);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,3*(BR/5));
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR/2);
  strip_a.setPixelColor(83,0,0,0,BR/4);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,3*(BR/5));
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,BR/2);
  strip_a.setPixelColor(1,0,0,0,BR/2);
  strip_a.setPixelColor(10,0,0,0,BR/2);
  strip_a.setPixelColor(100,0,BR,0,0);
  strip_a.setPixelColor(101,BR/2,BR,0,0);
  strip_a.setPixelColor(102,BR/4,BR,0,0);
  strip_a.setPixelColor(103,BR/2,BR,0,0);
  strip_a.setPixelColor(104,BR/4,BR,0,0);
  strip_a.setPixelColor(105,BR/4,BR,0,0);
  strip_a.setPixelColor(106,BR/2,BR,0,0);
  strip_a.setPixelColor(107,BR/4,BR,0,0);
  strip_a.setPixelColor(108,BR/2,BR,0,0);
  strip_a.setPixelColor(109,BR/4,BR/2,0,0);
  strip_a.setPixelColor(11,0,0,0,BR/2);
  strip_a.setPixelColor(110,BR/2,BR,0,0);
  strip_a.setPixelColor(111,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(112,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(113,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(114,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(115,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(116,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(117,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(118,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(119,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,BR/2);
  strip_a.setPixelColor(120,5*BR/20,5*BR/20,0,0);
  strip_a.setPixelColor(121,0,8*(BR/10),0,0);
  strip_a.setPixelColor(122,0,8*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,BR/2);
  strip_a.setPixelColor(14,0,0,0,BR/2);
  strip_a.setPixelColor(15,0,0,0,BR/2);
  strip_a.setPixelColor(16,0,0,0,BR/2);
  strip_a.setPixelColor(17,0,0,0,BR/2);
  strip_a.setPixelColor(18,0,0,0,BR/2);
  strip_a.setPixelColor(19,0,0,0,BR/2);
  strip_a.setPixelColor(2,0,0,0,BR/2);
  strip_a.setPixelColor(20,0,0,0,BR/2);
  strip_a.setPixelColor(21,0,0,0,BR/2);
  strip_a.setPixelColor(22,0,0,0,BR/2);
  strip_a.setPixelColor(23,0,0,0,BR/2);
  strip_a.setPixelColor(24,0,0,0,BR/2);
  strip_a.setPixelColor(25,0,0,0,BR/2);
  strip_a.setPixelColor(26,0,0,0,BR/2);
  strip_a.setPixelColor(27,0,0,0,BR/2);
  strip_a.setPixelColor(28,0,0,0,BR/2);
  strip_a.setPixelColor(29,0,0,0,BR/2);
  strip_a.setPixelColor(3,0,0,0,BR/2);
  strip_a.setPixelColor(30,0,0,0,BR/2);
  strip_a.setPixelColor(31,0,0,0,BR/2);
  strip_a.setPixelColor(32,0,0,0,BR/2);
  strip_a.setPixelColor(33,0,0,0,BR/2);
  strip_a.setPixelColor(4,0,0,0,BR/2);
  strip_a.setPixelColor(5,0,0,0,BR/2);
  strip_a.setPixelColor(6,0,0,0,BR/2);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,BR/2);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,BR/4);
  strip_a.setPixelColor(73,0,0,0,BR/2);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,BR/2);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR/2);
  strip_a.setPixelColor(82,0,0,0,BR/4);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,BR/2);
  strip_a.setPixelColor(96,BR/2,BR,0,0);
  strip_a.setPixelColor(97,BR/4,BR,0,0);
  strip_a.setPixelColor(98,BR/2,BR/2,0,0);
  strip_a.setPixelColor(99,BR/4,BR,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,2*(BR/5));
  strip_a.setPixelColor(1,0,0,0,2*(BR/5));
  strip_a.setPixelColor(10,0,0,0,2*(BR/5));
  strip_a.setPixelColor(100,0,BR/2,0,0);
  strip_a.setPixelColor(101,BR/4,BR/4,0,0);
  strip_a.setPixelColor(102,BR/8,BR/2,0,0);
  strip_a.setPixelColor(103,BR/4,BR/2,0,0);
  strip_a.setPixelColor(104,0,BR/4,0,0);
  strip_a.setPixelColor(105,BR/8,BR/2,0,0);
  strip_a.setPixelColor(106,BR/4,BR/2,0,0);
  strip_a.setPixelColor(107,0,BR/4,0,0);
  strip_a.setPixelColor(108,BR/4,BR/2,0,0);
  strip_a.setPixelColor(109,BR/8,BR/4,0,0);
  strip_a.setPixelColor(11,0,0,0,2*(BR/5));
  strip_a.setPixelColor(110,BR/4,BR/2,0,0);
  strip_a.setPixelColor(111,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(112,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(113,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(114,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(115,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(116,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(117,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(118,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(119,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,2*(BR/5));
  strip_a.setPixelColor(120,4*BR/20,4*BR/20,0,0);
  strip_a.setPixelColor(121,0,6*(BR/10),0,0);
  strip_a.setPixelColor(122,0,6*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,2*(BR/5));
  strip_a.setPixelColor(14,0,0,0,2*(BR/5));
  strip_a.setPixelColor(15,0,0,0,2*(BR/5));
  strip_a.setPixelColor(16,0,0,0,2*(BR/5));
  strip_a.setPixelColor(17,0,0,0,2*(BR/5));
  strip_a.setPixelColor(18,0,0,0,2*(BR/5));
  strip_a.setPixelColor(19,0,0,0,2*(BR/5));
  strip_a.setPixelColor(2,0,0,0,2*(BR/5));
  strip_a.setPixelColor(20,0,0,0,2*(BR/5));
  strip_a.setPixelColor(21,0,0,0,2*(BR/5));
  strip_a.setPixelColor(22,0,0,0,2*(BR/5));
  strip_a.setPixelColor(23,0,0,0,2*(BR/5));
  strip_a.setPixelColor(24,0,0,0,2*(BR/5));
  strip_a.setPixelColor(25,0,0,0,2*(BR/5));
  strip_a.setPixelColor(26,0,0,0,2*(BR/5));
  strip_a.setPixelColor(27,0,0,0,2*(BR/5));
  strip_a.setPixelColor(28,0,0,0,2*(BR/5));
  strip_a.setPixelColor(29,0,0,0,2*(BR/5));
  strip_a.setPixelColor(3,0,0,0,2*(BR/5));
  strip_a.setPixelColor(30,0,0,0,2*(BR/5));
  strip_a.setPixelColor(31,0,0,0,2*(BR/5));
  strip_a.setPixelColor(32,0,0,0,2*(BR/5));
  strip_a.setPixelColor(33,0,0,0,2*(BR/5));
  strip_a.setPixelColor(4,0,0,0,2*(BR/5));
  strip_a.setPixelColor(5,0,0,0,2*(BR/5));
  strip_a.setPixelColor(6,0,0,0,2*(BR/5));
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,2*(BR/5));
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,0);
  strip_a.setPixelColor(73,0,0,0,BR/4);
  strip_a.setPixelColor(74,0,0,0,BR/2);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,2*(BR/5));
  strip_a.setPixelColor(80,0,0,0,BR/2);
  strip_a.setPixelColor(81,0,0,0,BR/4);
  strip_a.setPixelColor(82,0,0,0,0);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,2*(BR/5));
  strip_a.setPixelColor(96,0,BR/2,0,0);
  strip_a.setPixelColor(97,BR/4,BR/2,0,0);
  strip_a.setPixelColor(98,BR/4,BR/4,0,0);
  strip_a.setPixelColor(99,BR/8,BR/2,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,3*(BR/10));
  strip_a.setPixelColor(1,0,0,0,3*(BR/10));
  strip_a.setPixelColor(10,0,0,0,3*(BR/10));
  strip_a.setPixelColor(100,0,BR/6,0,0);
  strip_a.setPixelColor(101,BR/2,BR/3,0,0);
  strip_a.setPixelColor(102,BR/6,BR/3,0,0);
  strip_a.setPixelColor(103,BR/12,BR/3,0,0);
  strip_a.setPixelColor(104,0,BR/6,0,0);
  strip_a.setPixelColor(105,BR/6,BR/3,0,0);
  strip_a.setPixelColor(106,0,BR/6,0,0);
  strip_a.setPixelColor(107,BR/6,BR/3,0,0);
  strip_a.setPixelColor(108,BR/6,BR/3,0,0);
  strip_a.setPixelColor(109,BR/12,BR/3,0,0);
  strip_a.setPixelColor(11,0,0,0,3*(BR/10));
  strip_a.setPixelColor(110,BR/2,BR/3,0,0);
  strip_a.setPixelColor(111,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(112,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(113,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(114,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(115,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(116,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(117,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(118,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(119,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,3*(BR/10));
  strip_a.setPixelColor(120,3*BR/20,3*BR/20,0,0);
  strip_a.setPixelColor(121,0,3*(BR/10),0,0);
  strip_a.setPixelColor(122,0,3*(BR/10),0,0);
  strip_a.setPixelColor(13,0,0,0,3*(BR/10));
  strip_a.setPixelColor(14,0,0,0,3*(BR/10));
  strip_a.setPixelColor(15,0,0,0,3*(BR/10));
  strip_a.setPixelColor(16,0,0,0,3*(BR/10));
  strip_a.setPixelColor(17,0,0,0,3*(BR/10));
  strip_a.setPixelColor(18,0,0,0,3*(BR/10));
  strip_a.setPixelColor(19,0,0,0,3*(BR/10));
  strip_a.setPixelColor(2,0,0,0,3*(BR/10));
  strip_a.setPixelColor(20,0,0,0,3*(BR/10));
  strip_a.setPixelColor(21,0,0,0,3*(BR/10));
  strip_a.setPixelColor(22,0,0,0,3*(BR/10));
  strip_a.setPixelColor(23,0,0,0,3*(BR/10));
  strip_a.setPixelColor(24,0,0,0,3*(BR/10));
  strip_a.setPixelColor(25,0,0,0,3*(BR/10));
  strip_a.setPixelColor(26,0,0,0,3*(BR/10));
  strip_a.setPixelColor(27,0,0,0,3*(BR/10));
  strip_a.setPixelColor(28,0,0,0,3*(BR/10));
  strip_a.setPixelColor(29,0,0,0,3*(BR/10));
  strip_a.setPixelColor(3,0,0,0,3*(BR/10));
  strip_a.setPixelColor(30,0,0,0,3*(BR/10));
  strip_a.setPixelColor(31,0,0,0,3*(BR/10));
  strip_a.setPixelColor(32,0,0,0,3*(BR/10));
  strip_a.setPixelColor(33,0,0,0,3*(BR/10));
  strip_a.setPixelColor(4,0,0,0,3*(BR/10));
  strip_a.setPixelColor(5,0,0,0,3*(BR/10));
  strip_a.setPixelColor(6,0,0,0,3*(BR/10));
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,3*(BR/10));
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,0);
  strip_a.setPixelColor(73,0,0,0,0);
  strip_a.setPixelColor(74,0,0,0,BR/4);
  strip_a.setPixelColor(75,0,0,0,BR/2);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR/2);
  strip_a.setPixelColor(8,0,0,0,3*(BR/10));
  strip_a.setPixelColor(80,0,0,0,BR/4);
  strip_a.setPixelColor(81,0,0,0,0);
  strip_a.setPixelColor(82,0,0,0,0);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,3*(BR/10));
  strip_a.setPixelColor(96,BR/6,BR/3,0,0);
  strip_a.setPixelColor(97,0,BR/6,0,0);
  strip_a.setPixelColor(98,BR/6,BR/3,0,0);
  strip_a.setPixelColor(99,BR/6,BR/3,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,BR/5);
  strip_a.setPixelColor(1,0,0,0,BR/5);
  strip_a.setPixelColor(10,0,0,0,BR/5);
  strip_a.setPixelColor(100,0,BR/4,0,0);
  strip_a.setPixelColor(101,BR/8,BR/8,0,0);
  strip_a.setPixelColor(102,BR/16,BR/4,0,0);
  strip_a.setPixelColor(103,BR/8,BR/4,0,0);
  strip_a.setPixelColor(104,0,BR/8,0,0);
  strip_a.setPixelColor(105,BR/16,BR/4,0,0);
  strip_a.setPixelColor(106,BR/8,BR/4,0,0);
  strip_a.setPixelColor(107,0,BR/8,0,0);
  strip_a.setPixelColor(108,BR/8,BR/4,0,0);
  strip_a.setPixelColor(109,BR/16,BR/8,0,0);
  strip_a.setPixelColor(11,0,0,0,BR/5);
  strip_a.setPixelColor(110,BR/8,BR/4,0,0);
  strip_a.setPixelColor(111,BR/20,BR/20,0,0);
  strip_a.setPixelColor(112,BR/20,BR/20,0,0);
  strip_a.setPixelColor(113,BR/20,BR/20,0,0);
  strip_a.setPixelColor(114,BR/20,BR/20,0,0);
  strip_a.setPixelColor(115,BR/20,BR/20,0,0);
  strip_a.setPixelColor(116,BR/20,BR/20,0,0);
  strip_a.setPixelColor(117,BR/20,BR/20,0,0);
  strip_a.setPixelColor(118,BR/20,BR/20,0,0);
  strip_a.setPixelColor(119,BR/20,BR/20,0,0);
  strip_a.setPixelColor(12,0,0,0,BR/5);
  strip_a.setPixelColor(120,BR/20,BR/20,0,0);
  strip_a.setPixelColor(121,0,BR/10,0,0);
  strip_a.setPixelColor(122,0,BR/10,0,0);
  strip_a.setPixelColor(13,0,0,0,BR/5);
  strip_a.setPixelColor(14,0,0,0,BR/5);
  strip_a.setPixelColor(15,0,0,0,BR/5);
  strip_a.setPixelColor(16,0,0,0,BR/5);
  strip_a.setPixelColor(17,0,0,0,BR/5);
  strip_a.setPixelColor(18,0,0,0,BR/5);
  strip_a.setPixelColor(19,0,0,0,BR/5);
  strip_a.setPixelColor(2,0,0,0,BR/5);
  strip_a.setPixelColor(20,0,0,0,BR/5);
  strip_a.setPixelColor(21,0,0,0,BR/5);
  strip_a.setPixelColor(22,0,0,0,BR/5);
  strip_a.setPixelColor(23,0,0,0,BR/5);
  strip_a.setPixelColor(24,0,0,0,BR/5);
  strip_a.setPixelColor(25,0,0,0,BR/5);
  strip_a.setPixelColor(26,0,0,0,BR/5);
  strip_a.setPixelColor(27,0,0,0,BR/5);
  strip_a.setPixelColor(28,0,0,0,BR/5);
  strip_a.setPixelColor(29,0,0,0,BR/5);
  strip_a.setPixelColor(3,0,0,0,BR/5);
  strip_a.setPixelColor(30,0,0,0,BR/5);
  strip_a.setPixelColor(31,0,0,0,BR/5);
  strip_a.setPixelColor(32,0,0,0,BR/5);
  strip_a.setPixelColor(33,0,0,0,BR/5);
  strip_a.setPixelColor(4,0,0,0,BR/5);
  strip_a.setPixelColor(5,0,0,0,BR/5);
  strip_a.setPixelColor(6,0,0,0,BR/5);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,BR/5);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,0);
  strip_a.setPixelColor(73,0,0,0,0);
  strip_a.setPixelColor(74,0,0,0,0);
  strip_a.setPixelColor(75,0,0,0,BR/4);
  strip_a.setPixelColor(76,0,0,0,BR/2);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR/2);
  strip_a.setPixelColor(79,0,0,0,BR/4);
  strip_a.setPixelColor(8,0,0,0,BR/5);
  strip_a.setPixelColor(80,0,0,0,0);
  strip_a.setPixelColor(81,0,0,0,0);
  strip_a.setPixelColor(82,0,0,0,0);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,BR/5);
  strip_a.setPixelColor(96,0,BR/4,0,0);
  strip_a.setPixelColor(97,BR/8,BR/4,0,0);
  strip_a.setPixelColor(98,BR/8,BR/8,0,0);
  strip_a.setPixelColor(99,BR/16,BR/4,0,0);
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_a.setPixelColor(0,0,0,0,0);
  strip_a.setPixelColor(1,0,0,0,0);
  strip_a.setPixelColor(10,0,0,0,0);
  strip_a.setPixelColor(100,0,0,0,0);
  strip_a.setPixelColor(101,0,0,0,0);
  strip_a.setPixelColor(102,0,0,0,0);
  strip_a.setPixelColor(103,0,0,0,0);
  strip_a.setPixelColor(104,0,0,0,0);
  strip_a.setPixelColor(105,0,0,0,0);
  strip_a.setPixelColor(106,0,0,0,0);
  strip_a.setPixelColor(107,0,0,0,0);
  strip_a.setPixelColor(108,0,0,0,0);
  strip_a.setPixelColor(109,0,0,0,0);
  strip_a.setPixelColor(11,0,0,0,0);
  strip_a.setPixelColor(110,0,0,0,0);
  strip_a.setPixelColor(111,0,0,0,0);
  strip_a.setPixelColor(112,0,0,0,0);
  strip_a.setPixelColor(113,0,0,0,0);
  strip_a.setPixelColor(114,0,0,0,0);
  strip_a.setPixelColor(115,0,0,0,0);
  strip_a.setPixelColor(116,0,0,0,0);
  strip_a.setPixelColor(117,0,0,0,0);
  strip_a.setPixelColor(118,0,0,0,0);
  strip_a.setPixelColor(119,0,0,0,0);
  strip_a.setPixelColor(12,0,0,0,0);
  strip_a.setPixelColor(120,0,0,0,0);
  strip_a.setPixelColor(121,0,0,0,0);
  strip_a.setPixelColor(122,0,0,0,0);
  strip_a.setPixelColor(13,0,0,0,0);
  strip_a.setPixelColor(14,0,0,0,0);
  strip_a.setPixelColor(15,0,0,0,0);
  strip_a.setPixelColor(16,0,0,0,0);
  strip_a.setPixelColor(17,0,0,0,0);
  strip_a.setPixelColor(18,0,0,0,0);
  strip_a.setPixelColor(19,0,0,0,0);
  strip_a.setPixelColor(2,0,0,0,0);
  strip_a.setPixelColor(20,0,0,0,0);
  strip_a.setPixelColor(21,0,0,0,0);
  strip_a.setPixelColor(22,0,0,0,0);
  strip_a.setPixelColor(23,0,0,0,0);
  strip_a.setPixelColor(24,0,0,0,0);
  strip_a.setPixelColor(25,0,0,0,0);
  strip_a.setPixelColor(26,0,0,0,0);
  strip_a.setPixelColor(27,0,0,0,0);
  strip_a.setPixelColor(28,0,0,0,0);
  strip_a.setPixelColor(29,0,0,0,0);
  strip_a.setPixelColor(3,0,0,0,0);
  strip_a.setPixelColor(30,0,0,0,0);
  strip_a.setPixelColor(31,0,0,0,0);
  strip_a.setPixelColor(32,0,0,0,0);
  strip_a.setPixelColor(33,0,0,0,0);
  strip_a.setPixelColor(4,0,0,0,0);
  strip_a.setPixelColor(5,0,0,0,0);
  strip_a.setPixelColor(6,0,0,0,0);
  strip_a.setPixelColor(68,0,0,0,0);
  strip_a.setPixelColor(69,0,0,0,0);
  strip_a.setPixelColor(7,0,0,0,0);
  strip_a.setPixelColor(70,0,0,0,0);
  strip_a.setPixelColor(71,0,0,0,0);
  strip_a.setPixelColor(72,0,0,0,0);
  strip_a.setPixelColor(73,0,0,0,0);
  strip_a.setPixelColor(74,0,0,0,0);
  strip_a.setPixelColor(75,0,0,0,0);
  strip_a.setPixelColor(76,0,0,0,BR/4);
  strip_a.setPixelColor(77,0,0,0,BR/2);
  strip_a.setPixelColor(78,0,0,0,BR/4);
  strip_a.setPixelColor(79,0,0,0,0);
  strip_a.setPixelColor(8,0,0,0,0);
  strip_a.setPixelColor(80,0,0,0,0);
  strip_a.setPixelColor(81,0,0,0,0);
  strip_a.setPixelColor(82,0,0,0,0);
  strip_a.setPixelColor(83,0,0,0,0);
  strip_a.setPixelColor(84,0,0,0,0);
  strip_a.setPixelColor(85,0,0,0,0);
  strip_a.setPixelColor(86,0,0,0,0);
  strip_a.setPixelColor(9,0,0,0,0);
  strip_a.setPixelColor(96,0,0,0,0);
  strip_a.setPixelColor(97,0,0,0,0);
  strip_a.setPixelColor(98,0,0,0,0);
  strip_a.setPixelColor(99,0,0,0,0);
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
    flash();
  strip_a.setPixelColor(76,0,0,0,0);
  strip_a.setPixelColor(77,0,0,0,0);
  strip_a.setPixelColor(78,0,0,0,0);
    flash();

}







void kylofinn1() {

// Kylo and Finn - 1 section of saber code


  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,5*BR/8,0,0);
  strip_c.setPixelColor(1,0,5*BR/8,0,0);
  strip_c.setPixelColor(10,0,5*BR/8,0,0);
  strip_c.setPixelColor(11,0,5*BR/8,0,0);
  strip_c.setPixelColor(12,0,5*BR/8,0,0);
  strip_c.setPixelColor(13,0,5*BR/8,0,0);
  strip_c.setPixelColor(14,0,5*BR/8,0,0);
  strip_c.setPixelColor(15,0,5*BR/8,0,0);
  strip_c.setPixelColor(16,0,5*BR/8,0,0);
  strip_c.setPixelColor(17,0,5*BR/8,0,0);
  strip_c.setPixelColor(18,0,5*BR/8,0,0);
  strip_c.setPixelColor(19,0,5*BR/8,0,0);
  strip_c.setPixelColor(2,0,5*BR/8,0,0);
  strip_c.setPixelColor(20,0,5*BR/8,0,0);
  strip_c.setPixelColor(21,0,5*BR/8,0,0);
  strip_c.setPixelColor(22,0,5*BR/8,0,0);
  strip_c.setPixelColor(23,0,5*BR/8,0,0);
  strip_c.setPixelColor(24,0,5*BR/8,0,0);
  strip_c.setPixelColor(25,0,5*BR/8,0,0);
  strip_c.setPixelColor(26,0,5*BR/8,0,0);
  strip_c.setPixelColor(27,0,5*BR/8,0,0);
  strip_c.setPixelColor(28,0,5*BR/8,0,0);
  strip_c.setPixelColor(29,0,5*BR/8,0,0);
  strip_c.setPixelColor(3,0,5*BR/8,0,0);
  strip_c.setPixelColor(30,0,5*BR/8,0,0);
  strip_c.setPixelColor(31,0,5*BR/8,0,0);
  strip_c.setPixelColor(4,0,5*BR/8,0,0);
  strip_c.setPixelColor(5,0,5*BR/8,0,0);
  strip_c.setPixelColor(6,0,5*BR/8,0,0);
  strip_c.setPixelColor(7,0,5*BR/8,0,0);
  strip_c.setPixelColor(8,0,5*BR/8,0,0);
  strip_c.setPixelColor(9,0,5*BR/8,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,BR,0,0);
  strip_c.setPixelColor(31,0,BR,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,3*BR/4,0,0);
  strip_c.setPixelColor(27,0,3*BR/4,0,0);
  strip_c.setPixelColor(28,0,3*BR/4,0,0);
  strip_c.setPixelColor(29,0,3*BR/4,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,3*BR/4,0,0);
  strip_c.setPixelColor(31,0,3*BR/4,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  
}







void finnkylooff1() {

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,BR,0,0);
  strip_c.setPixelColor(25,0,BR,0,0);
  strip_c.setPixelColor(26,0,BR,0,0);
  strip_c.setPixelColor(27,0,BR,0,0);
  strip_c.setPixelColor(28,0,BR,0,0);
  strip_c.setPixelColor(29,0,BR,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,3*BR/4,0,0);
  strip_c.setPixelColor(25,0,3*BR/4,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,BR,0,0);
  strip_c.setPixelColor(16,0,BR,0,0);
  strip_c.setPixelColor(17,0,BR,0,0);
  strip_c.setPixelColor(18,0,BR,0,0);
  strip_c.setPixelColor(19,0,BR,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,BR,0,0);
  strip_c.setPixelColor(21,0,BR,0,0);
  strip_c.setPixelColor(22,0,BR,0,0);
  strip_c.setPixelColor(23,0,BR,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,3*BR/4,0,0);
  strip_c.setPixelColor(21,0,3*BR/4,0,0);
  strip_c.setPixelColor(22,0,3*BR/4,0,0);
  strip_c.setPixelColor(23,0,3*BR/4,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,3*BR/4,0,0);
  strip_c.setPixelColor(11,0,3*BR/4,0,0);
  strip_c.setPixelColor(12,0,3*BR/4,0,0);
  strip_c.setPixelColor(13,0,3*BR/4,0,0);
  strip_c.setPixelColor(14,0,3*BR/4,0,0);
  strip_c.setPixelColor(15,0,3*BR/4,0,0);
  strip_c.setPixelColor(16,0,3*BR/4,0,0);
  strip_c.setPixelColor(17,0,3*BR/4,0,0);
  strip_c.setPixelColor(18,0,3*BR/4,0,0);
  strip_c.setPixelColor(19,0,3*BR/4,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,BR,0,0);
  strip_c.setPixelColor(11,0,BR,0,0);
  strip_c.setPixelColor(12,0,BR,0,0);
  strip_c.setPixelColor(13,0,BR,0,0);
  strip_c.setPixelColor(14,0,BR,0,0);
  strip_c.setPixelColor(15,0,0,0,0);
  strip_c.setPixelColor(16,0,0,0,0);
  strip_c.setPixelColor(17,0,0,0,0);
  strip_c.setPixelColor(18,0,0,0,0);
  strip_c.setPixelColor(19,0,0,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,BR,0,0);
  strip_c.setPixelColor(6,0,BR,0,0);
  strip_c.setPixelColor(7,0,BR,0,0);
  strip_c.setPixelColor(8,0,BR,0,0);
  strip_c.setPixelColor(9,0,BR,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,3*BR/4,0,0);
  strip_c.setPixelColor(1,0,3*BR/4,0,0);
  strip_c.setPixelColor(10,0,0,0,0);
  strip_c.setPixelColor(11,0,0,0,0);
  strip_c.setPixelColor(12,0,0,0,0);
  strip_c.setPixelColor(13,0,0,0,0);
  strip_c.setPixelColor(14,0,0,0,0);
  strip_c.setPixelColor(15,0,0,0,0);
  strip_c.setPixelColor(16,0,0,0,0);
  strip_c.setPixelColor(17,0,0,0,0);
  strip_c.setPixelColor(18,0,0,0,0);
  strip_c.setPixelColor(19,0,0,0,0);
  strip_c.setPixelColor(2,0,3*BR/4,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,3*BR/4,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,3*BR/4,0,0);
  strip_c.setPixelColor(5,0,3*BR/4,0,0);
  strip_c.setPixelColor(6,0,3*BR/4,0,0);
  strip_c.setPixelColor(7,0,3*BR/4,0,0);
  strip_c.setPixelColor(8,0,3*BR/4,0,0);
  strip_c.setPixelColor(9,0,3*BR/4,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_c.setPixelColor(0,0,BR,0,0);
  strip_c.setPixelColor(1,0,BR,0,0);
  strip_c.setPixelColor(10,0,0,0,0);
  strip_c.setPixelColor(11,0,0,0,0);
  strip_c.setPixelColor(12,0,0,0,0);
  strip_c.setPixelColor(13,0,0,0,0);
  strip_c.setPixelColor(14,0,0,0,0);
  strip_c.setPixelColor(15,0,0,0,0);
  strip_c.setPixelColor(16,0,0,0,0);
  strip_c.setPixelColor(17,0,0,0,0);
  strip_c.setPixelColor(18,0,0,0,0);
  strip_c.setPixelColor(19,0,0,0,0);
  strip_c.setPixelColor(2,0,BR,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,BR,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,BR,0,0);
  strip_c.setPixelColor(5,0,0,0,0);
  strip_c.setPixelColor(6,0,0,0,0);
  strip_c.setPixelColor(7,0,0,0,0);
  strip_c.setPixelColor(8,0,0,0,0);
  strip_c.setPixelColor(9,0,0,0,0);
  flash();
  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_c.setPixelColor(0,0,0,0,0);
  strip_c.setPixelColor(1,0,0,0,0);
  strip_c.setPixelColor(10,0,0,0,0);
  strip_c.setPixelColor(11,0,0,0,0);
  strip_c.setPixelColor(12,0,0,0,0);
  strip_c.setPixelColor(13,0,0,0,0);
  strip_c.setPixelColor(14,0,0,0,0);
  strip_c.setPixelColor(15,0,0,0,0);
  strip_c.setPixelColor(16,0,0,0,0);
  strip_c.setPixelColor(17,0,0,0,0);
  strip_c.setPixelColor(18,0,0,0,0);
  strip_c.setPixelColor(19,0,0,0,0);
  strip_c.setPixelColor(2,0,0,0,0);
  strip_c.setPixelColor(20,0,0,0,0);
  strip_c.setPixelColor(21,0,0,0,0);
  strip_c.setPixelColor(22,0,0,0,0);
  strip_c.setPixelColor(23,0,0,0,0);
  strip_c.setPixelColor(24,0,0,0,0);
  strip_c.setPixelColor(25,0,0,0,0);
  strip_c.setPixelColor(26,0,0,0,0);
  strip_c.setPixelColor(27,0,0,0,0);
  strip_c.setPixelColor(28,0,0,0,0);
  strip_c.setPixelColor(29,0,0,0,0);
  strip_c.setPixelColor(3,0,0,0,0);
  strip_c.setPixelColor(30,0,0,0,0);
  strip_c.setPixelColor(31,0,0,0,0);
  strip_c.setPixelColor(4,0,0,0,0);
  strip_c.setPixelColor(5,0,0,0,0);
  strip_c.setPixelColor(6,0,0,0,0);
  strip_c.setPixelColor(7,0,0,0,0);
  strip_c.setPixelColor(8,0,0,0,0);
  strip_c.setPixelColor(9,0,0,0,0);
  flash();

}








void finnonly1() {

// Finn - 1/2 section of saber code

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  flash();

  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  flash();

  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  flash();

}






void finnoff1() {
  
// Finn Turning off
  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,BR,0);
  strip_b.setPixelColor(15,0,0,BR,0);
  strip_b.setPixelColor(16,0,0,BR,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,7*BR/8,0);
  strip_b.setPixelColor(12,0,0,7*BR/8,0);
  strip_b.setPixelColor(13,0,0,7*BR/8,0);
  strip_b.setPixelColor(14,0,0,7*BR/8,0);
  strip_b.setPixelColor(15,0,0,7*BR/8,0);
  strip_b.setPixelColor(16,0,0,7*BR/8,0);
  flash();

  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,BR,0);
  strip_b.setPixelColor(8,0,0,BR,0);
  strip_b.setPixelColor(9,0,0,BR,0);
  strip_b.setPixelColor(10,0,0,BR,0);
  strip_b.setPixelColor(11,0,0,BR,0);
  strip_b.setPixelColor(12,0,0,BR,0);
  strip_b.setPixelColor(13,0,0,BR,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,7*BR/8,0);
  strip_b.setPixelColor(6,0,0,7*BR/8,0);
  strip_b.setPixelColor(7,0,0,7*BR/8,0);
  strip_b.setPixelColor(8,0,0,7*BR/8,0);
  strip_b.setPixelColor(9,0,0,7*BR/8,0);
  strip_b.setPixelColor(10,0,0,7*BR/8,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,BR,0);
  strip_b.setPixelColor(1,0,0,BR,0);
  strip_b.setPixelColor(2,0,0,BR,0);
  strip_b.setPixelColor(3,0,0,BR,0);
  strip_b.setPixelColor(4,0,0,BR,0);
  strip_b.setPixelColor(5,0,0,BR,0);
  strip_b.setPixelColor(6,0,0,BR,0);
  strip_b.setPixelColor(7,0,0,0,0);
  strip_b.setPixelColor(8,0,0,0,0);
  strip_b.setPixelColor(9,0,0,0,0);
  strip_b.setPixelColor(10,0,0,0,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,7*BR/8,0);
  strip_b.setPixelColor(3,0,0,7*BR/8,0);
  strip_b.setPixelColor(4,0,0,7*BR/8,0);
  strip_b.setPixelColor(5,0,0,0,0);
  strip_b.setPixelColor(6,0,0,0,0);
  strip_b.setPixelColor(7,0,0,0,0);
  strip_b.setPixelColor(8,0,0,0,0);
  strip_b.setPixelColor(9,0,0,0,0);
  strip_b.setPixelColor(10,0,0,0,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,7*BR/8,0);
  strip_b.setPixelColor(1,0,0,7*BR/8,0);
  strip_b.setPixelColor(2,0,0,0,0);
  strip_b.setPixelColor(3,0,0,0,0);
  strip_b.setPixelColor(4,0,0,0,0);
  strip_b.setPixelColor(5,0,0,0,0);
  strip_b.setPixelColor(6,0,0,0,0);
  strip_b.setPixelColor(7,0,0,0,0);
  strip_b.setPixelColor(8,0,0,0,0);
  strip_b.setPixelColor(9,0,0,0,0);
  strip_b.setPixelColor(10,0,0,0,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

  strip_b.setPixelColor(0,0,0,0,0);
  strip_b.setPixelColor(1,0,0,0,0);
  strip_b.setPixelColor(2,0,0,0,0);
  strip_b.setPixelColor(3,0,0,0,0);
  strip_b.setPixelColor(4,0,0,0,0);
  strip_b.setPixelColor(5,0,0,0,0);
  strip_b.setPixelColor(6,0,0,0,0);
  strip_b.setPixelColor(7,0,0,0,0);
  strip_b.setPixelColor(8,0,0,0,0);
  strip_b.setPixelColor(9,0,0,0,0);
  strip_b.setPixelColor(10,0,0,0,0);
  strip_b.setPixelColor(11,0,0,0,0);
  strip_b.setPixelColor(12,0,0,0,0);
  strip_b.setPixelColor(13,0,0,0,0);
  strip_b.setPixelColor(14,0,0,0,0);
  strip_b.setPixelColor(15,0,0,0,0);
  strip_b.setPixelColor(16,0,0,0,0);
  flash();

}



void staticupdate1() {

// Credits
  strip_a.setPixelColor(0,0,0,0,BR);
  strip_a.setPixelColor(1,0,0,0,BR);
  strip_a.setPixelColor(2,0,0,0,BR);
  strip_a.setPixelColor(3,0,0,0,BR);
  strip_a.setPixelColor(4,0,0,0,BR);
  strip_a.setPixelColor(5,0,0,0,BR);
  strip_a.setPixelColor(6,0,0,0,BR);
  strip_a.setPixelColor(7,0,0,0,BR);
  strip_a.setPixelColor(8,0,0,0,BR);
  strip_a.setPixelColor(9,0,0,0,BR);
  strip_a.setPixelColor(10,0,0,0,BR);
  strip_a.setPixelColor(11,0,0,0,BR);
  strip_a.setPixelColor(12,0,0,0,BR);
  strip_a.setPixelColor(13,0,0,0,BR);
  strip_a.setPixelColor(14,0,0,0,BR);
  strip_a.setPixelColor(15,0,0,0,BR);
  strip_a.setPixelColor(16,0,0,0,BR);
  strip_a.setPixelColor(17,0,0,0,BR);
  strip_a.setPixelColor(18,0,0,0,BR);
  strip_a.setPixelColor(19,0,0,0,BR);
  strip_a.setPixelColor(20,0,0,0,BR);
  strip_a.setPixelColor(21,0,0,0,BR);
  strip_a.setPixelColor(22,0,0,0,BR);
  strip_a.setPixelColor(23,0,0,0,BR);
  strip_a.setPixelColor(24,0,0,0,BR);
  strip_a.setPixelColor(25,0,0,0,BR);
  strip_a.setPixelColor(26,0,0,0,BR);
  strip_a.setPixelColor(27,0,0,0,BR);
  strip_a.setPixelColor(28,0,0,0,BR);
  strip_a.setPixelColor(29,0,0,0,BR);
  strip_a.setPixelColor(30,0,0,0,BR);
  strip_a.setPixelColor(31,0,0,0,BR);
  strip_a.setPixelColor(32,0,0,0,BR);
  strip_a.setPixelColor(33,0,0,0,BR);

// Wars
  strip_a.setPixelColor(34,BR,BR,0,0);
  strip_a.setPixelColor(35,BR,BR,0,0);
  strip_a.setPixelColor(36,BR,BR,0,0);
  strip_a.setPixelColor(37,BR,BR,0,0);
  strip_a.setPixelColor(38,BR,BR,0,0);
  strip_a.setPixelColor(39,BR,BR,0,0);
  strip_a.setPixelColor(40,BR,BR,0,0);
  strip_a.setPixelColor(41,BR,BR,0,0);
  strip_a.setPixelColor(42,BR,BR,0,0);
  strip_a.setPixelColor(43,BR,BR,0,0);
  strip_a.setPixelColor(44,BR,BR,0,0);
  strip_a.setPixelColor(45,BR,BR,0,0);
  strip_a.setPixelColor(46,BR,BR,0,0);
  strip_a.setPixelColor(47,BR,BR,0,0);
  strip_a.setPixelColor(48,BR,BR,0,0);
  strip_a.setPixelColor(49,BR,BR,0,0);
  strip_a.setPixelColor(50,BR,BR,0,0);
// Star
  strip_a.setPixelColor(51,BR,BR,0,0);
  strip_a.setPixelColor(52,BR,BR,0,0);
  strip_a.setPixelColor(53,BR,BR,0,0);
  strip_a.setPixelColor(54,BR,BR,0,0);
  strip_a.setPixelColor(55,BR,BR,0,0);
  strip_a.setPixelColor(56,BR,BR,0,0);
  strip_a.setPixelColor(57,BR,BR,0,0);
  strip_a.setPixelColor(58,BR,BR,0,0);
  strip_a.setPixelColor(59,BR,BR,0,0);
  strip_a.setPixelColor(60,BR,BR,0,0);
  strip_a.setPixelColor(61,BR,BR,0,0);
  strip_a.setPixelColor(62,BR,BR,0,0);
  strip_a.setPixelColor(63,BR,BR,0,0);
  strip_a.setPixelColor(64,BR,BR,0,0);
  strip_a.setPixelColor(65,BR,BR,0,0);
  strip_a.setPixelColor(66,BR,BR,0,0);
  strip_a.setPixelColor(67,BR,BR,0,0);
// The Force Awakens
  strip_a.setPixelColor(68,0,0,0,BR);
  strip_a.setPixelColor(69,0,0,0,BR);
  strip_a.setPixelColor(70,0,0,0,BR);
  strip_a.setPixelColor(71,0,0,0,BR);
  strip_a.setPixelColor(72,0,0,0,BR);
  strip_a.setPixelColor(73,0,0,0,BR);
  strip_a.setPixelColor(74,0,0,0,BR);
  strip_a.setPixelColor(75,0,0,0,BR);
  strip_a.setPixelColor(76,0,0,0,BR);
  strip_a.setPixelColor(77,0,0,0,BR);
  strip_a.setPixelColor(78,0,0,0,BR);
  strip_a.setPixelColor(79,0,0,0,BR);
  strip_a.setPixelColor(80,0,0,0,BR);
  strip_a.setPixelColor(81,0,0,0,BR);
  strip_a.setPixelColor(82,0,0,0,BR);
  strip_a.setPixelColor(83,0,0,0,BR);
  strip_a.setPixelColor(84,0,0,0,BR);
  strip_a.setPixelColor(85,0,0,0,BR);
  strip_a.setPixelColor(86,0,0,0,BR);


}




