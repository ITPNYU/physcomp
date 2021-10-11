/*
  This reads a wave file from an SD card and plays it
  using the I2S interface to an I2S Amp Breakout board.
  It's been tested with the UDA1334A and the MAX98357 amps.

  The wav file must be stereo signed 16 bit 44100Hz.

  Circuit:
     Arduino/Genuino Zero or MKR series board
     SD breakout or shield connected. If using the MKRZero,
   the on-board SD card will work.
     .wav file called SOUND.WAV on the card
     
     Amp wiring:
     GND connected GND
     VIN connected Vdd
     LRCLK (aka WSEL) connected to:
        - pin 3 (MKR1000, MKRZero)
        - pin 0 (Zero)
        - pin A2 (Nano 33 IoT)
     BCLK connected to:
        - pin 2 (MKR1000, MKRZero)
        - pin 1 (Zero)
        - pin A3 (Nano 33 IoT)
     DIN connected to:
        - pin A6 (MKR1000, MKRZero)
        - pin 9 (Zero)
        - pin 4 (Nano 33 IoT)

  created 24 Sep 2021
  modified 11 Oct 2021
  by Tom Igoe
*/

#include <SD.h>
#include <ArduinoSound.h>
#define I2S_DEVICE 1   // this enables the I2C bus

// filename of wave file to play
// file name must be 8chars . 3 chars
const char filename[] = "MUSIC.WAV";

// variable representing the Wave File
SDWaveFile waveFile;
// timestamp for printing the current time:
long lastPrintTime = 0;

void setup() {
  // Open serial communications:
  Serial.begin(9600);
  // wait for serial  monitor to open:
  while (!Serial);

  // setup the SD card.
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("SD card initialization failed!");
    while (true); // do nothing
  }
  Serial.println("SD card is valid.");

  // create a SDWaveFile
  waveFile = SDWaveFile(filename);

  // check if the WaveFile is valid
  if (!waveFile) {
    Serial.print("There is no .wav file called ");
    Serial.println(filename);
    while (true); // do nothing
  }
  // print the file's duration:
  long duration = waveFile.duration();
  Serial.print("Duration = ");
  Serial.print(duration);
  Serial.println(" seconds");

  // check if the I2S output can play the wave file
  if (!AudioOutI2S.canPlay(waveFile)) {
    Serial.println("unable to play wave file using I2S");
    while (true); // do nothing
  }

  // set the playback volume:
  AudioOutI2S.volume(80);
  // start playback
  Serial.println("playing file");
  AudioOutI2S.play(waveFile);
}

void loop() {
  // the play function is non-blocking, so you can do
  // other things while the file plays. Here are a few examples:

  // print the current playing time, once a second:
  if (millis() - lastPrintTime > 1000) {
    Serial.print(waveFile.currentTime());
    Serial.println( " seconds");
    lastPrintTime = millis();
  }
  
  // if the file is no longer playing, print that:
  if (!AudioOutI2S.isPlaying()) {
    Serial.println("File has stopped");
    while (true); // do nothing
  }
  
  // if the file is paused, print that
  // (n.b. nothing in this sketch can cause a pause,
  // but you could add one):
  if (AudioOutI2S.isPaused()) {
    Serial.println("File is paused");
  }
}
