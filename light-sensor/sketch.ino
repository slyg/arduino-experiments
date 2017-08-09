const int LED_START      = 6;
const int LED_END        = 13;
const int P_RESISTOR     = A0;
const int P_RESISTOR_MIN = 0;
const int P_RESISTOR_MAX = 255;

int sensVal  = 0;
int ledLimit = LED_START;

void setup() {
  pinMode(P_RESISTOR, INPUT);
  for (int led = LED_START; led <= LED_END; led++){ pinMode(led, OUTPUT); }
}

void loop() {

  sensVal = constrain(analogRead(P_RESISTOR), P_RESISTOR_MIN, P_RESISTOR_MAX);
  ledLimit = map(sensVal, P_RESISTOR_MIN, P_RESISTOR_MAX, LED_START, LED_END);

  for (int led = LED_START; led <= LED_END; led++){
    digitalWrite(led, led <= ledLimit ? HIGH : LOW);
  }
  
}