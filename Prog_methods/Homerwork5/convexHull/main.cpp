#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Point
{
	int x, y;
};

int findMinPoint(vector<Point>& points)
{
	int minPoint = 0;

	for (int i = 1; i < points.size(); ++i)
	{
		if (make_pair(points[i].y, points[i].x) < make_pair(points[minPoint].y, points[minPoint].x))
		{
			minPoint = i;
		}
	}

	return minPoint;
}

int orientation(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool comparePoints(Point a, Point b) 
{
	int orientationValue = orientation({ 0, 0 }, a, b);

	if (orientationValue == 0) 
	{
		return a.x * a.x + a.y * a.y < b.x* b.x + b.y * b.y;
	}

	return orientationValue > 0;
}

stack<Point> buildConvexHull(vector<Point>& points)
{
	int minPoint;

	minPoint = findMinPoint(points);

	swap(points[0], points[minPoint]);

	sort(points.begin() + 1, points.end(), comparePoints);

	stack<Point> S;

	S.push(points[0]);
	S.push(points[1]);

	for (int i = 2; i < points.size(); ++i)
	{
		while (S.size() >= 2)
		{
			Point a = S.top();
			S.pop();

			Point b = S.top();

			if (orientation(b, a, points[i]) > 0)
			{
				S.push(a);
				break;
			}
		}
		S.push(points[i]);
	}

	return S;
}

int main()
{
	vector<Point> points = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3} };

	stack<Point> convexHull = buildConvexHull(points);

	cout << "Convex Hull Points:" << endl;

	while (!convexHull.empty())
	{
		Point p = convexHull.top();
		cout << "(" << p.x << ", " << p.y << ")" << endl;
		convexHull.pop();
	}

	return 0;
}
