#include <FastLED.h>
//# of leds
#define NUM_LEDS 140
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

float smoothed = 0;
float baseline = 0;
float peak = 0;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  //lots of leds, set cap on power
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 4000);
 Serial.begin(115200);
  //stabilizing
 long total = 0;
 for (int i = 0; i < 500; i++) {
  total += analogRead(A0);
  delay(2);
 }
 baseline = total / 500;
}

void loop() {
  //read and smooth
  int soundValue = analogRead(A0);
  smoothed = (smoothed * 0.97) + (soundValue * 0.03);

  //sound level
  int soundLevel = abs(smoothed - baseline);
  if (soundLevel < 15) soundLevel = 0;

  //peak with faster decay for more reactivity
  if (soundLevel > peak) {
    peak = soundLevel;
  } else {
    peak = peak * 0.85;
  }

  // map peak to leds [lower ceiling = more sensitive (this is the "80" on the map)]
  int ledsLit = map(peak, 0, 80, 0, NUM_LEDS);
  ledsLit = constrain(ledsLit, 0, NUM_LEDS);

  //gradient purple to blue lawlawl
  CRGB colorA = CRGB(148, 0, 211);
  CRGB colorB = CRGB(0, 0, 255);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledsLit) {
      uint8_t blendAmount = map(i, 0, NUM_LEDS, 0, 255);
      leds[i] = blend(colorA, colorB, blendAmount);
    } else {
      //ambient glow when not lit by sound, nonlit leds too boring
      leds[i] = CRGB(20, 0, 30);
    }
}
  

  FastLED.show();

  Serial.print(soundLevel);
  Serial.print(",");
  Serial.println(peak);

  delay(10);
}