#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

void drawCenteredText(const char* text, int rectX, int rectY, int rectWidth, int rectHeight) {
  int16_t x1, y1;
  uint16_t w, h;

  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int textX = rectX + (rectWidth - w) / 2;
  int textY = rectY + (rectHeight - h) / 2;

  textY += h / 2;

  tft.setCursor(textX, textY);
  tft.print(text);
}

void setup() 
{
  uint16_t identifier = tft.readID();
  tft.begin(identifier);

  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);

  tft.fillRect(90, 10, 300, 140, TFT_WHITE);

  tft.fillRect(15, 170, 220, 70, TFT_WHITE);
  tft.fillRect(15, 250, 220, 70, TFT_WHITE);
  tft.fillRect(245, 170, 220, 70, TFT_WHITE);
  tft.fillRect(245, 250, 220, 70, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);

  drawCenteredText("What is 2 + 2?", 90, 10, 300, 140);
  drawCenteredText("A: 3", 15, 170, 220, 70); 
  drawCenteredText("B: 4", 15, 250, 220, 70);
  drawCenteredText("C: 5", 245, 170, 220, 70);
  drawCenteredText("D: 6", 245, 250, 220, 70);
}

void loop() 
{

}
