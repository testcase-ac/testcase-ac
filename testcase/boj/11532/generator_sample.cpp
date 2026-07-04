#include "testlib.h"

#include <vector>

using namespace std;

struct Droplet {
    int x;
    int y;
    int vx;
    int vy;
    int r;
};

void printDroplets(vector<Droplet> droplets) {
    shuffle(droplets.begin(), droplets.end());
    println(int(droplets.size()));
    for (const Droplet& d : droplets) {
        println(d.x, d.y, d.vx, d.vy, d.r);
    }
}

void addFarStationary(vector<Droplet>& droplets, int count, int startY) {
    for (int i = 0; i < count; ++i) {
        droplets.push_back({-400 + i * 200, startY + i * 350, 0, 0,
                            rnd.next(1, 20)});
    }
}

vector<Droplet> makeNoCollisionCase() {
    int n = rnd.next(2, 10);
    int spacing = rnd.next(250, 600);
    int y = rnd.next(-3000, 3000);
    int sharedVx = rnd.next(-5, 5);
    int sharedVy = rnd.next(-5, 5);

    vector<Droplet> droplets;
    for (int i = 0; i < n; ++i) {
        droplets.push_back({-4500 + i * spacing, y + (i % 3) * 250,
                            sharedVx, sharedVy, rnd.next(1, 40)});
    }
    return droplets;
}

vector<Droplet> makeSingleCollisionCase() {
    int r = rnd.next(1, 20);
    int distance = rnd.next(60, 260);
    int speed = rnd.next(2, 25);
    int y = rnd.next(-200, 200);
    int extra = rnd.next(0, 6);

    vector<Droplet> droplets;
    droplets.push_back({-distance, y, speed, 0, r});
    droplets.push_back({distance, y, 0, 0, r});
    addFarStationary(droplets, extra, 1500);
    return droplets;
}

vector<Droplet> makeChainCollisionCase() {
    int r = rnd.next(2, 10);
    int d1 = rnd.next(35, 90);
    int d2 = rnd.next(80, 220);
    int speed = rnd.next(6, 24);
    int x0 = rnd.next(-300, 300);
    int y = rnd.next(-200, 200);
    int extra = rnd.next(0, 5);

    vector<Droplet> droplets;
    droplets.push_back({x0, y, speed, 0, r});
    droplets.push_back({x0 + d1, y, 0, 0, r});
    droplets.push_back({x0 + d1 + d2, y, 0, 0, r});
    addFarStationary(droplets, extra, -2500);
    return droplets;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    if (mode == 0) {
        printDroplets(makeNoCollisionCase());
    } else if (mode == 1) {
        printDroplets(makeSingleCollisionCase());
    } else {
        printDroplets(makeChainCollisionCase());
    }

    return 0;
}
