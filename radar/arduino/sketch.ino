#include <Servo.h>
#define PWM_TRIG 9
#define PWM_ECHO 10
#define PWM_SERVO 11
#define DELIMITER "\n" // used to separate each message

const int PI_proportion = 90;  // Number of PI divisions where the servo stops
const int PI_delay = 10;       // Delay (ms) given to the servo to accomplish a PI/PI_proportion angle

long duration;
int distance;
int angle;

Servo servo;

int measureDistance(){
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
  return duration*0.034/2; // in cm;
}

void sendData(int a, int d){
  Serial.print(a);
  Serial.print(",");
  Serial.print(d);
  Serial.print(DELIMITER);
}

void setup() {

  pinMode(PWM_TRIG, OUTPUT);
  pinMode(PWM_ECHO, INPUT);

  servo.attach(PWM_SERVO);
  servo.write(0);

  // let the servo time to reach the initial angle
  delay(100);

  Serial.begin(9600);

}

void loop() {

  for (int piRatio = 0; piRatio <= PI_proportion; piRatio++){
    angle = map(piRatio, 0, PI_proportion, 0, 180);
    servo.write(angle);
    delay(PI_delay);
    distance = measureDistance();
    sendData(angle, distance);
  }
  for (int piRatio = 0; piRatio <= PI_proportion; piRatio++){
    angle = map(piRatio, 0, PI_proportion, 180, 0);
    servo.write(angle);
    delay(PI_delay);
    distance = measureDistance();
    sendData(angle, distance);
  }

}
