#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Reservation {
    int room;
    int start;
    int end;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 18);
    } else {
        n = rnd.next(1, 8);
        m = rnd.next(1, 28);
    }

    vector<Reservation> reservations;
    reservations.reserve(m);
    vector<int> lastEnd(n + 1, 0);

    int current = rnd.next(1, 5);
    for (int i = 0; i < m; ++i) {
        int remaining = m - i;
        int maxGap = max(1, (1000000000 - current - remaining) / remaining);
        int gap = rnd.next(1, min(maxGap, 12));
        int start = (i == 0 ? current : current + gap);

        int room;
        if (mode == 0) {
            room = 1;
        } else if (mode == 1) {
            room = (i % n) + 1;
        } else if (mode == 2 && i > 0 && rnd.next(0, 99) < 70) {
            room = reservations[rnd.next((int)reservations.size())].room;
        } else {
            room = rnd.next(1, n);
        }

        int duration;
        if (mode == 3 && lastEnd[room] > 0 && rnd.next(0, 99) < 50) {
            start = max(start, lastEnd[room]);
            duration = rnd.next(1, 8);
        } else if (lastEnd[room] > start && rnd.next(0, 99) < 65) {
            duration = rnd.next(1, min(20, lastEnd[room] - start + 8));
        } else {
            duration = rnd.next(1, 15);
        }

        if (mode == 4 && i + 1 == m) {
            start = 999999900;
            duration = rnd.next(1, 99);
        }

        int end = min(1000000000, start + duration);
        if (end <= start) {
            end = start + 1;
        }

        reservations.push_back({room, start, end});
        lastEnd[room] = max(lastEnd[room], end);
        current = start;
    }

    sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
        return a.start < b.start;
    });

    println(n, m);
    for (const Reservation& reservation : reservations) {
        println(reservation.room, reservation.start, reservation.end);
    }

    return 0;
}
