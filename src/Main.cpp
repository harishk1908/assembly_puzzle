// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
int main()
{
	Board b;
	b.printBoard();
	b.placePiece(0, 3, Point(2,3));
	b.printBoard();
	b.placePiece(1, 0, Point(1, 1));
	b.printBoard();

	system("pause");
}
