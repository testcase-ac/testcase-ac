#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int m;
    int l;

    if (mode == 0) {
        m = 1;
        l = rnd.next(2, 12);
    } else if (mode == 1) {
        m = rnd.next(2, 8);
        l = rnd.next(m + 2, 80);
    } else if (mode == 2) {
        m = rnd.next(5, 18);
        l = rnd.next(max(20, m + 2), 250);
    } else {
        m = rnd.next(8, 35);
        l = rnd.next(max(100, m + 2), 4000);
    }

    int n = rnd.next(1, m);

    set<int> cutSet;
    if (mode == 0) {
        cutSet.insert(rnd.next(1, l - 1));
    } else if (mode == 1) {
        while ((int)cutSet.size() < m) {
            int center = rnd.next(1, l - 1);
            int delta = rnd.next(-3, 3);
            int value = min(l - 1, max(1, center + delta));
            cutSet.insert(value);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= m; ++i) {
            int base = (long long)i * l / (m + 1);
            int jitter = rnd.next(-2, 2);
            cutSet.insert(min(l - 1, max(1, base + jitter)));
        }
        while ((int)cutSet.size() < m) cutSet.insert(rnd.next(1, l - 1));
    } else {
        while ((int)cutSet.size() < m) {
            if (rnd.next(3) == 0) {
                cutSet.insert(rnd.next(1, min(l - 1, 30)));
            } else if (rnd.next(3) == 0) {
                cutSet.insert(rnd.next(max(1, l - 30), l - 1));
            } else {
                cutSet.insert(rnd.next(1, l - 1));
            }
        }
    }

    vector<int> cuts(cutSet.begin(), cutSet.end());

    set<int> querySet;
    querySet.insert(1);
    if (n > 1) querySet.insert(m);
    while ((int)querySet.size() < n) querySet.insert(rnd.next(1, m));
    vector<int> queries(querySet.begin(), querySet.end());

    println(n, m, l);
    for (int cut : cuts) println(cut);
    for (int query : queries) println(query);

    return 0;
}
