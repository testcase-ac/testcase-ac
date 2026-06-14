#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 20);
    int m = rnd.next(2, 12);
    vector<pair<int, int>> days;

    auto add_valid_day = [&](int free_slots) {
        int used = n - free_slots;
        int a = rnd.next(0, used);
        days.emplace_back(a, used - a);
    };

    if (mode == 0) {
        n = 1;
        m = rnd.next(2, 8);
        for (int i = 0; i < m; ++i) add_valid_day(rnd.next(0, 1));
    } else if (mode == 1) {
        m = rnd.next(2, min(12, max(2, n + 2)));
        vector<int> free_slots(m, 0);
        for (int i = 0; i < n; ++i) ++free_slots[rnd.next(m)];
        for (int i = 0; i < m; ++i) free_slots[i] = min(free_slots[i], n);
        for (int free_slot : free_slots) add_valid_day(free_slot);
    } else if (mode == 2) {
        m = rnd.next(2, 12);
        int total_free = rnd.next(n, min(n + 15, n * m));
        vector<int> free_slots(m, 0);
        for (int i = 0; i < total_free; ++i) {
            int pos = rnd.next(m);
            if (free_slots[pos] < n) ++free_slots[pos];
        }
        for (int free_slot : free_slots) add_valid_day(free_slot);
    } else if (mode == 3) {
        m = rnd.next(2, 12);
        int total_free = rnd.next(0, n - 1);
        vector<int> free_slots(m, 0);
        for (int i = 0; i < total_free; ++i) ++free_slots[rnd.next(m)];
        for (int free_slot : free_slots) add_valid_day(free_slot);
    } else if (mode == 4) {
        m = rnd.next(2, 12);
        int bad_day = rnd.next(m);
        for (int i = 0; i < m; ++i) {
            if (i == bad_day) {
                int a = rnd.next(1, n);
                int b = rnd.next(n - a + 1, n);
                days.emplace_back(a, b);
            } else {
                add_valid_day(rnd.next(0, n));
            }
        }
    } else {
        n = rnd.next(70, 100);
        m = rnd.next(70, 100);
        for (int i = 0; i < m; ++i) {
            int free_slots = rnd.next(0, min(8, n));
            if (rnd.next(4) == 0) free_slots = rnd.next(0, n);
            add_valid_day(free_slots);
        }
    }

    if (mode != 4) shuffle(days.begin(), days.end());

    println(n, m);
    for (auto [a, b] : days) println(a, b);

    return 0;
}
