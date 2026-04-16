#include <iostream>
#include<conio.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <iomanip>
using namespace std;


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const char PLAYER_HEAD = '^';
const char PLAYER_BODY = 'A';
const char PLAYER_LEFT = '/';
const char PLAYER_RIGHT = '\\';
const char POLICE_SYMBOL = 'P';
const char OBSTACLES[] = { '#', 'X', '*' };
const int OBSTACLE_COUNT = sizeof(OBSTACLES) / sizeof(OBSTACLES[0]);

void mainmenu();
void playGame();
bool goBack();
void howToPlay();
void map(char arr[][21]);
void  display(char arr[][21], int a, int b, int coina, int coinb, int policex, int policey);
void player(char arr[][21], int& x, int& y);
void movement(char arr[][21], int& x, int& y);
void randObj(char arr[][21], int& a, int& b);
void randObjMov(char arr[][21], int& a, int& b, char& obstacleSymbol);
void coin(char arr[][21], int& coina, int& coinb);
void coincollect(char arr[][21], int& coina, int& coinb, int x, int y, int& score);
void healthCounter(char arr[][21], int& health);
int healthCheck(int health, int score, int distance);
void timecheck(int& time, int distance);
void policeKill(char arr[][21], int& policex, int& policey, int x, int y, int& health);
void policeMove(char arr[][21], int& policex, int& policey, int x, int y);
void police(char arr[][21], int policex, int policey);
void gameHistoryOnFile(int score, int distance, string name);
void gameHistoryInFile();
void setupConsoleForGame();
void moveCursorTopLeft();
bool isObstacle(char cell);
const int ROWS = 27;
const int COLS = 21;

int main()
{

	mainmenu();
}

void setupConsoleForGame()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void moveCursorTopLeft()
{
	COORD cursorPos = { 0, 0 };
	SetConsoleCursorPosition(hConsole, cursorPos);
}

bool isObstacle(char cell)
{
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		if (cell == OBSTACLES[i])
		{
			return true;
		}
	}
	return false;
}

bool goBack() //function for going back to main menu
{
	char press;
	bool flag;
	cout << "\nIf you want to go back press any button \nTo exit press 0\n";
	press = _getch();
	if (press != '0')
	{
		flag = true;
	}
	else {
		flag = false;
	}
	return flag;
}
void mainmenu() //Mainmenu display
{
	srand(time(0));
	char x;
	bool flag = true;
	
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
		SetConsoleTextAttribute(hConsole, 3);
		cout << setw(73) << "==========================" << endl;
		Sleep(100);
		SetConsoleTextAttribute(hConsole, 11);
		cout << setw(49) << "||"<<setw(18) << "ENDLESS RUNNER" << setw(6) << "||" << endl;
		Sleep(100);
		SetConsoleTextAttribute(hConsole, 3);
		cout << setw(73) << "==========================" << endl;
		Sleep(2000);
	do
	{
		system("cls");
		
		
		system("cls");
		Sleep(100);
		SetConsoleTextAttribute(hConsole, 2);
		cout << setw(42) << "****************************\n";
		Sleep(100);
		SetConsoleTextAttribute(hConsole, 10);
		cout << setw(35) << "ENDLESS RUNNER\n\n";
		Sleep(100);
		SetConsoleTextAttribute(hConsole, 2);
		cout << setw(44) << "****************************\n\n\n";
		Sleep(100);
		SetConsoleTextAttribute(hConsole, 3);
		cout << "1) Play Game\n"
			<< "2) Game History\n"
			<< "3) How to Play?\n"
			<< "4) Exit\n"
			<< "\n\nChoose one: ";
		cin >> x;
		cin.ignore();
		switch (x)
		{
		case'1':
		{
			playGame();          //STARTS THE GAME
			flag = goBack();
			break;
		}
		case'2':
		{
			gameHistoryInFile(); //Score history
			flag = goBack();
			break;
		}
		case'3':
		{
			howToPlay(); //Instructions
			flag = goBack();
			break;
		}
		case'4':
		{
			////exit()
			flag = false;
			break;
		}
		default:
		{
			cout << "Invalid Choice\n Try again";
			flag = true;
			break;
		}
		}
	} while (flag);
}


void playGame() //gamecode
{
	string name;
	cout << "Enter Name:";
	cin >> name;
	srand(time(0));
	int coinb = rand() % 17 + 2;
	int coina = rand() % 11 + 15;
	
	char arr[ROWS][COLS]{};
	int x = 25, y = 9;
	int policex = -1000, policey = -1000;
	
	int health = 3, score = 0, count = 0, distance = 0, time = 151, speedCount=0;
	int a[3] = {}, b[3] = {};
	char obstacleSymbol[3] = { '#', '#', '#' };
	setupConsoleForGame();
	system("cls");
	for (int i = 0; i < 3; i++)
	{
		b[i] = (rand() % 19) + 1;
		obstacleSymbol[i] = OBSTACLES[rand() % OBSTACLE_COUNT];
	}
	while (1)
	{
		
		moveCursorTopLeft();
		map(arr);
		player(arr, x, y);
		randObjMov(arr, a[0], b[0], obstacleSymbol[0]);
		if (count > 30)
		{
			randObjMov(arr, a[1], b[1], obstacleSymbol[1]);
		}
		if (count > 50)
		{
			randObjMov(arr, a[2], b[2], obstacleSymbol[2]);
		}
		
		coin(arr, coina, coinb);
		
	
		if (distance >= 500)
		{
			if (distance == 500)
			{
				policex = 0; policey = 19;
			}
			police(arr, policex, policey);	
			
		}
		
		healthCounter(arr, health);
		cout << "Score:" << score << "  	health:" << health << "		Distance: " << distance << "m" << "		Speed Level: " << speedCount << endl;
		display(arr,x,y,coina,coinb,policex,policey);
		movement(arr, x, y);
		
		coincollect(arr, coina, coinb, x, y, score);
		Sleep(time);
		if (distance % 1000 == 0 && time > 20)
		{
			speedCount++;
			time=time - 20;
		}
		
		if (distance >= 500 && count % 6 == 0)
		{

			policeMove(arr, policex, policey, x, y);
		}
		if (distance >= 500)
		{
			policeKill(arr, policex, policey, x, y, health);
		}
		distance = distance + 10;
		count++;
		
		if (healthCheck(health,score,distance))
		{
			break;
		}

	}
	gameHistoryOnFile(score, distance, name);


}


void map(char arr[][21]) //map initialization
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (j == 0 || j == COLS - 1)
			{
				arr[i][j] = '|';
			}
			else
			{
				arr[i][j] = ' ';
			}


		}

	}
}
void display(char arr[][21], int a, int b, int coina, int coinb, int policex, int policey) //map printing
{
	SetConsoleTextAttribute(hConsole, 5);
	for (int i = 0; i < ROWS; i++)
	{
		
		for (int j = 0; j < COLS; j++)
		{
			if (arr[i][j] == PLAYER_HEAD || arr[i][j] == PLAYER_RIGHT || arr[i][j] == PLAYER_LEFT || arr[i][j] == PLAYER_BODY)
			{
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (arr[i][j]=='$')
			{
				SetConsoleTextAttribute(hConsole, 6);
			}
			else if (arr[i][j] == POLICE_SYMBOL)
			{
				SetConsoleTextAttribute(hConsole, 4);
			}
			else if (isObstacle(arr[i][j]))
			{
				SetConsoleTextAttribute(hConsole, 9);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 14);
			}
			cout << arr[i][j];
		}

		cout << endl;
	}

}

void player(char arr[][21], int& x, int& y)  //character "^" generation
{
	
	arr[x][y] = PLAYER_HEAD;
		arr[x + 1][y + 1] = PLAYER_RIGHT;
		arr[x + 1][y - 1] = PLAYER_LEFT;
		arr[x + 1][y] = PLAYER_BODY;
	
}


void movement(char arr[][21], int& x, int& y) //character movement
{
	

	char ch;

	if (_kbhit())
	{
		ch = _getch();
		arr[x][y] = ' ';
		arr[x + 1][y + 1] = ' ';
		arr[x + 1][y - 1] = ' ';
		arr[x + 1][y] = ' ';

		if (ch == 'w' || ch == 'W')
		{
			if (x > 12)
			{
				x = x - 1;
			}
		}
		else if (ch == 'a' || ch == 'A')
		{
			if (y > 2)
			{
				y = y - 1;
			}
		}
		else if (ch == 'd' || ch == 'D')
		{
			if (y < 18)
			{
				y = y + 1;
			}
		}
		else if (ch == 's' || ch == 'S')
		{
			if (x < 25)
			{
				x = x + 1;
			}
		}
		else if (ch == ' ')
		{
			if (x > 13)
			{
				x = x - 2;
			}
		}
		
		arr[x][y] = PLAYER_HEAD; // Set the new character position
		arr[x + 1][y + 1] = PLAYER_RIGHT;
		arr[x + 1][y - 1] = PLAYER_LEFT;
		arr[x + 1][y] = PLAYER_BODY;
	}
}


void randObj(char arr[][21], int& a, int& b) //random obj "#" generation
{
	{
		arr[a][b] = '#';

	}
}

void randObjMov(char arr[][21], int& a, int& b, char& obstacleSymbol)  //random object movement
{


	arr[a][b] = ' ';  

	a = a + 1;
	
	if (a >= 25 || arr[a][b] == POLICE_SYMBOL || arr[a][b] == PLAYER_RIGHT || arr[a][b] == PLAYER_LEFT || isObstacle(arr[a][b]))
	{
		a = 0;
		b = (rand() % 17) + 2;
		obstacleSymbol = OBSTACLES[rand() % OBSTACLE_COUNT];
	}

	arr[a][b] = obstacleSymbol;
	
}
void coin(char arr[][21], int& coina, int& coinb)  //coin "+" generation
{
	arr[coina][coinb] = '$';
}
void coincollect(char arr[][21], int& coina, int& coinb, int x, int y, int& score)  // coin/score code
{
	if (coina == x && coinb == y)
	{
		score++;
		coinb = rand() % 17 + 2;
		coina = rand() % 11 + 15;
		
	}
}
void healthCounter(char arr[][21], int& health) // health counter
{
	for (int i = 0; i < ROWS - 1; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			
			if (isObstacle(arr[i][j]) && arr[i + 1][j] == PLAYER_HEAD)
				health--;
			
		}
	}

}
int healthCheck(int health, int score,int distance)  //health check
{
	if (health == 0)
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "			YOU LOST			";
		cout << "Score:" << score  << "		Distance: " << distance << "m" << endl;
		Sleep(1000);
		return 1;
	}
	else
	{
		return 0;
	}
}
void timecheck(int& time, int distance) //speedup map check
{
	if (distance % 100 == 0 && time > 0)
	{
		time = time - 10;

	}
}

void howToPlay() //instructons
{
	system("cls");
	SetConsoleTextAttribute(hConsole, 3);
	cout << "\nThe objective of the game is to cover the maximum distance possible while collecting coins.";
	cout << "\nWhile avoiding randomly generated obstacles.\nThe player character will have a limited capacity to move sideways, forwards and backwards.";
	cout << "\nThe game will end when the player runs out of lives.";
	cout << "\nYou have 3 Lives";
	cout << "\nUse w,a,s,d and spacebar to move Upward,Left,Downward,Right and jump respectively.";
	cout << "\n$ are coins try to collect them to raise your score.";
	cout << "\n# , X and * are random objects,try to avoid them.";
	cout << "\nafter 500 m a policeman '" << POLICE_SYMBOL << "' will try to kill you.\n\n";
}
void gameHistoryOnFile(int score, int distance, string name) //puts data in the file
{
	SetConsoleTextAttribute(hConsole, 3);
	ofstream fout;
	fout.open("Endless Runner Game History", ios::app);
	if (!fout.is_open())
	{
		SetConsoleTextAttribute(hConsole, 3);
		cout << "file not found \n";
		return;
	}

	fout << endl;
	fout << "name of player : " << name << endl;
	fout << "score " << score << endl;
	fout << "distance " << distance << "m" << endl;
	fout.close();

	return;
}

void gameHistoryInFile() //reads data in file
{
	char ch1;
	ifstream fin;
	SetConsoleTextAttribute(hConsole, 3);
	fin.open("Endless Runner Game History");
	if (!fin.is_open())
	{
		SetConsoleTextAttribute(hConsole, 3);
		cout << "file not found \n";
		return;
	}
	while (!fin.eof())
	{
		fin.get(ch1);
		cout << ch1;
	}
	fin.close();
	
}
void police(char arr[][21], int policex, int policey) //police "O" character
{
	arr[policex][policey] = POLICE_SYMBOL;
}
void policeMove(char arr[][21], int& policex, int& policey, int x, int y) // police movement
{
	if (x > policex)
	{
		policex++;
	}
	else if (x < policex)
	{
		policex--;
	}
	if (y > policey)
	{
		policey++;
	}
	else if (y < policey)
	{
		policey--;
	}
	
	
}
void policeKill(char arr[][21], int& policex, int& policey, int x, int y, int& health) //police kill code
{
	if (x == policex && y == policey)
	{
		policex = 0;
		policey = 19;
		health--;
	}

}