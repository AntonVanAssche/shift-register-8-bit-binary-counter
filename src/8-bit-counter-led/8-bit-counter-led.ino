#define latchPin 8 // Pin 8 is connected to the latch pin (`ST_CP`) of the shift register.
#define clockPin 12 // Pin 12 is connected to the clock pin (`SH_CP`) of the shift register.
#define dataPin 11 // Pin 11 is connected to the data pin of the shift register.
#define buzzPin 2 // Pin 2 is connected to the buzzer.

int ledDelay = 1000; // The delay between each LED being turned on.

void setup() {
   pinMode(latchPin, OUTPUT); // Set the latch pin as an output.
   pinMode(clockPin, OUTPUT); // Set the clock pin as an output.
   pinMode(dataPin, OUTPUT); // Set the data pin as an output.

   pinMode(buzzPin, OUTPUT); // Set the buzzer pin as an output.
}

// Note the datatype of `dataOut` is a byte, since 1 byte = 8 bits.
void shiftOut(byte dataOut) {
   // Shift out 8 bits LSB first, on the rising edge of the clock.
   // Note that the clock pin is left low at the end of the function.

   // Initialize a boolean `pinState` to keep track of the current pin state.
   boolean pinState;

   // Clear shift register.
   digitalWrite(dataPin, LOW); // Set data pin low.
   digitalWrite(clockPin, LOW); // Set the clock pin low.

   // Shift out the data.
   // We want to send out a bit for each bit in `dataOut`.
   // Therefore we need to loop 8 times.
   for (int i = 0; i < 8; i++) {
      digitalWrite(clockPin, LOW); // Set the clock pin low before sending out a bit.

      // If the value of `dataOut` AND a `bitmask` result is true, set the pin to high.
      // Keep in mind that the `&` is a bitwise AND operation.
      if (dataOut & (1 << i)) {
         pinState = HIGH;
      } else {
         pinState = LOW;
      }

      // Set the data pin to the value of `pinState`.
      digitalWrite(dataPin, pinState);

      // Set the clock pin high to signal that the bit is sent.
      digitalWrite(clockPin, HIGH);
   }

   // Stop shifting out data.
   digitalWrite(clockPin, LOW); // Set the clock pin low.
}

void loop() {
   // Count from 0 to 255.
   for (int i = 0; i < 256; i++) {
      // Set the latch pin low to allow data flow.
      digitalWrite(latchPin, LOW);

      // Use our `shiftOut` method to shift out the data.
      // This is will basically do the same as the built-in `shiftOut`
      // method when we use the `MSBFIRST` option.
      shiftOut(i);

      // Set the latch pin high to stop data flow.
      digitalWrite(latchPin, HIGH);

      // Power the buzzer for a short time.
      // THIS ISN'T NECESSARY, BUT IT MAKES THE EXPERIENCE MORE FUN!
      // SO DEEL WITH IT!
      digitalWrite(buzzPin, HIGH);
      delay(10);
      digitalWrite(buzzPin, LOW);

      // Wait for the next LED to be turned on.
      delay(ledDelay);
   }
}

