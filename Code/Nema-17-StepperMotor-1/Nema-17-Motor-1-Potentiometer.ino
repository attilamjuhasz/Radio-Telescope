const int stepPin = 2;
const int dirPin  = 5;
const int potPin  = A0;

// Delay range (microseconds): larger = slower, smaller = faster
const int maxDelayMicros = 2000; // at 0° -> slowest
const int minDelayMicros = 700;  // at 180° -> fastest

// Dead zone (degrees) around 0 where motor is stopped
const int deadbandDegrees = 30;

// Calibration time (ms) — move pot to both ends during this time
const unsigned long calibTimeMs = 3000;

int rawMin = 1023;
int rawMax = 0;
int smoothedRaw = 512;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);

  // --- Auto-calibration: sample the pot for calibTimeMs to find raw min/max ---
  unsigned long start = millis();
  while (millis() - start < calibTimeMs) {
    int r = analogRead(potPin);
    if (r < rawMin) rawMin = r;
    if (r > rawMax) rawMax = r;
    delay(5);
  }

  // Fallback if the user didn't move the pot or measured range is tiny
  if (rawMax - rawMin < 50) {
    rawMin = 0;
    rawMax = 1023;
  }

  // initialize the smoother with the midpoint
  smoothedRaw = (rawMin + rawMax) / 2;
}

void loop() {
  int raw = analogRead(potPin);

  // simple exponential smoothing to reduce jitter
  smoothedRaw = (smoothedRaw * 7 + raw) / 8;

  float angle = rawToAngle(smoothedRaw); // -180 .. +180

  // Deadband: motor off if within ±deadbandDegrees around center
  if (fabs(angle) <= deadbandDegrees) {
    digitalWrite(stepPin, LOW); // ensure STEP is low
    delay(10);
    return;
  }

  // Direction: positive angle -> clockwise, negative -> counterclockwise
  if (angle > 0) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }

  // Map speed: 0° -> slowest, 180° -> fastest
  int stepDelay = map((int)fabs(angle), 0, 180, maxDelayMicros, minDelayMicros);

  // Single step pulse
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(stepDelay);
}

// Convert calibrated raw ADC value to angle in degrees (-180..+180)
float rawToAngle(int r) {
  int center = (rawMin + rawMax) / 2;
  if (r == center) return 0.0f;

  if (r < center) {
    // map center..rawMin -> 0..-180
    float denom = float(center - rawMin);
    if (denom <= 0.0f) return -180.0f;
    return - (float)(center - r) / denom * 180.0f;
  } else {
    // map center..rawMax -> 0..+180
    float denom = float(rawMax - center);
    if (denom <= 0.0f) return 180.0f;
    return (float)(r - center) / denom * 180.0f;
  }
}
