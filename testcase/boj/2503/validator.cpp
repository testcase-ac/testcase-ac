#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Store inputs
    vector<array<int,3>> queries(N);
    for (int i = 0; i < N; i++) {
        // Read guess
        int guess = inf.readInt(100, 999, "guess_" + to_string(i));
        inf.readSpace();
        int S = inf.readInt(0, 3, "strikes_" + to_string(i));
        inf.readSpace();
        int B = inf.readInt(0, 3, "balls_" + to_string(i));
        inf.readEoln();

        // Validate guess digits: must be 1..9 and all distinct
        int d0 = guess / 100;
        int d1 = (guess / 10) % 10;
        int d2 = guess % 10;
        ensuref(d0 >= 1 && d0 <= 9, "guess_%d has digit %d out of range [1,9]", i, d0);
        ensuref(d1 >= 1 && d1 <= 9, "guess_%d has digit %d out of range [1,9]", i, d1);
        ensuref(d2 >= 1 && d2 <= 9, "guess_%d has digit %d out of range [1,9]", i, d2);
        ensuref(d0 != d1 && d0 != d2 && d1 != d2,
                "guess_%d has repeated digits: %d, %d, %d", i, d0, d1, d2);

        // Validate logical constraints on output
        ensuref(S + B <= 3, "At query %d, strikes+balls = %d which exceeds 3", i, S + B);
        // Since the game is ongoing, there must be no 3 strikes yet.
        ensuref(S < 3, "At query %d, strikes = 3 indicates game would have ended", i);

        queries[i] = {guess, S, B};
    }

    // Global check: there must be at least one candidate secret consistent with all queries
    int possible = 0;
    // Try all 3-digit numbers with distinct digits 1..9
    for (int a = 1; a <= 9; a++) {
        for (int b = 1; b <= 9; b++) if (b != a) {
            for (int c = 1; c <= 9; c++) if (c != a && c != b) {
                int cand = 100*a + 10*b + c;
                bool ok = true;
                for (int i = 0; i < N; i++) {
                    int guess = queries[i][0];
                    int wantS = queries[i][1];
                    int wantB = queries[i][2];
                    // extract guess digits
                    int g0 = guess / 100;
                    int g1 = (guess / 10) % 10;
                    int g2 = guess % 10;
                    // compute strike and ball
                    int s = 0, bcnt = 0;
                    int cd[3] = {a, b, c};
                    int gd[3] = {g0, g1, g2};
                    for (int x = 0; x < 3; x++) {
                        for (int y = 0; y < 3; y++) {
                            if (cd[x] == gd[y]) {
                                if (x == y) s++;
                                else bcnt++;
                            }
                        }
                    }
                    if (s != wantS || bcnt != wantB) {
                        ok = false;
                        break;
                    }
                }
                if (ok) possible++;
            }
        }
    }
    ensuref(possible >= 1, "No possible secret number matches all queries");

    inf.readEof();
    return 0;
}
