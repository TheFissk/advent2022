#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <algorithm>
#include <vector>

int findPriority(char item)
{
  int score = (int)item - 38;

  if (score > 52)
    score -= 58;

  return score;
}

int scoreChallenge(std::string inventory)
{

  std::string half = inventory.substr(0, inventory.length() / 2);
  std::string otherHalf = inventory.substr(inventory.length() / 2);
  std::set<char> chars;
  char shared = ' ';

  for (char &item : half)
  {
    if (chars.count(item))
      continue;
    chars.insert(item);
  }

  for (char &item : otherHalf)
  {
    if (chars.count(item))
      shared = item;
  }
  return findPriority(shared);
}

void challenge(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  int score = 0;

  while (std::getline(inputFile, inputText))
  {
    score += scoreChallenge(inputText);
  }
  std::cout << "Challenge: " << score << "\n";
  inputFile.close();
}

int scoreBonus(std::vector<std::string>::iterator firstElf)
{
  std::set<char> uniqueInOne, uniqueInTwo;
  char shared;

  for (char &item : *firstElf)
    uniqueInOne.insert(item);

  for (char &item : *(firstElf + 1))
  {
    if (uniqueInOne.count(item))
      uniqueInTwo.insert(item);
  }

  for (char &item : *(firstElf + 2))
  {
    if (uniqueInTwo.count(item))
      return findPriority(item);
  }
  return 0;
}

void bonus(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  std::vector<std::string> elves;
  int score = 0;

  while (std::getline(inputFile, inputText))
    elves.push_back(inputText);

  for (size_t i = 0; i < elves.size(); i += 3)
    score += scoreBonus(elves.begin() + i);

  std::cout << "Bonus: " << score << "\n";
  inputFile.close();
}
int main()
{
  std::string file = "input.txt";
  challenge(file);
  bonus(file);
  return 0;
}
