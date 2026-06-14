#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Box {
    int lx;
    int ly;
    int lz;
    int px;
    int py;
};

int randSize(int limit) {
    return rnd.next(1, limit);
}

int randPos(int limit, int size) {
    return rnd.next(0, limit - size);
}

Box randomBox(int Lx, int Ly, int maxHeight = 30) {
    int lx = randSize(Lx);
    int ly = randSize(Ly);
    return {lx, ly, rnd.next(1, maxHeight), randPos(Lx, lx), randPos(Ly, ly)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int Lx = rnd.next(3, 12);
    int Ly = rnd.next(3, 12);
    vector<Box> boxes;

    if (mode == 0) {
        Lx = rnd.next(1, 6);
        Ly = rnd.next(1, 6);
        int n = rnd.next(1, 10);
        int lx = rnd.next(1, Lx);
        int ly = rnd.next(1, Ly);
        int px = randPos(Lx, lx);
        int py = randPos(Ly, ly);
        for (int i = 0; i < n; ++i) {
            boxes.push_back({lx, ly, rnd.next(1, 100000), px, py});
        }
    } else if (mode == 1) {
        Lx = rnd.next(4, 15);
        Ly = rnd.next(4, 15);
        int n = rnd.next(4, 12);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                int lx = rnd.next(1, Lx);
                int py = rnd.next(0, Ly - 1);
                boxes.push_back({lx, 1, rnd.next(1, 40), randPos(Lx, lx), py});
            } else {
                int ly = rnd.next(1, Ly);
                int px = rnd.next(0, Lx - 1);
                boxes.push_back({1, ly, rnd.next(1, 40), px, randPos(Ly, ly)});
            }
        }
    } else if (mode == 2) {
        Lx = rnd.next(6, 20);
        Ly = rnd.next(3, 8);
        int n = rnd.next(3, 8);
        int width = rnd.next(2, min(5, Lx));
        for (int i = 0; i < n; ++i) {
            int px = min(Lx - width, i);
            int ly = rnd.next(1, Ly);
            boxes.push_back({width, ly, rnd.next(1, 50), px, randPos(Ly, ly)});
        }
    } else if (mode == 3) {
        Lx = rnd.next(6, 20);
        Ly = rnd.next(6, 20);
        int splitX = rnd.next(1, Lx - 1);
        int splitY = rnd.next(1, Ly - 1);
        boxes.push_back({splitX, splitY, rnd.next(1, 60), 0, 0});
        boxes.push_back({Lx - splitX, splitY, rnd.next(1, 60), splitX, 0});
        boxes.push_back({splitX, Ly - splitY, rnd.next(1, 60), 0, splitY});
        boxes.push_back({Lx - splitX, Ly - splitY, rnd.next(1, 60), splitX, splitY});
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) {
            boxes.push_back(randomBox(Lx, Ly, 60));
        }
        shuffle(boxes.begin(), boxes.end());
    } else if (mode == 4) {
        Lx = rnd.next(1, 1000);
        Ly = rnd.next(1, 1000);
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int lx = rnd.next(1, Lx);
            int ly = rnd.next(1, Ly);
            int px = rnd.next(0, 1) ? 0 : Lx - lx;
            int py = rnd.next(0, 1) ? 0 : Ly - ly;
            boxes.push_back({lx, ly, rnd.next(99950, 100000), px, py});
        }
    } else {
        int n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            boxes.push_back(randomBox(Lx, Ly, 100));
        }
    }

    println(Lx, Ly, static_cast<int>(boxes.size()));
    for (const Box& box : boxes) {
        println(box.lx, box.ly, box.lz, box.px, box.py);
    }

    return 0;
}
