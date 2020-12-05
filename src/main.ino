#include "LiquidCrystal.h"
#include "race.h"

using namespace Race;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Game game = Game();

const byte leftButtonPin = 2;
const byte rightButtonPin = 3;

Position* LEFT_POSITION = new Position{Position::left};
Position* RIGHT_POSITION = new Position{Position::right};
Position* volatile nextPosition = nullptr;

void moveLeft() { nextPosition = LEFT_POSITION; }
void moveRight() { nextPosition = RIGHT_POSITION; }

void setup() {
  // Serial.begin(9600);

  pinMode(latch, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);

  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(leftButtonPin), moveLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(rightButtonPin), moveRight, FALLING);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("LCD Race");

  game.start();
  delay(1000);
}

void loop() {
  State state = game.getState();

  if (state == State::running) {
    // get input
    if (nextPosition != nullptr) {
      game.setPlayerPosition(*nextPosition);
    }

    // game continues
    game.tick();

    // render
    char** track = game.getTrack();

    lcd.setCursor(0, 0);
    lcd.write(track[0]);

    lcd.setCursor(0, 1);
    lcd.write(track[1]);

    delay(250);
  } else if (state == State::over) {
    lcd.setCursor(0, 0);
    lcd.write("XXXXXXXXXXXXXXXX");

    lcd.setCursor(0, 1);
    lcd.write("XXXXXXXXXXXXXXXX");

    nextPosition = nullptr;
    while (nextPosition == nullptr) {
    };

    game.start();
  }
}
