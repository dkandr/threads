#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include "simpletimer.h"

int ArraySum(int *array, int size)
{
	int sum = 0;

	for (int i = 0; i < size; ++i)
	{
		sum += array[i];
	}
	return sum;
}

int main()
{
	setlocale(LC_ALL, "");

	int arr_size, arr_parts;

	do
	{
		std::cout << "N % M == 0, M != 0" << std::endl;
		std::cout << "Введите размер массива (N) : ";
		std::cin >> arr_size;
		std::cout << "Количество частей, на которые будет разбит массив (M) : ";
		std::cin >> arr_parts;
	} while (arr_parts == 0 || arr_size % arr_parts != 0);

	srand((unsigned)time(0));

	std::cout << "Массив : ";

	int array[arr_size];
	// Заполняем массив
	for(int i = 0; i < arr_size; ++i)
	{
		array[i] = rand() % 100 + 1;
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;

	SimpleTimer timer; // запускаем таймер

	int part_of_array_size = arr_size / arr_parts; // размер части массива

	int part_of_array[part_of_array_size];

	int result = 0;

	std::vector<std::thread> threads;

	std::cout << "разбиваем на :\n";
	for (int i = 0; i < arr_parts; ++i)
	{
		std::memcpy(part_of_array, array + i * part_of_array_size, sizeof(part_of_array));
		
		for (int j = 0; j < part_of_array_size; ++j)
		{
			std::cout << part_of_array[j] << " ";
		}

		std::cout << std::endl;

		// result += ArraySum(part_of_array, part_of_array_size);
		std::thread t([&result, &part_of_array, part_of_array_size]()
		{
			result += ArraySum(part_of_array, part_of_array_size);
		});
		threads.push_back(std::move(t));
	}

	for (auto& t : threads)
	{
		if (t.joinable())
		t.join();
	}
	
	std::cout << "Результат : " << result << std::endl;

	return 0;
}
