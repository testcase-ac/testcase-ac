#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    int m = rnd.next(1, 30);
    vector<pair<int, int>> researchers;

    if (mode == 0) {
        int current = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int stay = rnd.next(1, 10);
            researchers.push_back({current, stay});
            current += stay + rnd.next(0, m);
        }
    } else if (mode == 1) {
        int current = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int stay = rnd.next(1, 12);
            researchers.push_back({current, stay});
            current += stay + m + rnd.next(1, 12);
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int arrival = base + rnd.next(0, 12);
            int stay = rnd.next(1, 20);
            researchers.push_back({arrival, stay});
        }
    } else if (mode == 3) {
        int stations = rnd.next(2, 6);
        vector<int> nextArrival(stations);
        for (int i = 0; i < stations; ++i) {
            nextArrival[i] = rnd.next(1, 10) + i;
        }
        for (int i = 0; i < n; ++i) {
            int station = rnd.next(0, stations - 1);
            int stay = rnd.next(1, 15);
            researchers.push_back({nextArrival[station], stay});
            nextArrival[station] += stay + rnd.next(0, m + 4);
        }
    } else if (mode == 4) {
        m = rnd.next(1, 100000000);
        int low = max(1, 100000000 - 2000);
        for (int i = 0; i < n; ++i) {
            int arrival = rnd.next(low, 100000000);
            int stay = rnd.next(1, 100000000);
            researchers.push_back({arrival, stay});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int arrival = rnd.next(1, 120);
            int stay = rnd.next(1, 35);
            researchers.push_back({arrival, stay});
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(researchers.begin(), researchers.end());
    }

    println(n, m);
    for (const auto& researcher : researchers) {
        println(researcher.first, researcher.second);
    }

    return 0;
}
