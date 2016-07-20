//serial.port=/dev/ttyACM0

#define BUTT1_PIN A5
#define BUTT2_PIN A4
#define BUTT3_PIN A3
#define BUTT4_PIN A2

// 2-dimensional array of row pin numbers:
const byte colPins[7] = {2,3,4,5,6,7,A1};
// 2-dimensional array of column pin numbers:
const byte rowPins[7] = {8,9,10,11,12,13,A0};

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

// To turn a pin on, write LOW to column, and HIGH to row

void loop() {
  int time = 100;
  
  if (digitalRead(BUTT1_PIN) == LOW) {
    testCol(time);
  }
  
  if (digitalRead(BUTT2_PIN) == LOW) {
    testRow(time);
  }
    
  if (digitalRead(BUTT3_PIN) == LOW) {
    swipeRightToLeft(time);
  }
    
  if (digitalRead(BUTT4_PIN) == LOW) {
    everySingleOne(time);
  }
}

//private
int getValueAt(int row, int col) {
  return mat[row][col];
}

//public
void everySingleOne(int wait_ms) {
  //resetPins();
  for (int i = 0; i < sizeof(colPins); i++) {
    for (int j = 0; j < sizeof(rowPins); j++) {
      if(getValueAt(i,j) == 1) {
        singleton(i,j);
        delay(10);
        resetPins();
      }
    }
  }
  resetPins();
}
// Turn an entire row on
void rowOn(byte row) { 
  // Turn on all the columns
  for (int i = 0; i < sizeof(colPins); i++) {
    digitalWrite(colPins[i], LOW);
  }
  
  digitalWrite(rowPins[row], HIGH);
}

//Turn an entire column on 
void colOn(byte col) {
  // Turn on all the columns
  for (int i = 0; i < sizeof(rowPins); i++) {
    digitalWrite(rowPins[i], HIGH);
  }
  
  digitalWrite(colPins[col], LOW);
}

// version 1 : Row -> Col
void singleton(byte row, byte col) {
  digitalWrite(colPins[col], LOW);
  delay(150);
  resetRowsExceptFor(row);
  delay(300);
}

// version 2 : Col -> Row

void resetRowsExceptFor(int row) {
  for (int i = 0; i < sizeof(rowPins); i++) {
    pinMode(rowPins[i], OUTPUT);
    if(i != row) {
      digitalWrite(rowPins[i], LOW);
    } else {
      digitalWrite(rowPins[i], HIGH);
    }
    
  }
}

void resetColsExceptFor(int col) {
  for (int i = 0; i < sizeof(colPins); i++) {
    pinMode(colPins[i], OUTPUT);
    if(i != col) {
      digitalWrite(colPins[i], HIGH);
    } else {
      digitalWrite(colPins[i], LOW);
    }
  }
}
// Turns off ALL LEDs
void resetPins() {
  for (int i = 0; i < sizeof(rowPins); i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }
  
  for (int i = 0; i < sizeof(colPins); i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}


// wait_ms is the time between swiching from one row/colum to another. use a lower value to get the animation to go faster.
void swipeLeftToRight(int wait_ms) {
  for (int i = 0; i < sizeof(colPins); i++) {
    resetPins();
    colOn(i);
    delay(wait_ms);
  }
  
  resetPins(); // Turn all off when done
}

// wait_ms is the time between swiching from one row/colum to another. use a lower value to get the animation to go faster.
void swipeRightToLeft(int wait_ms) {
  for (int i = sizeof(colPins); i >= 0 ; i--) {
    resetPins();
    colOn(i);
    delay(wait_ms);
  }
  
  resetPins(); // Turn all off when done
}

void swipeTopToBottom(int wait_ms) {
  for (int i = 0; i < sizeof(rowPins); i++) {
    resetPins();
    rowOn(i);
    delay(wait_ms);
  }
  
  resetPins(); // Turn all off when done
}

void swipeBottomToTop(int wait_ms) {
  for (int i = sizeof(rowPins); i >= 0; i--) {
    resetPins();
    rowOn(i);
    delay(wait_ms);
  }
  
  resetPins(); // Turn all off when done
}


//*************** WRAPPER INTERFACE ***************//
// newly added features

void testCol(int time) {
  swipeLeftToRight(time);
}

void testRow(int time) {
  swipeTopToBottom(time);
}

void action_cross(int wait_ms) {
  colOn(3);
  delay(wait_ms);
  colOn(4);
  delay(wait_ms);
  rowOn(3);
  delay(wait_ms);
  rowOn(4);
  delay(wait_ms);
}
