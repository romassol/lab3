#include "button.h"
#include <Servo.h>
#include "LedControl.h"

#define PIN_BUTTON 44
#define PIN_SERVO 10

struct Point {
    int x;
    int y;
};

int angle = 0;
int servoDelay = 512;
Button button(PIN_BUTTON);
Servo servo;
Point point;
int cellToDrawNamber;


const int din = 26;
const int clk = 22;
const int cs = 24;
const int displayCount = 1;
const int boardSizeX = 8;
const int boardSizeY = 8;
const int maxAngle = 90;
const int maxServoDelay = 64;
const int delayServoStep = 8;
const int drawDelay = 300;

LedControl ledDisplay = LedControl(din, clk, cs, displayCount);

void setup() {
  Serial.begin(115200);
  servo.attach(PIN_SERVO);
  ledDisplay.shutdown(0, false);
  ledDisplay.setIntensity(0, 10);
  ledDisplay.clearDisplay(0);
  servo.write(0);
}

void loop() {
  if (button.wasUp())
  {
    for(int i=0; i<=angle; i++){
        servo.write(i);
        delay(servoDelay);
    }
    delay(300);
    angle = 0;
    servoDelay = maxServoDelay;
    servo.write(0);
    ledDisplay.clearDisplay(0);
    Serial.println(servoDelay);
  }
  else
  {
    angle = maxAngle;
    servoDelay = max(servoDelay - delayServoStep, 1);
    Serial.println(servoDelay);
    cellToDrawNamber = ((maxServoDelay - servoDelay)/delayServoStep) - 1;
    point.y = servoDelay / boardSizeY;
    for(int i=0; i<=8; i++){
        point.x = i;
        drawPoint(point);
    }
//    point.x = cellToDrawNamber % boardSizeX;
//    point.y = cellToDrawNamber / boardSizeY;

    Serial.println();
    Serial.println(point.x);
    Serial.println(point.y);
    Serial.println();
//    drawPoint(point);
    delay(drawDelay);
  }
}

void drawPoint(Point point)
{
  ledDisplay.setLed(0, boardSizeY - 1 - point.y, point.x, true);
}
