#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string nameFor(int caseIndex, int node) {
    string s;
    s.push_back(char('A' + caseIndex));
    s += "Emp";
    int x = node;
    do {
        s.push_back(char('A' + (x % 26)));
        x /= 26;
    } while (x > 0);
    return s;
}

vector<int> buildParents(int n, int mode) {
    vector<int> parent(n, -1);

    if (mode == 0) {
        for (int i = 1; i < n; ++i) parent[i] = i - 1;
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) parent[i] = 0;
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) parent[i] = (i - 1) / 2;
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            if (i % 3 == 1) {
                parent[i] = max(0, i - 2);
            } else {
                parent[i] = i - 1;
            }
        }
    } else if (mode == 4) {
        int backbone = rnd.next(max(1, n / 3), max(1, (2 * n) / 3));
        for (int i = 1; i < backbone; ++i) parent[i] = i - 1;
        for (int i = backbone; i < n; ++i) parent[i] = rnd.next(0, backbone - 1);
    } else {
        int bias = rnd.next(-3, 3);
        for (int i = 1; i < n; ++i) {
            parent[i] = rnd.wnext(i, bias);
        }
    }

    return parent;
}

void printCase(int caseIndex, int n, int mode) {
    vector<int> parent = buildParents(n, mode);
    vector<int> order;
    for (int i = 1; i < n; ++i) order.push_back(i);
    shuffle(order.begin(), order.end());

    println(n);
    println(nameFor(caseIndex, 0));
    for (int employee : order) {
        println(nameFor(caseIndex, employee), nameFor(caseIndex, parent[employee]));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 4);
    int remaining = 200;
    for (int tc = 0; tc < caseCount; ++tc) {
        int left = caseCount - tc - 1;
        int maxN = remaining - left;
        int n;
        if (tc == 0 && rnd.next(0, 9) == 0) {
            n = 1;
        } else if (tc == caseCount - 1 && rnd.next(0, 5) == 0) {
            n = rnd.next(max(1, maxN - 20), maxN);
        } else {
            n = rnd.next(2, min(maxN, rnd.next(8, 45)));
        }

        int mode = (n == 1) ? 1 : rnd.next(0, 5);
        printCase(tc, n, mode);
        remaining -= n;
    }
    println(0);

    return 0;
}
