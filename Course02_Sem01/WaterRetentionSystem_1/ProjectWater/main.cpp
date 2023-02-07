#include<iostream>
#include <vector>

using namespace std;
int trap(const vector<int>& heights);

int main()
{
	vector <int> heights = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };

	int countWater = 0;
	//heights.at(1) = 5;  // 

	//cout << heights.at(1); 

	

	countWater = trap(heights);
	cout << countWater;

	return 0;
}

int trap(const vector<int>& heights)
{
	/*for (int i = 0; i < heights.size(); i++) {
		cout << heights[i] << " ";
	}*/

	int maxLeft = heights[0], maxRight = heights[heights.size() - 1], leftIndex = 1, rightIndex = heights.size() - 2, count = 0;
	//cout << maxLeft << maxRight;

	while (leftIndex <= rightIndex)
	{
		if (maxLeft <= maxRight)
		{
			if (maxLeft - heights[leftIndex] > 0)
				count += maxLeft - heights[leftIndex];
			maxLeft = maxLeft > heights[leftIndex] ? maxLeft : heights[leftIndex];
			leftIndex++;
		}
		else
		{
			if (maxRight - heights[rightIndex] > 0)
				count += maxRight - heights[rightIndex];
			maxRight = maxRight > heights[rightIndex] ? maxRight : heights[rightIndex];
			rightIndex--;
		}
	}

	return count;
}