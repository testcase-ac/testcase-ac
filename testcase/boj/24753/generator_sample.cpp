#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> buildSeats(int s, int n, int mode) {
    vector<int> gaps(n, 2);
    int extra = s - 2 * n;

    if (extra > 0) {
        if (mode == 1) {
            gaps[rnd.next(n)] += extra;
        } else if (mode == 2) {
            int heavy = rnd.next(n);
            gaps[heavy] += rnd.next(extra / 2, extra);
            extra -= gaps[heavy] - 2;
            while (extra-- > 0) {
                gaps[rnd.next(n)]++;
            }
        } else {
            while (extra-- > 0) {
                gaps[rnd.next(n)]++;
            }
        }
    }

    int start = rnd.next(1, s);
    vector<int> seats;
    int cur = start;
    for (int gap : gaps) {
        seats.push_back(cur);
        cur += gap;
        while (cur > s) {
            cur -= s;
        }
    }
    sort(seats.begin(), seats.end());
    return seats;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int s;
    int n;
    if (mode == 0) {
        s = rnd.next(3, 12);
        n = rnd.next(1, s / 2);
    } else if (mode == 1) {
        s = rnd.next(20, 120);
        n = rnd.next(1, min(8, s / 2));
    } else if (mode == 2) {
        s = rnd.next(6, 80);
        n = s / 2;
    } else if (mode == 3) {
        s = rnd.next(30, 200);
        n = rnd.next(max(1, s / 4), s / 2);
    } else {
        s = rnd.next(3, 1000);
        n = rnd.next(1, min(50, s / 2));
    }

    vector<int> seats = buildSeats(s, n, mode);
    println(s, n);
    println(seats);

    return 0;
}
