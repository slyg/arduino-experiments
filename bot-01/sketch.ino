#include <Servo.h>
#define TRIG_LEFT     2
#define PWM_ECHO_LEFT 3

#define TRIG_MIDL     7
#define PWM_ECHO_MIDL 6

#define TRIG_RIGHT     4
#define PWM_ECHO_RIGHT 5

#define PWM_SERVO_RIGHT 9
#define PWM_SERVO_LEFT 10

Servo motor_right;
Servo motor_left;

void setup() {

  motor_right.attach(PWM_SERVO_RIGHT);
  motor_left.attach(PWM_SERVO_LEFT);
  motor_right.write(90);
  motor_left.write(90);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(PWM_ECHO_LEFT, INPUT);

  pinMode(TRIG_MIDL, OUTPUT);
  pinMode(PWM_ECHO_MIDL, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(PWM_ECHO_RIGHT, INPUT);

  delay(2000);

  Serial.begin(9600);
}

int get_closest_distance(int trigger, int echo){

    long duration;
    int distance;

    // reset trigger
    digitalWrite(trigger, LOW);
    delayMicroseconds(10);

    // trigger for 10μs,
    // signaling to the sensor to do a 10μs sonic bursts
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10); // the sensor generates sonic bursts during this time
    digitalWrite(trigger, LOW);

    // Compute duration
    // Read the time when the echo comes back
    duration = pulseIn(echo, HIGH); // in μs
    distance = duration * 0.034 / 2; // in cm

    return distance;
}

void go_forward() {
  motor_right.write(70);
  motor_left.write(117);
}


void go_backwards() {
  motor_right.write(117);
  motor_left.write(63);
}

void turn_right() {
  motor_right.write(90);
  motor_left.write(117);
  delay(100);
}

void turn_left() {
  motor_right.write(70);
  motor_left.write(90);
  delay(100);
}

void rotate() {
  motor_right.write(170);
  motor_left.write(170);
  delay(200);
}

void go_stop() {
  motor_right.write(90);
  motor_left.write(90);
}

int leftD;
int midlD;
int rightD;
int closestD;

void loop() {

  leftD   = get_closest_distance(TRIG_LEFT, PWM_ECHO_LEFT);
  midlD   = get_closest_distance(TRIG_MIDL, PWM_ECHO_MIDL);
  rightD  = get_closest_distance(TRIG_RIGHT, PWM_ECHO_RIGHT);

  closestD = min(leftD, min(midlD, rightD));

  if (closestD < 8) {

    if (closestD == leftD) {
      // turn right
      turn_right();
    } else if (closestD == midlD) {
      // go backwards then rotate
      go_backwards();
      delay(200);
      rotate();
    } else if (closestD == rightD) {
      // turn left
      turn_left();
    } else {
      // stop
      go_stop();
    }

  } else {
    go_forward();
  }

  delay(100);

}
