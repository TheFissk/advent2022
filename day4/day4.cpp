#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

int i = 0;

int findPriority(char item)
{
  int score = (int)item - 38;

  if (score > 52)
    score -= 58;

  return score;
}

int containsEachOther(std::string cleaningSections)
{
  std::string e1 = cleaningSections.substr(0, cleaningSections.find(","));
  std::string e2 = cleaningSections.substr(cleaningSections.find(",") + 1);

  int e1Low{std::stoi(e1.substr(0, e1.find("-")), nullptr)};
  int e1High{std::stoi(e1.substr(e1.find("-") + 1), nullptr)};
  int e2Low{std::stoi(e2.substr(0, e2.find("-")), nullptr)};
  int e2High{std::stoi(e2.substr(e2.find("-") + 1), nullptr)};

  if ((e1Low <= e2Low) && (e1High >= e2High))
    return 1;

  if ((e1Low >= e2Low) && (e1High <= e2High))
    return 1;

  return 0;
}

void challenge(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  int score = 0;

  while (std::getline(inputFile, inputText))
    score += containsEachOther(inputText);

  std::cout << "Challenge: " << score << "\n";
  inputFile.close();
}

int overlapBonus(std::string cleaningSections)
{
  std::string elf1 = cleaningSections.substr(0, cleaningSections.find(","));
  std::string elf2 = cleaningSections.substr(cleaningSections.find(",") + 1);

  int e1Low{std::stoi(elf1.substr(0, elf1.find("-")), nullptr)};
  int e1High{std::stoi(elf1.substr(elf1.find("-") + 1), nullptr)};
  int e2Low{std::stoi(elf2.substr(0, elf2.find("-")), nullptr)};
  int e2High{std::stoi(elf2.substr(elf2.find("-") + 1), nullptr)};

  if (((e1Low <= e2Low) && (e1High >= e2Low)))
    return 1;
  if (((e1Low <= e2High) && (e1High >= e2High)))
    return 1;

  if (((e1Low >= e2Low) && (e1Low <= e2High)))
    return 1;
  if (((e1High >= e2Low) && (e1High <= e2High)))
    return 1;

  return 0;
}

void bonus(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  int score = 0;

  while (std::getline(inputFile, inputText))
    score += overlapBonus(inputText);

  std::cout << "Challenge: " << score << "\n";
  inputFile.close();
}

int main()
{
  std::string file = "input.txt";
  challenge(file);
  bonus(file);
  return 0;
}
