#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 30);
    int q = rnd.next(3, 40);

    string s;
    if (mode == 0) {
        char c = rnd.any(string("ABCZ"));
        s.assign(n, c);
    } else if (mode == 1) {
        string alphabet = rnd.next(0, 1) ? "AB" : "AZ";
        for (int i = 0; i < n; ++i) {
            s += alphabet[i % (int)alphabet.size()];
        }
    } else if (mode == 2) {
        string alphabet = "ABCXYZ";
        for (int i = 0; i < n;) {
            char c = rnd.any(alphabet);
            int len = min(n - i, rnd.next(1, 5));
            s.append(len, c);
            i += len;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            s += rnd.any(string("YZABC"));
        }
    } else {
        string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int limit = rnd.next(3, 8);
        for (int i = 0; i < n; ++i) {
            s += alphabet[rnd.next(0, limit - 1)];
        }
    }

    vector<vector<int>> queries;
    queries.push_back({1, 1, n});
    queries.push_back({2, rnd.next(1, n), rnd.next(1, n)});
    if (queries.back()[1] > queries.back()[2]) {
        swap(queries.back()[1], queries.back()[2]);
    }

    while ((int)queries.size() < q) {
        int type;
        if ((int)queries.size() + 1 == q && rnd.next(0, 3) == 0) {
            type = 1;
        } else {
            type = rnd.next(1, 2);
        }

        int l, r;
        int shape = rnd.next(0, 4);
        if (shape == 0) {
            l = 1;
            r = n;
        } else if (shape == 1) {
            l = r = rnd.next(1, n);
        } else if (shape == 2) {
            l = rnd.next(1, n);
            r = min(n, l + rnd.next(0, min(4, n - l)));
        } else if (shape == 3) {
            r = rnd.next(1, n);
            l = max(1, r - rnd.next(0, min(4, r - 1)));
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }
        queries.push_back({type, l, r});
    }

    shuffle(queries.begin(), queries.end());

    bool hasTypeOne = false;
    for (const auto& query : queries) {
        hasTypeOne = hasTypeOne || query[0] == 1;
    }
    if (!hasTypeOne) {
        queries[rnd.next(0, q - 1)][0] = 1;
    }

    println(n, q);
    println(s);
    for (const auto& query : queries) {
        println(query);
    }

    return 0;
}
