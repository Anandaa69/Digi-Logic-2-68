const int ledPin = 32;
const int ledChannel = 0;
const int resolution = 8;
const int freq = 10;
const int maxDuty = 255;
void setup() {
  Serial.begin(115200);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  for(int dutyCycle = 0; dutyCycle <= maxDuty; dutyCycle++){   
    ledcWrite(ledChannel, dutyCycle);
    Serial.println(dutyCycle);
    delay(30);
  }
}
