#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static string makeTitle(int tc, int index, bool longName) {
    string title = string(1, char('A' + index % 26)) + to_string(tc) + to_string(index);
    if (longName) {
        title += "Song";
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            title += char('A' + rnd.next(0, 25));
        }
    }
    return title;
}

static vector<int> interestingQueries(int n) {
    vector<int> values = {1, n, n + 1, 100000000};
    long long blockStart = 1;
    long long power = n;
    for (int len = 1; len <= 6 && blockStart <= 100000000; ++len) {
        values.push_back(int(blockStart));
        values.push_back(int(min(100000000LL, blockStart + power - 1)));
        blockStart += power;
        if (power <= 100000000LL / max(1, n)) {
            power *= n;
        } else {
            power = 100000001LL;
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(2, 5);
    for (int tc = 1; tc <= testCases; ++tc) {
        int n;
        if (tc == 1) {
            n = rnd.any(vector<int>{1, 2, 3});
        } else if (tc == testCases) {
            n = rnd.any(vector<int>{10, 26});
        } else {
            n = rnd.next(1, 26);
        }

        int q = rnd.next(1, 12);
        println(n, q);

        vector<string> titles;
        for (int i = 0; i < n; ++i) {
            titles.push_back(makeTitle(tc, i, rnd.next(0, 3) == 0));
        }
        println(titles);

        vector<int> pool = interestingQueries(n);
        vector<int> queries;
        for (int i = 0; i < q; ++i) {
            if (rnd.next(0, 2) == 0) {
                queries.push_back(rnd.any(pool));
            } else if (rnd.next(0, 3) == 0) {
                queries.push_back(rnd.next(1, min(200, 100000000)));
            } else {
                queries.push_back(rnd.next(1, 100000000));
            }
        }
        println(queries);
    }

    println(0, 0);
    return 0;
}
