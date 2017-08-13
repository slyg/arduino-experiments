#include <Servo.h>
#define PWM_SERVO 9

const int PI_proportion = 4;  // Number of PI divisions where the servo stops
const int PI_delay = 200;     // Delay (ms) given to the servo to accomplish a PI/PI_proportion angle

Servo servo;

void setup() {
  servo.attach(PWM_SERVO);
  servo.write(0);
  delay(100);
}

void loop() {
  for (int piRatio = 0; piRatio <= PI_proportion; piRatio++){
    servo.write(map(piRatio, 0, PI_proportion, 0, 180));
    delay(PI_delay);
  }
  for (int piRatio = 0; piRatio <= PI_proportion; piRatio++){
    servo.write(map(piRatio, 0, PI_proportion, 180, 0));
    delay(PI_delay);
  }
}
