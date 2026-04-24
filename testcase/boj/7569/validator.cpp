#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions M, N, H
    int M = inf.readInt(2, 100, "M");
    inf.readSpace();
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int H = inf.readInt(1, 100, "H");
    inf.readEoln();

    bool hasTomato = false;
    // Read H layers, each with N rows of M integers
    for (int z = 0; z < H; z++) {
        for (int y = 0; y < N; y++) {
            vector<int> row = inf.readInts(M, -1, 1, "tomato");
            inf.readEoln();
            for (int x = 0; x < M; x++) {
                if (row[x] != -1) {
                    hasTomato = true;
                }
            }
        }
    }

    // Global constraint: at least one tomato (0 or 1) must exist
    ensuref(hasTomato,
            "Input must contain at least one tomato (value 0 or 1), got only -1's");

    inf.readEof();
    return 0;
}
