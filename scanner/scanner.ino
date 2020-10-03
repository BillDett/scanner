/*

Sweeping right/left scanner for array of LEDs attached to ESP8266 (Wemos D1) GPIO pins.

intensity array denotes the brightness of the 'sweeper'- to simulate a motion blur instead of just
  discrete LEDs blinking on and off.

Should work for any number of PWN compatible GPIO pins.

*/
const int pins[] = {0, 1, 2, 3, 4, 5, 12, 13, 14, 15, 16};
const int numPins = 11;
const int intensity[] = { 1023, 500, 250, 50 };
const int numIntensities = 4;

const int delayms = 50;

int rightward = 1;  // 1 = right, -1 = left
int cycle = 0;

void setup() {
  for (int c=0; c<numPins; c++) {
    pinMode(pins[c], OUTPUT);
  }
}

void scanRight() {
  for (int pre=0; pre<cycle; pre++) {
    if ((cycle-pre) < numIntensities)
      analogWrite(pins[pre], intensity[cycle-pre]);
    else
      analogWrite(pins[pre], 0);
  }
  
  analogWrite(pins[cycle], intensity[0]);
  
  for (int post=cycle+1; post<numPins-1; post++) {
    analogWrite(pins[post], 0);
  }

  delay(delayms);
  
  cycle++;
  if (cycle > numPins-1) {
    cycle = numPins-1;
    rightward *= -1;
  }
}


void scanLeft() {

  for (int pre=0; pre<cycle; pre++) {
    analogWrite(pins[pre], 0);
  }
  
  analogWrite(pins[cycle], intensity[0]);

  for (int post=cycle+1; post<numPins; post++) {
    if ((post-cycle) < numIntensities)
      analogWrite(pins[post], intensity[post-cycle]);
    else
      analogWrite(pins[post], 0);
  }
  
  delay(delayms);
  
  cycle--;
  if (cycle < 0) {
    cycle = 0;
    rightward *= -1;
  }
}


void loop() {
  if (rightward == 1)
    scanRight();
  else
    scanLeft();
}
