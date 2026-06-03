#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> days;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(3, 20);
        for (int day = 1; day <= n; ++day) {
            days.push_back(day);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 30);
        int parity = rnd.next(0, 1);
        for (int day = 1; day <= n; ++day) {
            if (day % 2 == parity) {
                days.push_back(day);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(8, 40);
        int blocks = rnd.next(1, 4);
        vector<bool> blocked(n + 1, false);
        for (int i = 0; i < blocks; ++i) {
            int start = rnd.next(1, n);
            int length = rnd.next(1, min(5, n - start + 1));
            for (int day = start; day < start + length; ++day) {
                blocked[day] = true;
            }
        }
        for (int day = 1; day <= n; ++day) {
            if (blocked[day]) {
                days.push_back(day);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(10, 60);
        double probability = rnd.next(0.05, 0.30);
        for (int day = 1; day <= n; ++day) {
            if (rnd.next() < probability) {
                days.push_back(day);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(10, 60);
        double probability = rnd.next(0.55, 0.90);
        for (int day = 1; day <= n; ++day) {
            if (rnd.next() < probability) {
                days.push_back(day);
            }
        }
    } else {
        n = rnd.next(61, 100);
        int m = rnd.next(0, min(n, 25));
        vector<int> candidates;
        for (int day = 1; day <= n; ++day) {
            candidates.push_back(day);
        }
        shuffle(candidates.begin(), candidates.end());
        candidates.resize(m);
        sort(candidates.begin(), candidates.end());
        days = candidates;
    }

    println(n, static_cast<int>(days.size()));
    if (!days.empty()) {
        println(days);
    }

    return 0;
}
