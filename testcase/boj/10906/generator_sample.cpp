#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> randomInterval() {
    int s = rnd.next(-11, 10);
    int e = rnd.next(s + 1, 11);
    return {s, e};
}

pair<int, int> intervalAroundPoint(int point) {
    int s = rnd.next(-11, point - 1);
    int e = rnd.next(point + 1, 11);
    return {s, e};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 5 ? 11 : rnd.next(1, 8);

    vector<pair<int, int>> first(n), second(n);
    for (int i = 0; i < n; ++i) {
        first[i] = randomInterval();
        second[i] = randomInterval();
    }

    if (mode == 0) {
        // Positive overlap in every dimension.
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(-10, 9);
            int e = rnd.next(s + 1, 10);
            first[i] = {max(-11, s - rnd.next(0, 2)), min(11, e + rnd.next(0, 2))};
            second[i] = {max(-11, s - rnd.next(0, 2)), min(11, e + rnd.next(0, 2))};
            if (first[i].first >= first[i].second) first[i] = {s, e};
            if (second[i].first >= second[i].second) second[i] = {s, e};
        }
    } else if (mode == 1) {
        // Touch at one or more boundary points, otherwise overlap.
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rnd.next(0, 2) == 0) {
                int p = rnd.next(-10, 10);
                first[i] = {rnd.next(-11, p - 1), p};
                second[i] = {p, rnd.next(p + 1, 11)};
            } else {
                int p = rnd.next(-10, 10);
                first[i] = intervalAroundPoint(p);
                second[i] = intervalAroundPoint(p);
            }
        }
    } else if (mode == 2) {
        // At least one dimension is disjoint.
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rnd.next(0, 3) == 0) {
                int cut = rnd.next(-10, 9);
                first[i] = {rnd.next(-11, cut - 1), cut};
                second[i] = {rnd.next(cut + 1, 10), 11};
            } else {
                int p = rnd.next(-10, 10);
                first[i] = intervalAroundPoint(p);
                second[i] = intervalAroundPoint(p);
            }
        }
    } else if (mode == 3) {
        // One orthotope mostly contained in the other.
        for (int i = 0; i < n; ++i) {
            int innerS = rnd.next(-10, 9);
            int innerE = rnd.next(innerS + 1, 10);
            first[i] = {rnd.next(-11, innerS), rnd.next(innerE, 11)};
            second[i] = {innerS, innerE};
            if (rnd.next(0, 1)) swap(first[i], second[i]);
        }
    } else if (mode == 4) {
        // Mixed dimensions to vary the resulting intersection dimension.
        for (int i = 0; i < n; ++i) {
            int type = rnd.next(0, 2);
            int p = rnd.next(-10, 10);
            if (type == 0) {
                first[i] = intervalAroundPoint(p);
                second[i] = intervalAroundPoint(p);
            } else if (type == 1) {
                first[i] = {rnd.next(-11, p - 1), p};
                second[i] = {p, rnd.next(p + 1, 11)};
            } else {
                int cut = rnd.next(-10, 9);
                first[i] = {rnd.next(-11, cut - 1), cut};
                second[i] = {rnd.next(cut + 1, 10), 11};
            }
        }
    } else {
        // Max dimension with broad and narrow coordinates near the bounds.
        for (int i = 0; i < n; ++i) {
            int s = -11 + i % 5;
            int e = 11 - i % 4;
            first[i] = {s, e};
            if (i % 3 == 0) second[i] = {s, e};
            else if (i % 3 == 1) second[i] = {s + 1, e - 1};
            else second[i] = {s, s + 1};
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        if (i) printf(" ");
        printf("%d %d", first[i].first, first[i].second);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        if (i) printf(" ");
        printf("%d %d", second[i].first, second[i].second);
    }
    printf("\n");

    return 0;
}
