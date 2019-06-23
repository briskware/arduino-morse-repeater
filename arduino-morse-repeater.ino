/**
 * Morse Code Repeater
 * 
 * Parses the incoming morse code string on the Serial interface
 * and sends the accurate duration signals to the internal Arduino LED (pin 13)
 * 
 * A dot is defined as a standard Aviation Navaid duration of 110ms. All other durations are derived from this value.
 * 
 * Accepts the following characters:
 * '.' -> dot
 * '-' -> dash (3 dots)
 * ' ' -> space between letters (3 dots)
 * '/' -> space betweeen words (same effect as CR or LF) (7 dots)
 * 
 * Author: Stefan Szaniszlo <stefan@briskware.com>
 */
int time_unit_ms = 110; //aviation navaid dot duration in ms.
int dot_ms = time_unit_ms;
int dash_ms = time_unit_ms * 3;
int symbol_gap_ms = dot_ms;
int letter_gap_ms = dash_ms;
int word_gap_ms = time_unit_ms * 7;

char dot_s        = '.';
char dash_s       = '-';
char nextLetter_s = ' ';
char nextWord_s   = '/';
char lf_s         = '\n';
char cr_s         = '\r';

void setup() {
  // set up the serial interface to talk at 9600 baud.
  Serial.begin(9600);
  // set pin 13 (onboard LED) as output
  pinMode(13, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    // read a character from the serial interface and respond accordingly
    char r = Serial.read();
    if(r == dot_s) { dot(); }
    else if(r == dash_s) { dash(); }
    else if(r == nextLetter_s) { nextLetter(); }
    else if(r == nextWord_s) { nextWord(); }
    else if(r == lf_s || r == cr_s) { nextWord(); Serial.write(lf_s); }
    else { error(r); }
  }
}

void dot() {
  digitalWrite(13, HIGH);
  Serial.write(dot_s);
  delay(dot_ms);
  digitalWrite(13, LOW);
  delay(symbol_gap_ms);
}

void dash() {
  digitalWrite(13, HIGH);
  Serial.write(dash_s);
  delay(dash_ms);
  digitalWrite(13, LOW);
  delay(symbol_gap_ms);
}

void nextLetter() {
  Serial.write(nextLetter_s);
  delay(letter_gap_ms);
}

void nextWord() {
  Serial.write(nextWord_s);
  delay(word_gap_ms);
}

void error(char in) {
  char err[32];
  sprintf(err, "Error[0x%02x]", in, in);
  Serial.write(err);
}
