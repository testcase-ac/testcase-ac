#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(13, 25);
    }

    const long long maxTime = (1LL << 31) - 1;
    vector<long long> points(2 * n + 2);

    long long cursor = 0;
    int gapLimit = rnd.next(1, 20);
    for (int i = 1; i < (int)points.size(); ++i) {
        cursor += rnd.next(1, gapLimit);
        points[i] = cursor;
    }

    long long offset = 0;
    if (mode == 4) {
        offset = maxTime - points.back() - rnd.next(0, 20);
    } else if (mode == 5) {
        offset = rnd.next(0, 1000);
    }

    int peopleMode = rnd.next(0, 3);

    println(n);
    for (int i = 0; i < n; ++i) {
        long long start = offset + points[2 * i];
        long long finish = offset + points[2 * i + (n == 1 ? 1 : 3)];

        int people;
        if (peopleMode == 0) {
            people = rnd.next(1, 20);
        } else if (peopleMode == 1) {
            people = rnd.next(900, 1000);
        } else if (peopleMode == 2) {
            people = (i % 2 == 0) ? rnd.next(700, 1000) : rnd.next(1, 100);
        } else {
            people = rnd.next(1, 1000);
        }

        println(start, finish, people);
    }

    return 0;
}
