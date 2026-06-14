#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> distinctValues(int n, int lo = 1, int step = 1) {
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = lo + i * step;
    }
    return values;
}

vector<int> makeMatchingPhoto(int n) {
    vector<int> values = distinctValues(n, rnd.next(1, 1000), rnd.next(1, 7));
    shuffle(values.begin(), values.end());

    int you = rnd.next(1, n - 2);
    int alice = rnd.next(0, you - 1);
    int bob = rnd.next(you + 1, n - 1);

    vector<int> special = distinctValues(3, 1000000000 - 100, rnd.next(1, 9));
    sort(special.begin(), special.end());
    values[you] = special[0];
    values[alice] = special[1];
    values[bob] = special[2];

    return values;
}

vector<int> makeMonotonePhoto(int n, bool increasing) {
    vector<int> values = distinctValues(n, rnd.next(1, 1000), rnd.next(1, 11));
    if (!increasing) {
        reverse(values.begin(), values.end());
    }
    return values;
}

vector<int> makeAlmostMatchingPhoto(int n) {
    vector<int> values = distinctValues(n, rnd.next(1, 1000), rnd.next(1, 5));
    shuffle(values.begin(), values.end());

    int you = rnd.next(1, n - 2);
    int left = rnd.next(0, you - 1);
    int right = rnd.next(you + 1, n - 1);

    int base = 500000000 + rnd.next(0, 1000);
    values[left] = base + 2;
    values[you] = base + 1;
    values[right] = base;

    return values;
}

vector<int> makeRandomPhoto(int n) {
    int lo = rnd.next(1, 100000);
    int step = rnd.next(1, 1000);
    vector<int> values = distinctValues(n, lo, step);
    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(4, 12);
    println(k);

    for (int photo = 0; photo < k; ++photo) {
        int mode = rnd.next(0, 4);
        int n;
        if (photo == 0) {
            n = 3;
        } else if (rnd.next(0, 9) == 0) {
            n = rnd.next(40, 120);
        } else {
            n = rnd.next(3, 18);
        }

        vector<int> heights;
        if (mode == 0) {
            heights = makeMatchingPhoto(n);
        } else if (mode == 1) {
            heights = makeMonotonePhoto(n, true);
        } else if (mode == 2) {
            heights = makeMonotonePhoto(n, false);
        } else if (mode == 3) {
            heights = makeAlmostMatchingPhoto(n);
        } else {
            heights = makeRandomPhoto(n);
        }

        println(n);
        println(heights);
    }

    return 0;
}
