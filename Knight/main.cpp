#include <iostream>
#include <iomanip>
#include <map>

namespace
{
	const int WIDTH = 8;

	enum class DIRECTION {
		UP_LEFT, UP_RIGHT,
		RIGHT_UP, RIGHT_DOWN,
		DOWN_RIGHT, DOWN_LEFT,
		LEFT_DOWN, LEFT_UP
	};
}

void print(const int* arr)
{
	system("cls");

	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
			std::cout << std::setfill(' ') << std::setw(3) << arr[i + WIDTH * j];

		std::cout << std::endl;
	}
}

bool canMove(const int* arr, int x, int y)
{
	return ((x >= 0 && x < WIDTH) && (y >= 0 && y < WIDTH) && (arr[y + WIDTH * x] == 0));
}

int findStepCount(const int* arr, int x, int y)
{
	int count = 0;

	if (canMove(arr, x - 1, y - 2)) // up left
		count++;
	if (canMove(arr, x + 1, y - 2)) // up right
		count++;
	if (canMove(arr, x + 2, y - 1)) // right up
		count++;
	if (canMove(arr, x + 2, y + 1)) // right down
		count++;
	if (canMove(arr, x + 1, y + 2)) // down right
		count++;
	if (canMove(arr, x - 1, y + 2)) // down left
		count++;
	if (canMove(arr, x - 2, y + 1)) // left down
		count++;
	if (canMove(arr, x - 2, y - 1)) // left up
		count++;

	return count;
}

bool move(int* arr, int x, int y)
{
	static int count = 0;
	std::multimap<int, DIRECTION> directions;

	if (count != WIDTH * WIDTH)
		arr[y + WIDTH * x] = ++count;

	if (canMove(arr, x - 1, y - 2))
		directions.insert({ findStepCount(arr, x - 1, y - 2), DIRECTION::UP_LEFT });
	if (canMove(arr, x + 1, y - 2))
		directions.insert({ findStepCount(arr, x + 1, y - 2), DIRECTION::UP_RIGHT });
	if (canMove(arr, x + 2, y - 1))
		directions.insert({ findStepCount(arr, x + 2, y - 1), DIRECTION::RIGHT_UP });
	if (canMove(arr, x + 2, y + 1))
		directions.insert({ findStepCount(arr, x + 2, y + 1), DIRECTION::RIGHT_DOWN });
	if (canMove(arr, x + 1, y + 2))
		directions.insert({ findStepCount(arr, x + 1, y + 2), DIRECTION::DOWN_RIGHT });
	if (canMove(arr, x - 1, y + 2))
		directions.insert({ findStepCount(arr, x - 1, y + 2), DIRECTION::DOWN_LEFT });
	if (canMove(arr, x - 2, y + 1))
		directions.insert({ findStepCount(arr, x - 2, y + 1), DIRECTION::LEFT_DOWN });
	if (canMove(arr, x - 2, y - 1))
		directions.insert({ findStepCount(arr, x - 2, y - 1), DIRECTION::LEFT_UP });


	for (auto itr = directions.begin(); itr != directions.end(); ++itr)
	{
		if (itr->second == DIRECTION::UP_LEFT)
			move(arr, x - 1, y - 2);
		if (itr->second == DIRECTION::UP_RIGHT)
			move(arr, x + 1, y - 2);
		if (itr->second == DIRECTION::RIGHT_UP)
			move(arr, x + 2, y - 1);
		if (itr->second == DIRECTION::RIGHT_DOWN)
			move(arr, x + 2, y + 1);
		if (itr->second == DIRECTION::DOWN_RIGHT)
			move(arr, x + 1, y + 2);
		if (itr->second == DIRECTION::DOWN_LEFT)
			move(arr, x - 1, y + 2);
		if (itr->second == DIRECTION::LEFT_DOWN)
			move(arr, x - 2, y + 1);
		if (itr->second == DIRECTION::LEFT_UP)
			move(arr, x - 2, y - 1);
	}

	if (count == WIDTH * WIDTH)
		return true;
	else
	{
		count--;
		arr[y + WIDTH * x] = 0;
		return false;
	}
}

void main()
{
	int arr[WIDTH * WIDTH]{ 0 };
	int x, y;

	std::cout << "Input coordinates(X Y): ";
	std::cin >> x >> y;
	
	if (x < WIDTH && y < WIDTH && move(arr, x, y))
		print(arr);
	else
		std::cout << "Incorrect coordinates!" << std::endl;

	system("pause");
}