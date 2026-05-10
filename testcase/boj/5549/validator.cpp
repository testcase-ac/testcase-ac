#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: M N (map size: M rows, N columns)
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Second line: K (number of queries)
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Next M lines: map rows, each of length N, characters in {J, O, I}
    vector<string> grid(M);
    for (int i = 0; i < M; ++i) {
        string row = inf.readToken("[JOI]{1,1000}", "row");
        inf.readEoln();
        ensuref((int)row.size() == N,
                "Row %d length is %d, expected %d", i + 1, (int)row.size(), N);
        grid[i] = row;
    }

    // Next K lines: queries a b c d
    // Coordinates are 1-based; rectangle from (a,b) top-left to (c,d) bottom-right
    for (int i = 0; i < K; ++i) {
        int a = inf.readInt(1, M, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readSpace();
        int c = inf.readInt(1, M, "c");
        inf.readSpace();
        int d = inf.readInt(1, N, "d");
        inf.readEoln();

        ensuref(a <= c,
                "Query %d has invalid vertical range: a=%d > c=%d", i + 1, a, c);
        ensuref(b <= d,
                "Query %d has invalid horizontal range: b=%d > d=%d", i + 1, b, d);
    }

    inf.readEof();
}
