#include <iostream>
#include <random>
using namespace std;


int* array_keyboard_filling(const size_t size, const string& message);
/**
* \brief  Filling the array from the keyboard.
* \param  size - array size, message - request for entering a new element.
* \return Filled array.
*/

int* array_random_filling(const size_t size);
/**
* \brief Random filling of an array.
* \param size - array size.
* \return Filled array.
*/

void array_print(const int* array, const size_t size);
/**
* \brief Prints an array.
* \param arr - array, size - array size.
*/

bool is_even(const int number);
/**
* \brief  Ñhecks the number for parity .
* \param  number - number.
* \return True if even else False.
*/

int sum_of_odd_numbers(int* array, const size_t size);
/**
* \brief  Calculates and prints sum of odd elements of array.
* \param  array - array, size - size of array
* \return Sum of odd elements.
*/

int count_of_elements(int* arr, const size_t size);
/**
* \brief  Counts elements of array which more then entered local maximum
*		  and multiples of 5.
* \param  array - array, size - size of array.
* \return Count of elements which more then entered local maximum
*		  and multiples of 5.
*/

bool multiple_of_5(const int number);
/**
* \brief  Checks number for a multiple of 5.
* \param  number - number.
* \return True if number multiple of 5, else - False.
*/

bool not_null_element(const int* array);
/**
* \brief  Checks if first element of array is not null
* \param  array - array
* \return True if 1st element is not null, else - False.
*/


int* create_divided_array(int* array, const size_t size);
/**
* \brief  Creates new array, which even numbers of elements are divided by first
*		  element of the old array.
* \param  array - array, size - size of array.
* \return New divided array.
*/


enum class Filling_Choice { keyboard, random };
/**
* \brief Users choice of array filling.
*		 0 - keyboard, 1 - random.
*/


void delete_array(int* array);
/**
* \brief Deletes an array from memory.
* \param array - array
*/


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
	const string message = "Enter the element of the array: ";
	switch (choice)
	{
	case Filling_Choice::keyboard:
	{
		my_array = array_keyboard_filling(size, message);
	};
	case Filling_Choice::random:
	{
		my_array = array_random_filling(size);
	};
	default: {};
	};

	array_print(my_array, size);
	cout << "Sum of odd numbers of array: " << sum_of_odd_numbers(my_array, size) << '\n';
	cout << "Count of elements which more then entered local maximum and multiples of 5: " << count_of_elements(my_array, size) << '\n';

	auto divided_array = create_divided_array(my_array, size);
	array_print(divided_array, size);

	delete_array(my_array);
	delete_array(divided_array);
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

bool is_even(const int number)
{
	return number % 2 == 0;
}

void array_print(const int* array, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << ", ";
	};
	cout << '\n';
};

int sum_of_odd_numbers(int* array, const size_t size)
{
	auto sum = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (!is_even(i))
		{
			sum += array[i];
		}
	}

	return sum;
};

int count_of_elements(int* array, const size_t size)
{
	int local_max;

	cout << "Enter local maximum A: ";
	cin >> local_max;

	int count_of_elements = 0;

	for (size_t i = 0; i < size; i++) {
		if ((array[i] > local_max) && (multiple_of_5(array[i])))
		{
			count_of_elements++;
		}
	}

	return count_of_elements;
};

int* create_divided_array(int* array, const size_t size)
{
	auto new_array = new int[size];

	if (not_null_element(array))
	{
		for (size_t i = 0; i < size; i++)
		{
			if (is_even(i))
			{
				new_array[i] = array[i] / array[0];
			}
			else
			{
				new_array[i] = array[i];
			}
		}
		return new_array;
	}
	else
	{
		cout << "Try to use this function with array, which first element is not null." << '\n';
	}

}

bool multiple_of_5(const int number)
{
	return (number % 5 == 0) ? true : false;
}

bool not_null_element(const int* array)
{
	return (array[0] != 0) ? true : false;
}

void delete_array(int* array)
{
	if (array == nullptr)
		return;
	delete[] array;
	array = nullptr;
}