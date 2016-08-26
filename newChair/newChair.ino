// A0, A1 are pre-defined as analaog inputs for first row and col.
#define BUTT1_PIN A2
#define BUTT2_PIN A3
#define BUTT3_PIN A4
#define BUTT4_PIN A5

// 2-dimensional array of row pin numbers:
const byte colPins[7] = {2, 3, 4, 5, 6, 7, A1};
// 2-dimensional array of column pin numbers:
const byte rowPins[7] = {8, 9, 10, 11, 12, 13, A0};

const int mat[7][7] = {{1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1}, {1, 0, 1, 1, 1, 0, 1}, {0, 0, 1, 1, 1, 0, 0}};

void testCol(int time);
void testRow(int time);
void swipeRightToLeft(int time);

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
  int time = 200;

  if (digitalRead(BUTT1_PIN) == LOW) {
    //colTest(3);
    fastSwipeOneCol(2, 100, 55); // Swipe Left Shoulder Blade
  }

  if (digitalRead(BUTT2_PIN) == LOW) {
    //colTest(2);
    fastSwipeOneCol(4, 100, 50); // Swipe Right Shoulder Blade
    
  }

  if (digitalRead(BUTT3_PIN) == LOW) {
    //colTest(1);
    fastRowOn(100, 55); // Swipe Top to Bottom w/ Overlap
  }

  if (digitalRead(BUTT4_PIN) == LOW) {
    colOn(0); // Swipe Top to Bottom w/o Overlap
    resetPins();
    delay(100);
    //colOff(0);
  }  
}
 

void fastSwipeOneCol(byte col, int dur_t, int delay_t) {
  
  /* Turn on all columns */
  for (int i = 0; i < sizeof(colPins); i++) {
    digitalWrite(colPins[i], LOW);
  }
  
  /* Enter the Overlap Mission */
  for (int j = 0; j < sizeof(rowPins)-1; j++) {
    digitalWrite(rowPins[j], HIGH);
    resetColsExceptForOne(col);
    delay(dur_t);
    digitalWrite(rowPins[j+1], HIGH);
    resetColsExceptForOne(col);
    delay(delay_t);
    digitalWrite(rowPins[j], LOW);
    resetColsExceptForOne(col);
  }

  /* Optional: reset all pins after each mission*/
  resetPins();
}

void fastRowOn(int dur_t, int delay_t) {

  /* Turn on all columns */
  for (int i = 0; i < sizeof(colPins); i++) {
    colOn(i);
  }
  for (int j = 0; j < sizeof(rowPins)-1; j++) {
    if(j == 0) {
      rowOn(j);
      delay(dur_t);
      rowOn(j+1);
      delay(delay_t);
      rowOff(j);
    }
    else {
      rowOn(j);
      delay(dur_t - delay_t);
      rowOn(j+1);
      delay(delay_t);
      rowOff(j);
    }
  }
  /* Optional: reset all pins after each mission */
  resetPins(); 
}

void interestIng(int dur_t, int delay_t) {
 /* Turn on all columns */
  for (int i = 0; i < sizeof(colPins); i++) {
    colOn(i);
  }
  for (int j = 1; j < sizeof(rowPins)-1; j++) {
    if(j == 1) {
      rowOn(j);
      delay(dur_t);
      rowOn(j-1);
      delay(delay_t);
      rowOff(j);
    }
    else {
      rowOn(j);
      delay(dur_t - delay_t);
      rowOn(j-1);
      delay(delay_t);
      rowOff(j);
    }
  }
  /* Optional: reset all pins after each mission */
  //resetPins();  
}

void rowTest(byte r) {
  resetPins();
  pckge_rowOn(r);
}

void colTest(byte c) {
  resetPins();
  pckge_colOn(c);
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

// Turn an entire row on
void pckge_rowOn(byte row) {
  // Turn on all the columns
  for (int i = 0; i < sizeof(colPins); i++) {
    digitalWrite(colPins[i], LOW);
  }
  digitalWrite(rowPins[row], HIGH);
}

//Turn an entire column on
void pckge_colOn(byte col) {
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
  resetRowsExceptForOne(row);
  delay(150);
}

// version 2 : Col -> Row

void resetRowsExceptForOne(int row) {
  for (int i = 0; i < sizeof(rowPins); i++) {
    pinMode(rowPins[i], OUTPUT);
    if (i != row) {
      digitalWrite(rowPins[i], LOW);
    } else {
      digitalWrite(rowPins[i], HIGH);
    }

  }
}

void resetColsExceptForOne(int col) {
  for (int i = 0; i < sizeof(colPins); i++) {
    pinMode(colPins[i], OUTPUT);
    if (i != col) {
      digitalWrite(colPins[i], HIGH);
    } else {
      digitalWrite(colPins[i], LOW);
    }
  }
}

void resetColsExceptForTwo(int col1, int col2) {
  for (int i = 0; i < sizeof(colPins); i++) {
    pinMode(colPins[i], OUTPUT);
    if ((i == col1) || (i != col2)) {
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


// wait_ms is the time between swiching from one row/colum to another. 
// use a lower value to get the animation to go faster.
void swipeLeftToRight(int wait_ms) {
  for (int i = 0; i < sizeof(colPins); i++) {
    resetPins();
    pckge_colOn(i);
    delay(wait_ms);
  }

  resetPins(); // Turn all off when done
}

// wait_ms is the time between swiching from one row/colum to another.
//use a lower value to get the animation to go faster.
void swipeRightToLeft(int wait_ms) {
  for (int i = sizeof(colPins); i >= 0 ; i--) {
    resetPins();
    pckge_colOn(i);
    delay(wait_ms);
  }

  resetPins(); // Turn all off when done
}

void swipeTopToBottom(int wait_ms) {
  for (int i = 0; i < sizeof(rowPins); i++) {
    resetPins();
    pckge_rowOn(i);
    delay(wait_ms);
  }

  resetPins(); // Turn all off when done
}

void swipeBottomToTop(int wait_ms) {
  for (int i = sizeof(rowPins); i >= 0; i--) {
    resetPins();
    pckge_rowOn(i);
    delay(wait_ms);
  }

  resetPins(); // Turn all off when done
}

/* Experimental Sesh */
/* (newly added features) */

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
