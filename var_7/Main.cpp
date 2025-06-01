#include "PriorityQueue.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
using namespace std;

PriorityQueue<string> queue;


string generateString(int length)
{
	string s = "";
	for (int i = 0; i < length; i++)
	{
		s += char(rand() % 100);
	}
	
	return s;
}

void enqueue(string s, int prio)
{
	queue.enqueue(s, prio);
}
void dequeue(string s, int prio)
{
	queue.dequeue();
}
void peek(string s, int prio)
{
	queue.peek();
}
void increasePriority(string s, int prio)
{
	queue.increasePriority(s, prio);
}

void checkFunctionTimeAndPrint(void (*func)(string, int), string funcName)
{

	const int Nstart = 10;
	const int Nend = 100;
	const int dN = 10;
	const int q = 7;
	const int timeN = (Nend - Nstart) / dN + 1;
	const int qNew = q * 80 / 100;

	double timeArray[q];
	double averageTimeArray[timeN][2];
	srand(time(0));

	for (int n = Nstart; n <= Nend; n += dN) {
		for (int count = 0; count < q; count++) {
			string s = generateString(n);
			int prio = rand() % n;

			auto start = chrono::high_resolution_clock::now();
			func(s, prio);
			auto end = chrono::high_resolution_clock::now();
			auto time = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			timeArray[count] = time.count();
		}
		sort(timeArray, timeArray + q);
		double sum = 0;
		for (int i = 0; i < qNew; i++) {
			sum += timeArray[i];
		}
		averageTimeArray[(n - Nstart) / dN][0] = n;
		averageTimeArray[(n - Nstart) / dN][1] = (int)sum / qNew;
	}
	cout << endl << "PriorityQueue: " << funcName << endl << endl;
	cout << "N\t" << "Time(nanoseconds)" << "\t" << endl;
	for (int i = 0; i < timeN; i++) {
		for (int j = 0; j < 2; j++) {
			cout << averageTimeArray[i][j] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	checkFunctionTimeAndPrint(enqueue, "enqueue element");
	checkFunctionTimeAndPrint(dequeue, "dequeue element");
	checkFunctionTimeAndPrint(peek, "peek element");
	checkFunctionTimeAndPrint(increasePriority, "increase priority of element");

	system("pause");
	return 0;
}