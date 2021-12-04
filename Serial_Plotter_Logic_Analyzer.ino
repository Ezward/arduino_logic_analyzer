/*
Simple logic analyzer using the Arduino Serial Plotter.
Readings are initiated by a button connected to D10.
Samples are read inputs D02 to D07 every 100 microseconds.
1500 samples (150 milliseconds) are recorded, then
sent to the serial port in comma delimited format.
*/
const int BUTTON_PIN = 10;

const long delayMicros = 100;

byte data[1500];

void setup (void)
{
  //
  // setup pin D10 for input.
  // This is used for a button to
  // trigger a reading
  //
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  //
  // set pins 02 to 07 as inputs
  // These are the pins that we
  // read and send to the plotter
  //
  DDRD = DDRD & B00000011;

  Serial.begin(115200);
}
void loop (void)
{
  bool headerSent = false;
  
  //
  // wait for button press
  //
  while(digitalRead(BUTTON_PIN) == LOW) {}

  //
  // read samples every 100 microseconds
  //
  long nextMicros = 0;
  int i = 0;
  while(i < sizeof(data)) {
    long nowMicros = micros();
    if(nowMicros >= nextMicros) {
      data[i++] = (PIND >> 2) &  B00111111;
      nextMicros = nowMicros + delayMicros;
    }
  }

  //
  // send samples to the plotter
  //
  if(!headerSent) {
      Serial.println("D02,D03,D04,D05,D06,D07");
      headerSent = true;
  }
  for (int i = 0; i < sizeof(data); i++) {
    sendDataRow(data[i], 6);
  }
}

void sendDataRow(byte bits, byte count)
{
  if(count > 0) {
    while(--count) {
      Serial.print((bits & 1) + (count << 1));
      Serial.print(",");
      bits >>= 1;
      delay(2);  // delay so plotter goes slowly
    }
    Serial.println(bits & 1);
  }
}