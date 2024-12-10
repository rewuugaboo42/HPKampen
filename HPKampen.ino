#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

void setup() 
{
  // Initialize the TFT
  uint16_t identifier = tft.readID();
  tft.begin(identifier);

  // Set the rotation (0-3 for different orientations)
  tft.setRotation(1); // Landscape mode

  // Set the background color
  tft.fillScreen(TFT_BLACK);

  // Draw a rectangle (x, y, width, height, color)
  tft.drawRect(50, 50, 100, 60, TFT_WHITE);

  // Fill a rectangle (x, y, width, height, color)
  tft.fillRect(100, 100, 50, 30, TFT_BLUE);
}

void loop() 
{
  
}
