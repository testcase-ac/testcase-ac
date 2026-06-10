#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(8, 35);
        k = rnd.next(1, min(n, 5));
    } else if (mode == 2) {
        n = rnd.next(10, 45);
        k = rnd.next(1, min(n, 8));
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        k = rnd.next(1, min(n, 6));
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        k = rnd.next(1, min(n, 12));
    } else {
        n = rnd.next(1, 60);
        k = rnd.next(1, n);
    }

    int c = rnd.next(1, 100);
    int r = rnd.next(1, 100);
    if (mode == 2) r = rnd.next(1, 25);
    if (mode == 3) r = rnd.next(50, 100);

    vector<int> base(k);
    vector<int> s(k);
    vector<int> p(k);
    for (int i = 0; i < k; ++i) {
        if (mode == 1) {
            base[i] = rnd.next(50000, 100000);
            s[i] = rnd.next(50, 100);
            p[i] = rnd.next(1, 20);
        } else if (mode == 2) {
            base[i] = rnd.next(1, 100000);
            s[i] = rnd.next(1, 100);
            p[i] = rnd.next(35, 100);
        } else if (mode == 3) {
            base[i] = rnd.next(1, 200);
            s[i] = rnd.next(1, 15);
            p[i] = rnd.next(1, 40);
        } else {
            base[i] = rnd.next(1, 100000);
            s[i] = rnd.next(1, 100);
            p[i] = rnd.next(1, 100);
        }
    }

    vector<int> plan;
    plan.reserve(n);
    if (mode == 0) {
        for (int day = 0; day < n; ++day) plan.push_back(rnd.next(0, k));
    } else if (mode == 1) {
        int spell = rnd.next(1, k);
        for (int day = 0; day < n; ++day) {
            if (day > 0 && rnd.next(0, 9) == 0) plan.push_back(0);
            else if (rnd.next(0, 3) == 0) plan.push_back(rnd.next(1, k));
            else plan.push_back(spell);
        }
    } else if (mode == 2) {
        int heavy = max_element(p.begin(), p.end()) - p.begin() + 1;
        for (int day = 0; day < n; ++day) {
            if (day < 4 || rnd.next(0, 4) != 0) plan.push_back(heavy);
            else plan.push_back(0);
        }
    } else if (mode == 3) {
        for (int day = 0; day < n; ++day) {
            if (day % 2 == 0 || rnd.next(0, 1) == 0) plan.push_back(0);
            else plan.push_back(rnd.next(1, k));
        }
    } else if (mode == 4) {
        int block = rnd.next(2, 8);
        for (int day = 0; day < n; ++day) {
            if ((day + 1) % block == 0) plan.push_back(0);
            else plan.push_back(rnd.next(1, k));
        }
    } else {
        for (int day = 0; day < n; ++day) {
            int restChance = rnd.next(0, 4);
            plan.push_back(restChance == 0 ? 0 : rnd.next(1, k));
        }
    }

    println(n, k, c, r);
    println(base);
    println(s);
    println(p);
    for (int action : plan) println(action);

    return 0;
}
