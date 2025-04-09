#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <ctime>


// Допоміжні для роботи 
void Shutdown();
void ClearConsole();
void WaitForEnter();

// Меню та підменю
void MenuProgram();
void ArrayMenu(int*& array, int& size);
void MenuSearch(int* array, int size);

// Робота с масивами
void CreateArray(int*& array, int& size);
void DeleteArray(int*& array, int& size);
void ShowArray(int* array, int size);

void SortArray(int* array, int size);
bool IsAscending(int* array, int size);
bool IsDescending(int* array, int size);

bool IsArray(int* array, int size);
bool IsEmpty(int* array, int size);
bool IsSort(int* array, int size);

void FillRandom(int* array, int size);
void FillManual(int* array, int size);

// Методи пошуку
void LinearSearch(int* array, int size);
void BinarySearch(int* array, int size);
int CalculateMaxSteps(int& size); // лише для бінарного пошуку
void IndexedSeqSearch(int* array, int size);

void Shutdown()
{
	std::cout << "========================================================\n";
	std::cout << "             Shutting down the program...               \n";
	std::cout << "========================================================\n";

	exit(0);
}

void ClearConsole()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear"); // Cross-platform support
#endif
}

void WaitForEnter()
{
	std::cout << "\nPress Enter to continue...";
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cin.get();
}

void MenuProgram()
{
	int* array = nullptr;
	int size = 0;

	int number;
	int minOptions = 1;
	int maxOptions = 3;
	do
	{
		ClearConsole();

		std::cout << "========================================================\n";
		std::cout << "                     Main menu (1-3)                    \n";
		std::cout << "========================================================\n";
		std::cout << " #1. Work with array.                                   \n";
		std::cout << " #2. Search algorithms.                                 \n";
		std::cout << " #3. Exit program.                                      \n";
		std::cout << "========================================================\n\n";

		std::cout << "Enter the option: ";
		std::cin >> number;
		std::cout << "\n";

		ClearConsole();

		switch (number)
		{
		case 1:
			ArrayMenu(array, size);
			break;
		case 2:
			MenuSearch(array, size);
			break;
		case 3:
			Shutdown();
			break;
		default:
			std::cout << "========================================================\n";
			std::cout << "        Invalid option number! Please try again.        \n";
			std::cout << "========================================================\n";
			WaitForEnter();
		}
	} while (true);
}

void ArrayMenu(int*& array, int& size)
{
	int number;
	int minOptions = 1;
	int maxOptions = 5;

	do
	{
		ClearConsole();

		std::cout << "========================================================\n";
		std::cout << "                     Work with array:                   \n";
		std::cout << "========================================================\n";
		std::cout << "1. Create array.                                        \n";
		std::cout << "2. Delete array.                                        \n";
		std::cout << "3. Display array elements.                              \n";
		std::cout << "4. Sort array.                                          \n";
		std::cout << "5. Return to main menu.                                 \n\n";

		//3
		std::cout << "========================================================\n";
		std::cout << "            Information about current array:            \n";
		std::cout << "========================================================\n";

		std::cout << "Status:     ";
		IsArray(array, size) ? std::cout << "Created\n" : std::cout << "Not Created\n\n";

		if (IsArray(array, size)) // If the array is sorted, then additionally print the data :
		{
			std::cout << "Size:       " << size << " elements" << std::endl;

			if (size != 1)
			{
				std::cout << "Order:      ";
				IsSort(array, size) ? std::cout << "Sorted\n" : std::cout << "Not sorted\n\n";

				if (IsSort(array, size))
				{
					std::cout << "Sorting:    ";
					IsAscending(array, size) ? std::cout << "Ascending\n\n" : std::cout << "Discending\n\n";
				}
			}
			else
			{
				std::cout << "Order:      Not applicable (1 element)\n\n";
			}

		}

		std::cout << "Enter the option: ";
		std::cin >> number;
		std::cout << "\n";

		ClearConsole();

		switch (number)
		{
		case 1:
			CreateArray(array, size);
			break;
		case 2:
			DeleteArray(array, size);
			break;
		case 3:
			ShowArray(array, size);
			break;
		case 4:
			SortArray(array, size);
			break;
		case 5:
			return;
		default:
			std::cout << "========================================================\n";
			std::cout << "        Invalid option number! Please try again.        \n";
			std::cout << "========================================================\n";
			WaitForEnter();
		}
	} while (true);
}

void CreateArray(int*& array, int& size)
{
	if (IsArray(array, size))
	{
		std::cout << "========================================================\n";
		std::cout << "               Error! Array already exict.              \n";
		std::cout << "========================================================\n";
		WaitForEnter();
		return;
	}

	int minSize = 1;

	// Step 1 - Get array size
	int input_size;
	do
	{
		ClearConsole();

		std::cout << "========================================================\n";
		std::cout << "     (Step 1) Enter array size (min " << minSize << "): \n";
		std::cout << "========================================================\n";
		std::cout << "Size: ";
		std::cin >> input_size;

		if (input_size < minSize)
		{
			ClearConsole();

			std::cout << "========================================================\n";
			std::cout << "          Invalid array size! Please try again.         \n";
			std::cout << "========================================================\n";

			WaitForEnter();
		}

	} while (input_size < minSize);

	// Allocate memory

	array = new int[input_size];
	size = input_size;

	ClearConsole();

	// Step 2 - Choose filling method

	int number;
	int minOptions = 1; 
	int maxOptions = 2;

	do
	{
		ClearConsole();

		std::cout << "========================================================\n";
		std::cout << "      (Step 2) Choose array initialization method:      \n";
		std::cout << "========================================================\n";
		std::cout << "1. Fill with random values (min to max).                \n";
		std::cout << "2. Manual data entry.                                   \n";
		std::cout << "========================================================\n\n";
		std::cout << "Enter the option: ";
		std::cin >> number;
		std::cout << "\n";

		ClearConsole();

		switch (number)
		{
		case 1:
			FillRandom(array, size);
			return;
		case 2:
			FillManual(array, size);
			return;
		default:
			std::cout << "========================================================\n";
			std::cout << "        Invalid option number! Please try again.        \n";
			std::cout << "========================================================\n";
			WaitForEnter();
		}
	} while (true);
}
void DeleteArray(int*& array, int& size)
{
	if (IsArray(array, size))
	{
		char decision;
		do
		{
			std::cout << "========================================================\n";
			std::cout << "        Are you sure, that array will be deleted?       \n";
			std::cout << "========================================================\n";
			std::cout << "Yes/No (y/n): ";
			std::cin >> decision;
			ClearConsole();
		} while (!(decision == 'y' || decision == 'n'));

		if (decision == 'y')
		{
			delete[] array;
			array = nullptr;
			size = 0;

			std::cout << "========================================================\n";
			std::cout << "               Array successfully deleted!              \n";
			std::cout << "========================================================\n";
			WaitForEnter();
		}

		else
		{
			std::cout << "========================================================\n";
			std::cout << "                  Array not deleted!                    \n";
			std::cout << "========================================================\n";
			WaitForEnter();
		}
	}
	else
	{
		std::cout << "========================================================\n";
		std::cout << "             Error! Array doesn't created.:(            \n";
		std::cout << "========================================================\n";
		WaitForEnter();
	}
}

void FillRandom(int* array, int size)
{
	int min, max;
	do
	{
		std::cout << "========================================================\n";
		std::cout << "         Enter range for random values (min; max)       \n";
		std::cout << "========================================================\n";

		std::cout << "..................[min .......... max]..................\n";

		std::cout << "========================================================\n\n";

		std::cout << "Minimum value: ";
		std::cin >> min;

		std::cout << "Maximum value: ";
		std::cin >> max;

		ClearConsole();

		if (max <= min)
		{
			std::cout << "========================================================\n";
			std::cout << "                         Error!                         \n";
			std::cout << "========================================================\n\n";

			std::cout << "        1) Minimum value is greater than maximum        \n\n";

			std::cout << "                           or                           \n\n";

			std::cout << "        2) Minimum value equels maximum value.          \n\n";

			std::cout << "========================================================\n";
			WaitForEnter();
			ClearConsole();
		}
	} while (max <= min);

	srand(static_cast<unsigned int>(time(nullptr))); // генератор випадкових чисел

	for (size_t i = 0; i < size; i++)
	{
		array[i] = rand() % (max - min + 1) + min;
	}

	std::cout << "========================================================\n";
	std::cout << "                      Success! :)                       \n";
	std::cout << "========================================================\n";
	std::cout << "        Array filled with random values in range        \n";
	std::cout << "                   (from " << min << " to " << max << ")\n";
	std::cout << "========================================================\n";
	WaitForEnter();
	ClearConsole();
}

void FillManual(int* array, int size)
{
	const char* elementword;

	if (size == 1)
		elementword = "element";
	else
		elementword = "elements";

	std::cout << "========================================================\n";
	std::cout << "   Enter " << size << " " << elementword << " into the array: \n";
	std::cout << "========================================================\n\n";

	for (size_t i = 0; i < size; i++)
	{
		std::cout << "Element " << i + 1 << ": ";
		std::cin >> array[i];
	}
	
	std::cout << "\n========================================================\n";
	std::cout << "                         Success!                       \n";
	std::cout << "             Array filled with entered values.          \n";
	std::cout << "========================================================\n";

	WaitForEnter();
	ClearConsole();
}

void SortArray(int* array, int size)
{
	int number;
	int minOptions = 1;
	int maxOptions = 2;
	do
	{
		ClearConsole();

		std::cout << "========================================================\n";
		std::cout << "                 Choice sorting method:                 \n";
		std::cout << "========================================================\n";
		std::cout << "1. Sort is ascending order                              \n";
		std::cout << "2. Sort is discending order                             \n";
		std::cout << "========================================================\n\n";

		std::cout << "Enter the option: ";
		std::cin >> number;
		std::cout << "\n";

		ClearConsole();

		// Bubble sort implementation
		if (number == 1 || number == 2) 
		{
			for (int i = 0; i < size - 1; i++)
			{
				for (int j = 0; j < size - i - 1; j++)
				{
					bool changePlaces = false;

					if (number == 1)
						changePlaces = array[j + 1] < array[j];
					else
						changePlaces = array[j + 1] > array[j];

					if (changePlaces)
					{
						int temp = array[j];
						array[j] = array[j + 1];
						array[j + 1] = temp;
					}
				}
			}
			ShowArray(array, size);
			return;
		}
		else
		{
			std::cout << "========================================================\n";
			std::cout << "        Invalid option number! Please try again.        \n";
			std::cout << "========================================================\n";
			WaitForEnter();
		}
	} while (true);
}

void ShowArray(int* array, int size)
{
	if (IsArray(array, size))
	{
		std::cout << "========================================================\n";
		std::cout << "                    Array elements:                     \n";
		std::cout << "========================================================\n\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << "Element #" << i + 1 << ": " << array[i] << std::endl;
		}
		std::cout << "\n========================================================\n";
		WaitForEnter();
	}
	else
	{
		std::cout << "========================================================\n";
		std::cout << "             Error: Array doesn't exict! :(             \n";
		std::cout << "========================================================\n";
		std::cout << "      * To create an array use the menu options:       \n";
		std::cout << "      --------------------------------------------      \n";
		std::cout << "     | -> Work with array                         |     \n";
		std::cout << "     | --> Create array                           |     \n";
		std::cout << "      --------------------------------------------      \n";
		std::cout << "========================================================\n";
		WaitForEnter();
	}
}

bool IsArray(int* array, int size)
{
	return array != nullptr && size > 0;
}

bool IsEmpty(int* array, int size)
{
	return size <= 0 || array == nullptr;
}

bool IsSort(int* array, int size)
{
	if (IsEmpty(array, size))
		return false;
	return IsAscending(array, size) || IsDescending(array, size);
}

bool IsAscending(int* array, int size)
{
	if (IsEmpty(array, size)) return false;

	for (int i = 0; i < size - 1; i++)
	{
		if (array[i] > array[i + 1])
			return false;
	}

	return true;
}

bool IsDescending(int* array, int size)
{
	if (IsEmpty(array, size)) return false;

	for (int i = 0; i < size - 1; i++)
	{
		if (array[i] < array[i + 1])
			return false;
	}

	return true;
}

void MenuSearch(int* array, int size)
{
	if (IsArray(array, size))
	{
		int number;
		int minOptions = 1;
		int maxOptions = 4;
		do
		{
			ClearConsole();

			std::cout << "========================================================\n";
			std::cout << "                 Search algorithms (1-4)                \n";
			std::cout << "========================================================\n";
			std::cout << "1. Linear Search.                                       \n";
			std::cout << "2. Binary Search.                                       \n";
			std::cout << "3. Indexed sequential search.                           \n";
			std::cout << "4. Return to main menu.                                 \n";
			std::cout << "========================================================\n\n";

			std::cout << "Enter the option: ";
			std::cin >> number;
			std::cout << "\n";

			ClearConsole();

			switch (number)
			{
			case 1:
				LinearSearch(array, size);
				break;
			case 2:
				BinarySearch(array, size);
				break;
			case 3:
				IndexedSeqSearch(array, size);
				break;
			case 4:
				return;
			default:
				std::cout << "========================================================\n";
				std::cout << "        Invalid option number! Please try again.        \n";
				std::cout << "========================================================\n";
				WaitForEnter();
			}
		} while (true);
	}
	else
	{
		std::cout << "========================================================\n";
		std::cout << "               Error! Array not created                 \n";
		std::cout << "========================================================\n";
		std::cout << "> To use search algorithm you need to:                  \n\n";

		std::cout << "  1. Go to:                                             \n";
		std::cout << "     \"Work with array\"                                \n\n";
		std::cout << "  2. Select:                                            \n";
		std::cout << "     \"Create array\"                                   \n\n";

		std::cout << "========================================================\n";


		WaitForEnter();
		return;
	}
}

void LinearSearch(int* array, int size)
{
	std::cout << "========================================================\n";
	std::cout << "                  ~~ Linear Search ~~                   \n";
	std::cout << "========================================================\n\n";

	std::cout << "Enter element to search for: ";
	int target;
	std::cin >> target;

	bool isFound = false;
	int foundIndex = -1;
	int iterations = 0;

	for (int i = 0; i < size; i++)
	{
		iterations++;
		if (array[i] == target)
		{
			isFound = true;
			foundIndex = i;
			break;
		}
	}

	ClearConsole();

	std::cout << "========================================================\n";
	std::cout << "                    Search results:                     \n";
	std::cout << "========================================================\n";
	std::cout << "Target value:       " << target << "\n";
	std::cout << "Search status:      " << (isFound ? "Found" : "Not found") << "\n";

	if (isFound)
	{
		std::cout << "Position in array:  " << foundIndex << "\n";
		std::cout << "Element number:     #" << foundIndex + 1 << "\n";
	}

	std::cout << "Iterations:         " << iterations << "/" << size << "\n";
	std::cout << "========================================================\n\n";

	WaitForEnter();
}

void BinarySearch(int* array, int size)
{
	if (IsSort(array, size))
	{
		std::cout << "========================================================\n";
		std::cout << "                  ~~ Binary Search ~~                   \n";
		std::cout << "========================================================\n\n";

		std::cout << "Enter element to search for: ";
		int target;
		std::cin >> target;

		int low = 0;
		int high = size - 1;
		int mid = high / 2;
		int steps = 0;
		int max_steps = CalculateMaxSteps(size);

		while (low <= high)
		{
			steps++;
			mid = low + (high - low) / 2; // Secure calculation (overflow protection)

			if (target == array[mid])
				break;
			else if (target < array[mid])
				high = mid - 1;
			else // (target > array[mid])
				low = mid + 1;
		}

		bool isFound = (array[mid] == target && low <= high);

		ClearConsole();

		std::cout << "========================================================\n";
		std::cout << "                    Search results:                     \n";
		std::cout << "========================================================\n";
		std::cout << "Target value:       " << target << "\n";
		std::cout << "Search status:      " << (isFound ? "Found" : "Not found") << "\n";

		if (isFound)
		{
			std::cout << "Position in array:  " << mid << "\n";
			std::cout << "Element number:     #" << mid + 1 << "\n";
		}

		std::cout << "Comparisons:        " << steps << "\n";
		std::cout << "Search depth:       " << steps << "/" << max_steps << "\n";
		std::cout << "========================================================\n\n";

		WaitForEnter();
	}
	else
	{
		std::cout << "========================================================\n";
		std::cout << "                Error! Array not sorted.                \n";
		std::cout << "========================================================\n";
		std::cout << "> Binary search requires a sorted array:                \n\n";

		std::cout << "  1. Go to:                                             \n";
		std::cout << "     \"Work with sorted array\"                         \n\n";
		std::cout << "  2. Select:                                            \n";
		std::cout << "     \"Sort array\"                                     \n\n";

		std::cout << "========================================================\n";

		WaitForEnter();

		return;
	}

}

int CalculateMaxSteps(int& size)  
{
	int max_steps = 0;
	while ((1 << max_steps) < size) // each bit shift multiplies the previous value by 2
		max_steps++;
	return max_steps;
}

void IndexedSeqSearch(int* array, int size)
{
	if (IsSort(array, size))
	{
		std::cout << "========================================================\n";
		std::cout << "             ~~ Indexed sequential search ~~            \n";
		std::cout << "========================================================\n\n";

		std::cout << "Enter element to search for: ";
		int target;
		std::cin >> target;

		ClearConsole();

		// Step 1 - Select index interval
		
		int step = 1; // default value

		do
		{
			std::cout << "========================================================\n";
			std::cout << "          Enter index table interval (min 1):           \n";
			std::cout << "========================================================\n";
			std::cout << "Array size: " << size << " elements.                     \n\n";

			std::cout << "Interval: ";
			std::cin >> step;

			ClearConsole();

			if (step >= 1)
				break;
			else
			{
				std::cout << "========================================================\n";
				std::cout << "                 Error! Invalid interval                \n";
				std::cout << "========================================================\n";
				std::cout << "  Interval can't be less that 1!                        \n";
				std::cout << "  Please enter a valid value.                           \n";
				std::cout << "========================================================\n";

				WaitForEnter();
				ClearConsole();
			}
		} while (true);

		// 2. Step 2 - Create index table
		int indexSize = (size + step - 1) / step;        
		int* indexValues = new int[indexSize];           
		int* indexPositions = new int[indexSize]; 
		for (int i = 0; i < indexSize; i++)
		{
			indexValues[i] = array[i * step]; 
			indexPositions[i] = i * step;	  
		}

		// Step 3 - Search in index table

		bool isFound = false;
		int foundPos = -1;

		for (int i = 0; i < indexSize; i++)
		{
			// If we immediately find exact match in index table
			if (target == indexValues[i])
			{
				isFound = true;
				foundPos = indexPositions[i];
				break;
			}
			// Check if target falls between index values:
			// 1) for ascending: target < indexValues[i]
			// 2) for discending: target > indexValues[i]
			else if ((IsAscending(array, size) ? (target < indexValues[i]) : (target > indexValues[i])))
			{
				// Determine block start:
				// If not a first element - take it previous position
				// If first - start from 0
				int blockStart = (i > 0) ? indexPositions[i - 1] : 0;

				// End block - current position in index
				int blockEnd = indexPositions[i];

				// Linear search in the defined block
				for (int j = blockStart; j < blockEnd; j++)
				{
					if (target == array[j])
					{
						isFound = true;
						foundPos = j;
						break;
					}
				}
				break;
			}
		}

		// 3. Search in the last block if wasn't found earlier
		if (!isFound)
		{
			// Start from last position in index table
			int lastBlockStart = indexPositions[indexSize - 1];

			// Search until the end of array
			for (int j = lastBlockStart; j < size; j++)
			{
				if (target == array[j])
				{
					isFound = true;
					foundPos = j;
					break;
				}
				else if (!IsAscending(array, size) && target > array[j])
					break; // Stop search for discending array
			}
		}

		ClearConsole();

		std::cout << "========================================================\n";
		std::cout << "                    Search results:                     \n";
		std::cout << "========================================================\n";
		std::cout << "Target value:       " << target << "\n";
		std::cout << "Search status:      " << (isFound ? "Found" : "Not found") << "\n";

		if (isFound)
		{
			std::cout << "Position in array:  " << foundPos << "\n";
			std::cout << "Element number:     #" << foundPos + 1 << "\n";
		}

		std::cout << "========================================================\n\n";

		delete[] indexValues;
		delete[] indexPositions;

		WaitForEnter();
	}
	else
	{
		std::cout << "========================================================\n";
		std::cout << "                Error! Array not sorted.                \n";
		std::cout << "========================================================\n";
		std::cout << "> Indexed sequential search requires a sorted array:    \n\n";

		std::cout << "  1. Go to:                                             \n";
		std::cout << "     \"Work with array\"                                \n\n";
		std::cout << "  2. Select:                                            \n";
		std::cout << "     \"Sort array\"                                     \n\n";

		std::cout << "========================================================\n";


		WaitForEnter();
		return;
	}
}

int main()
{
	MenuProgram();
	return 0;
}