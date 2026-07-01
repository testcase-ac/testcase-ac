#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 18);
    } else {
        n = rnd.next(10, 70);
    }

    vector<int> smallerBefore(n + 1);
    for (int slot = 2; slot <= n; ++slot) {
        if (mode == 0) {
            smallerBefore[slot] = rnd.next(0, slot - 1);
        } else if (mode == 1) {
            smallerBefore[slot] = 0;
        } else if (mode == 2) {
            smallerBefore[slot] = slot - 1;
        } else if (mode == 3) {
            smallerBefore[slot] = rnd.next() < 0.70 ? 0 : rnd.next(0, slot - 1);
        } else if (mode == 4) {
            smallerBefore[slot] = rnd.next() < 0.70 ? slot - 1 : rnd.next(0, slot - 1);
        } else if (mode == 5) {
            int period = rnd.next(2, 6);
            smallerBefore[slot] = (slot % period == 0) ? rnd.next(0, slot - 1) : (slot - 1) / 2;
        } else {
            smallerBefore[slot] = rnd.wnext(slot, rnd.next(-3, 3));
        }
    }

    println(n);
    for (int slot = 2; slot <= n; ++slot) {
        println(smallerBefore[slot]);
    }

    return 0;
}
