#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Lecture {
    int sa;
    int ea;
    int sb;
    int eb;
};

pair<int, int> shifted(pair<int, int> interval, int delta) {
    return {interval.first + delta, interval.second + delta};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    vector<Lecture> lectures;

    if (mode == 0) {
        // Same overlap graph in both venues, with randomized shifts and order.
        int gap = rnd.next(0, 3);
        int cur = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(0, 4);
            pair<int, int> a = {cur, cur + len};
            pair<int, int> b = shifted(a, rnd.next(20, 60));
            lectures.push_back({a.first, a.second, b.first, b.second});
            cur += len + gap + 1;
        }
    } else if (mode == 1) {
        // A has one forced overlap while B separates the same pair.
        n = max(n, 2);
        lectures.push_back({10, 20, 10, 12});
        lectures.push_back({rnd.next(15, 20), rnd.next(20, 25), 13, 15});
        for (int i = 2; i < n; ++i) {
            int base = 30 + i * 5;
            lectures.push_back({base, base + rnd.next(0, 2), base + 100, base + 100 + rnd.next(0, 2)});
        }
    } else if (mode == 2) {
        // B has one forced overlap while A separates the same pair.
        n = max(n, 2);
        lectures.push_back({10, 12, 10, 20});
        lectures.push_back({13, 15, rnd.next(15, 20), rnd.next(20, 25)});
        for (int i = 2; i < n; ++i) {
            int base = 30 + i * 6;
            lectures.push_back({base, base + rnd.next(0, 3), base + 200, base + 200 + rnd.next(0, 3)});
        }
    } else if (mode == 3) {
        // Boundary-touching inclusive intervals, mirrored with mild shifts.
        int cur = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(0, 3);
            int nextStart = cur + len;
            lectures.push_back({cur, cur + len, cur + 50, cur + 50 + len});
            cur = nextStart + rnd.next(0, 2);
        }
    } else if (mode == 4) {
        // Nested intervals in A, with independently nested or short intervals in B.
        int left = rnd.next(1, 10);
        int right = left + rnd.next(15, 30);
        for (int i = 0; i < n; ++i) {
            int shrink = rnd.next(0, min(i + 2, (right - left) / 2));
            int sa = left + shrink;
            int ea = right - shrink;
            int sb = 100 + i * 2;
            int eb = sb + rnd.next(0, 5);
            lectures.push_back({sa, ea, sb, eb});
        }
    } else {
        // General compact intervals with varied lengths and overlap density.
        int maxCoord = rnd.next(8, 40);
        for (int i = 0; i < n; ++i) {
            int sa = rnd.next(1, maxCoord);
            int ea = rnd.next(sa, min(maxCoord, sa + rnd.next(0, 8)));
            int sb = rnd.next(1, maxCoord);
            int eb = rnd.next(sb, min(maxCoord, sb + rnd.next(0, 8)));
            lectures.push_back({sa, ea, sb + 100, eb + 100});
        }
    }

    shuffle(lectures.begin(), lectures.end());

    println((int)lectures.size());
    for (const Lecture& lecture : lectures) {
        println(lecture.sa, lecture.ea, lecture.sb, lecture.eb);
    }

    return 0;
}
