#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

static pair<int, int> randomRoomWithArea(int area) {
    vector<pair<int, int>> rooms;
    for (int w = 1; w <= 1000; ++w) {
        if (area % w == 0) {
            int h = area / w;
            if (h >= 1 && h <= 1000) rooms.push_back({w, h});
        }
    }
    return rnd.any(rooms);
}

static pair<int, int> randomRoomWithProductInRange(int low, int high) {
    while (true) {
        int w = rnd.next(1, 1000);
        int minH = max(1, (low + w - 1) / w);
        int maxH = min(1000, high / w);
        if (minH <= maxH) return {w, rnd.next(minH, maxH)};
    }
}

static pair<int, int> randomRoomBelowMaxArea() {
    while (true) {
        pair<int, int> room = {rnd.next(1, 1000), rnd.next(1, 1000)};
        if (room.first * room.second < 1000000) return room;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    pair<int, int> masha;
    pair<int, int> petya;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int area = rnd.any(vector<int>{1, 2, 4, 6, 12, 24, 36, 100, 144, 400, 900, 1000, 10000, 250000, 1000000});
        masha = randomRoomWithArea(area);
        petya = randomRoomWithArea(area);
    } else if (mode == 1) {
        petya = randomRoomBelowMaxArea();
        int petyaArea = petya.first * petya.second;
        masha = randomRoomWithProductInRange(petyaArea + 1, 1000000);
    } else if (mode == 2) {
        masha = randomRoomBelowMaxArea();
        int mashaArea = masha.first * masha.second;
        petya = randomRoomWithProductInRange(mashaArea + 1, 1000000);
    } else if (mode == 3) {
        petya = randomRoomBelowMaxArea();
        int base = petya.first * petya.second;
        masha = randomRoomWithProductInRange(base + 1, min(1000000, base + 20));
    } else if (mode == 4) {
        masha = randomRoomBelowMaxArea();
        int base = masha.first * masha.second;
        petya = randomRoomWithProductInRange(base + 1, min(1000000, base + 20));
    } else {
        masha = rnd.next(0, 1) == 0 ? make_pair(1000, rnd.next(1, 1000)) : make_pair(rnd.next(1, 1000), 1000);
        petya = rnd.next(0, 1) == 0 ? make_pair(1, rnd.next(1, 1000)) : make_pair(rnd.next(1, 1000), 1);
        if (rnd.next(0, 1)) swap(masha, petya);
    }

    if (rnd.next(0, 1)) swap(masha.first, masha.second);
    if (rnd.next(0, 1)) swap(petya.first, petya.second);

    println(masha.first, masha.second, petya.first, petya.second);
    return 0;
}
