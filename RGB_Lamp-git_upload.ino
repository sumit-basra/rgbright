#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelAnimator.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "auth_token_blynk_app";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your_ssid";
char pass[] = "your_password";

const uint16_t PixelCount = 30;
const uint8_t PixelPin = 12;

int r = 0;
int g = 0;
int b = 0;

int animation_choice = 0;
int switch_value = 0;
int random_choice = 0;
int brightness = 0;

NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> strip ( PixelCount, PixelPin );
NeoPixelAnimator animations(PixelCount, NEO_CENTISECONDS);

void random_seed ( ) {
    uint32_t seed;

    // random works best with a seed that can use 31 bits
    // analogRead on a unconnected pin tends toward less than four bits
    seed = analogRead(0);
    delay(1);

    for (int shifts = 3; shifts < 31; shifts += 3)
    {
        seed ^= analogRead(0) << shifts;
        delay(1);
    }

    // Serial.println(seed);
    randomSeed(seed);
}

BLYNK_WRITE ( V0 ) {

  if ( random_choice == 1 ) {
    random_seed();
    r = random ( 255 );
    g = random ( 255 );
    b = random ( 255 );
    for ( uint16_t pixel = 0; pixel < PixelCount; pixel++ ) {
        RgbColor color = RgbColor ( r, g, b );
        strip.SetPixelColor ( pixel, color) ;
    }
  }
  else {
    r = param[0].asInt();
    g = param[1].asInt();
    b = param[2].asInt();
    for ( uint16_t pixel = 0; pixel < PixelCount; pixel++ ) {
        RgbColor color = RgbColor ( r, g, b );
        strip.SetPixelColor ( pixel, color) ;
    }
  }
  strip.Show();
}

BLYNK_WRITE ( V1 ) {
  switch_value = param.asInt();
}

BLYNK_WRITE ( V3 ) {
  random_choice = param.asInt();
}

BLYNK_WRITE ( V4 ) {
  brightness = param.asInt();
  strip.SetBrightness ( brightness );
  strip.Show ();
}

BLYNK_WRITE ( V5 ) {
  int led_power = param.asInt();
  if ( led_power == 0 ) {
    strip.SetBrightness ( 0 );
  }
  else {
    strip.SetBrightness ( brightness );
    if ( random_choice == 1 ) {
      random_seed();
      for ( uint16_t pixel = 0; pixel < PixelCount; pixel++ ) {
        RgbColor color = RgbColor ( random ( 255 ), random ( 255 ), random ( 255 ) );
        strip.SetPixelColor ( pixel, color) ;
      }
    }
    else {
      for ( uint16_t pixel = 0; pixel < PixelCount; pixel++ ) {
        RgbColor color = RgbColor ( r, g, b );
        strip.SetPixelColor ( pixel, color) ;
      }
    }
  }
  strip.Show ();
}

void setup () {

  Serial.begin ( 9600 );

  Blynk.begin ( auth, ssid, pass );

  strip.Begin();
  strip.Show();

  random_seed();
}

void loop () {
  Blynk.run();
}
