#include <iostream>
#include <conio.h>

#pragma warning(disable:4996)

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();

char getMapValue(int value);

const int mapwidth = 11;
const int mapheight = 22;

const int size = mapwidth * mapheight;

int map[size];

int headxpos;
int headypos;
int direction;

int food = 3;

bool running;

int main()
{
	run();
	return 0;
}

void run()
{
	initMap();
	running = true;
	while (running) {
		if (kbhit()) {
			changeDirection(getch());
		}
		update();

		clearScreen();

		printMap();

		_sleep(500);
	}

	std::cout << "\t\t!!!Game over!" << std::endl << "\t\tYour score is: " << food;

	std::cin.ignore();
}

void changeDirection(char key) {
	switch (key) {
	case 'w':
		if (direction != 2) direction = 0;
		break;
	case 'd':
		if (direction != 3) direction = 1;
		break;
	case 's':
		if (direction != 4) direction = 2;
		break;
	case 'a':
		if (direction != 5) direction = 3;
		break;
	}
}

void move(int dx, int dy) {
	int newx = headxpos + dx;
	int newy = headypos + dy;

	if (map[newx + newy * mapwidth] == -2) {
		food++;

		generateFood();
	}

	else if (map[newx + newy * mapwidth] != 0) {
		running = false;
	}

	headxpos = newx;
	headypos = newy;
	map[headxpos + headypos * mapwidth] = food + 1;

}

void clearScreen() {
	system("cls");
}

void generateFood() {
	int x = 0;
	int y = 0;
	do {
		x = rand() % (mapwidth - 2) + 1;
		y = rand() % (mapheight - 2) + 1;

	} while (map[x + y * mapwidth] != 0);

	map[x + y * mapwidth] = -2;
}

void update() {
	switch (direction) {
	case 0: move(-1, 0);
		break;
	case 1: move(0, 1);
		break;
	case 2: move(1, 0);
		break;
	case 3: move(0, -1);
		break;
	}

	for (int i = 0; i < size; i++) {
		if (map[i] > 0) map[i]--;
	}
}

void initMap()
{
	headxpos = mapwidth / 2;
	headypos = mapheight / 2;
	map[headxpos + headypos * mapwidth] = 1;

	for (int x = 0; x < mapwidth; ++x) {
		map[x] = -1;
		map[x + (mapheight - 1) * mapwidth] = -1;
	}

	for (int y = 0; y < mapheight; y++) {
		map[0 + y * mapwidth] = -1;
		map[(mapwidth - 1) + y * mapwidth] = -1;
	}

	generateFood();
}

void printMap()
{
	for (int x = 0; x < mapwidth; ++x) {
		for (int y = 0; y < mapheight; ++y) {
			std::cout << getMapValue(map[x + y * mapwidth]);
		}
		std::cout << std::endl;
	}
}

char getMapValue(int value)
{
	if (value > 0) return '0';

	switch (value) {
	case -1: return 'X';
	case -2: return 'O';
	}

	return ' ';
}