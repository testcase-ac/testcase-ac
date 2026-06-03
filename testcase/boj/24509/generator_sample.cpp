#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(4, mode == 4 ? 20 : 12);

    vector<int> ids(n);
    for (int i = 0; i < n; ++i) ids[i] = i + 1;
    if (rnd.next(0, 1)) {
        shuffle(ids.begin(), ids.end());
    } else if (rnd.next(0, 1)) {
        reverse(ids.begin(), ids.end());
    }

    vector<array<int, 4>> score(n);
    int base = rnd.next(0, 60);
    for (int i = 0; i < n; ++i) {
        for (int subject = 0; subject < 4; ++subject) {
            score[i][subject] = rnd.next(base, min(100, base + rnd.next(0, 40)));
        }
    }

    if (mode == 0) {
        int tied = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            for (int subject = 0; subject < 4; ++subject) score[i][subject] = tied;
        }
    } else if (mode == 1) {
        int favoriteId = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            for (int subject = 0; subject < 4; ++subject) {
                score[i][subject] = ids[i] == favoriteId ? 100 : rnd.next(0, 96);
            }
        }
    } else if (mode == 2) {
        vector<int> leaders = ids;
        shuffle(leaders.begin(), leaders.end());
        for (int subject = 0; subject < 4; ++subject) {
            for (int i = 0; i < n; ++i) {
                score[i][subject] = rnd.next(0, 70);
                if (ids[i] == leaders[subject]) score[i][subject] = rnd.next(95, 100);
            }
        }
    } else if (mode == 3) {
        int tieHigh = rnd.next(80, 100);
        for (int subject = 0; subject < 4; ++subject) {
            int tiedCount = rnd.next(2, min(n, 5));
            vector<int> order(n);
            for (int i = 0; i < n; ++i) order[i] = i;
            shuffle(order.begin(), order.end());
            for (int i = 0; i < n; ++i) score[i][subject] = rnd.next(0, tieHigh);
            for (int i = 0; i < tiedCount; ++i) score[order[i]][subject] = tieHigh;
        }
    } else {
        for (int subject = 0; subject < 4; ++subject) {
            int slope = rnd.next(1, 4);
            for (int i = 0; i < n; ++i) {
                int byId = (ids[i] * slope + subject * 17) % 101;
                score[i][subject] = rnd.next(max(0, byId - 12), min(100, byId + 12));
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(ids[i], score[i][0], score[i][1], score[i][2], score[i][3]);
    }

    return 0;
}
