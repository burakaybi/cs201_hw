#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <thread>
#include <mutex>

using namespace std;

mutex mut;
int max, min, *intArray;
int indexOfThreads = 0;

void systemClockPrint() {
	time_t tt = chrono::system_clock::to_time_t
	(chrono::system_clock::now());
	struct tm *ptm = new struct tm;
	localtime_s(ptm, &tt);
	cout << put_time(ptm, "%X");
}

int random_range(const int & min, const int & max) {
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void threadWorker(int id, int limit, int& sum) {

	int max, min;
	bool IsFinished = false;

	do {

		this_thread::sleep_for(chrono::seconds(random_range(min, max)));

		mut.lock();

		// stops threads for into sum
		if (indexOfThreads == limit) {
			IsFinished = true;
		}

		if (!IsFinished) {
			
			// do the sum
			sum = sum + intArray[indexOfThreads];
			cout << "Thread " << id << " added number index " << indexOfThreads << " to the total sum at ";
			systemClockPrint();
			cout << endl << "Current sum: " << sum << endl;

			// increase index
			indexOfThreads++;
		}

		// stops threads for into sum
		if (indexOfThreads == limit && IsFinished != true) {
			IsFinished = true;
		}

		mut.unlock();

	} while (!IsFinished);
}

int main() {

	int max, min;
	string fileString;
	cout << "Please enter the file name." << endl;
	cin >> fileString;

	ifstream input(fileString.c_str());

	/* 
	gets inputs
	min max
	int *array
	*/

	cout << "Please enter the wait range of threads." << endl;
	cin >> min;
	cin >> max;

	cout << endl << "Starting reading the array at ";
	systemClockPrint();
	cout << endl;
	
	// initiliaze
	int inputSize = -1;
	int num = -1;
	int rowInt;

	// get all the inputs
	while (input >> rowInt) {
		if (num != -1) {
			//new index with new int
			intArray[num] = rowInt;
		}
		else {
			 //first line is size
			inputSize = rowInt;
			intArray = new int[inputSize];
		}
		num++;
	}

	cout << "Array stored in the memory. Starting the summation at ";
	systemClockPrint();
	cout << endl << endl;

	int sum = 0;

	thread threads[5];

	// thread management
	for (int i = 0; i < 5; ++i) {
		int j = i + 1;
		threads[i] = thread(threadWorker, j, inputSize, ref(sum));
	}

	for (int i = 0; i < 5; i++)
	{
		threads[i].join();
	}

	cout << endl << "Adding finished at ";
	systemClockPrint();
	cout << endl << "Sum: " << sum << endl;

	input.close();
	delete[] intArray;
	
	cin.get();
	cin.ignore();
	
	
	return 0;
}