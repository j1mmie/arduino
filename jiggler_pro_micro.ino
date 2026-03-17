#include <Mouse.h>
#include <math.h>

// Designed for Sparkfun Pro Micro 5v / 16MHz

int RXLED = 17; // The RX LED has a defined Arduino pin

void setup()
{
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  // TX LED is set as an output behind the scenes

  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");

  Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
  Serial1.println("Initialize Serial Hardware UART Pins");
}

const float MAX_RADIUS = 96;
const int STEP_SIZE = 10;
const int SPIN_COUNT = 6;
const int FREQUENCY_MS = 5000;
const int ANIM_DURATION_MS = 1500;

void loop()
{
  float lastX = 0;
  float lastY = 0;

  Serial.println("Starting loop");

  const int loopCount = 360 * SPIN_COUNT;
  const int iterations = loopCount / STEP_SIZE;
  const float halfwayPoint = (float)loopCount / 2.0;
  
  const int frameDelayMs = ANIM_DURATION_MS / iterations;

  for (int i = 0; i < loopCount; i += STEP_SIZE) {
    float percentCircle = (float)i / 360.0;
    float percentFromHalfway = (halfwayPoint - abs(halfwayPoint - i)) / halfwayPoint;
    
    float radians = percentCircle * TWO_PI;
    float radius = percentFromHalfway * MAX_RADIUS;

    float nextX = cos(radians) * radius;
    float nextY = sin(radians) * radius;

    int deltaX = static_cast<int>(nextX - lastX);
    int deltaY = static_cast<int>(nextY - lastY);

    if (deltaX != 0 || deltaY != 0) {
      Mouse.move(deltaX, deltaY, 0);
      lastX = nextX;
      lastY = nextY;
    }

    delay(frameDelayMs);
  }

  delay(FREQUENCY_MS);
}
