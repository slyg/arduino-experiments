#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define LED_R 9
#define LED_G 10
#define LED_B 11

int frequency   = 0;
int intensity_R = 0;
int intensity_G = 0;
int intensity_B = 0;

// Maps frequency invert to color code intensity [0-255]
int colourIntensity(int frequency, int min_, int max_){
  return constrain(map(frequency, min_, max_, 255, 0), 0, 255);
}

String guessedColour (int r, int g, int b) {
  if (r > g && r > b) {
    return "Red-ish";
  }
  if (g > r && g > b) {
    return "Green-ish";
  }
  if (b > r && b > g) {
    return "Blue-ish";
  }
  return "White-ish";
}

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Frequency-scaling 20 %
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  Serial.begin(9600);

}

void loop() {

  // ---------------- RED ----------------
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  frequency = pulseIn(sensorOut, LOW);
  intensity_R = colourIntensity(frequency, 8, 40);

  // ---------------- Green ----------------
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  frequency = pulseIn(sensorOut, LOW);
  intensity_G = colourIntensity(frequency, 8, 50);

  // ---------------- Blue ----------------
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  frequency = pulseIn(sensorOut, LOW);
  intensity_B = colourIntensity(frequency, 6, 40);

  // ---------------- Update LED ----------------
  analogWrite(LED_R, intensity_R);
  analogWrite(LED_G, intensity_G);
  analogWrite(LED_B, intensity_B);

  // ---------------- Print guessed colour ----------------
  Serial.print(guessedColour(intensity_R, intensity_G, intensity_B));
  Serial.println();

}
