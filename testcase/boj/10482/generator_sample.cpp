#include "testlib.h"
#include <vector>

using namespace std;

int randomEven(int lo, int hi) {
    int a = (lo + 1) / 2;
    int b = hi / 2;
    return 2 * rnd.next(a, b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> values;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) values.push_back(randomEven(4, 60));
    } else if (mode == 1) {
        int n = rnd.next(5, 20);
        for (int i = 0; i < n; ++i) values.push_back(2 * rnd.next(2, 200));
    } else if (mode == 2) {
        int n = rnd.next(3, 12);
        int base = randomEven(4, 200);
        for (int i = 0; i < n; ++i) values.push_back(base);
    } else if (mode == 3) {
        vector<int> interesting = {4, 6, 8, 10, 12, 26, 100, 1000, 31998, 32000};
        shuffle(interesting.begin(), interesting.end());
        int n = rnd.next(1, (int)interesting.size());
        values.assign(interesting.begin(), interesting.begin() + n);
    } else if (mode == 4) {
        int n = rnd.next(8, 30);
        for (int i = 0; i < n; ++i) values.push_back(randomEven(30000, 32000));
    } else {
        int n = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                values.push_back(randomEven(4, 120));
            } else {
                values.push_back(randomEven(4, 32000));
            }
        }
    }

    println((int)values.size());
    for (int x : values) println(x);

    return 0;
}
