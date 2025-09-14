#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// See: https://github.com/ZinggJM/GxEPD2/blob/master/examples/GxEPD2_HelloWorld/GxEPD2_HelloWorld.ino

#define D1_MINI_CS 15
#define D1_MINI_DC 0
#define D1_MINI_RST 2
#define D1_MINI_BUSY 4

GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(/*CS=D8*/ D1_MINI_CS, /*DC=D3*/ D1_MINI_DC, /*RST=D4*/ D1_MINI_RST, /*BUSY=D2*/ D1_MINI_BUSY));
// GxEPD2_BW<GxEPD2_213, GxEPD2_213::HEIGHT> display(GxEPD2_213(/*CS=D8*/ 15, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));  // didn't work
// GxEPD2_BW<GxEPD2_213_B73, GxEPD2_213_B73::HEIGHT> display(GxEPD2_213_B73(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));  // didn't work

void setup() {
    Serial.begin(115200);
    while (!Serial);
    delay(3000);  // wait a bit for Serial to really be connected/ready
    Serial.println("Initializing e-Paper display...");

    // Initialize with a baud rate and extra params recommended for Waveshare board
    // with "clever" reset. See: https://github.com/ZinggJM/GxEPD2/blob/master/README.md
    // Might need a pulldown 3.3k on SS pin 
    display.init(115200, true, 2, false);
    display.setRotation(3); // 3 == landscape w/ harness plug at bottom.

    display.setFont(&FreeMonoBold9pt7b); // Example font
    display.setTextColor(GxEPD_BLACK);
    // This works like the low-ram version of U8G2... loops until all blocks are refreshed
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(0, 20);
        display.println(F("    Working Example"));
        display.println(F(" - Wemos D1 Mini"));
        display.println(F(" - Waveshare 2.13\""));
        display.println(F("   e-Paper HAT"));
        display.println(F(" - GxEPD2 Lib v1.6.5"));
        display.println(F(" - 2025/09/14 @ 3:30pm"));
    } while (display.nextPage());

    Serial.println("Display updated.");
}

void loop() {
    // No continuous updates in this simple example, e-paper holds content
}