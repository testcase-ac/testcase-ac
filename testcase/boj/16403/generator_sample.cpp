#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clippedBlock(int x) {
    return max(0, min(10000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int a;
    int b;
    vector<int> blocks;

    if (mode == 0) {
        n = rnd.next(1, 12);
        a = rnd.next(0, 5);
        b = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) blocks.push_back(rnd.next(0, 60));
    } else if (mode == 1) {
        n = rnd.next(20, 48);
        a = rnd.next(1, 20);
        b = rnd.next(1, 500);
        int center = rnd.next(20, 9980);
        int radius = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            blocks.push_back(clippedBlock(center + rnd.next(-radius, radius)));
        }
    } else if (mode == 2) {
        n = rnd.next(35, 85);
        a = rnd.next(1, 1000);
        b = rnd.next(1, 100000);
        int first = rnd.next(0, 200);
        int second = rnd.next(9000, 10000);
        for (int i = 0; i < n; ++i) {
            int base = (i % 2 == 0 ? first : second);
            blocks.push_back(clippedBlock(base + rnd.next(-5, 5)));
        }
    } else if (mode == 3) {
        n = rnd.next(39, 82);
        a = rnd.next(0, 1000);
        b = rnd.next(0, 100000);
        int block = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                blocks.push_back(rnd.next(0, 10000));
            } else {
                blocks.push_back(block);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(1, 70);
        a = rnd.next(0, 1) == 0 ? 0 : rnd.next(1, 1000);
        b = rnd.next(0, 1) == 0 ? 0 : rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) blocks.push_back(rnd.next(0, 10000));
    } else if (mode == 5) {
        n = rnd.next(2, 90);
        a = rnd.next(1, 30);
        b = rnd.next(1, 300);
        int start = rnd.next(0, 10000);
        int step = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) {
            blocks.push_back(clippedBlock(start + (i - n / 2) * step));
        }
    } else {
        n = rnd.next(80, 140);
        a = rnd.next(1, 1000);
        b = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) blocks.push_back(0);
            else if (bucket == 1) blocks.push_back(10000);
            else blocks.push_back(rnd.next(0, 10000));
        }
    }

    shuffle(blocks.begin(), blocks.end());

    println(n);
    println(a, b);
    println(blocks);

    return 0;
}
