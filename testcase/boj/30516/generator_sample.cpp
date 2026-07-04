#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 30);
        a.assign(n, 0);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 12);
        int solos = rnd.next(0, 8);
        for (int value = 1; value <= pairs; ++value) {
            a.push_back(value);
            a.push_back(value);
            if (solos > 0 && rnd.next(0, 2) == 0) {
                a.push_back(0);
                --solos;
            }
        }
        while (solos-- > 0) {
            a.push_back(0);
        }
    } else if (mode == 2) {
        int pairs = rnd.next(1, 12);
        int solos = rnd.next(0, 8);
        for (int value = 1; value <= pairs; ++value) {
            a.push_back(value);
        }
        for (int i = 0; i < solos; ++i) {
            a.push_back(0);
        }
        for (int value = pairs; value >= 1; --value) {
            a.push_back(value);
        }
    } else if (mode == 3) {
        int pairs = rnd.next(2, 12);
        vector<int> values(pairs);
        iota(values.begin(), values.end(), 1);
        for (int value : values) {
            a.push_back(value);
            a.push_back(value);
        }
        shuffle(a.begin(), a.end());
        int solos = rnd.next(0, 8);
        while (solos-- > 0) {
            a.insert(a.begin() + rnd.next(0, static_cast<int>(a.size())), 0);
        }
    } else if (mode == 4) {
        int pairs = rnd.next(2, 10);
        a.push_back(1);
        for (int value = 2; value <= pairs; ++value) {
            a.push_back(value);
            if (rnd.next(0, 1) == 0) {
                a.push_back(0);
            }
            a.push_back(value);
        }
        a.push_back(1);
    } else {
        int n = rnd.next(1, 35);
        int pairs = rnd.next(0, n / 2);
        vector<int> slots(n, 0);
        vector<int> positions(n);
        iota(positions.begin(), positions.end(), 0);
        shuffle(positions.begin(), positions.end());
        for (int value = 1; value <= pairs; ++value) {
            slots[positions.back()] = value;
            positions.pop_back();
            slots[positions.back()] = value;
            positions.pop_back();
        }
        a = slots;
    }

    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
