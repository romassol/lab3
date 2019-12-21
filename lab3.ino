#include "button.h"
#include <Servo.h>
#include "LedControl.h"

#define PIN_BUTTON 44
#define PIN_SERVO 10

int angle = 0;
int servoDelay = 512;
Button button(PIN_BUTTON);
Servo servo;
int cellToDrawNamber;
bool buttunWasDown = false;


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
  servo.attach(PIN_SERVO);
  ledDisplay.shutdown(0, false);
  ledDisplay.setIntensity(0, 10);
  setInitState();
}

void loop() {    
  if (!button.isUp())
  {
    buttunWasDown = true;
    servoDelay = max(servoDelay - delayServoStep, 1);
    drawRow(servoDelay / boardSizeY);
    delay(drawDelay);
  }
  if (button.isUp() && buttunWasDown)
  {
    turnServo();
    delay(300);
    setInitState();
    buttunWasDown = false;
  }
}

void setInitState()
{
  ledDisplay.clearDisplay(0);
  servo.write(0);
  servoDelay = maxServoDelay;
}

void turnServo()
{
  for(int i=0; i<=maxAngle; i++){
      servo.write(i);
      delay(servoDelay);
  }
}

void drawRow(int y){
  for(int i=0; i<=8; i++){
      drawPoint(i, y);
  }
}

void drawPoint(int x, int y)
{
  ledDisplay.setLed(0, boardSizeY - 1 - y, x, true);
}
