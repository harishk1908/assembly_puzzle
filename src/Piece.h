#pragma once
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include "Point.h"
using namespace std;

#ifndef PIECE
#define PIECE

typedef unordered_set<Point, PointHasher> pointSet;
class Piece {
private:

public:
	string color = "red";
	int index = 0;
	vector<pointSet> pointsUnderRotations;

	Piece() {

	}
	Piece(string _c, int _i, pointSet points) {
		color = _c;
		index = _i;
		pointsUnderRotations.push_back(points);
		for (int i = 1; i <= 3; i++)
			pointsUnderRotations.push_back(getCCWRotatedPoints(pointsUnderRotations[i-1]));
	}

	pointSet getCCWRotatedPoints(pointSet points) {
		pointSet res;
		int maxX = -1;
		for (Point p : points)
			if (p.x > maxX)
				maxX = p.x;
		for (Point p : points) {
			int tempX = p.x;
			p.x = p.y;
			p.y = maxX - tempX;
			//cout << p.x << " " << p.y << endl;
			res.insert(p);
		}
		return res;

	}

	static bool isOverlap(Piece a, int rotationIndexA, Point positionA, Piece b, int rotationIndexB, Point positionB) {
		for (Point p : a.pointsUnderRotations[rotationIndexA]) {
			p.x += positionA.x - positionB.x;
			p.y += positionA.y - positionB.y;
			if (b.pointsUnderRotations[rotationIndexB].count(p))
				return true;
		}
		return false;
	}

	Point getBottomRightCorner(int rotationIndex) {
		Point res(0,0);
		for (Point p : pointsUnderRotations[rotationIndex]) {
			if (p.x > res.x)
				res.x = p.x;
			if (p.y > res.y)
				res.y = p.y;
		}
		return res;
	}
};
#endif
