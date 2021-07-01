#include <iostream>
#include <random>
using namespace std;

/**
* \brief Filling the array from the keyboard.
* \param size - array size, message - request for entering a new element.
* \return Filled array.
*/
int* array_keyboard_filling(const size_t size, const string& message);

/**
* \brief Random filling of an array.
* \param size - array size.
* \return Filled array.
*/
int* array_random_filling(const size_t size);

/**
* \brief Replaces the last negative element of the array with the penultimate element.
* \param arr - array, size - array size.
* \return Filled array.
*/
int* replace_last_el(int* array, const size_t size);

/**
* \brief Deletes even elements from the array.
* \param arr - array, size - array size, odd_size - size of array without even elements.
* \return New array without even numbers.
*/
int* del_even_numbers(int* array, const size_t size, const size_t odd_size);

/**
* \brief Creates a new array based on the old array according to rule:
*		 if the number of the element of the old array is even - the element
*		 of new array is equal to the square of the element of the old one,
*		 else - to the doubled element of the old one.
* \param arr - array, num - array size.
* \return New array.
*/
int* create_new_array(const int* array, const size_t size);

/**
* \brief Prints an array.
* \param arr - array, size - array size, odd_size - size of array without even elements.
*/
void array_print(const int* array, const size_t size);

/**
* \brief Ñhecks the number for parity .
* \param number - number.
* \return True if even else False.
*/
bool is_even(const int number);

/**
* \brief Counts odd elements of the array.
* \param arr - array, size - size.
* \return Count of odd elements.
*/
size_t odd_size(const int* array, const size_t size);

/**
* \brief Users choice of array filling.
*		 0 - keyboard, 1 - random.
*/
enum class Filling_Choice { keyboard, random };

/**
* \brief Deletes an array from memory.
* \param array - array
*/
void delete_array(int* array);



int main()
{
	cout << "Enter number of array elements: ";
	size_t size;
	cin >> size;

	cout << '\n' << "Choose how to fill the array\n"
		<< static_cast<int>(Filling_Choice::keyboard) << " - keyboard,\n"
		<< static_cast<int>(Filling_Choice::random) << " - random,\n"
		<< "Your choice is ";

	int input;
	cin >> input;
	cout << '\n';

	const auto choice = static_cast<Filling_Choice>(input);

	int* my_array = nullptr;
	const string message = "Enter the element of the array";
	switch (choice)
	{
	case Filling_Choice::keyboard:
	{
		my_array = array_keyboard_filling(size, message);
		break;
	};
	case Filling_Choice::random:
	{
		my_array = array_random_filling(size);
		break;
	};
	default: {};
	}

	array_print(my_array, size);
	my_array = replace_last_el(my_array, size);
	array_print(my_array, size);

	const auto new_size = odd_size(my_array, size);

	auto odd_array = del_even_numbers(my_array, size, new_size);
	array_print(odd_array, new_size);
	delete_array(odd_array);

	auto new_array = create_new_array(my_array, size);
	array_print(new_array, size);
	delete_array(new_array);

	delete_array(my_array);

	return 0;
}

int* array_keyboard_filling(const size_t size, const string& message)
{
	auto array = new int[size];
	for (size_t i = 0; i < size; i++) {
		cout << '\n' << message;
		cin >> array[i];
	};

	return array;
};

int* array_random_filling(const size_t size)
{
	random_device rd;
	mt19937 gen(rd());

	const int rand_min = -10;
	const int rand_max = 20;

	uniform_int_distribution <> dis(rand_min, rand_max);

	auto array = new int[size];
	for (size_t i = 0; i < size; i++) {
		array[i] = dis(gen);
	};

	return array;
};

int* replace_last_el(int* array, const size_t size)
{
	size_t number = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (array[i] < 0)
		{
			number = i;
		}
	}
	array[number] = array[size - 2];
	return array;
};

int* del_even_numbers(int* array, const size_t size, const size_t odd_size) {

	auto new_array = new int[odd_size];
	int index = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (!is_even(array[i]))
		{
			new_array[index++] = array[i];
		}
	}

	return new_array;
}

bool is_even(const int number)
{
	return number % 2 == 0;
}

size_t odd_size(const int* array, const size_t size)
{
	auto new_size = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (!is_even(array[i]))
		{
			new_size++;
		}
	}

	return new_size;
}

int* create_new_array(const int* array, const size_t size)
{
	auto new_array = new int[size];

	for (size_t i = 0; i < size; i++)
	{
		if (is_even(i))
		{
			new_array[i] = array[i] * array[i];
		}
		else
		{
			new_array[i] = 2 * array[i];
		}
	}

	return new_array;
}

void array_print(const int* array, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << ", ";
	};
	cout << '\n';
};

void delete_array(int* array)
{
	if (array == nullptr)
		return;
	delete[] array;
	array = nullptr;
}