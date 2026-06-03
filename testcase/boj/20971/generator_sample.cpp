#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int q = rnd.next(1, 40);

    string colors;
    colors.reserve(n);

    if (mode == 0) {
        int alphabet = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            colors.push_back(char('A' + rnd.next(0, alphabet - 1)));
        }
    } else if (mode == 1) {
        int alphabet = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            colors.push_back(char('A' + (i % alphabet)));
        }
    } else if (mode == 2) {
        int alphabet = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            colors.push_back(char('A' + ((n - 1 - i) % alphabet)));
        }
    } else if (mode == 3) {
        char lo = char('A' + rnd.next(0, 8));
        char hi = char(lo + rnd.next(1, min(17, 'Z' - lo)));
        for (int i = 0; i < n; ++i) {
            colors.push_back((i % 2 == 0) ? lo : hi);
        }
    } else if (mode == 4) {
        int alphabet = rnd.next(2, 6);
        while ((int)colors.size() < n) {
            char color = char('A' + rnd.next(0, alphabet - 1));
            int run = rnd.next(1, 5);
            while (run-- > 0 && (int)colors.size() < n) {
                colors.push_back(color);
            }
        }
    } else {
        int peak = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            int dist = min(i, n - 1 - i);
            colors.push_back(char('A' + max(0, peak - dist)));
        }
    }

    vector<pair<int, int>> queries;
    queries.emplace_back(1, n);

    while ((int)queries.size() < q) {
        int queryMode = rnd.next(0, 4);
        int a, b;
        if (queryMode == 0) {
            a = b = rnd.next(1, n);
        } else if (queryMode == 1) {
            a = 1;
            b = rnd.next(1, n);
        } else if (queryMode == 2) {
            a = rnd.next(1, n);
            b = n;
        } else if (queryMode == 3) {
            int width = rnd.next(1, min(n, 5));
            a = rnd.next(1, n - width + 1);
            b = a + width - 1;
        } else {
            a = rnd.next(1, n);
            b = rnd.next(a, n);
        }
        queries.emplace_back(a, b);
    }
    queries.resize(q);

    shuffle(queries.begin(), queries.end());

    println(n, q);
    println(colors);
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
