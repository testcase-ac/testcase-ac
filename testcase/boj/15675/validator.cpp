#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read the grid and count jewels
    long long jewelCount = 0;
    // Build a regex to match exactly M characters of '.', '*', or '#'
    string rowPattern = "[.*#]{" + to_string(M) + "," + to_string(M) + "}";
    for (int i = 0; i < N; i++) {
        string row = inf.readLine(rowPattern, "row");
        for (char c : row) {
            if (c == '*') {
                jewelCount++;
            }
        }
    }

    // There must be at least one jewel
    ensuref(jewelCount >= 1, "There must be at least one '*' in the grid, found %lld", jewelCount);

    inf.readEof();
    return 0;
}
