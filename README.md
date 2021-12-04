# Serial Plotter Logic Analyzer
This is a simple hacky logic analyzer that displays results using the Arduino IDE's serial plotter.


- Readings are initiated by a button connected to D10.
- Samples are read inputs D02 to D07 every 100 microseconds.
- 1500 samples (150 milliseconds) are recorded, then sent to the serial port in comma delimited format.
- The results are sent after all readings are made.  They are sent slowly so the user can see them pass by since the serial plotter does not allow scrolling/scrubbing.

