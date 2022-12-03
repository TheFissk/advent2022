#include <iostream>
#include <fstream>
#include <string.h>

// A X Rock -1
// B Y Paper -2
// C Z Scissor -3
// 6 for a win, 3 for a draw

int scoreChallenge(char opponent, char self)
{
  switch (opponent)
  {
  case 'A': // Rock
    switch (self)
    {
    case 'X': // Rock
      return 1 + 3;
    case 'Y': // Paper
      return 2 + 6;
    case 'Z':
      return 3 + 0; // Scissors
    }
  case 'B': // Paper
    switch (self)
    {
    case 'X': // Rock
      return 1 + 0;
    case 'Y': // Paper
      return 2 + 3;
    case 'Z':
      return 3 + 6; // Scissors
    }
  case 'C': // Scissors
    switch (self)
    {
    case 'X': // Rock
      return 1 + 6;
    case 'Y': // Paper
      return 2 + 0;
    case 'Z':
      return 3 + 3; // Scissors
    }
  }
  return 0;
}

void challenge(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  int score = 0;

  while (std::getline(inputFile, inputText))
  {
    score += scoreChallenge(inputText.at(0), inputText.at(2));
  }
  std::cout << "Challenge: " << score << "\n";
  inputFile.close();
}

int scoreBonus(char opponent, char self)
{
  switch (self)
  {
  case 'X': // Lose
    switch (opponent)
    {
    case 'A': // Rock
      return 3;
    case 'B': // Paper
      return 1;
    case 'C':
      return 2; // Scissors
    }
  case 'Y': // Draw
    switch (opponent)
    {
    case 'A': // Rock
      return 4;
    case 'B': // Paper
      return 5;
    case 'C':
      return 6; // Scissors
    }
  case 'Z': // Win
    switch (opponent)
    {
    case 'A': // Rock
      return 8;
    case 'B': // Paper
      return 9;
    case 'C':
      return 7; // Scissors
    }
  }
  return 0;
}

void bonus(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  int score = 0;

  while (std::getline(inputFile, inputText))
  {
    score += scoreBonus(inputText.at(0), inputText.at(2));
  }
  std::cout << "Bonus: " << score << "\n";
  inputFile.close();
}
int main()
{
  std::string file = "Input.txt";
  challenge(file);
  bonus(file);
  return 0;
}
