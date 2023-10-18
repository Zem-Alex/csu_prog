#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#include <random>



using namespace std;

struct Point
{
	double x;
	double y;

	double norm() const
	{
		return pow(x, 2) + pow(y, 2);
	}

	Point operator+(const Point& rhs) const
	{
		return { x + rhs.x, y + rhs.y };
	}
	Point operator-(const Point& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}
	bool operator<(const Point& rhs) const
	{
		double result = (x * rhs.y - y * rhs.x);
		return result > 0 || result == 0 && norm() < rhs.norm();
	}
};

vector<Point> convexHull(vector<Point> p)
{
	if (p.size() <= 3)
		return p;

	std::iter_swap(p.begin(), std::min_element(p.begin(), p.end(),
		[](const Point& lhs, const Point& rhs)
		{
			return lhs.y < rhs.y;
		}
	));

	std::sort(p.begin() + 1, p.end(), [&p](auto a, auto b)
		{
			return a - p[0] < b - p[0];
		}
	);

	vector<Point> res{ p[0], p[1] };

	for (size_t i = 2; i < p.size(); i++)
	{
		size_t k = res.size() - 1;
		while (p[i] - res[k] < res[k] - res[k - 1])
		{
			res.pop_back();
			k--;
		}
		res.push_back(p[i]);
	}
	return res;
}

int main()
{
	vector<Point> points{
		{4.0, -3.0},
		{3.0, 4.0},
		{2.0, 2.0},
		{2.0, -5.0},
		{1.0, -1.0},
		{0.0, 0.0},
		{0.0, 0.0},
		{0.0, -5.0},
		{-1.0, -1.0},
		{-1.0, 2.0},
		{-3.0, -3.0},
		{-3.0, 3.0},
		{-4.0, 1.0},
		{5.0, -1.0},
	};

	vector<Point> result = convexHull(points);

	for (size_t i = 0; i < result.size(); i++)
	{
		cout << i << ") (" << result[i].x << ", " << result[i].x << ")" << endl;
	}

}