#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Representations for digits 0-9 and plus sign at index 10
    vector<vector<string>> rep = {
        {"xxxxx","x...x","x...x","x...x","x...x","x...x","xxxxx"}, // 0
        {"....x","....x","....x","....x","....x","....x","....x"}, // 1
        {"xxxxx","....x","....x","xxxxx","x....","x....","xxxxx"}, // 2
        {"xxxxx","....x","....x","xxxxx","....x","....x","xxxxx"}, // 3
        {"x...x","x...x","x...x","xxxxx","....x","....x","....x"}, // 4
        {"xxxxx","x....","x....","xxxxx","....x","....x","xxxxx"}, // 5
        {"xxxxx","x....","x....","xxxxx","x...x","x...x","xxxxx"}, // 6
        {"xxxxx","....x","....x","....x","....x","....x","....x"}, // 7
        {"xxxxx","x...x","x...x","xxxxx","x...x","x...x","xxxxx"}, // 8
        {"xxxxx","x...x","x...x","xxxxx","....x","....x","xxxxx"}, // 9
        {".....","..x..","..x..","xxxxx","..x..","..x..","....."}  // +
    };

    // Hyper-parameters for lengths of a and b
    int la = rnd.next(1, 4);
    int lb = rnd.next(1, 4);

    // Generate positive integer a without leading zeros
    string sa;
    sa += char('0' + rnd.next(1, 9));
    for (int i = 1; i < la; i++) sa += char('0' + rnd.next(0, 9));
    // Generate positive integer b without leading zeros
    string sb;
    sb += char('0' + rnd.next(1, 9));
    for (int i = 1; i < lb; i++) sb += char('0' + rnd.next(0, 9));

    // Prepare sequence: digits of a, plus, digits of b
    vector<int> seq;
    for (char c : sa) seq.push_back(c - '0');
    seq.push_back(10);
    for (char c : sb) seq.push_back(c - '0');

    // Build 7 rows of ASCII art for the input expression
    vector<string> rows(7, "");
    for (int i = 0; i < (int)seq.size(); i++) {
        int idx = seq[i];
        for (int r = 0; r < 7; r++) {
            rows[r] += rep[idx][r];
        }
        if (i + 1 < (int)seq.size()) {
            for (int r = 0; r < 7; r++) rows[r] += '.';
        }
    }

    // Output the 7 lines
    for (int r = 0; r < 7; r++) {
        println(rows[r]);
    }

    return 0;
}
