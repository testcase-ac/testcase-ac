#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    // 1 ≤ m < n
    int m = inf.readInt(1, n - 1, "m");
    inf.readEoln();

    // Read the RPS machine's sequence of length n
    string s = inf.readToken("[RPS]+", "rps_sequence");
    ensuref((int)s.length() == n,
            "Length of RPS machine string must be %d but found %d",
            n, (int)s.length());
    inf.readEoln();

    // Read your machine's sequence of length m
    string t = inf.readToken("[RPS]+", "your_sequence");
    ensuref((int)t.length() == m,
            "Length of your machine string must be %d but found %d",
            m, (int)t.length());
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
