#include <iostream>
#include <random>
using namespace std;

int** array_keyboard_filling(const size_t rows, const size_t columns, const string& message);
/**
* /brief  Fills array from keyboard.
* /params rows - rows, columns - columns, message - request for entering a new element.
* /return Filled array.
*/

int** array_random_filling(const size_t rows, const size_t columns);
/**
* /brief  Fills array with random numbers.
* /params rows - rows, columns - columns;
* /return Filled array.
*/

int** replace_3_columns(int** array, const size_t rows, const size_t columns);
/**
* /brief  Fills array with random numbers.
* /params rows - rows, columns - columns;
* /return Filled array.
*/

bool is_even(const int number);
/**
* \brief  Ñhecks the number for parity.
* \param  number - number.
* \return True if even else False.
*/

size_t new_rows_number(const size_t rows);
/**
* \brief  Calulates count of rows, if after each odd row insert dirst row.
* \param  rows - count of rows in old array.
* \return New count of rows.
*/

int** extended_array(int** array, const size_t rows);
/**
* \brief  Expands the array by inserting the first row after each odd row.
* \param  array - old array, rows - number of rows of old array.
* \return New extended array.
*/

enum class Filling_Choice { keyboard, random };
/**
* \brief Users choice of array filling.
*		 0 - keyboard, 1 - random.
*/

void array_print(int** array, const size_t rows, const size_t columns);
/**
* \brief Prints an array.
* \param array - array, rows - number of rows, columns - number of columns.
*/

void delete_array(int** array, const size_t rows);
/**
* \brief Deletes an array.
* \param array - array, rows - number of rows, columns - number of columns.
*/

int main()
{
	cout << "Enter number of rows: ";
	size_t rows;
	cin >> rows;

	cout << "Enter number of columns: ";
	size_t columns;
	cin >> columns;

	cout << '\n' << "Choose how to fill the array\n"
		<< static_cast<int>(Filling_Choice::keyboard) << " - keyboard,\n"
		<< static_cast<int>(Filling_Choice::random) << " - random,\n"
		<< "Your choice is ";

	int input;
	cin >> input;
	cout << '\n';

	const auto choice = static_cast<Filling_Choice>(input);

	int** my_array = new int* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		my_array[i] = nullptr;
	}
	const string message = "Enter the element of the array";
	switch (choice)
	{
	case Filling_Choice::keyboard:
	{
		my_array = array_keyboard_filling(rows, columns, message);
	};
	case Filling_Choice::random:
	{
		my_array = array_random_filling(rows, columns);
	};
	default: {};
	};

	array_print(my_array, rows, columns);
	auto replaced_array = replace_3_columns(my_array, rows, columns);
	array_print(replaced_array, rows, columns);
	auto new_array = extended_array(my_array, rows);
	array_print(new_array, new_rows_number(rows), columns);

	delete_array(my_array, rows);
	delete_array(replaced_array, rows);
	delete_array(new_array, new_rows_number(rows));
	return 0;
}

int** array_keyboard_filling(const size_t rows, const size_t columns, const string& message)
{
	auto** array = new int* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		array[i] = new int[columns];
	}

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			cout << message;
			cin >> array[i][j];
		}
	}

	return array;
}

int** array_random_filling(const size_t rows, const size_t columns)
{
	random_device rd;
	mt19937 gen(rd());

	const int rand_min = -10;
	const int rand_max = 20;

	uniform_int_distribution <> dis(rand_min, rand_max);

	auto** array = new int* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		array[i] = new int[columns];
	};

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			array[i][j] = dis(gen);
		};
	};

	return array;
}

bool is_even(const int number)
{
	return (number % 2 == 0) ? true : false;
}

int** replace_3_columns(int** array, const size_t rows, const size_t columns)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			array[i][j] = array[i][j] * array[i][j];
		}
	}

	return array;
}

size_t new_rows_number(const size_t rows)
{
	return rows + rows / 2;
}

int** extended_array(int** array, const size_t rows)
{
	auto** new_array = new int* [new_rows_number(rows)];
	for (size_t i = 0; i < new_rows_number(rows); i++)
	{
		new_array[i] = nullptr;
	};

	auto step = 0;

	for (size_t i = 0; i < rows; i++)
	{
		if (!is_even(i))
		{
			new_array[i + step] = array[i];
			new_array[i + step + 1] = array[0];
			step++;
		}
		else
		{
			new_array[i + step] = array[i];
		}

	}

	return new_array;
}

void array_print(int** array, const size_t rows, const size_t columns)
{

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			cout << array[i][j] << ',';
		};
		cout << '\n';
	};
	cout << endl;
}

void delete_array(int** array, const size_t rows)
{
	if (array == nullptr)
		return;
	for (int i = 0; i < rows; i++)
		delete[] array[i];
	delete[] array;
}