#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Shortcut {
    int start;
    int end;
    int length;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int D = rnd.next(30, 300);
    int N = rnd.next(1, 12);
    int mode = rnd.next(0, 4);

    vector<Shortcut> shortcuts;

    if (mode == 0) {
        int cursor = rnd.next(0, 10);
        while ((int)shortcuts.size() < N && cursor + 2 <= D) {
            int maxEnd = min(D, cursor + rnd.next(5, 45));
            int end = rnd.next(cursor + 1, maxEnd);
            int roadDistance = end - cursor;
            int length = rnd.next(0, max(0, roadDistance - 1));
            shortcuts.push_back({cursor, end, length});
            cursor = end + rnd.next(0, 15);
        }
    } else if (mode == 1) {
        int base = rnd.next(0, max(0, D - 20));
        for (int i = 0; i < N; ++i) {
            int start = rnd.next(base, min(10000, base + 40));
            int end = rnd.next(start + 1, min(10000, start + rnd.next(2, 80)));
            int roadDistance = end - start;
            int length = rnd.next(0, roadDistance + rnd.next(0, 30));
            shortcuts.push_back({start, end, length});
        }
    } else if (mode == 2) {
        for (int i = 0; i < N; ++i) {
            int start = rnd.next(0, max(0, D - 1));
            int endLimit = rnd.next() < 0.75 ? D : min(10000, D + rnd.next(1, 200));
            int end = rnd.next(start + 1, max(start + 1, endLimit));
            int roadDistance = end - start;
            int length = rnd.next(max(0, roadDistance - 5), roadDistance + 20);
            shortcuts.push_back({start, end, length});
        }
    } else if (mode == 3) {
        for (int i = 0; i < N; ++i) {
            int start = rnd.next(0, min(10000, D + 100));
            int end = rnd.next(start + 1, min(10000, start + rnd.next(1, 300)));
            int roadDistance = end - start;
            int length = rnd.next(0, max(0, roadDistance - 1));
            shortcuts.push_back({start, end, length});
        }
    } else {
        for (int i = 0; i < N; ++i) {
            int start = rnd.next(0, min(9999, D + 50));
            int end = rnd.next(start + 1, 10000);
            int length = rnd.next(0, 10000);
            shortcuts.push_back({start, end, length});
        }
    }

    while ((int)shortcuts.size() < N) {
        int start = rnd.next(0, min(9999, D + 100));
        int end = rnd.next(start + 1, min(10000, start + rnd.next(1, 200)));
        int roadDistance = end - start;
        int length = rnd.next(0, roadDistance + 20);
        shortcuts.push_back({start, end, length});
    }

    shuffle(shortcuts.begin(), shortcuts.end());

    println(N, D);
    for (const Shortcut& shortcut : shortcuts) {
        println(shortcut.start, shortcut.end, shortcut.length);
    }

    return 0;
}
