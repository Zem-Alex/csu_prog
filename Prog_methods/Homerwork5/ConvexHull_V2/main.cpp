#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

# define M_PI  3.14159265358979323846

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

// Функция для генерации случайных точек внутри круга радиуса 1
vector<Point> generatePointsInCircle(int numPoints) {
    vector<Point> points;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(-1.0, 1.0);

    for (int i = 0; i < numPoints; i++) {
        double x = dis(gen);
        double y = dis(gen);
        // Проверяем, находится ли точка внутри круга радиуса 1
        if (x * x + y * y <= 1.0) {
            points.push_back({ x, y });
        }
    }

    return points;
}

// Функция для генерации случайных точек внутри квадрата со стороной sqrt(pi)
vector<Point> generatePointsInSquare(int numPoints) {
    vector<Point> points;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(-sqrt(M_PI), sqrt(M_PI));

    for (int i = 0; i < numPoints; i++) {
        double x = dis(gen);
        double y = dis(gen);
        points.push_back({ x, y });
    }

    return points;
}

void runExperiments(int numPoints, int numExperiments)
{
    double totalAreaCircle = 0.0;
    double totalAreaSquare = 0.0;
    int totalEdgesCircle = 0;
    int totalEdgesSquare = 0;

    for (int experiment = 0; experiment < numExperiments; experiment++) {
        // Генерируем случайные точки внутри круга и квадрата
        vector<Point> pointsCircle = generatePointsInCircle(numPoints);
        vector<Point> pointsSquare = generatePointsInSquare(numPoints);

        // Вычисляем выпуклые оболочки для каждого набора точек
        vector<Point> resultCircle = convexHull(pointsCircle);
        vector<Point> resultSquare = convexHull(pointsSquare);

        int numEdgesCircle = resultCircle.size();
        int numEdgesSquare = resultSquare.size();

        double areaCircle = 0.0;
        double areaSquare = 0.0;

        // Вычисляем площадь выпуклых оболочек
        for (int i = 0; i < numEdgesCircle; i++) {
            int j = (i + 1) % numEdgesCircle;
            areaCircle += resultCircle[i].x * resultCircle[j].y - resultCircle[j].x * resultCircle[i].y;
        }
        areaCircle = 0.5 * abs(areaCircle);

        for (int i = 0; i < numEdgesSquare; i++) {
            int j = (i + 1) % numEdgesSquare;
            areaSquare += resultSquare[i].x * resultSquare[j].y - resultSquare[j].x * resultSquare[i].y;
        }
        areaSquare = 0.5 * abs(areaSquare);

        totalEdgesCircle += numEdgesCircle;
        totalEdgesSquare += numEdgesSquare;
        totalAreaCircle += areaCircle;
        totalAreaSquare += areaSquare;
    }

    double avgEdgesCircle = static_cast<double>(totalEdgesCircle) / numExperiments;
    double avgAreaCircle = totalAreaCircle / numExperiments;
    double avgEdgesSquare = static_cast<double>(totalEdgesSquare) / numExperiments;
    double avgAreaSquare = totalAreaSquare / numExperiments;

    // Выводим результаты экспериментов

    cout << "Points: " << numPoints << endl;
    cout << "Average Edges (Circle): " << avgEdgesCircle << ", Average Area (Circle): " << avgAreaCircle << endl;
    cout << "Average Edges (Square): " << avgEdgesSquare << ", Average Area (Square): " << avgAreaSquare << endl << endl;
}

int main()
{
    vector<int> numPointsToTest = { 10, 50, 100, 500, 1000 , 2000, 4000, 5000, 10000, 20000, 30000, 40000, 50000 };
    int numExperiments = 100;

    for (int numPoints : numPointsToTest) 
    {
        runExperiments(numPoints, numExperiments);
    }

    return 0;
}