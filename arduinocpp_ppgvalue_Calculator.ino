const int PPG_PIN = A0;

const int NUM_SAMPLES = 3000;
const int SAMPLE_DELAY = 10;   // 10 ms = 100 Hz

void setup()
{
  Serial.begin(115200);

  delay(3000);   // Gives you time to place your finger

  Serial.println("ppg = [");

  for(int i = 0; i < NUM_SAMPLES; i++)
  {
    int value = analogRead(PPG_PIN);

    Serial.print(value);

    if(i != NUM_SAMPLES - 1)
      Serial.print(",");

    if((i + 1) % 10 == 0)
      Serial.println();

    delay(SAMPLE_DELAY);
  }

  Serial.println("]");
}

void loop()
{
}