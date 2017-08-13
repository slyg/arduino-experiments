#define PWM_TRIG 9
#define PWM_ECHO 10
#define DELIMITER "\n" // used to separate each message

long duration;
int distance;

void setup() {

  pinMode(PWM_TRIG, OUTPUT);
  pinMode(PWM_ECHO, INPUT);

  Serial.begin(9600);
}

void loop() {

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
  distance = duration*0.034/2; // in cm

  Serial.print(distance);
  Serial.print(DELIMITER);

}
