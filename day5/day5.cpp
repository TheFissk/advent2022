#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::vector<char>> parseStack(std::vector<std::string> input)
{
  input.pop_back();
  std::vector<std::vector<char>> output;
  output.resize((input[0].size() + 1) / 4);

  for (auto line : input)
  {
    for (int i = 1, j = 0; i < line.size(); i += 4, j++)
    {
      char crate = line.at(i);
      if (crate != ' ')
        output[j].push_back(crate);
    }
  }
  return output;
}

std::vector<std::tuple<int, int, int>> parseInstruction(std::vector<std::string> input)
{
  std::vector<std::tuple<int, int, int>> output;
  for (auto line : input)
  {
    
    std::cout << line << '\n';
  }
  return output;
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

  std::vector<std::string> stackInput;
  std::vector<std::vector<char>> stack;

  std::vector<std::string> instructionInput;
  std::vector<std::tuple<int, int, int>> instruction;

  while (std::getline(inputFile, inputText))
  {
    if (inputText.size() <= 0)
      continue;
    if (inputText.at(0) == 'm')
      instructionInput.push_back(inputText);
    else
      stackInput.push_back(inputText);
  }

  //stack = parseStack(stackInput);
  instruction = parseInstruction(instructionInput);

  std::cout << "Challenge: " << /*score <<*/ "\n";
  inputFile.close();
}

void bonus(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  int score = 0;

  while (std::getline(inputFile, inputText))
    inputText = inputText;

  std::cout << "Challenge: " << score << "\n";
  inputFile.close();
}

int main()
{
  std::string file = "toyinput.txt";
  challenge(file);
  // bonus(file);
  return 0;
}
