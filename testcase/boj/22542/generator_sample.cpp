#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Crop {
    string name;
    int p;
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int s;
    int m;
};

string nameFor(int dataset, int index) {
    string name;
    int value = dataset * 100 + index;
    do {
        name.push_back(char('a' + value % 26));
        value /= 26;
    } while (value > 0);
    reverse(name.begin(), name.end());
    return name;
}

Crop randomCrop(int dataset, int index, int mode) {
    Crop crop;
    crop.name = nameFor(dataset, index);

    if (mode == 0) {
        int t = rnd.next(1, 4);
        crop.p = rnd.next(1, 20);
        crop.a = t;
        crop.b = t;
        crop.c = t;
        crop.d = t;
        crop.e = t;
        crop.f = rnd.next(1, 8);
        crop.s = rnd.next(1, 12);
        crop.m = rnd.next(1, 5);
    } else if (mode == 1) {
        int baseProfit = rnd.next(-5, 20);
        int time = rnd.next(5, 25);
        crop.p = rnd.next(1, 50);
        crop.a = rnd.next(1, time);
        crop.b = rnd.next(1, time);
        crop.c = rnd.next(1, time);
        crop.d = rnd.next(1, time);
        crop.e = rnd.next(1, time);
        crop.f = rnd.next(1, 10);
        crop.m = rnd.next(1, 5);
        int revenue = max(crop.p + baseProfit, 1);
        crop.s = max(1, min(100, (revenue + crop.f * crop.m - 1) / (crop.f * crop.m)));
    } else if (mode == 2) {
        crop.p = rnd.next(90, 100);
        crop.a = rnd.next(80, 100);
        crop.b = rnd.next(80, 100);
        crop.c = rnd.next(80, 100);
        crop.d = rnd.next(80, 100);
        crop.e = rnd.next(80, 100);
        crop.f = rnd.next(90, 100);
        crop.s = rnd.next(90, 100);
        crop.m = rnd.next(4, 5);
    } else {
        int common = rnd.next(1, 5);
        crop.p = common;
        crop.a = 1;
        crop.b = 1;
        crop.c = 1;
        crop.d = 1;
        crop.e = 1;
        crop.f = common + 1;
        crop.s = 1;
        crop.m = 1;
    }

    return crop;
}

void printDataset(vector<Crop> crops) {
    shuffle(crops.begin(), crops.end());
    println(int(crops.size()));
    for (const Crop& crop : crops) {
        printf("%s %d %d %d %d %d %d %d %d %d\n", crop.name.c_str(),
               crop.p, crop.a, crop.b, crop.c, crop.d, crop.e, crop.f,
               crop.s, crop.m);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(2, 5);
    for (int dataset = 1; dataset <= datasets; ++dataset) {
        int mode = rnd.next(0, 3);
        int n = (mode == 2) ? rnd.next(2, 8) : rnd.next(1, 12);
        vector<Crop> crops;
        for (int i = 0; i < n; ++i) {
            crops.push_back(randomCrop(dataset, i, mode));
        }
        printDataset(crops);
    }

    println(0);
    return 0;
}
