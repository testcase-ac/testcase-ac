#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;
    vector<int> initial;

    if (mode == 0) {
        n = rnd.next(3, 8);
        k = 0;
        int m = rnd.next(1, n);
        vector<int> people(n);
        for (int i = 0; i < n; ++i) people[i] = i;
        shuffle(people.begin(), people.end());
        initial.assign(people.begin(), people.begin() + m);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        k = rnd.next(1, 8);
        initial.push_back(rnd.next(0, n - 1));
    } else if (mode == 2) {
        n = rnd.next(4, 20);
        k = rnd.next(1, 30);
        int parity = rnd.next(0, 1);
        for (int i = parity; i < n; i += 2) initial.push_back(i);
        if (initial.empty()) initial.push_back(rnd.next(0, n - 1));
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        k = rnd.next(1, 100);
        int start = rnd.next(0, n - 1);
        int len = rnd.next(1, n);
        for (int i = 0; i < len; ++i) initial.push_back((start + i) % n);
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        k = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) initial.push_back(i);
    } else if (mode == 5) {
        n = rnd.next(3, 40);
        k = rnd.next(100000, 1000000);
        int m = rnd.next(1, min(n, 12));
        set<int> chosen;
        while ((int)chosen.size() < m) chosen.insert(rnd.next(0, n - 1));
        initial.assign(chosen.begin(), chosen.end());
    } else if (mode == 6) {
        n = 200;
        k = rnd.next(0, 1000000);
        int m = rnd.next(1, 20);
        set<int> chosen;
        while ((int)chosen.size() < m) chosen.insert(rnd.next(0, n - 1));
        initial.assign(chosen.begin(), chosen.end());
    } else {
        n = rnd.next(3, 35);
        k = rnd.next(1, 200);
        double density = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            if (rnd.next() < density) initial.push_back(i);
        }
        if (initial.empty()) initial.push_back(rnd.next(0, n - 1));
    }

    shuffle(initial.begin(), initial.end());

    println(n, (int)initial.size(), k);
    for (int person : initial) println(person);

    return 0;
}
