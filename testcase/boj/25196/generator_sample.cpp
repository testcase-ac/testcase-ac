#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Bird {
    int v;
    int s;
    int e;
};

Bird randomBird(int minV, int maxV) {
    int v = rnd.next(minV, maxV);
    int s = rnd.next(0, v - 1);
    int e = rnd.next(s, v - 1);
    return {v, s, e};
}

Bird pointBird(int minV, int maxV) {
    int v = rnd.next(minV, maxV);
    int s = rnd.next(0, v - 1);
    return {v, s, s};
}

Bird wideBird(int minV, int maxV) {
    int v = rnd.next(minV, maxV);
    int s = rnd.next(0, max(0, v / 3));
    int e = rnd.next(max(s, 2 * v / 3), v - 1);
    return {v, s, e};
}

void printBird(const Bird& bird) {
    println(bird.v, bird.s, bird.e);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Bird> birds;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int v = rnd.next(1, 15);
        int t = rnd.next(0, v - 1);
        for (int i = 0; i < 3; ++i) {
            int s = rnd.next(0, t);
            int e = rnd.next(t, v - 1);
            birds.push_back({v, s, e});
        }
    } else if (mode == 1) {
        int v = rnd.next(3, 20);
        vector<int> starts;
        for (int i = 0; i < v; ++i) starts.push_back(i);
        shuffle(starts.begin(), starts.end());
        sort(starts.begin(), starts.begin() + 3);
        for (int i = 0; i < 3; ++i) {
            birds.push_back({v, starts[i], starts[i]});
        }
    } else if (mode == 2) {
        for (int i = 0; i < 3; ++i) birds.push_back(pointBird(2, 35));
    } else if (mode == 3) {
        for (int i = 0; i < 3; ++i) birds.push_back(wideBird(2, 40));
    } else if (mode == 4) {
        for (int i = 0; i < 3; ++i) birds.push_back(randomBird(1, 60));
    } else {
        birds.push_back(randomBird(1500, 2000));
        birds.push_back(pointBird(1500, 2000));
        birds.push_back(wideBird(1500, 2000));
    }

    shuffle(birds.begin(), birds.end());
    for (const Bird& bird : birds) printBird(bird);

    return 0;
}
