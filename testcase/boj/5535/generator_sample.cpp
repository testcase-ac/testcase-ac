#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Clothing {
    int a;
    int b;
    int c;
};

int clampTemp(int x) {
    return max(0, min(60, x));
}

bool covers(const Clothing& clothing, int temperature) {
    return clothing.a <= temperature && temperature <= clothing.b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int d = rnd.next(2, 14);
    int n = rnd.next(max(2, d / 2), 22);

    vector<int> temperatures;
    if (mode == 0) {
        int lo = rnd.next(0, 45);
        int hi = rnd.next(lo + 1, 60);
        for (int i = 0; i < d; ++i) temperatures.push_back(rnd.next(lo, hi));
    } else if (mode == 1) {
        int low = rnd.next(0, 25);
        int high = rnd.next(35, 60);
        for (int i = 0; i < d; ++i) temperatures.push_back(i % 2 == 0 ? rnd.next(0, low) : rnd.next(high, 60));
    } else if (mode == 2) {
        int current = rnd.next(0, 60);
        for (int i = 0; i < d; ++i) {
            current = clampTemp(current + rnd.next(-12, 12));
            temperatures.push_back(current);
        }
    } else {
        for (int i = 0; i < d; ++i) temperatures.push_back(rnd.next(0, 60));
    }

    vector<Clothing> clothes;
    if (mode != 3) {
        clothes.push_back({0, 60, rnd.next(0, 20)});
        clothes.push_back({0, 60, rnd.next(80, 100)});
    }

    while ((int)clothes.size() < n) {
        int center = rnd.any(temperatures);
        int width;
        if (mode == 0) {
            width = rnd.next(0, 18);
        } else if (mode == 1) {
            width = rnd.next(0, 8);
        } else if (mode == 2) {
            width = rnd.next(4, 24);
        } else {
            width = rnd.next(0, 60);
        }

        int a = clampTemp(center - rnd.next(0, width));
        int b = clampTemp(center + rnd.next(0, width));
        if (rnd.next(5) == 0) {
            a = rnd.next(0, center);
            b = rnd.next(center, 60);
        }

        int c;
        if (mode == 1) {
            c = (clothes.size() % 2 == 0) ? rnd.next(0, 15) : rnd.next(85, 100);
        } else {
            c = rnd.next(0, 100);
        }
        clothes.push_back({a, b, c});
    }

    for (int temperature : temperatures) {
        bool hasWearable = false;
        for (const Clothing& clothing : clothes) {
            if (covers(clothing, temperature)) {
                hasWearable = true;
                break;
            }
        }
        if (!hasWearable) {
            int index = rnd.next(n);
            clothes[index] = {temperature, temperature, rnd.next(0, 100)};
        }
    }

    shuffle(clothes.begin(), clothes.end());

    println(d, n);
    for (int temperature : temperatures) println(temperature);
    for (const Clothing& clothing : clothes) println(clothing.a, clothing.b, clothing.c);

    return 0;
}
