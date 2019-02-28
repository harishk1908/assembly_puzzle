#pragma once
#include <boost/functional/hash.hpp>

#ifndef POINT
#define POINT

class Point {
public:
	int x = 0;
	int y = 0;

	Point() {
		x = 0;
		y = 0;
	}

	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}

	bool operator==(const Point& p) const {
		return x == p.x && y == p.y;
	}

	bool operator<(const Point& p) const {
		return x < p.x || y < p.y;
	}

};

struct PointComparator {
	bool operator() (const Point& p1, const Point& p2) const {
		if (p1.x < p2.x) return true;
		if (p1.x > p2.x) return false;
		if (p1.y < p2.y) return true;
		return false;
	}
};

struct PointHasher {
	std::size_t operator()(const Point& p) const {

		using boost::hash_value;
		using boost::hash_combine;

		std::size_t seed = 0;
		boost::hash_combine(seed, hash_value(p.x));
		boost::hash_combine(seed, hash_value(p.y));

		return seed;
	}
};
#endif

