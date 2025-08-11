#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cstring>
#include <limits>
#include <vector>
#include <windows.h>
using namespace std;

struct Coordinates
{
    int x;
    int y;
};
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const char direction[] = {'L', 'R', 'U', 'D'};

char **BFS(char **array, Coordinates beginning, Coordinates destination, int Length, int Width)
{
    queue<pair<int, Coordinates>> q;
    q.push({0, beginning});

    bool visited[Width][Length];
    memset(visited, false, sizeof(visited));
    visited[beginning.y][beginning.x] = true;

    // second array for directions
    char **Dir;
    Dir = new char *[Width];
    for (int i = 0; i < Width; i++)
    {
        Dir[i] = new char[Length];
    }
    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            Dir[i][j] = 'G';
        }
    }
    Dir[beginning.y][beginning.x] = 'p';

    while (!q.empty())
    {
        auto current = q.front();
        q.pop();

        int distance = current.first;
        Coordinates point = current.second;

        for (int i = 0; i < 4; i++)
        {
            int CurrentX = point.x + dx[i];
            int CurrentY = point.y + dy[i];

            if (CurrentX == destination.x && CurrentY == destination.y)
            {
                Dir[CurrentY][CurrentX] = direction[i];
                cout << "The distance between the pointed cells is: " << distance + 1;
                return Dir;
            }

            if (CurrentX >= 0 && CurrentY >= 0 && CurrentY < Width && CurrentX < Length && !visited[CurrentY][CurrentX] && array[CurrentY][CurrentX] == '#')
            {
                visited[CurrentY][CurrentX] = true;
                q.push({distance + 1, {CurrentX, CurrentY}});
                Dir[CurrentY][CurrentX] = direction[i];
            }
        }
    }

    return Dir;
}

bool AliveCheck(char **Screen, int i, int j, int Length, int Width)
{
    int AliveCounter = 0;
    for (int k = i - 1; k <= i + 1; k++)
    {
        for (int u = j - 1; u <= j + 1; u++)
        {
            if ((u == j && k == i) || u < 0 || k < 0 || u >= Length || k >= Width)
                continue;

            else if (Screen[k][u] == '@')
            {
                AliveCounter++;
            }
        }
    }
    if (AliveCounter == 2 || AliveCounter == 3)
        return true;

    else
        return false;
}

void Printer(char **array, int Length, int Width)
{
    system("cls");
    for (size_t i = 0; i < 2 * Width - 1; i++)
    {
        for (size_t j = 0; j < Length; j++)
        {
            if (i % 2 == 0)
            {
                if (j < Length - 1)
                    cout << array[i / 2][j] << " | ";
                else if (j == Length - 1)
                    cout << array[i / 2][j];
            }
            else if (i % 2 == 1)
            {
                if (j != Length - 1)
                    cout << "----";
                else
                    cout << "-";
            }
        }
        cout << endl;
    }
}

vector<Coordinates> PathFinder(char **DirTable, Coordinates Destination, Coordinates Beginning)
{
    vector<Coordinates> Path;
    queue<Coordinates> q;
    q.push(Destination);
    while (!q.empty())
    {
        Coordinates temp = q.front();
        q.pop();

        Path.push_back(temp);

        if (temp.x == Beginning.x && temp.y == Beginning.y)
        {
            return Path;
        }
        else
        {
            if (DirTable[temp.y][temp.x] == 'L')
            {
                q.push({temp.x + 1, temp.y});
            }
            else if (DirTable[temp.y][temp.x] == 'R')
            {
                q.push({temp.x - 1, temp.y});
            }
            else if (DirTable[temp.y][temp.x] == 'D')
            {
                q.push({temp.x, temp.y - 1});
            }
            else if (DirTable[temp.y][temp.x] == 'U')
            {
                q.push({temp.x, temp.y + 1});
            }
        }
    }
}

int main()
{
    srand(time(0));
    int ScreenLength, ScreenWidth;

    cout << "Enter the number of columns: ";
    while (!(cin >> ScreenLength) || ScreenLength <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n');
        cout << "Invalid amount of columns. Please enter a positive integer: ";
    }
    cout << "Enter the number of rows: ";
    while (!(cin >> ScreenWidth) || ScreenWidth <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n');
        cout << "Invalid amount of rows. Please enter a positive integer: ";
    }

    char **Screen = new char *[ScreenWidth];
    for (size_t i = 0; i < ScreenWidth; i++)
    {
        *(Screen + i) = new char[ScreenLength];
    }

    // the way you want to fill the Screen
    string answer;
    cout << "Do you want to enter the amount of cells alive?" << endl;
    while (!(cin >> answer) || (answer != "yes" && answer != "no" && answer != "Yes" && answer != "No"))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n');
        cout << "Invalid answer. Please enter 'yes' or 'no': ";
    }

    if (answer == "yes" || answer == "Yes")
    {
        int CellAliveNum;
        cout << "Please enter the amount of cells you wish to be alive: " << endl;
        while (!(cin >> CellAliveNum) || CellAliveNum < 0 || CellAliveNum > ScreenWidth * ScreenLength)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');
            if (CellAliveNum > ScreenWidth * ScreenLength)
            {
                cout << "Error: alive cells can not be more than the amount of cells themselves." << "Please try again :" << endl;
            }
            else
                cout << "Invalid amount of alive cells. Please enter a positive integer: ";
        }

        // First Frame

        int AliveCounter = 0;

        for (size_t i = 0; i < ScreenWidth; i++)
        {
            for (size_t j = 0; j < ScreenLength; j++)
            {
                Screen[i][j] = '#';
            }
        }

        while (AliveCounter < CellAliveNum)
        {
            int RandomRow = rand() % ScreenWidth;
            int RandomColumn = rand() % ScreenLength;

            if (Screen[RandomRow][RandomColumn] != '@')
            {
                Screen[RandomRow][RandomColumn] = '@';
                AliveCounter++;
            }
        }

        cout << "The First Frame :" << endl
             << endl;
        Sleep(500);
        Printer(Screen, ScreenLength, ScreenWidth);
        cout << endl;
        Sleep(1500);

        for (size_t RefreshRate = 0; RefreshRate < 2; RefreshRate++)
        {
            for (size_t i = 0; i < ScreenWidth; i++)
            {
                for (size_t j = 0; j < ScreenLength; j++)
                {
                    if (AliveCheck(Screen, i, j, ScreenLength, ScreenWidth))
                        Screen[i][j] = '1';

                    else
                        Screen[i][j] = '#';
                }
            }

            for (size_t i = 0; i < ScreenWidth; i++)
            {
                for (size_t j = 0; j < ScreenLength; j++)
                {
                    if (Screen[i][j] == '1')
                        Screen[i][j] = '@';
                }
            }

            // PRINTING
            if (RefreshRate == 0)
            {
                cout << "The Second Frame :" << endl
                     << endl;
                Sleep(500);
                Printer(Screen, ScreenLength, ScreenWidth);
                cout << endl;
                Sleep(1500);
            }
            else if (RefreshRate == 1)
            {
                cout << "The Third Frame :" << endl
                     << endl;
                Sleep(500);
                Printer(Screen, ScreenLength, ScreenWidth);
                cout << endl;
                Sleep(1500);
            }
        }
        cout << endl;
    }

    else if (answer == "No" || answer == "no")
    {
        Sleep(400);
        cout << endl
             << "Here's your random seed: " << endl
             << endl;
        Sleep(700);

        // First Frame
        for (size_t i = 0; i < ScreenWidth; i++)
        {
            for (size_t j = 0; j < ScreenLength; j++)
            {
                int RandomNumber = rand() % 2;
                if (RandomNumber == 0)
                {
                    Screen[i][j] = '@'; // alive
                }
                else
                {
                    Screen[i][j] = '#'; // dead
                }
            }
        }

        cout << "The First Frame :" << endl
             << endl;
        Sleep(500);
        Printer(Screen, ScreenLength, ScreenWidth);
        cout << endl;
        Sleep(1500);

        for (size_t RefreshRate = 0; RefreshRate < 2; RefreshRate++)
        {
            for (size_t i = 0; i < ScreenWidth; i++)
            {
                for (size_t j = 0; j < ScreenLength; j++)
                {
                    if (AliveCheck(Screen, i, j, ScreenLength, ScreenWidth))
                        Screen[i][j] = '1';

                    else
                        Screen[i][j] = '#';
                }
            }

            for (size_t i = 0; i < ScreenWidth; i++)
            {
                for (size_t j = 0; j < ScreenLength; j++)
                {
                    if (Screen[i][j] == '1')
                        Screen[i][j] = '@';
                }
            }

            // PRINTING
            if (RefreshRate == 0)
            {
                cout << "The Second Frame :" << endl
                     << endl;
                Sleep(500);
                Printer(Screen, ScreenLength, ScreenWidth);
                cout << endl;
                Sleep(1500);
            }
            else if (RefreshRate == 1)
            {
                cout << "The Third Frame :" << endl
                     << endl;
                Sleep(500);
                Printer(Screen, ScreenLength, ScreenWidth);
                cout << endl;
                Sleep(1500);
            }
        }
        cout << endl;
    }
    ////////////////////////////////////////////////////////////////////////////////  BFS  ///////////////////////////////////////////////////////////////////////////////////
    Coordinates beginning, destination;

    cout << "Enter the beginning's coordinates (x, y): ";
    while (!(cin >> beginning.x >> beginning.y) || beginning.x < 0 || beginning.x >= ScreenLength || beginning.y < 0 || beginning.y >= ScreenWidth)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Coordinates. Please try again: ";
    }
    cout << "Enter the destination's coordinates (x, y): ";
    while (!(cin >> destination.x >> destination.y) || destination.x < 0 || destination.x >= ScreenLength || destination.y < 0 || destination.y >= ScreenWidth)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Coordinates. Please try again: ";
    }

    char **DirTable = BFS(Screen, beginning, destination, ScreenLength, ScreenWidth);

    if (DirTable[destination.y][destination.x] == 'G')
    {
        cout << "No path found." << endl
             << "You have lost";
    }
    else
    {
        vector<Coordinates> Path = PathFinder(DirTable, destination, beginning);

        cout << endl
             << "The Path is: " << endl;
        for (int i = Path.size() - 1; i >= 0; i--)
        {
            cout << '(' << Path[i].x << " , " << Path[i].y << ")  ";
        }
    }
    for (size_t i = 0; i < ScreenWidth; i++)
    {
        delete[] Screen[i];
    }
    delete[] Screen;

    for (size_t i = 0; i < ScreenWidth; i++)
    {
        delete[] DirTable[i];
    }
    delete[] DirTable;
}