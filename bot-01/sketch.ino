#include <Servo.h>
#define PWM_TRIG 5
#define PWM_ECHO 6
#define PWM_SERVO_RIGHT 9
#define PWM_SERVO_LEFT 10

Servo motor_right;
Servo motor_left;

void setup() {

  motor_right.attach(PWM_SERVO_RIGHT);
  motor_left.attach(PWM_SERVO_LEFT);
  motor_right.write(90);
  motor_left.write(90);

  pinMode(PWM_TRIG, OUTPUT);
  pinMode(PWM_ECHO, INPUT);

  delay(2000);
}

int get_closest_distance(){

    long duration;
    int distance;

    // reset trigger
    digitalWrite(PWM_TRIG, LOW);
    delayMicroseconds(10);

    // trigger for 10μs,
    // signaling to the sensor to do a 10μs sonic bursts
    digitalWrite(PWM_TRIG, HIGH);
    delayMicroseconds(10); // the sensor generates sonic bursts during this time
    digitalWrite(PWM_TRIG, LOW);

    // Compute duration
    // Read the time when the echo comes back
    duration = pulseIn(PWM_ECHO, HIGH); // in μs
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

void turn() {
  motor_right.write(170);
  motor_left.write(170);
  delay(200);
}

void go_stop() {
  motor_right.write(90);
  motor_left.write(90);
}

void loop() {

  if (get_closest_distance() < 5) {
    go_stop();
    delay(100);
    go_backwards();
    delay(200);
    turn();
  } else {
    go_forward();
  }

  delay(50);

}
