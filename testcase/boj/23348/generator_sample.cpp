#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

array<int, 3> randomTriple(int lo, int hi) {
    return {rnd.next(lo, hi), rnd.next(lo, hi), rnd.next(lo, hi)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int weightMode = rnd.next(0, 5);
    array<int, 3> weight;
    if (weightMode == 0) {
        weight = {0, 0, 0};
    } else if (weightMode == 1) {
        weight = {1000, 1000, 1000};
    } else if (weightMode == 2) {
        int x = rnd.next(0, 1000);
        weight = {x, x, x};
    } else if (weightMode == 3) {
        weight = {rnd.next(0, 3), rnd.next(0, 3), rnd.next(0, 3)};
    } else if (weightMode == 4) {
        weight = {rnd.next(997, 1000), rnd.next(997, 1000), rnd.next(997, 1000)};
    } else {
        weight = randomTriple(0, 1000);
    }

    int nMode = rnd.next(0, 4);
    int n;
    if (nMode == 0) {
        n = 1;
    } else if (nMode == 1) {
        n = rnd.next(2, 4);
    } else if (nMode == 2) {
        n = rnd.next(5, 9);
    } else if (nMode == 3) {
        n = rnd.next(10, 20);
    } else {
        n = rnd.next(21, 40);
    }

    int countMode = rnd.next(0, 5);
    vector<array<int, 3>> rows;
    rows.reserve(3 * n);
    for (int club = 0; club < n; ++club) {
        array<int, 3> clubBase = randomTriple(0, 100);
        if (countMode == 2) {
            clubBase = randomTriple(0, 3);
        } else if (countMode == 3) {
            clubBase = randomTriple(97, 100);
        }

        for (int member = 0; member < 3; ++member) {
            array<int, 3> count;
            if (countMode == 0) {
                count = {0, 0, 0};
            } else if (countMode == 1) {
                count = {100, 100, 100};
            } else if (countMode == 4) {
                count = clubBase;
            } else if (countMode == 5) {
                int active = rnd.next(0, 2);
                count = {0, 0, 0};
                count[active] = rnd.next(0, 100);
            } else {
                count = clubBase;
                for (int skill = 0; skill < 3; ++skill) {
                    int delta = rnd.next(-2, 2);
                    count[skill] = max(0, min(100, count[skill] + delta));
                }
            }
            rows.push_back(count);
        }
    }

    println(weight[0], weight[1], weight[2]);
    println(n);
    for (const auto& row : rows) {
        println(row[0], row[1], row[2]);
    }

    return 0;
}
