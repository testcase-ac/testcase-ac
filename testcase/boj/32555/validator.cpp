#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N (number of guesses/rows) and M (guess length/columns)
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read the color grid: N lines, each with exactly M characters 'G' or 'Y'
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        // readLine with a permissive regex, then enforce exact length and chars
        string row = inf.readLine("[GY]{1,100}", "row");
        ensuref((int)row.length() == M,
                "Row %d has length %d but M = %d", i, (int)row.length(), M);
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c == 'G' || c == 'Y',
                    "Invalid character at row %d, col %d: '%c'", i, j, c);
        }
        grid[i] = row;
    }

    // Compute number of 'Y's in each row and ensure uniformity
    vector<int> yCount(N, 0);
    for (int i = 0; i < N; i++) {
        int cnt = 0;
        for (char c : grid[i]) {
            if (c == 'Y') cnt++;
        }
        yCount[i] = cnt;
    }
    for (int i = 0; i < N; i++) {
        ensuref(yCount[i] == yCount[0],
                "Row %d has %d Ys but row 0 has %d Ys",
                i, yCount[i], yCount[0]);
    }

    // Read Sigma
    long long Sigma = inf.readLong(1LL, 1000000LL, "Sigma");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
