#include <LiquidCrystal.h>

//initilize pin
const int buttonPin = 8;
const int ledPin = 13;

//var
unsigned long cTime = 0; //current time
unsigned long rTime = 0; //reset time

unsigned long aTime = 2700000; //45min
unsigned long bTime = 900000; //15min
int checkMode = 0; //0->A, 1->B
int checkOver = 0; //0->safe , 1->over

int buttonState = 0; //buttonState

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //set up pinmode
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  //serial setup
  //Serial.begin(9600);

  //display mode
  statusDisplay(checkMode);
}

void loop() {


  //button check
  buttonState = digitalRead(buttonPin);

  if (checkOver == 1) { //time is over
    digitalWrite(ledPin, HIGH);

    if (buttonState == HIGH) {
      //overtime is reset
      checkOver = 0;
      lcd.clear();

      // reset time
      rTime = millis();
      cTime = 0;

      //modeChange
      if (checkMode == 0) {
        checkMode = 1;
        //display mode
        statusDisplay(checkMode);
      } else {
        checkMode = 0;
        //display mode
        statusDisplay(checkMode);
      }
    }
  } else {
    digitalWrite(ledPin, LOW);
  }

  //time set,if time is complete,then over
  cTime = millis() - rTime;

  if (checkMode == 0) {
    if (cTime >= aTime) {
      checkOver = 1; //over
    }
  } else {
    if (cTime >= bTime) {
      checkOver = 1; //over
    }
  }

  //set lcd cursor
  lcd.setCursor(0, 0);
  // print the time
  if (checkOver == 0) {
    lcd.print(cTime / 1000);
  } else {
    statusDisplay(2);
    if (checkMode == 0) {
      lcd.print(aTime / 1000);
    } else if (checkMode == 1) {
      lcd.print(bTime / 1000);
    }
  }

}

void statusDisplay(int cMode) {

  if (cMode == 0) {
    lcd.setCursor(0, 1);
    lcd.print("45 min");
    lcd.setCursor(0, 0);
  } else if (cMode == 1) {
    lcd.setCursor(0, 1);
    lcd.print("15 min");
    lcd.setCursor(0, 0);
  } else if (cMode == 2) {
    lcd.setCursor(0, 1);
    lcd.print("TIME IS OVER");
    lcd.setCursor(0, 0);
  }
}



