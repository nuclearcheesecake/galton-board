// Wickus Bester
// Galton Board simulation - X trials
// 19 November 2019 and edited 29 March 2020

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main()
{
    int X;
    int totalObtained[X]; // each row represents the total number of turns made (0 = left, 1 = right) from 0 rights to X rights
    int tempTotal, totalNumOfTests;

    srand(time(0));

    cout << "\t\tGALTON BOARD: A simulation\n";
    cout << "\t\t===========================\n\n";
    cout << "Please enter the number of levels to include in the experiment: "; // recommended is 12
    cin >> X;
    cout << "Please enter a number of balls to include in the experiment: "; // recommended is 500 - 1000
    cin >> totalNumOfTests;

    for (int k = 0; k < X; k++) // initialise all turns to 0
    {
      totalObtained[k] = 0;
    }

    for (int m = 0; m < totalNumOfTests; m++)
    {
        // results of a single trial (ie a single ball)
        tempTotal = 0;

        for (int k = 0; k < X; k++) // X layers of decisions to traverse, either goes left(0) or right(1)
        {
            int turn = rand() % 2;
            tempTotal += turn;
        }

        totalObtained[tempTotal]++; // the total number of rights it made is the index of where it lands
    }

    cout << "\n\n\tResults\n"; // displaying the simulation of the galton board
    cout << "-------------------------\n\n";

    for (int k = 0; k < X; k++)
    {
        for (int r = 0; r < totalObtained[k]; r++)
        {
            cout << "X";
        }
        cout << endl;
    }

    return 0;
}
