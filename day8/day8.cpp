#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template <typename T>
void printGrid(std::vector<std::vector<T>> grid)
{
  for (auto row : grid)
  {
    for (auto cell : row)
      std::cout << cell;
    std::cout << std::endl;
  }
}

std::vector<std::vector<int>> buildGrid(std::string path)
{
  std::string inputText = "";
  std::ifstream inputFile(path);
  std::vector<std::vector<int>> grid;
  int i = 0;
  while (std::getline(inputFile, inputText))
  {
    i++;
    grid.resize(i);
    inputText = inputText.substr(0, inputText.find('\r')); // strip out the \r
    for (auto ascii : inputText)
    {
      auto number = (int)ascii - 48;
      grid[i - 1].push_back(number);
    }
  }
  return grid;
}

void challenge(std::vector<std::vector<int>> grid)
{
  int width = grid[0].size();
  int height = grid.size();

  std::vector<std::vector<bool>> visible;
  visible.resize(height);

  // first and last column are always visible, and we assume the rest are not
  for (auto &row : visible)
  {
    row.assign(width, false);
    row[0] = true;
    row[width - 1] = true;
  }
  // first row and last row is always visible
  visible[0].assign(width, true);
  visible[height - 1].assign(width, true);

  // visible from the left or right
  for (int k = 1; k < height - 1; k++)
  {
    auto row = grid[k];
    int leftHeight = row[0];
    int rightHeight = row[width - 1];
    for (int i = 1; i < width - 1; i++)
    {
      // Look from the left
      int leftCellHeight = row[i];
      if (leftCellHeight > leftHeight)
      {
        visible[k][i] = true;
        leftHeight = leftCellHeight;
      }
      // Look from the right
      int rightOffset = width - 1 - i;
      int rightCellHeight = row[rightOffset];
      if (rightCellHeight > rightHeight)
      {
        visible[k][rightOffset] = true;
        rightHeight = rightCellHeight;
      }
    }
  }
  // visible from the top or bottom
  for (int i = 1; i < width - 1; i++)
  {
    int topHeight = grid[0][i];
    int bottomHeight = grid[height - 1][i];
    for (int k = 1; k < height - 1; k++)
    {
      // look from the top
      int topCellHeight = grid[k][i];
      if (topCellHeight > topHeight)
      {
        topHeight = topCellHeight;
        visible[k][i] = true;
      }
      int bottomOffset = height - 1 - k;
      int bottomCellHeight = grid[bottomOffset][i];
      if (bottomCellHeight > bottomHeight)
      {
        bottomHeight = bottomCellHeight;
        visible[bottomOffset][i] = true;
      }
    }
  }
  int count = 0;
  for (auto row : visible)
    for (auto cell : row)
      count += cell;
  std::cout << count << std::endl;
  // printGrid(visible);
}

void bonus(std::vector<std::vector<int>> grid)
{
  int width = grid[0].size();
  int height = grid.size();

  int bestScenicScore = 0;
  // the outside rows will always have a score of 0, and can be ignored
  for (int verticalPosition = 1; verticalPosition < height - 1; verticalPosition++)
  {
    for (int horizontalPosition = 1; horizontalPosition < width - 1; horizontalPosition++)
    {
      int height = grid[verticalPosition][horizontalPosition];
      // looking North
      int northScenicScore = 1;
      for (int lookOffset = verticalPosition - 1; lookOffset >= 1; lookOffset--, northScenicScore++)
        if (grid[lookOffset][horizontalPosition] >= height)
          break;
      // looking South
      int southScenicScore = 1;
      for (int lookOffset = verticalPosition + 1; lookOffset < grid.size() - 1; lookOffset++, southScenicScore++)
        if (grid[lookOffset][horizontalPosition] >= height)
          break;
      // looking East
      int eastScenicScore = 1;
      for (int lookOffset = horizontalPosition - 1; lookOffset >= 1; lookOffset--, eastScenicScore++)
        if (grid[verticalPosition][lookOffset] >= height)
          break;
      // looking West
      int westScenicScore = 1;
      for (int lookOffset = horizontalPosition + 1; lookOffset < grid[horizontalPosition].size() - 1; lookOffset++, westScenicScore++)
        if (grid[verticalPosition][lookOffset] >= height)
          break;

      int scenicScore = northScenicScore * southScenicScore * eastScenicScore * westScenicScore;
      if (scenicScore > bestScenicScore)
        bestScenicScore = scenicScore;
    }
  }
  std::cout << bestScenicScore << std::endl;
}

int main()
{
  std::string file = "input.txt";
  auto grid = buildGrid(file);
  challenge(grid);
  bonus(grid);
  return 0;
}
