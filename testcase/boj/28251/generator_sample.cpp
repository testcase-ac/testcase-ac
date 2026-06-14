#include "testlib.h"
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int q = rnd.next(1, 30);
    int valueMode = rnd.next(0, 4);
    int queryMode = rnd.next(0, 3);

    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        if (valueMode == 0) {
            s[i] = rnd.next(0, 12);
        } else if (valueMode == 1) {
            s[i] = rnd.any(vector<int>{0, 1, 1999, 2000});
        } else if (valueMode == 2) {
            s[i] = (i % 2 == 0 ? 0 : rnd.next(1, 2000));
        } else if (valueMode == 3) {
            s[i] = rnd.next(1800, 2000);
        } else {
            s[i] = rnd.next(0, 2000);
        }
    }

    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());

    vector<pair<int, int>> queries;
    for (int i = 1; i < n && (int)queries.size() < q; ++i) {
        if (queryMode == 0) {
            queries.emplace_back(label[i - 1], label[i]);
        } else if (queryMode == 1) {
            queries.emplace_back(label[0], label[i]);
        } else {
            int j = rnd.next(0, i - 1);
            queries.emplace_back(label[j], label[i]);
        }
    }

    while ((int)queries.size() < q) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;

        if (queryMode == 3 && rnd.next(0, 1) == 0) {
            int l = rnd.next(0, n - 2);
            int r = rnd.next(l + 1, n - 1);
            a = label[l];
            b = label[r];
        }

        queries.emplace_back(a, b);
    }

    println(n, q);
    println(s);
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
