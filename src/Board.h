#pragma once

#ifndef BOARD
#define BOARD

#include "Piece.h"
#include "Point.h"
#include <algorithm>
#include <iostream>
#include <exception>
#include <iomanip>
#include <unordered_map>

using namespace std;

class Board {
private:
public:
	vector<Piece> pieces;
	unordered_set<int> placedPieces;
	int WIDTH = 7;
	int HEIGHT = 7;
	vector<vector<char>> boardConfig;
	
	Board() {

		initializePieces(Point(0,0));
		boardConfig = vector<vector<char>>(HEIGHT, vector<char>(WIDTH, '.'));

	}



	Board(Point hole) {
		initializePieces(hole);
		boardConfig = vector<vector<char>>(HEIGHT, vector<char>(WIDTH, '.'));
		placePiece(0, 0, hole);
	}

	void initializePieces(Point hole) {
		pieces = vector<Piece>({
			Piece(string("hole"), -1, pointSet({
						  Point(0,0)})
		 ),
	Piece(string("green"), 0, pointSet({
						  Point(1,0), Point(2,0),
			  Point(0,1), Point(1,1), Point(2,1),
						  Point(1,2), Point(2,2), Point(3,2)
			  })),
	Piece(string("red"), 1, pointSet({
			  Point(0,0), Point(1,0),
			  Point(0,1), Point(1,1), Point(2,1),
			  Point(0,2), Point(1,2)
			  })),
	Piece(string("dark orange"), 2, pointSet({
						  Point(1,0),
			  Point(0,1), Point(1,1),
			  Point(0,2), Point(1,2),
						  Point(1,3)
			  })),
	Piece(string("violet"), 3, pointSet({
			  Point(0,0),
			  Point(0,1), Point(1,1),
			  Point(0,2), Point(1,2), Point(2,2)
			  })),
	Piece(string("sky blue"), 4, pointSet({
			  Point(0,0), Point(1,0), Point(2,0), Point(3,0),
									  Point(2,1)
			  })),
	Piece(string("dark green"), 5, pointSet({
			  Point(0,0),
			  Point(0,1),
			  Point(0,2),
			  Point(0,3),
			  Point(0,4)
			  })),
	Piece(string("yellow"), 6, pointSet({
			  Point(0,0), Point(1,0),
						  Point(1,1), Point(2,1),
									  Point(2,2)
			  })),
	Piece(string("purple"), 7, pointSet({
						  Point(1,0),
			  Point(0,1), Point(1,1), Point(2,1)
			  })),
	Piece(string("light orange"), 8, pointSet({
			  Point(0,0),
			  Point(0,1),
			  }))
			});
	}
	void printBoard() {
		
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				cout << setw(2)<<boardConfig[i][j];
			}
			cout << endl;
		}

		cout << endl;
	}

	inline bool canPlacePiece(int pieceIndex, int rotationIndex, Point& position) {
		Point bottomRight = pieces[pieceIndex].getBottomRightCorner(rotationIndex);
		if (bottomRight.x + position.x >= WIDTH || bottomRight.y + position.y >= HEIGHT)
			return false;

		for (Point p : pieces[pieceIndex].pointsUnderRotations[rotationIndex]) {
			if (boardConfig[position.y + p.y][position.x + p.x] != '.')
				return false;
		}

		return true;
	}

	void placePiece(int pieceIndex, int rotationIndex, Point& position) {
		for (Point p : pieces[pieceIndex].pointsUnderRotations[rotationIndex]) {
			boardConfig[position.y + p.y][position.x + p.x] = '0' + (pieceIndex);
		}

		placedPieces.insert(pieceIndex);
	}

	void removePiece(int pieceIndex, int rotationIndex, Point& position) {
		for (Point p : pieces[pieceIndex].pointsUnderRotations[rotationIndex]) {
			boardConfig[position.y + p.y][position.x + p.x] = '.';
		}

		placedPieces.insert(pieceIndex);
	}
};
#endif