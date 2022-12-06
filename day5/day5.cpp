#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::vector<char>> parseStack(std::vector<std::string> input)
{
  input.pop_back();
  std::vector<std::vector<char>> output;
  output.resize((input[0].size() + 1) / 4);

  for (auto lineit = input.rbegin(); lineit != input.rend(); ++lineit)
  {
    auto line = *lineit;
    for (int i = 1, j = 0; i < line.size(); i += 4, j++)
    {
      char crate = line.at(i);
      if (crate != ' ')
        output[j].push_back(crate);
    }
  }
  return output;
}

struct instruction
{
  instruction(std::string text)
  {
    auto rem = std::remove(text.begin(), text.end(), '\r');
    text.erase(rem, text.end());

    int offset = text.size() - 18;

    from = std::stoi(text.substr(12 + offset, 1), nullptr) - 1;
    to = std::stoi(text.substr(17 + offset, 1), nullptr) - 1;
    numberToMove = std::stoi(text.substr(5, 1 + offset), nullptr);
  }
  int numberToMove;
  int from;
  int to;
};

void parseInstruction(std::string instruct, std::vector<std::vector<char>> &stack)
{
  instruction inst(instruct);
  for (int i = 0; i < inst.numberToMove; i++)
  {
    stack[inst.to].push_back(stack[inst.from].back());
    stack[inst.from].pop_back();
  }
}

void parseInstructionBonus(std::string instruct, std::vector<std::vector<char>> &stack)
{
  instruction inst(instruct);
  int firstIter = stack[inst.from].size() - inst.numberToMove;
  for (int i = 0; i < inst.numberToMove; i++)
    stack[inst.to].push_back(stack[inst.from][firstIter + i]);
  stack[inst.from].resize(firstIter);
}

void challenge(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  std::vector<std::string> stackInput;
  std::vector<std::vector<char>> stack;

  while (std::getline(inputFile, inputText))
  {
    if (inputText.size() <= 2)
      break;
    stackInput.push_back(inputText);
  }
  stack = parseStack(stackInput);

  while (std::getline(inputFile, inputText))
    parseInstruction(inputText, stack);

  std::cout << "Challenge: ";
  for (auto pile : stack)
    std::cout << pile.back();
  std::cout << '\n';

  inputFile.close();
}

void bonus(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  std::vector<std::string> stackInput;
  std::vector<std::vector<char>> stack;

  while (std::getline(inputFile, inputText))
  {
    if (inputText.size() <= 2)
      break;
    stackInput.push_back(inputText);
  }
  stack = parseStack(stackInput);

  while (std::getline(inputFile, inputText))
    parseInstructionBonus(inputText, stack);

  std::cout << "Bonus: ";
  for (auto pile : stack)
    std::cout << pile.back();
  std::cout << '\n';

  inputFile.close();
}

int main()
{
  std::string file = "input.txt";
  challenge(file);
  bonus(file);
  return 0;
}
