#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int smallCount() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(0, 5);
    if (mode == 2) return rnd.next(6, 30);
    if (mode == 3) return rnd.next(970, 1000);
    return rnd.next(0, 1000);
}

pair<int, int> randomEvent(int mode) {
    int in = 0, out = 0;
    if (mode == 0) {
        in = smallCount();
        out = smallCount();
    } else if (mode == 1) {
        in = rnd.next(0, 8);
        out = rnd.next(in, min(1000, in + rnd.next(0, 40)));
    } else if (mode == 2) {
        out = rnd.next(0, 8);
        in = rnd.next(out, min(1000, out + rnd.next(0, 40)));
    } else if (mode == 3) {
        in = rnd.next(0, 1) ? 1000 : rnd.next(0, 20);
        out = rnd.next(0, 1) ? 1000 : rnd.next(0, 20);
    } else {
        int delta = rnd.next(-25, 25);
        if (delta >= 0) {
            out = rnd.next(0, 25);
            in = min(1000, out + delta);
        } else {
            in = rnd.next(0, 25);
            out = min(1000, in - delta);
        }
    }
    return {in, out};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int m = rnd.next(1, 18);
        if (rnd.next(0, 9) == 0) m = rnd.next(40, 100);

        vector<pair<int, int>> events;
        events.reserve(m);

        for (int i = 0; i < m; ++i) {
            events.push_back(randomEvent(mode));
        }

        if (m >= 3 && rnd.next(0, 1)) {
            int first = rnd.next(1, min(1000, 20 + tc));
            events[0] = {0, first};
            events[1] = {first, 0};
            events[2] = {rnd.next(0, 5), rnd.next(0, 5)};
        }

        println(m);
        for (auto event : events) {
            println(event.first, event.second);
        }
    }

    return 0;
}
