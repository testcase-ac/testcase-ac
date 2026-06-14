#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> compactValues(int n, int mode) {
    vector<int> values;
    values.reserve(n);

    if (mode == 0) {
        int start = rnd.next(1, 30);
        int step = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            values.push_back(start + i * step);
        }
    } else if (mode == 1) {
        int x = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(1, i % 3 == 0 ? 25 : 6);
            values.push_back(x);
        }
    } else {
        int low = rnd.next(1, 100);
        int high = 999999999 - rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                values.push_back(low++);
            } else {
                values.push_back(high--);
            }
        }
        sort(values.begin(), values.end());
    }

    return values;
}

static vector<int> orderDonggyu(vector<int> values, int mode) {
    int n = (int)values.size();
    vector<int> ordered;
    ordered.reserve(n);

    if (mode == 0) {
        return values;
    }
    if (mode == 1) {
        reverse(values.begin(), values.end());
        return values;
    }
    if (mode == 2) {
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            ordered.push_back(values[lo++]);
            if (lo <= hi) ordered.push_back(values[hi--]);
        }
        return ordered;
    }
    if (mode == 3) {
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            ordered.push_back(values[hi--]);
            if (lo <= hi) ordered.push_back(values[lo++]);
        }
        return ordered;
    }
    if (mode == 4) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < split; ++i) ordered.push_back(values[i]);
        for (int i = n - 1; i >= split; --i) ordered.push_back(values[i]);
        return ordered;
    }
    if (mode == 5) {
        int split = rnd.next(1, n - 1);
        for (int i = split - 1; i >= 0; --i) ordered.push_back(values[i]);
        for (int i = split; i < n; ++i) ordered.push_back(values[i]);
        return ordered;
    }

    shuffle(values.begin(), values.end());
    return values;
}

static vector<int> orderSanggeun(vector<int> values, int mode) {
    if (mode == 0) {
        return values;
    }
    if (mode == 1) {
        reverse(values.begin(), values.end());
        return values;
    }
    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n = rnd.next(2, 18);
    if (sizeMode >= 7) n = rnd.next(19, 80);
    if (sizeMode == 9) n = rnd.next(100, 400);

    int valueMode = rnd.next(0, 2);
    vector<int> donggyu = compactValues(n, valueMode);
    vector<int> sanggeun = compactValues(n, rnd.next(0, 2));

    donggyu = orderDonggyu(donggyu, rnd.next(0, 6));
    sanggeun = orderSanggeun(sanggeun, rnd.next(0, 2));

    println(n);
    println(donggyu);
    println(sanggeun);

    return 0;
}
