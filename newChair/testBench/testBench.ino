#define BUTT1_PIN A2
#define BUTT2_PIN A3
#define BUTT3_PIN A4
#define BUTT4_PIN A5

// 2-dimensional array of row pin numbers:
const byte colPins[7] = {2, 3, 4, 5, 6, 7, A1};
// 2-dimensional array of column pin numbers:
const byte rowPins[7] = {8, 9, 10, 11, 12, 13, A0};

const int mat[7][7] = {{1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1}, {1, 0, 1, 1, 1, 0, 1}, {0, 0, 1, 1, 1, 0, 0}};

void setup() {
  Serial.begin(9600);

  // Setup input pins
  pinMode(BUTT1_PIN, INPUT_PULLUP);
  pinMode(BUTT2_PIN, INPUT_PULLUP);
  pinMode(BUTT3_PIN, INPUT_PULLUP);
  pinMode(BUTT4_PIN, INPUT_PULLUP);

  // Setup output pins
  resetPins();
}

void loop() {
  int time = 200;
  //resetPins();
  if (digitalRead(BUTT1_PIN) == LOW) {
    //
    singleton_red(3,3);
    resetPins();
  }

  if (digitalRead(BUTT2_PIN) == LOW) {
    //
    //digitalWrite(colPins[2], LOW);
    test_colOn(4);
    resetPins();
  }

  if (digitalRead(BUTT3_PIN) == LOW) {
    singleton_blue(4,4);
    delay(100);
    resetPins();
  }

  if (digitalRead(BUTT4_PIN) == LOW) {
    rowOn(4);
    delay(100);
    resetPins();
  }  
}

void test_colOn(byte col) {
  for (int i = 0; i < sizeof(rowPins); i++) {
    digitalWrite(rowPins[i], HIGH);
  }
  colOn(col);
  delay(100);
}

void rowOn(byte row) {
  digitalWrite(rowPins[row], HIGH);
}

void colOn(byte col) {
  digitalWrite(colPins[col], LOW);
}

void rowOff(byte row) {
  digitalWrite(rowPins[row], LOW);
}

void colOff(byte col) {
  digitalWrite(colPins[col], HIGH);
}

void singleton_red(byte row, byte col) {
  for (int i = 0; i < sizeof(colPins); i++) {
    if(i == col) {
      digitalWrite(colPins[col], HIGH);
    }
    else {
      digitalWrite(colPins[col], LOW);
    }
  }
  for (int j = 0; j < sizeof(rowPins); j++) {
    if(j == row) {
      digitalWrite(rowPins[row], HIGH);
    }
    else {
      digitalWrite(rowPins[row], LOW);
    }
  }
  delay(100);
  
}

void singleton_red2(byte row, byte col) {
  for (int i = 0; i < sizeof(rowPins); i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  for (int j = 0; j < sizeof(colPins); j++) {
    pinMode(colPins[j], OUTPUT);
    digitalWrite(rowPins[j], HIGH);
  }
  
  colOn(1);
  delay(100);  
}

void singleton_blue(byte row, byte col) {
  for (int j = 0; j < sizeof(rowPins); j++) {
    if(j == row) {
      digitalWrite(rowPins[row], LOW);
    }
    else {
      digitalWrite(rowPins[row], HIGH);
    }
  }
  
  for (int i = 0; i < sizeof(colPins); i++) {
    if(i == col) {
      digitalWrite(colPins[col], LOW);
    }
    else {
      digitalWrite(colPins[col], HIGH);
    }
  }

  delay(100);
}

void singleton_blue2(byte row, byte col) {
  for (int j = 0; j < sizeof(rowPins); j++) {
    digitalWrite(rowPins[row], LOW);
  }
  
  for (int i = 0; i < sizeof(colPins); i++) {
    digitalWrite(colPins[col], LOW);
  }
  
  delay(100);  
}

void resetPins() {
  for (int i = 0; i < sizeof(colPins); i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

    for (int i = 0; i < sizeof(rowPins); i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }
}
