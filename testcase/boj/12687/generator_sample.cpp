#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Animal {
    int h;
    int w;
    string label;
};

int randomCoord() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(999980, 1000000);
    if (mode == 2) return rnd.next(490000, 510000);
    return rnd.next(1, 1000000);
}

int clampCoord(int value) {
    return max(1, min(1000000, value));
}

pair<int, int> randomPointNear(int loH, int hiH, int loW, int hiW) {
    int hMode = rnd.next(0, 2);
    int wMode = rnd.next(0, 2);

    int h;
    if (hMode == 0) h = rnd.next(loH, hiH);
    else if (hMode == 1) h = loH - rnd.next(1, 12);
    else h = hiH + rnd.next(1, 12);

    int w;
    if (wMode == 0) w = rnd.next(loW, hiW);
    else if (wMode == 1) w = loW - rnd.next(1, 12);
    else w = hiW + rnd.next(1, 12);

    return {clampCoord(h), clampCoord(w)};
}

vector<Animal> buildKnownAnimals(int mode, int& loH, int& hiH, int& loW, int& hiW) {
    vector<Animal> animals;

    loH = rnd.next(2, 999980);
    hiH = rnd.next(loH, min(1000000, loH + rnd.next(0, 30)));
    loW = rnd.next(2, 999980);
    hiW = rnd.next(loW, min(1000000, loW + rnd.next(0, 30)));

    if (mode == 0) {
        int n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) animals.push_back({randomCoord(), randomCoord(), "NOT BIRD"});
        return animals;
    }

    animals.push_back({loH, loW, "BIRD"});
    if (rnd.next(0, 1)) animals.push_back({hiH, hiW, "BIRD"});
    if (rnd.next(0, 1)) animals.push_back({loH, hiW, "BIRD"});
    if (rnd.next(0, 1)) animals.push_back({hiH, loW, "BIRD"});

    int target = rnd.next((int)animals.size(), 10);
    while ((int)animals.size() < target) {
        if (mode == 1 || rnd.next(0, 2) == 0) {
            animals.push_back({rnd.next(loH, hiH), rnd.next(loW, hiW), "BIRD"});
        } else {
            auto [h, w] = randomPointNear(loH, hiH, loW, hiW);
            if (h >= loH && h <= hiH && w >= loW && w <= hiW) {
                h = clampCoord(hiH + 1);
                if (h == hiH) w = clampCoord(hiW + 1);
            }
            animals.push_back({h, w, "NOT BIRD"});
        }
    }

    shuffle(animals.begin(), animals.end());
    return animals;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(3, 10);
    println(c);

    for (int tc = 0; tc < c; ++tc) {
        int mode = (tc + rnd.next(0, 3)) % 4;
        int loH, hiH, loW, hiW;
        vector<Animal> animals = buildKnownAnimals(mode, loH, hiH, loW, hiW);

        println((int)animals.size());
        for (const Animal& animal : animals) {
            println(animal.h, animal.w, animal.label);
        }

        int m = rnd.next(3, 10);
        println(m);
        for (int i = 0; i < m; ++i) {
            pair<int, int> query;
            int queryMode = rnd.next(0, 5);
            if (queryMode == 0 && mode != 0) query = {rnd.next(loH, hiH), rnd.next(loW, hiW)};
            else if (queryMode <= 3 && mode != 0) query = randomPointNear(loH, hiH, loW, hiW);
            else query = {randomCoord(), randomCoord()};
            println(query.first, query.second);
        }
    }

    return 0;
}
