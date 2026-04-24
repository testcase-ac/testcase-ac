#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of rows/columns, 1 <= N <= 20
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read N lines of coin states
    for (int i = 0; i < N; i++) {
        // Each line is a token of H/T, length between 1 and 20
        string rowName = string("row[") + to_string(i) + "]";
        string s = inf.readToken("[HT]{1,20}", rowName.c_str());
        // Enforce exact length N
        ensuref((int)s.size() == N,
                "Length of %s must be exactly %d but got %d", 
                rowName.c_str(), N, (int)s.size());
        // No other characters; regex already ensures only H or T
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
