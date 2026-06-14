#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

const int MAX_A = 1000000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> values;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        values.insert(rnd.next(1, 12));
    } else if (mode == 1) {
        int n = rnd.next(2, 10);
        while ((int)values.size() < n) {
            values.insert(rnd.next(MAX_A - 40, MAX_A));
        }
    } else if (mode == 2) {
        int limit = rnd.next(8, 40);
        int n = rnd.next(2, limit);
        while ((int)values.size() < n) {
            values.insert(rnd.next(1, limit));
        }
    } else {
        int pairs = rnd.next(1, 8);
        for (int k = 0; k < pairs; ++k) {
            int x = rnd.next(1, 700);
            int y = rnd.next(1, 700);
            int target = 2 * x * y + y * y;
            if (target <= MAX_A) {
                values.insert(x);
                values.insert(target);
            }
        }

        int fillerTarget = rnd.next((int)values.size(), (int)values.size() + 12);
        while ((int)values.size() < fillerTarget) {
            int band = rnd.next(0, 3);
            if (band == 0) {
                values.insert(rnd.next(1, 60));
            } else if (band == 1) {
                values.insert(rnd.next(61, 5000));
            } else {
                values.insert(rnd.next(MAX_A - 1000, MAX_A));
            }
        }
    }

    vector<int> a(values.begin(), values.end());
    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
