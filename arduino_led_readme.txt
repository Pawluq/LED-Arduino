SETUP
 - The Adafruit NeoPixel library is used for controlling the LED strip
    > It's necessary to create an Adafruit NeoPixel object to use the library
    > The parameters represent the following values:
        LED_COUNT: Amount of LEDs on the connected strip
        LED_PIN:   Pin connected to the LED strip
        NEO_GRB + NEO_KHZ800: Can usually be left unchanged; refer to the Adafruit NeoPixel documentation

 - setup() is called once on startup
    > Setup the LED strip by calling strip.begin()
    > Clear (= remove currently set colors) from all LEDs with strip.clear()
    > strip.show() updates the display of all LEDs

 - Serial.begin() enables Bluetooth communication via the designated Serial pin
 - Alternatively, using SoftwareSerial is possible if the Serial functionality should be delegated to
   another pin instead

LOOP
 - loop() is called continuously
 - First if-statement automatically clears the LED strip if no input is received for TIMEOUT_INTERVAL minutes

 - Serial.available() returns the number of bytes that were received but not read
 - Read the bytes sequentially and store them in a char[] array
 - A delay of 5 milliseconds in between reading ensures that bytes are not read faster than they are received

 - As soon as the character limit is reached or no bytes are left to read, the input is processed
 - currentTimeout is reset to TIMEOUT_INTERVAL minutes
 - memset() clears the char[] array

COLOR
 - The switch statement cannot be used when comparing more than one character
 - Suitable alternatives for comparing more than one character are strcmp() and strncmp()

 - strip.fill() sets the color of all LEDs
 - strip.setPixelColor() can be used instead if the color should be set only for individual pins
 - It's important that the sum of RGB values in every color must not exceed 255; otherwise, the LED strip
   will consume too much power and shut down in a matter of time

DEPLOYING
 - Disconnect the Bluetooth adapter from the Arduino board before uploading
 - In the Arduino IDE (or online), select 'Sketch > Upload' and wait for the process to finish
