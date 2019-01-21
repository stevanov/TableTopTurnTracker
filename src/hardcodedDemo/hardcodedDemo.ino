#include <FastLED.h>

#define NUM_LEDS 100
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

void setup() {
   delay(2000);
  Serial.begin(9600);
//  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  
  byte numPlayers = 5; //user input eventually
  byte playerSegmentSize = floor(NUM_LEDS / numPlayers);
  uint32_t playerColours[] = {0xff0000, 0x00ff00, 0x0000ff, 0xffff00, 0xff00ff, 0xffffff, 0x00ffff};
  struct playerLeds_t {
    byte first;
    byte last;
    uint32_t colour;
  } playerLeds[numPlayers];
  
  byte offset = 0;  
  for (int i = 0; i < numPlayers; i++)
  {
    playerLeds[i].colour = playerColours[i];
    playerLeds[i].first = 0 + offset;
    playerLeds[i].last = (playerSegmentSize - 1) + offset;
    offset = offset + playerSegmentSize;
  }

  for (int i = 0; i < numPlayers; i++)
  {
    Serial.println(playerLeds[i].first);
    Serial.println(playerLeds[i].last);
    Serial.println();

//    leds[playerLeds[i].first] = playerColours[i];
//    leds[playerLeds[i].last] = playerColours[i];
    for (int j = 0; j < playerSegmentSize; j++) 
    {
      leds[playerLeds[i].first+j] = playerColours[i];
      FastLED.show();
      FastLED.delay(25);
    }
    for (int j = 0; j < 3; j++)
    {
      fill_solid( &(leds[playerLeds[i].first]), playerSegmentSize, 0x000000);
      FastLED.show();
      FastLED.delay(125);
      fill_solid( &(leds[playerLeds[i].first]), playerSegmentSize, playerColours[i]);
      FastLED.show();
      FastLED.delay(50);
    }
    for (int j = 0; j < playerSegmentSize; j++) 
    {
     leds[playerLeds[i].first+j].fadeToBlackBy( 240 );
     FastLED.show();
     FastLED.delay(1000);
    }
  }

//  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
//    leds[whiteLed] = CRGB::White;
//    FastLED.show();
//    delay(100);
//    leds[whiteLed] = CRGB::Black;
//  }
}
