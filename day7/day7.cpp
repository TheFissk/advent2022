#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

struct directory
{
public:
  directory() : totalFileSize{0}, parent{nullptr}, home{this}, name{"/"} {}

  directory(std::string Name) : totalFileSize{0}, name{Name}
  {
  }

  void addFile(std::string fileName, int fileSize)
  {
    if (files.count(fileName))
      return;
    files.insert(fileName);
    totalFileSize += fileSize;
  }

  void addDirectory(directory *dir)
  {
    children.push_back(dir);
    dir->parent = this;
    dir->home = this->home;
  }

  int getFileSize()
  {
    if (cachedFileSize > 0)
      return cachedFileSize;
    int fileSize = totalFileSize;
    for (auto child : children)
      fileSize += child->getFileSize();
    cachedFileSize = fileSize;
    return fileSize;
  }

  std::string name;
  directory *home;
  directory *parent;
  std::set<std::string> files;
  std::vector<directory *> children;

private:
  int totalFileSize;
  int cachedFileSize = -1;
};

directory base;

bool cd(std::string command, directory *&location)
{
  std::string argument = command.substr(5, command.size() - 6);

  if (argument == "/")
  {
    location = location->home;
    std::cout << "cd to base: " << location->name << "\n";
    return true;
  }
  else if (argument == "..")
  {
    location = location->parent;
    std::cout << "cd to parent: " << location->name << "\n";
    return true;
  }
  else
  {
    for (auto child : location->children)
    {
      if (child->name == argument)
      {
        location = child;
        std::cout << "cd to child: " << location->name << "\n";
        return true;
      }
    }
  }
  std::cout << "failure to cd" << std::endl;
  return false;
}

std::string ls(std::ifstream &inputPipe, directory *&location)
{
  std::string Pipe;
  while (std::getline(inputPipe, Pipe))
  {
    if (Pipe.at(0) == '$')
    {
      if (Pipe.at(2) == 'l')
        continue;
      return Pipe;
    }
    else if (Pipe.at(0) == 'd')
    {
      location->addDirectory(new directory(Pipe.substr(4, Pipe.size() - 5)));
      std::cout << "creating directory called: " << Pipe.substr(4, Pipe.size() - 5) << std::endl;
    }
    else
    {
      int split = Pipe.find(' ');
      int size = std::stoi(Pipe.substr(0, split));
      int pipeSize = Pipe.size();
      std::string fileName = Pipe.substr(split + 1, Pipe.size() - 1);
      std::cout << "creating new file in: " << location->name << " called: " << fileName << std::endl;

      location->addFile(fileName, size);
    }
  }
  return Pipe;
}

void buildFileSystem(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);

  int score = 0;
  directory *location = &base;

  while (std::getline(inputFile, inputText))
  {
    std::cout << "location: " << location->name << std::endl;
    switch (inputText.at(2))
    {
    case 'l':
      std::cout << inputText << "\n";
      inputText = ls(inputFile, location);
    case 'c':
      if (inputText.at(0) != '$')
        break;
      std::cout << inputText << "\n";
      cd(inputText, location);
      break;

    default:
      std::cout << "failure\n";
      break;
    }
  }
  inputFile.close();
}

int determineChallengeScore(directory start, int threshold)
{
  int selfFileSize = start.getFileSize();
  int totalFileSize = 0;
  if (selfFileSize <= threshold)
    totalFileSize += selfFileSize;
  for (auto child : start.children)
    totalFileSize += determineChallengeScore(*child, threshold);
  return totalFileSize;
}

void findSmallestLargerThan(const directory *start, int threshold, directory *&currentSmallest)
{
  for (auto child : start->children)
  {
    if (child->getFileSize() < threshold)
      continue;
    if (child->getFileSize() < currentSmallest->getFileSize())
      currentSmallest = child;
    findSmallestLargerThan(child, threshold, currentSmallest);
  }
}

int deleteDir(int spaceToFree)
{
  directory *toDelete = &base;
  findSmallestLargerThan(&base, spaceToFree, toDelete);
  return toDelete->getFileSize();
}

void challenge(int threshold)
{
  std::cout << "Challenge: " << determineChallengeScore(base, threshold) << "\n";
}

void bonus(int totalSpace, int targetSpace)
{
  int spaceToFree = targetSpace - totalSpace + base.getFileSize();
  std::cout << "Bonus: " << deleteDir(spaceToFree) << "\n";
}

int main()
{
  std::string file = "input.txt";
  buildFileSystem(file);
  challenge(100000);
  bonus(70000000, 30000000);
  return 0;
}
