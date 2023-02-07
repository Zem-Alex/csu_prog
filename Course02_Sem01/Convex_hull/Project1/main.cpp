#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "SFML\Graphics.hpp"
#include <windows.h>
#include <time.h>
#include "Header.hpp"

//37:51

int main()
{
	srand(time(0));
	const int n = 10;
	//cin >> n;
	vector<point2d> points(n);

	sf::ConvexShape polygon;
	sf::CircleShape circle[n];

	for (auto& pt : points)
	{
		pt.x = rand() % 1500 + 50;
		pt.y = rand() % 700 + 50;
		//cin >> pt.x >> pt.y;
	}
	
	auto ch = get_convex_hull(points);

	cout << ch.size() << endl;
    polygon.setPointCount(ch.size());
	polygon.setFillColor(sf::Color::White);
	polygon.setOutlineColor(sf::Color::Green);
	polygon.setOutlineThickness(3);

	for (int i = 0; i < ch.size(); i++) {
		polygon.setPoint(i, sf::Vector2f(ch[i].x, ch[i].y));
		//cout << ch[i].x << ' ' << ch[i].y << endl;
	}

	for (int i = 0; i < n; i++)
	{
		circle[i].setFillColor(sf::Color::Red);
		circle[i].setRadius(4);
	}
	while (1)
	{
		window.clear(sf::Color::White);

		for (int i = 0; i < n; i++)
		{
			circle[i].setPosition(points[i].x - 3.5, points[i].y - 3.5);
		}
		//Sleep(1000);
		window.draw(polygon);
		for (int i = 0; i < n; i++)
		{
			window.draw(circle[i]);
		}
		window.display();
		
	}
	
	window.close();
	return 0;
}