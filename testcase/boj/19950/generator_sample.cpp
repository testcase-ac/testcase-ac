#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampCoord(int value) {
    return max(-1000, min(1000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int x1 = 0;
    int y1 = 0;
    int z1 = 0;
    int x2 = 0;
    int y2 = 0;
    int z2 = 0;
    vector<int> sticks;

    if (mode == 0) {
        int distance = rnd.next(1, 80);
        int n = rnd.next(1, min(8, distance));
        x2 = distance;
        int remaining = distance;
        for (int i = 0; i < n; ++i) {
            int left = n - i - 1;
            int k = (i == n - 1) ? remaining : rnd.next(1, remaining - left);
            sticks.push_back(k);
            remaining -= k;
        }
    } else if (mode == 1) {
        int distance = rnd.next(20, 120);
        x2 = distance;
        int n = rnd.next(2, 12);
        int total = rnd.next(n, distance - 1);
        int remaining = total;
        for (int i = 0; i < n; ++i) {
            int left = n - i - 1;
            int k = (i == n - 1) ? remaining : rnd.next(1, remaining - left);
            sticks.push_back(k);
            remaining -= k;
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 12);
        int otherSum = rnd.next(n - 1, 45);
        int longest = otherSum + rnd.next(1, 40);
        int distance = rnd.next(0, longest - otherSum - 1);
        x2 = distance;
        sticks.push_back(longest);
        int remaining = otherSum;
        for (int i = 1; i < n; ++i) {
            int left = n - i - 1;
            int k = (i == n - 1) ? remaining : rnd.next(1, remaining - left);
            sticks.push_back(k);
            remaining -= k;
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 20);
        x2 = rnd.next(-3, 3);
        y2 = rnd.next(-3, 3);
        z2 = rnd.next(-3, 3);
        if (x2 == 0 && y2 == 0 && z2 == 0) x2 = 1;
        int longest = rnd.next(1, 25);
        int otherSum = max(n - 1, longest + rnd.next(0, 25));
        sticks.push_back(longest);
        int remaining = otherSum;
        for (int i = 1; i < n; ++i) {
            int left = n - i - 1;
            int k = (i == n - 1) ? remaining : rnd.next(1, remaining - left);
            sticks.push_back(k);
            remaining -= k;
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 15);
        x1 = rnd.next(-1000, 1000);
        y1 = rnd.next(-1000, 1000);
        z1 = rnd.next(-1000, 1000);
        x2 = x1;
        y2 = y1;
        z2 = z1;
        for (int i = 0; i < n; ++i) sticks.push_back(rnd.next(1, 100));
    } else if (mode == 5) {
        x1 = rnd.next(0, 1) ? -1000 : 1000;
        y1 = rnd.next(-1000, 1000);
        z1 = rnd.next(-1000, 1000);
        x2 = -x1;
        y2 = clampCoord(y1 + rnd.next(-20, 20));
        z2 = clampCoord(z1 + rnd.next(-20, 20));
        int n = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) sticks.push_back(rnd.next(80, 100));
    } else if (mode == 6) {
        int n = rnd.next(85, 100);
        x2 = rnd.next(0, 1) ? 0 : rnd.next(1, 1000);
        y2 = rnd.next(0, 1) ? 0 : rnd.next(-1000, 1000);
        z2 = rnd.next(0, 1) ? 0 : rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) sticks.push_back(rnd.next(1, 100));
    } else {
        x1 = rnd.next(-20, 20);
        y1 = rnd.next(-20, 20);
        z1 = rnd.next(-20, 20);
        x2 = clampCoord(x1 + rnd.next(-30, 30));
        y2 = clampCoord(y1 + rnd.next(-30, 30));
        z2 = clampCoord(z1 + rnd.next(-30, 30));
        int n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) sticks.push_back(rnd.next(1, 40));
    }

    shuffle(sticks.begin(), sticks.end());

    println(x1, y1, z1, x2, y2, z2);
    println((int)sticks.size());
    println(sticks);

    return 0;
}
