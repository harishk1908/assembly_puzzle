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
	unordered_map<int, Point> piecePositions;
	unordered_map<int, int> pieceRotations;
	vector<Piece> pieces;
	unordered_set<int> placedPieces;
	int WIDTH = 7;
	int HEIGHT = 7;
	
	Board() {
		pieces = vector<Piece>({
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
					  })),
			});
	}

	Board(vector<Piece> _pieces) {
		pieces = _pieces;
	}

	void printBoard() {
		
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				cout << setw(2)<<getPieceIndexAtPoint(j, i);
			}
			cout << endl;
		}

		cout << endl;
	}

	string getPieceIndexAtPoint(int i, int j) {
		Piece p(string(), -1, pointSet({ Point(0,0) }));
		string pieceIndex = ".";
		for (auto kv : piecePositions) {
			Piece candidatePiece = pieces[kv.first];
			if (candidatePiece.isOverlap(candidatePiece, pieceRotations[candidatePiece.index],
				piecePositions[candidatePiece.index], p, 0, Point(i, j)))
				return to_string(candidatePiece.index);

		}
		return pieceIndex;
	}

	bool canPlacePiece(int pieceIndex, int rotationIndex, Point position) {
		for (auto kv : piecePositions) {
			if (Piece::isOverlap(pieces[pieceIndex], rotationIndex, position, pieces[kv.first],
				pieceRotations[kv.first], piecePositions[kv.first]))
				return false;
		}
		Point bottomRight = pieces[pieceIndex].getBottomRightCorner(rotationIndex);
		if (bottomRight.x + position.x >= WIDTH || bottomRight.y + position.y >= HEIGHT)
			return false;
		return true;
	}

	void placePiece(int pieceIndex, int rotationIndex, Point position) {
		if (placedPieces.count(pieceIndex) || !canPlacePiece(pieceIndex, rotationIndex, position))
			throw exception("Cannot place piece.");
		pieceRotations[pieceIndex] = rotationIndex;
		piecePositions[pieceIndex] = position;
		placedPieces.insert(pieceIndex);
	}
};
#endif