// test using the NeoBuffer with Blt to load strips after a buffer has been created, simple blt example, full buffer dump to single strip.

#include <NeoPixelBus.h>
#include <arduino.h>

// manually configure these params:
const uint16_t strip01_PixelCount = 18;
const uint8_t strip01_PixelPin = 2;

//const uint16_t strip02_PixelCount = 0;
//const uint8_t strip02_PixelPin = 13;

// calculate total pixel count for use later:
//const uint16_t totalPixelCount = strip01_PixelCount + strip02_PixelCount;

const uint16_t totalPixelCount = strip01_PixelCount;

//create two new NeoPixelBus objects:  strip01, and strip02, set the number of pins and the output pin for each in this object:
//notice the channel difference here for the RMT method defintion: 0,1,2,3,4,5,6,7  can only use each channel once, so max of 8 pins using this method on ESP32.

// create the needed NeoPixelBus objects used to drive the pins:
// these are the "output" objects, but we'll use a "buffer" to collect the led color info, then assign peices of the buffer to these real pins:
NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod> strip01(strip01_PixelCount, strip01_PixelPin);
//NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1Ws2812xMethod> strip02(strip02_PixelCount, strip02_PixelPin);

// create the "input" LED array to store the LED data, use the "buffer" method so the LEDs array can be used later:
// wants    name, width, height, pixels
//
//  The buffer is a bitmap. so it has a height, width. Our use case is a single "strip" of leds put together by WLED
//  so the width of this bitmap really represents our total pixel count:
//
NeoBuffer<NeoBufferMethod<NeoGrbFeature>> strip00(totalPixelCount,1,NULL);


#define colorSaturation 128

// four element pixels, RGBW
//NeoPixelBus<NeoRgbwFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);

// create a new layout map for later use to move the buffer pixels out to NeoPixelBus objects
// in our case, width is equal to total pixel count, and height is 1, since its not a panel.
//NeoTopology<RowMajorLayout> topo(totalPixelCount, 1);

//uint16_t LayoutMap(int16_t x, int16_t y)
//{
//  return topo.MapProbe(x, y);
//}

void setup()
{
    //Serial.begin(115200);
    //while (!Serial); // wait for serial attach

    //Serial.println();
    //Serial.println("Initializing...");
    //Serial.flush();

    // required init:
    strip01.Begin();
    //strip02.Begin();

    // reset them to off:
    strip01.Show();
    //strip02.Show();

    // set the entire buffer to black color to set off for all pixels:
    strip00.ClearTo(black);

    //Serial.println();
    //Serial.println("setup area done...");
}


void loop()
{


// assign color to the buffer object LEDs instead: (notice the x/y coordiinate, just use 0 since we're using a "single row" bitmap)

    strip00.SetPixelColor(17,0, red);
    strip00.SetPixelColor(16,0, green);
    strip00.SetPixelColor(15,0, blue);
    strip00.SetPixelColor(14,0, white);
    strip00.SetPixelColor(13,0, red);
    strip00.SetPixelColor(12,0, green);
    strip00.SetPixelColor(11,0, blue);
    strip00.SetPixelColor(10,0, white);
    strip00.SetPixelColor(9,0, red);
    strip00.SetPixelColor(8,0, green);
    strip00.SetPixelColor(7,0, blue);
    strip00.SetPixelColor(6,0, white);
    strip00.SetPixelColor(5,0, red);
    strip00.SetPixelColor(4,0, green);
    strip00.SetPixelColor(3,0, blue);
    strip00.SetPixelColor(2,0, white);
    strip00.SetPixelColor(1,0, red);
    strip00.SetPixelColor(0,0, green);


    //using simplified Blt method:

    strip00.Blt(strip01, 0);


    strip01.Show();


    delay(2000);

}


