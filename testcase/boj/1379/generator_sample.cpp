#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Lecture {
    int id;
    long long start;
    long long end;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    vector<Lecture> lectures;
    lectures.reserve(n);

    if (mode == 0) {
        long long cur = rnd.next(0, 20);
        for (int i = 1; i <= n; ++i) {
            long long len = rnd.next(1, 8);
            lectures.push_back({i, cur, cur + len});
            cur += len + rnd.next(0, 3);
        }
    } else if (mode == 1) {
        long long base = rnd.next(0, 30);
        long long common = base + rnd.next(1, 10);
        for (int i = 1; i <= n; ++i) {
            long long start = rnd.next(max(0LL, common - 10), common - 1);
            long long end = rnd.next(common + 1, common + 12);
            lectures.push_back({i, start, end});
        }
    } else if (mode == 2) {
        long long cur = rnd.next(0, 15);
        for (int i = 1; i <= n; ++i) {
            if (i > 1 && rnd.next(0, 2) == 0) cur += rnd.next(0, 5);
            long long len = rnd.next(1, 12);
            long long back = rnd.next(0LL, min(5LL, cur));
            lectures.push_back({i, cur - back, cur - back + len});
            cur += rnd.next(0, 4);
        }
    } else if (mode == 3) {
        long long anchor = rnd.next(0, 100);
        for (int i = 1; i <= n; ++i) {
            long long start = anchor + rnd.next(0, 3) * 5;
            long long end = start + rnd.next(1, 5) * 5;
            lectures.push_back({i, start, end});
        }
    } else {
        n = rnd.next(2, 12);
        long long nearLimit = 1000000000LL - rnd.next(20, 200);
        for (int i = 1; i <= n; ++i) {
            long long start = min(999999999LL, nearLimit + rnd.next(0, 80));
            long long end = rnd.next(start + 1, 1000000000LL);
            lectures.push_back({i, start, end});
        }
    }

    vector<int> ids(n);
    for (int i = 0; i < n; ++i) ids[i] = i + 1;
    shuffle(ids.begin(), ids.end());
    for (int i = 0; i < n; ++i) lectures[i].id = ids[i];
    shuffle(lectures.begin(), lectures.end());

    println(n);
    for (const Lecture& lecture : lectures) {
        println(lecture.id, lecture.start, lecture.end);
    }

    return 0;
}
