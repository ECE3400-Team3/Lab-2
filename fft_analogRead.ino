/*
fft_adc_serial.pde
guest openmusiclabs.com 7.7.14
example sketch for testing the fft library.
it takes in data on ADC0 (Analog0) and processes them
with the fft. the data is sent out over the serial
port at 115.2kb.
*/

#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
#define AMP_THRESHOLD 50 
#define FFT_TRIGGER 5

#include <FFT.h> // include the library
int threshold = AMP_THRESHOLD;
int fft_counter = 0; //for false positives

void setup() {
  Serial.begin(9600); // use the serial port
}

void loop() {
  while(1) { // reduces jitter
    //cli();  // UDRE interrupt slows this way down on arduino1.0 TODO: check if needed
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      int k = analogRead(A1);
      //Serial.println(k);
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    //sei(); //TODO: check if needed
    if (fft_counter > FFT_TRIGGER) {
      Serial.println("On");
    }
    for (byte i = 0 ; i < FFT_N/2 ; i++) { // TODO: check if needed 
      if ( i == 19 ) {
        Serial.println(fft_log_out[i]); // send out the data
        if (fft_log_out[i] > threshold) {
          fft_counter+=1;
        } else (
          fft_counter=0;
        }
      } 
    }
  }
}
