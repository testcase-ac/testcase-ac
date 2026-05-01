#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    double emptyProb = rnd.next();         // probability to place an empty cell
    double whiteBias = rnd.next();         // probability that a piece is white when placed
    bool allEmpty = rnd.next() < 0.1;       // 10% chance of entirely empty board
    bool allFull = !allEmpty && rnd.next() < 0.1; // 10% chance of entirely full board (no empties)

    string whites = "PNBRQK";
    string blacks = "pnbrqk";

    // Generate 8x8 board
    for (int i = 0; i < 8; i++) {
        string row;
        for (int j = 0; j < 8; j++) {
            char c;
            if (allEmpty) {
                c = '.';
            } else if (allFull) {
                // Always place a piece
                if (rnd.next() < whiteBias)
                    c = whites[rnd.next(0, 5)];
                else
                    c = blacks[rnd.next(0, 5)];
            } else {
                // Mixed scenario
                if (rnd.next() < emptyProb) {
                    c = '.';
                } else if (rnd.next() < whiteBias) {
                    c = whites[rnd.next(0, 5)];
                } else {
                    c = blacks[rnd.next(0, 5)];
                }
            }
            row.push_back(c);
        }
        println(row);
    }
    return 0;
}
