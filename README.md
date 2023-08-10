# Serial Plotter Logic Analyzer
This is a simple hacky logic analyzer that uses an Arduino Nano or Uno to collect a batch of samples from input phins then displays results using the Arduino IDE's serial plotter.


- Readings are initiated by a button connected to D10.
- Samples are read from input pins D02 to D07 every 100 microseconds.
- 1500 samples (150 milliseconds) are recorded, then printed to the serial port in comma delimited format.
- The results are sent after all readings are made.  They are sent slowly so the user can see them pass by since the serial plotter does not allow scrolling/scrubbing.

To use:
- Connect the TTL signals that you wish to measure to Arduino pins D02 to D07.  It if ok to leave some of those pins empty; they will just read low.
- Connect a momentary button using a pull down resistor to Arduino D10
- Upload the sketch to the Arduino
- Open the Arduino Serial Plotter in the Arduino IDE using 115200 baud.
- Start the process you wish to record and then press the button to begin recording.
- Switch to the Arduio Serial Plotter to see the readings scroll by.

Notes
- The sketch presumes Arduino Uno or Nano as it uses DDRD and PIND to read from a bank on input pins simulaneously.
- This will work to read pins from a 3.3v.
