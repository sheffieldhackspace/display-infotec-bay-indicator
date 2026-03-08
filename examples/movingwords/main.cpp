/**
 * Moving words
 */

#include <Arduino.h>
#include <BayIndicator.h>

BayIndicator display1 = BayIndicator(D5, D6, D4);
BayIndicator display2 = BayIndicator(D8, D7, D9);

uint16_t topX = 0;
uint16_t topY = 1;
uint16_t bottomX = 0;
uint16_t bottomY = 1;

int8_t topDirection = 1;
int8_t bottomDirection = -1;

int16_t x, y;
uint16_t w, h;

void setup() {
  delay(1000);

  display1.begin();
  display2.begin();

  Serial.begin(115200);
  display2.getTextBounds("Hackspace", bottomX, bottomY, &x, &y, &w, &h);
  bottomX = 191 - w;
  Serial.println(bottomX);
}

void loop() {
  if (topDirection == -1 && topX == 0) {
    topDirection = 1;
  }

  display1.getTextBounds("Sheffield", topX, topY, &x, &y, &w, &h);

  if (topDirection == 1 && x + w >= 191) {
    topDirection = -1;
  }

  if (bottomDirection == -1 && bottomX == 0) {
    bottomDirection = 1;
  }

  display2.getTextBounds("Hackspace", bottomX, bottomY, &x, &y, &w, &h);

  if (bottomDirection == 1 && x + w >= 191) {
    bottomDirection = -1;
  }

  display1.fillScreen(0);
  display1.setCursor(topX, topY);
  display1.print("Sheffield");

  display2.fillScreen(0);
  display2.setCursor(bottomX, bottomY);
  display2.print("Hackspace");
  
  display1.display();
  display2.display();

  topX += topDirection;
  bottomX += bottomDirection;
}
