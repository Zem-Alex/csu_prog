#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

double MaxValueOfExpression(vector<double>& numbers)
{
	if (numbers.empty())
		return 0;
	if (numbers.size() == 1)
		return numbers[0];

	double tmpMin = numbers[0], tmpMax = numbers[0];
	vector<double> findMax = { 0, 0, 0, 0}, findMin = { 0, 0, 0, 0 };

	for (auto i = 1; i < numbers.size(); i++)
	{
			findMax[0] = tmpMax + numbers[i];
			findMax[1] = tmpMax - numbers[i];
			findMax[2] = tmpMax * numbers[i];

			findMin[0] = tmpMin + numbers[i];
			findMin[1] = tmpMin - numbers[i];
			findMin[2] = tmpMin * numbers[i];

		if (numbers[i])
		{
			findMax[3] = tmpMax / numbers[i];
			findMin[3] = tmpMin / numbers[i];
		}

		tmpMax = max(*max_element(findMax.begin(), findMax.end()), *max_element(findMin.begin(), findMin.end()));
		tmpMin = min(*min_element(findMax.begin(), findMax.end()), *min_element(findMin.begin(), findMin.end()));
	}

	return tmpMax;
}


int main()
{
	vector<double> numbers = { 1.0, 2.0, -4, -1.0 };

	cout << "Max value of the expression: " << MaxValueOfExpression(numbers) << endl;

	return 0;
}