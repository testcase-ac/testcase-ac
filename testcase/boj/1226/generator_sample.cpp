#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> seats;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        seats.assign(n, 0);
        seats[rnd.next(n)] = rnd.next(1, 20);
    } else if (mode == 1) {
        int n = rnd.next(2, 20);
        int value = rnd.next(1, 12);
        seats.assign(n, value);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) seats[i] += rnd.next(0, 2);
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 18);
        int anchor = rnd.next(5, 40);
        seats.push_back(anchor);
        seats.push_back(anchor + rnd.next(0, 3));
        while ((int)seats.size() < n) {
            seats.push_back(rnd.next(0, max(1, anchor / 2)));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 25);
        int large = rnd.next(30, 120);
        seats.push_back(large);
        for (int i = 1; i < n; ++i) {
            seats.push_back(rnd.next(0, 10));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            seats.push_back(rnd.wnext(35, -2));
        }
        if (accumulate(seats.begin(), seats.end(), 0) == 0) {
            seats[rnd.next(n)] = 1;
        }
    } else if (mode == 5) {
        int n = rnd.next(80, 300);
        seats.assign(n, 0);
        int positives = rnd.next(1, min(n, 20));
        vector<int> indexes(n);
        iota(indexes.begin(), indexes.end(), 0);
        shuffle(indexes.begin(), indexes.end());
        for (int i = 0; i < positives; ++i) {
            seats[indexes[i]] = rnd.next(1, 100);
        }
    } else {
        int n = rnd.next(1, 40);
        int remaining = rnd.next(1, 1000);
        seats.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i == n - 1) {
                seats[i] = remaining;
            } else {
                int take = rnd.next(0, remaining);
                seats[i] = take;
                remaining -= take;
            }
        }
    }

    shuffle(seats.begin(), seats.end());

    println((int)seats.size());
    println(seats);

    return 0;
}
