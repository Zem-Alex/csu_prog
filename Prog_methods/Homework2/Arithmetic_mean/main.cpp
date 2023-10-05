#include <iostream>
#include <random>
#include <cmath>

using namespace std;

int arithmeticMean(int* &Sequence, int &size)
{
	int count = 0, sum = 0, average = 0;
	
	for (; count < size; count++)
	{
		if (sum > 0 && INT_MAX - sum < Sequence[count] || sum < 0 && INT_MIN - sum > Sequence[count])
		{
			return -1;
		}
		sum += Sequence[count];

	}

	//average = round((double)sum / (double)count);

	if (sum % count < count - (sum % count))
		average = sum / count;
	else
		average = (sum / count) + 1;

	cout << "sum = " << sum << endl;
	cout << "count = " << count << endl;
	cout << "average = " << average << endl;

	return 0;
}

int main()
{
	srand(time(NULL));

	int size = 3;

	int* Sequence = new int[size];

	for (size_t i = 0; i < size; i++)
	{
		Sequence[i] = rand() % 10;

	}
	
	arithmeticMean(Sequence, size);

	for (size_t i = 0; i < size; i++)
	{
		cout << Sequence[i] << endl;

	}
	delete[] Sequence;

	return 0;
}