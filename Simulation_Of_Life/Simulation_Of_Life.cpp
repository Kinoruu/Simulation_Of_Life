#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;


class Object {
public:
  int position_x;
  int position_y;
  int age;        // current age
  int hair;       // 1 blonde, 2 black, 3 brown, 4 red, 5 white
  int height;     // (max) 150-190 cm
  int eyes;       // blue, green, brown, black, grey
  int character;  // 
  int age_max;    // 1-110
  int offspring;  // offspring number possibility - 0 - cammot have, 1, 2 - high chance of twins
  float mutation; // mutation probability 0.001-0.01
};


void Write(int tab[][30], const int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      tab[i][j] = 0;
    }
  }
  int k, l;
  /*
  for(int i = 0; i < 100; i++)              //for manual choose of living position at the beginning
  {
      cin >> k;
      cin >> l;
      tab[k][l] = 1;
  }
  */

  for (int i = 0; i < 100; i++)              // random choose of living position at the beginning
  {
    k = rand() % 30;
    l = rand() % 30;
    if (tab[k][l] != 1)
    {
      tab[k][l] = 1;
    }
    else
    {
      i--;
    }
  }
}

void SumOfNeighbours(int mat[][30], const int size, int tab_neighbours[][30], int tab_temp[][30])
{
  int sum;
  int col, row;
  for (int r = 0; r < size; r++)
  {
    for (int c = 0; c < size; c++)
    {
      sum = 0;
      row = r - 1;
      col = c - 1;
      for (int i = row; i < row + 3; i++)
      {
        for (int j = col; j < col + 3; j++)
        {
          sum += mat[(i + size) % size][(j + size) % size];
        }
      }
      sum -= mat[r][c];
      tab_neighbours[r][c] = sum;
    }
  }
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if ((tab_neighbours[i][j] == 3) && (mat[i][j] == 0))
      {
        tab_temp[i][j] = 1;
      }
      else if (((tab_neighbours[i][j] == 3) || (tab_neighbours[i][j] == 2)) && (mat[i][j] == 1))
      {
        tab_temp[i][j] = 1;
      }
      else
      {
        tab_temp[i][j] = 0;
      }
    }
  }
}

void Disp(int tab[][30], const int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      cout << tab[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int SumOfLife(int tab[][30], const int size)
{
  int life_sum = 0;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (tab[i][j] == 1)
      {
        life_sum++;
      }
    }
  }
  return life_sum;
}

void Ost(const int size2, char tab_ost[][31], const int size3)
{
  for (int k = 0; k < 30; k++)
  {
    for (int j = 0; j < 30; j++)
    {
      tab_ost[k][j] = ' ';
    }
  }
  for (int i = 0; i < 30; i++)
  {
    tab_ost[30][i] = '-';
  }
  for (int m = 0; m < 30; m++)
  {
    tab_ost[m][30] = '|';
  }
  tab_ost[30][30] = '+';
}

void DispOst(const int size2, char tab_ost[][31], const int size3)
{
  for (int k = 0; k < size2; k++)
  {
    for (int j = 0; j < size2; j++)
    {
      cout << tab_ost[k][j];
    }
    cout << endl;
  }
  cout << endl;
}

void Cykl(int tab[][30], const int size, int tab_neighbours[][30], int tab_temp[][30], char tab_ost[][31], const int size2, const int size3, int time)
{
  for (int i = 0; i < 1000; i++)
  {
    system("cls");
    DispOst(size2, tab_ost, size3);
    Sleep(0);                                           // setting refreshing time in ms
    SumOfNeighbours(tab, size, tab_neighbours, tab_temp);
    cout << "Time of simulation: " << time;
    ++time;
    for (int k = 0; k < size; k++)
    {
      for (int j = 0; j < size; j++)
      {
        tab[k][j] = tab_temp[k][j];
        if (tab[k][j] == 1)
        {
          tab_ost[k][j] = '#';
        }
        else
        {
          tab_ost[k][j] = ' ';
        }
      }
    }
  }
}

int main()
{
  CONSOLE_SCREEN_BUFFER_INFOEX consolesize;

  consolesize.cbSize = sizeof(consolesize);

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  GetConsoleScreenBufferInfoEx(hConsole, &consolesize);

  COORD c;
  c.X = 40;
  c.Y = 40;
  consolesize.dwSize = c;

  consolesize.srWindow.Left = 0;
  consolesize.srWindow.Right = 80;
  consolesize.srWindow.Top = 0;
  consolesize.srWindow.Bottom = 40;

  SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
  const int size = 30;
  const int size2 = 31;
  const int size3 = 91;
  int time = 0;
  int tab[size][size];
  int tab_temp[size][size];
  int tab_neighbours[size][size];
  char tab_ost[size2][size2];
  //Disp(tab, size);
  Write(tab, size);
  Ost(size2, tab_ost, size3);
  //Disp(tab, size);
  //SumOfNeighbours(tab, size, tab_neighbours);
  Cykl(tab, size, tab_neighbours, tab_temp, tab_ost, size2, size3, time);
  //cout << SumOfLife(tab, size);
  return 0;
}
