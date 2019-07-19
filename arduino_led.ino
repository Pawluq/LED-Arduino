/* Receives messages through serial communication and changes
 * the color of all attached LED pixels accordingly.
 * 
 * Notes:
 *  - Uncomment SoftwareSerial and all related code if pins other than
 *    the predefined ones should be used for serial communication
 */

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 6
#define LED_COUNT 40
#define SERIAL_SPEED 9600
#define BUFFER_SIZE 10

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t RED = strip.Color(255, 0 , 0);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t YELLOW = strip.Color(128, 127, 0);
uint32_t PINK = strip.Color(139, 10, 80);
uint32_t ORANGE = strip.Color(205, 50, 5);

int index = 0;
char readColorCode[BUFFER_SIZE];
unsigned long TIMEOUT_INTERVAL = 5 * 60 * 1000UL;
unsigned long currentTimeout = millis() + TIMEOUT_INTERVAL;

void setup() {
  strip.begin();
  strip.clear();
  strip.show();
  strip.setBrightness(50);
  Serial.begin(SERIAL_SPEED);
  while (!Serial) {} // Wait for serial port to connect
}

void loop() {
  if ((long)(millis() - currentTimeout) >= 0) {
    strip.clear();
    strip.show();
    currentTimeout += TIMEOUT_INTERVAL;
  }
  
  if (Serial.available() > 0) {
    while (Serial.available() > 0 && index < BUFFER_SIZE) {
      readColorCode[index] = Serial.read();
      index++;
      delay(5);
    }
    processColorCode();
    index = 0;
    currentTimeout = millis() + TIMEOUT_INTERVAL;
    memset(readColorCode, 0, sizeof(readColorCode));
  }
}

void processColorCode() {
  switch (readColorCode[0]) {
    case 'R':
      setColor(RED);
      break;
    case 'G':
      setColor(GREEN);
      break;
    case 'B':
      setColor(BLUE);
      break;
    case 'Y':
      setColor(YELLOW);
      break;
    case 'P':
      setColor(PINK);
      break;
    case 'O':
      setColor(ORANGE);
      break;
    default:
      Serial.println("ERROR - Color not recognized. Skipping operation");
      break;
  }
}

void setColor(uint32_t color) {
  strip.fill(color);
  strip.show();
}
