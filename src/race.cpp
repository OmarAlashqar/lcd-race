#include "race.h"
using namespace Race;

Race::Game::Game() {
  track = new char*[2];
  track[0] = new char[17];
  track[1] = new char[17];

  track[0][16] = '\0';
  track[1][16] = '\0';

  srand(time(NULL));

  reset();
}

void Race::Game::reset() {
  state = State::menu;

  // clear the track
  for (int r = 0; r < 2; r++) {
    for (int c = 0; c < 16; c++) {
      track[r][c] = spaceChar;
    }
  }
}

void Race::Game::start() {
  reset();

  state = State::running;
  step = 0;
  track[0][2] = playerChar;
}

void Race::Game::tick() {
  if (state != State::running) return;

  if (position != nextPosition) {
    position = nextPosition;

    if (nextPosition == Position::left) {
      if (track[0][2] == obstacleChar) {
        state = State::over;
        return;
      }
    } else {
      if (track[1][2] == obstacleChar) {
        state = State::over;
        return;
      }
    }

    char temp = track[0][2];
    track[0][2] = track[1][2];
    track[1][2] = temp;
  }

  // shift obstacles forward (not for last column)
  for (int r = 0; r < 2; r++) {
    for (int c = 0; c < 16 - 1; c++) {
      char current = track[r][c];
      char next = track[r][c + 1];

      if (current == playerChar) {
        if (next == obstacleChar) {
          // collision
          state = State::over;
          return;
        }
      } else if (next == playerChar) {
        track[r][c] = spaceChar;
      } else {
        track[r][c] = next;
      }
    }
  }

  // generate new column
  track[0][15] = spaceChar;
  track[1][15] = spaceChar;

  if (wait-- == 0) {
    wait = rand() % 7 + 2;
    // cout << "[RACE]: Generating obstacle, next wait is: " << wait << endl;

    int side = rand() % 2;
    track[side][15] = obstacleChar;
  }

  step++;
}

int Race::Game::setPlayerPosition(Position p) { nextPosition = p; }
char** Race::Game::getTrack() { return track; }
int Race::Game::getScore() { return step; }
int Race::Game::setDifficulty(Difficulty d) { difficulty = d; }
int Race::Game::getDifficulty(Difficulty d) { return difficulty; }
State Race::Game::getState() { return state; }

Race::Game::~Game() {
  free(track[0]);
  free(track[1]);
  free(track);
}