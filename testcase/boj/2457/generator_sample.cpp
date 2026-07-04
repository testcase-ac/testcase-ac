#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Flower {
    int start;
    int end;
};

static const int daysInMonth[13] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static pair<int, int> fromOrdinal(int day) {
    int month = 1;
    while (day > daysInMonth[month]) {
        day -= daysInMonth[month];
        ++month;
    }
    return {month, day};
}

static void addFlower(vector<Flower>& flowers, int start, int end) {
    if (start < 1) start = 1;
    if (end > 365) end = 365;
    if (start < end) flowers.push_back({start, end});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Flower> flowers;
    const int targetStart = 60;  // 3/1
    const int targetEnd = 335;   // 12/1, exclusive coverage endpoint
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        addFlower(flowers, targetStart, targetEnd);
        int extras = rnd.next(1, 8);
        for (int i = 0; i < extras; ++i) {
            int start = rnd.next(1, targetStart + 40);
            int end = rnd.next(start + 1, 365);
            addFlower(flowers, start, end);
        }
    } else if (mode == 1) {
        int current = rnd.next(1, targetStart);
        while (current < targetEnd) {
            int latestStart = min(current, targetEnd - 1);
            int start = rnd.next(max(1, latestStart - rnd.next(0, 12)), latestStart);
            int end = rnd.next(current + 1, min(365, current + rnd.next(18, 75)));
            addFlower(flowers, start, end);
            current = end;
        }
    } else if (mode == 2) {
        int gap = rnd.next(targetStart + 5, targetEnd - 5);
        int leftCount = rnd.next(1, 6);
        int rightCount = rnd.next(1, 6);
        for (int i = 0; i < leftCount; ++i) {
            int start = rnd.next(1, min(gap - 1, targetStart + 40));
            int end = rnd.next(start + 1, gap);
            addFlower(flowers, start, end);
        }
        for (int i = 0; i < rightCount; ++i) {
            int start = rnd.next(gap + 1, targetEnd - 1);
            int end = rnd.next(start + 1, 365);
            addFlower(flowers, start, end);
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 15);
        for (int i = 0; i < n; ++i) {
            int start = rnd.next(1, 364);
            int span = rnd.next(1, 45);
            addFlower(flowers, start, min(365, start + span));
        }
    } else {
        int current = rnd.next(1, targetStart);
        while (current < targetEnd) {
            int start = rnd.next(max(1, current - 20), current);
            int end = min(365, current + rnd.next(1, 35));
            addFlower(flowers, start, end);
            current = end;
            if (rnd.next(0, 4) == 0 && current < targetEnd) {
                current += rnd.next(1, 4);
            }
        }
        int extras = rnd.next(0, 5);
        for (int i = 0; i < extras; ++i) {
            int start = rnd.next(1, 364);
            addFlower(flowers, start, rnd.next(start + 1, 365));
        }
    }

    shuffle(flowers.begin(), flowers.end());

    println(static_cast<int>(flowers.size()));
    for (const Flower& flower : flowers) {
        auto [sm, sd] = fromOrdinal(flower.start);
        auto [em, ed] = fromOrdinal(flower.end);
        println(sm, sd, em, ed);
    }

    return 0;
}
