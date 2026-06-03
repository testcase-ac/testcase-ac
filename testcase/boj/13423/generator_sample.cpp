#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MIN_X = -100000000;
const int MAX_X = 100000000;

bool inRange(int x) {
    return MIN_X <= x && x <= MAX_X;
}

void addIfValid(set<int>& values, int x) {
    if (inRange(x)) values.insert(x);
}

vector<int> buildCase() {
    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 18);
    set<int> values;

    if (mode == 0) {
        int step = rnd.next(1, 20);
        int first = rnd.next(-200, 200 - step * (n - 1));
        for (int i = 0; i < n; ++i) values.insert(first + step * i);
    } else if (mode == 1) {
        int step = rnd.next(1, 15);
        int first = rnd.next(-200, 200 - step * 23);
        for (int i = 0; i < 24 && (int)values.size() < n; ++i) {
            if (rnd.next(0, 3) != 0) values.insert(first + step * i);
        }
    } else if (mode == 2) {
        int center = rnd.next(-50, 50);
        int radius = rnd.next(8, 40);
        for (int d = 1; d <= radius && (int)values.size() + 2 <= n; ++d) {
            if (rnd.next(0, 2) == 0) {
                addIfValid(values, center - d);
                addIfValid(values, center + d);
            }
        }
        addIfValid(values, center);
    } else if (mode == 3) {
        int base = rnd.next(0, 1) == 0 ? MIN_X : MAX_X;
        int direction = base == MIN_X ? 1 : -1;
        while ((int)values.size() < n) {
            values.insert(base + direction * rnd.next(0, 500));
        }
    } else {
        while ((int)values.size() < n) {
            int band = rnd.next(0, 2);
            if (band == 0) values.insert(rnd.next(-30, 30));
            else if (band == 1) values.insert(rnd.next(-1000, -900));
            else values.insert(rnd.next(900, 1000));
        }
    }

    while ((int)values.size() < n) values.insert(rnd.next(-200, 200));

    vector<int> result(values.begin(), values.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        vector<int> x = buildCase();
        println((int)x.size());
        println(x);
    }

    return 0;
}
