#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> scores;
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        int start = rnd.next(49, 300);
        for (int i = 0; i < 50; ++i) {
            scores.push_back(start - i);
        }
    } else if (mode == 1) {
        int start = rnd.next(0, 251);
        for (int i = 0; i < 50; ++i) {
            scores.push_back(start + i);
        }
    } else {
        set<int> chosen;
        bool includeLow = rnd.next(0, 1);
        bool includeHigh = rnd.next(0, 1);
        if (includeLow) {
            chosen.insert(0);
        }
        if (includeHigh) {
            chosen.insert(300);
        }
        while ((int)chosen.size() < 50) {
            chosen.insert(rnd.next(0, 300));
        }
        scores.assign(chosen.begin(), chosen.end());
    }

    sort(scores.rbegin(), scores.rend());

    vector<int> boundaryRanks = {
        1, 5, 6, 15, 16, 30, 31, 35, 36, 45, 46, 48, 49, 50,
    };
    int rank;
    if (rnd.next(0, 2) == 0) {
        rank = rnd.any(boundaryRanks);
    } else {
        rank = rnd.next(1, 50);
    }
    int hongik = scores[rank - 1];

    println(scores);
    println(hongik);

    return 0;
}
