#include <Adafruit_NeoPixel.h>

#ifdef __AVR__

#include <avr/power.h>

#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(131, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() 
{
  strip.begin();
}

void loop() 
{
    // create the colours neede
    uint32_t pink = strip.Color(0, 255, 75);
    uint32_t white = strip.Color(255, 255, 255);
    uint32_t black = strip.Color(0, 0, 0);

    // no. 1
    // chase around the body
    for(uint16_t i = 1; i < 10; i++)
    {
      if(i % 2 == 0) // move forward
        vardel_chase(pink, 0, 131, i, 30 - i);
      else          // move back  
        vardel_chase_back(pink, 0, 131, i, 30 - i);
    }
    
    // no. 2
    // electric shock affect
    for(uint16_t i = 0; i < 15; i++)
    {
      ele_ring2(); 
      ele_ring(); 
      ele_ring2(); 
    }
    
    // no. 3
    // fast chase varying between white and black    
    for(uint16_t i = 0; i < 12; i++)
    {      
      if(i % 2 == 0)
        vardel_chase(pink, 0, 131, 4, 12 - i);  
      else
        vardel_chase_back(white, 0, 131, 4, 12 - i);    
    }
    
    // no. 4
    // the beating affect on the rings - arm sleeves
    beating_rings(pink);
    
    // no. 5
    // the beating affect same as above but all over the garment
    beating_all();
    
    // no. 6
    // the electricuting affect all over the garment
    for(uint16_t i = 0; i < 15; i++)
    {
      ele_all();
      ele_all_pink();
      ele_all();
    }
} // loop

// **** the dimensions for the garment sections **** //
// front --> fR = 120 -> 131 + fL = 0 -> 6       [17]
// back  --> back = 52 -> 71                     [19]
// hL    --> 7  -> 52                            [45]
// hR    --> 73 -> 119                           [47]

void beating_all()
{
  uint32_t pink = strip.Color(0, 255, 75);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t black = strip.Color(0, 0, 0);
  
  for(uint16_t i = 0; i < 9; i++)
  {
    uint32_t pink = strip.Color(0, 255, 75);
    light(pink, 0, 131);
    delay(350);
    light(black, 0, 131);
    delay(500);
    
    light(pink, 0, 131);
    delay(350);
    light(black, 0, 131);
    delay(500);
  }
}

// this function is used to simulate a beating or pulsing
void beating_rings(uint32_t c)
{
  uint32_t pink = strip.Color(0, 255, 75);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t black = strip.Color(0, 0, 0);
  
  for(uint16_t i = 0; i < 9; i++)
  {
    uint32_t pink = strip.Color(0, 255, 75);
    dual_light(pink, 7, 52, 72, 118);
    delay(350);
    dual_light(black, 7, 52, 72, 118);
    delay(500);
    
    dual_light(pink, 7, 52, 72, 118);
    delay(350);
    dual_light(black, 7, 52, 72, 118);
    delay(500);
  } // for  
} // beating_rings

// ele_ring -> electricity ring
// flashing pink and white to give an electricity feeling
// on the sleeves
void ele_ring()
{
  uint32_t pink = strip.Color(0, 255, 75);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t black = strip.Color(0, 0, 0);
  
  // light outer half of rings
  // outter hL -> 7 to 30
  // outter hR -> 95 to 118
  light(pink, 7, 30);
  light(pink, 95, 118);
  delay(15);
  
  // black them out
  light(black, 7, 30);
  light(black, 95, 118);
  delay(35);
  
  // light outer half of rings
  // inner hL -> 30 to 52
  // inner hR -> 72 to 95
  light(pink, 30, 52);
  light(pink, 72, 95);
  delay(15);
  
  // black them out
  light(black , 30, 52);
  light(black, 72, 95);
  delay(35);  
}

// same as ele_ring except it is the whole lighting system
// and it is just pink instead of pink and white
void ele_all_pink()
{
  uint32_t pink = strip.Color(0, 255, 75);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t black = strip.Color(0, 0, 0);
  
  // light outer half of rings
  // outter hL -> 7 to 30
  // outter hR -> 95 to 118
  light(pink, 0, 131);
  delay(15);
  
  // black them out
  light(black, 0, 131);
  delay(35);
  
  light(pink, 0, 131);
  delay(15);
  
  light(black, 0, 131);
  delay(35);  
}

void ele_all()
{
  uint32_t pink = strip.Color(0, 255, 75);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t black = strip.Color(0, 0, 0);
  
  // light outer half of rings
  // outter hL -> 7 to 30
  // outter hR -> 95 to 118
  light(pink, 0, 131);
  delay(15);
  
  // black them out
  light(black, 0, 131);
  delay(35);
  
  light(pink, 0, 131);
  delay(15);
  
  // black them out
  light(black, 0, 131);
  delay(35);
  
  light(white, 0, 131);
  delay(15);
  
  // black them out
  light(black, 0, 131);
  delay(35);
  
  // light outer half of rings
  // inner hL -> 30 to 52
  // inner hR -> 72 to 95
  light(white, 30, 52);
  light(white, 72, 95);
  delay(15);
  
  // black them out
  light(black , 30, 52);
  light(black, 72, 95);
  delay(35);
  
  
}

// ele_ring 2.0
void ele_ring2()
{
  uint32_t pink = strip.Color(0, 255, 75);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t black = strip.Color(0, 0, 0);
  
  // light outer half of rings
  // outter hL -> 7 to 30
  // outter hR -> 95 to 118
  light(pink, 7, 30);
  light(pink, 95, 118);
  delay(15);
  
  // black them out
  light(black, 7, 30);
  light(black, 95, 118);
  delay(35);
  
  // light outer half of rings
  // inner hL -> 30 to 52
  // inner hR -> 72 to 95
  light(pink, 30, 52);
  light(pink, 72, 95);
  delay(15);
  
  // black them out
  light(black , 30, 52);
  light(black, 72, 95);
  delay(35);
  
  light(white, 7, 30);
  light(white, 95, 118);
  delay(15);
  
  // black them out
  light(black, 7, 30);
  light(black, 95, 118);
  delay(35);
  
  // light outer half of rings
  // inner hL -> 30 to 52
  // inner hR -> 72 to 95
  light(white, 30, 52);
  light(white, 72, 95);
  delay(15);
  
  // black them out
  light(black , 30, 52);
  light(black, 72, 95);
  delay(35); 
  
}

// quite simply this is used to light a particular portion
// of the system a desired colour
void light(uint32_t c, uint16_t start, uint16_t finish)
{
  while(start <= finish)
  {
 
    strip.setPixelColor(start, c);
    
    start++;
  }
  strip.show();
}

// used to light to separte parts of the the system at the same time
// for example the two rings on either sleeve
void dual_light(uint32_t c, uint16_t start_1, uint16_t finish_1, 
    uint16_t start_2, uint16_t finish_2)
{
  while(start_1 <= finish_2)
  {
    if(start_1 <= finish_1)
      strip.setPixelColor(start_1, c);
      
    if(start_1 >= start_2 && start_1 <= finish_2)
      strip.setPixelColor(start_1, c);
    
    start_1++;
  }

  strip.show();  
}


// vardel = variable delay with the same features as fixed
// a chase around the garment,
// this function has 5 params to customize you preferred chase effect
void vardel_chase(uint32_t c, uint16_t start, 
    uint16_t finish, uint16_t trail, uint16_t wait)
{
    uint32_t black = strip.Color(0, 0, 0);
    while(start <= (finish + trail))
    {
      if(start <= finish)
        strip.setPixelColor(start, c);
        
      strip.setPixelColor(start - trail, black);
      strip.show(); // this needs to be outside the if above
      delay(wait);
      start++;
    } 
}

  // this function performs the opposite as vardel_chase
  // in that it goes the opposite direction starting from the end
  void vardel_chase_back(uint32_t c, uint16_t start, 
    uint16_t finish, uint16_t trail, uint16_t wait)
  {
    uint32_t black = strip.Color(0, 0, 0);
    while(finish + trail > start)
    {
      if(finish > start)
        strip.setPixelColor(finish, c);
        
      strip.setPixelColor(finish + trail, black);
      strip.show(); // this needs to be outside the if above
      delay(wait);
      finish--;
    } 
  }




