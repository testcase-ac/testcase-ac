#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int normDish(int x, int n) {
    x %= n;
    if (x <= 0) x += n;
    return x;
}

vector<int> makeUniquePool(int n, int count) {
    vector<int> dishes;
    for (int i = 0; i < count; ++i) dishes.push_back(normDish(rnd.next(1, n), n));
    return dishes;
}

vector<int> randomFromPool(int length, const vector<int>& pool) {
    vector<int> result;
    for (int i = 0; i < length; ++i) result.push_back(rnd.any(pool));
    return result;
}

vector<int> clusterSequence(int length, int n, int center, int radius) {
    vector<int> result;
    for (int i = 0; i < length; ++i) {
        int offset = rnd.next(-radius, radius);
        result.push_back(normDish(center + offset, n));
    }
    return result;
}

void printPerson(const vector<int>& dishes) {
    printf("%d", int(dishes.size()));
    for (int dish : dishes) printf(" %d", dish);
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<vector<int>> wants(3);

    if (mode == 0) {
        n = rnd.any(vector<int>{3, 6, 9, 12});
        for (int person = 0; person < 3; ++person) {
            int length = rnd.next(1, 4);
            wants[person] = randomFromPool(length, makeUniquePool(n, rnd.next(1, min(n, 4))));
        }
    } else if (mode == 1) {
        n = 3 * rnd.next(1, 8);
        for (int person = 0; person < 3; ++person) {
            int repeated = rnd.next(1, n);
            wants[person].assign(rnd.next(8, 18), repeated);
        }
    } else if (mode == 2) {
        int k = rnd.next(2, 12);
        n = 3 * k;
        for (int person = 0; person < 3; ++person) {
            int seat = person * k + 1;
            vector<int> pool = {normDish(seat - 1, n), seat, normDish(seat + 1, n), normDish(seat + k, n)};
            wants[person] = randomFromPool(rnd.next(5, 15), pool);
        }
    } else if (mode == 3) {
        n = 3 * rnd.next(2, 20);
        vector<int> pool = {1, 2, n - 1, n};
        for (int person = 0; person < 3; ++person) {
            wants[person] = randomFromPool(rnd.next(6, 20), pool);
            if (rnd.next(0, 1)) reverse(wants[person].begin(), wants[person].end());
        }
    } else if (mode == 4) {
        n = 3 * rnd.next(3, 25);
        for (int person = 0; person < 3; ++person) {
            wants[person] = clusterSequence(rnd.next(10, 30), n, rnd.next(1, n), rnd.next(1, min(5, n / 2)));
        }
    } else {
        n = 3 * rnd.next(20, 60);
        for (int person = 0; person < 3; ++person) {
            int length = rnd.next(40, 100);
            vector<int> pool = makeUniquePool(n, rnd.next(3, 12));
            wants[person] = randomFromPool(length, pool);
        }
    }

    println(n);
    for (const vector<int>& dishes : wants) printPerson(dishes);

    return 0;
}
