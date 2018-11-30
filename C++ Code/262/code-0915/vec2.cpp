#include <iostream>
#include <vector>
using namespace std;

void printgrid(vector<vector<int>> grid , int width, int height)
{
  for (int y=0; y < height; ++y)
  {
    for (int x= 0; x < width; ++x)
      cout << " " << grid[x][y];

    cout << endl;
  }
}

int main()
{
  int width, height;
  cin >> width >> height;

  //int grid[width][height];
  vector<vector<int>> grid;
  grid.resize(width);
  for (int x = 0; x < width; ++x)
    grid[x].resize(height);

  printgrid(grid, width, height);

}
