/*
Simple logic analyzer using the Arduino Serial Plotter.
Readings are initiated by a button connected to D10.
Samples are read inputs D02 to D07 every 100 microseconds.
1500 samples (150 milliseconds) are recorded, then
sent to the serial port in comma delimited format.
*/
const int BUTTON_PIN = 10; // button initiates readings when it goes from low to high
const long PRINT_DELAY_MILLIS = 10;  // wait 10ms between each reading when printing to serial port
const int NUMBER_OF_READINGS = 1500;  // number of one-byte readings to make (1500 for Arduino UNO, but could be more with another microcontroller)
const long DELAY_MICROS = 100;  // microseconds between each reading

byte data[NUMBER_OF_READINGS];

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
      nextMicros = nowMicros + DELAY_MICROS;
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
    delay(10);  // delay so plotter goes slowly
  }
}

void sendDataRow(byte bits, byte count)
{
  if(count > 0) {
    while(--count) {
      Serial.print((bits & 1) + (count << 1));
      Serial.print(",");
      bits >>= 1;
    }
    Serial.println(bits & 1);
  }
}
