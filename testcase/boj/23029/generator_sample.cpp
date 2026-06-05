#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 6) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(4, 30);
    }

    vector<int> food(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) food[i] = rnd.next(0, 5);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) food[i] = rnd.next(0, 1) ? rnd.next(0, 3) : 0;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) food[i] = rnd.next(990, 1000);
    } else if (mode == 3) {
        int high = rnd.next(700, 1000);
        int low = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) food[i] = (i % 2 == 0 ? high : low);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) food[i] = 2 * rnd.next(0, 500) + 1;
    } else if (mode == 5) {
        int block = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            if ((i / block) % 2 == 0) {
                food[i] = rnd.next(400, 1000);
            } else {
                food[i] = rnd.next(0, 60);
            }
        }
    } else {
        int limit = rnd.next(20, 1000);
        for (int i = 0; i < n; ++i) food[i] = rnd.next(0, limit);
    }

    println(n);
    for (int x : food) println(x);

    return 0;
}
