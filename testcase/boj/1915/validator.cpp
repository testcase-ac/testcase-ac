#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions n and m
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Read the grid: n lines, each exactly m characters '0' or '1'
    string regex = "[01]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; i++) {
        inf.readLine(regex, "row");
    }

    // No extra content
    inf.readEof();
    return 0;
}
