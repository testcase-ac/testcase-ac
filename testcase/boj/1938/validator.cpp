#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(4, 50, "N");
    inf.readEoln();

    // Prepare to collect positions of B and E
    vector<pair<int,int>> Bpos, Epos;
    // Build regex for a row: exactly N characters from {0,1,B,E}
    string row_regex = "[01BE]{" + to_string(N) + "}";

    // Read each row
    for (int i = 0; i < N; i++) {
        string row = inf.readLine(row_regex, "row");
        for (int j = 0; j < N; j++) {
            char c = row[j];
            if (c == 'B') {
                Bpos.emplace_back(i, j);
            } else if (c == 'E') {
                Epos.emplace_back(i, j);
            }
            // '0' and '1' are allowed by the regex already
        }
    }

    // Must have exactly 3 B's and 3 E's
    ensuref((int)Bpos.size() == 3, "Expected exactly 3 B's, found %d", (int)Bpos.size());
    ensuref((int)Epos.size() == 3, "Expected exactly 3 E's, found %d", (int)Epos.size());

    // B and E positions must be disjoint
    for (auto &b : Bpos) {
        for (auto &e : Epos) {
            ensuref(b != e,
                    "B and E overlap at cell (%d, %d)", b.first+1, b.second+1);
        }
    }

    // Helper to check a triple of positions forms a straight segment of length 3
    auto check_segment = [&](const vector<pair<int,int>>& P, const char label) {
        // Extract rows and cols
        vector<int> R, C;
        for (auto &p : P) {
            R.push_back(p.first);
            C.push_back(p.second);
        }
        bool same_row = (R[0] == R[1] && R[1] == R[2]);
        bool same_col = (C[0] == C[1] && C[1] == C[2]);
        ensuref(same_row || same_col,
                "%c's do not lie on a straight line", label);

        if (same_row) {
            // Check columns are consecutive
            sort(C.begin(), C.end());
            ensuref(C[1] == C[0] + 1 && C[2] == C[0] + 2,
                    "%c's in row %d are not in three consecutive columns", 
                    label, R[0]+1);
        } else {
            // same_col
            sort(R.begin(), R.end());
            ensuref(R[1] == R[0] + 1 && R[2] == R[0] + 2,
                    "%c's in column %d are not in three consecutive rows", 
                    label, C[0]+1);
        }
    };

    // Validate B-segment and E-segment
    check_segment(Bpos, 'B');
    check_segment(Epos, 'E');

    // No extra data
    inf.readEof();
    return 0;
}
