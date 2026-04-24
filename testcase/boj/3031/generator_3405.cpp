#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of teams
    int N = rnd.next(1, 10);

    // store rows as vectors of strings
    vector<vector<string>> table;
    table.reserve(N);

    for (int i = 0; i < N; i++) {
        // generate a valid complete record
        int g = rnd.next(0, 100);
        int w = rnd.next(0, g);
        int d = rnd.next(0, g - w);
        int l = g - w - d;
        int p = 3 * w + d;

        // decide how many blanks: 0, 1, or 2 (but ensure at least one blank in first row)
        int k = rnd.next(0, 2);
        if (i == 0 && k == 0) k = 1;
        // pick k distinct positions to blank
        vector<int> idx = {0,1,2,3,4};
        shuffle(idx.begin(), idx.end());
        vector<bool> blank(5, false);
        for (int t = 0; t < k; t++) {
            blank[idx[t]] = true;
        }

        // build row
        vector<string> row(5);
        row[0] = blank[0] ? "?" : to_string(g);
        row[1] = blank[1] ? "?" : to_string(w);
        row[2] = blank[2] ? "?" : to_string(l);
        row[3] = blank[3] ? "?" : to_string(d);
        row[4] = blank[4] ? "?" : to_string(p);
        table.push_back(row);
    }

    // output
    println(N);
    for (auto &row : table) {
        println(row);
    }

    return 0;
}
