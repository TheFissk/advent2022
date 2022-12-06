#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <deque>

bool isDuplicateCharacter(std::deque<char> queue)
{
  std::set<char> dups;

  for (auto iter = queue.begin(); iter != queue.end(); iter++)
  {
    if (dups.count(*iter))
      return true;
    dups.insert(*iter);
  }
  return dups.count(*queue.end());
}

// I could do this with an acutal stream, but a string works too
int findStart(std::string stream, int numDups)
{
  std::deque<char> dups;

  // load this first 4 characters
  for (int i = 0; i < numDups; i++)
    dups.push_back(stream.at(i));

  if (!isDuplicateCharacter(dups))
    return 4;

  for (int i = numDups; i < stream.size(); i++)
  {
    dups.pop_front();
    dups.push_back(stream.at(i));
    if (!isDuplicateCharacter(dups))
      return i + 1;
  }
  return -1;
}

void challenge(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  std::getline(inputFile, inputText);
  inputFile.close();

  std::cout << "Challenge: " << findStart(inputText, 4) << "\n";
}

void bonus(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  std::getline(inputFile, inputText);
  inputFile.close();

  std::cout << "Challenge: " << findStart(inputText, 14) << "\n";
}

int main()
{
  std::string file = "input.txt";
  challenge(file);
  bonus(file);
  return 0;
}
