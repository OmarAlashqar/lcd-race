#ifndef RACE_H
#define RACE_H

#include <stdlib.h>
#include <time.h>

// #include <iostream>
#include <string.h>

using namespace std;

namespace Race {
enum Difficulty { easy, hard };

enum State { menu, running, over };

enum Position { left, right };

class Game {
 public:
  Game();
  // Game(int rows, int columns, char playerChar, char[4] obstacleChars);
  ~Game();

  void reset();
  void start();
  void tick();

  char** getTrack();
  int getScore();
  int setDifficulty(Difficulty d);
  int getDifficulty(Difficulty d);
  int setPlayerPosition(Position p);
  State getState();

 private:
  Difficulty difficulty = Difficulty::easy;
  int step = 0;
  char** track;
  char playerChar = '>';
  char spaceChar = ' ';
  char obstacleChar = 'O';
  State state = State::menu;
  int wait = 0;
  Position position = Position::left;
  Position nextPosition = Position::left;
};
}  // namespace Race

#endif