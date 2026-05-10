#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Helper to check if a character is valid and to get its cable length
int get_cable_length(char c) {
    if (c == '0') return 0;
    if ('a' <= c && c <= 'z') return c - 'a' + 1;
    if ('A' <= c && c <= 'Z') return c - 'A' + 27;
    return -1; // invalid
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // 2. Read N lines of length N, check characters and build adjacency
    vector<string> mat(N);
    for (int i = 0; i < N; ++i) {
        mat[i] = inf.readLine("[a-zA-Z0]{"+to_string(N)+","+to_string(N)+"}", "cable_row");
        ensuref((int)mat[i].size() == N, "Row %d: Expected length %d, got %d", i+1, N, (int)mat[i].size());
        for (int j = 0; j < N; ++j) {
            char c = mat[i][j];
            int len = get_cable_length(c);
            ensuref(len != -1, "Invalid character '%c' at row %d, col %d", c, i+1, j+1);
        }
    }

    // 3. No further global properties to check (symmetry is NOT required by the problem statement)
    //    The sample inputs are not symmetric, so do NOT check for symmetry.

    inf.readEof();
}
