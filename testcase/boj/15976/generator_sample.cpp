#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_INDEX = 1000000000 - 1;
const int MAX_VALUE = 3000;
const int MAX_SHIFT = 1000000000;

vector<int> uniqueSortedIndices(int count, int lo, int hi) {
    vector<int> values;
    for (int i = lo; i <= hi; ++i) values.push_back(i);
    shuffle(values.begin(), values.end());
    values.resize(count);
    sort(values.begin(), values.end());
    return values;
}

vector<int> randomValues(int count, int mode) {
    vector<int> values(count);
    for (int i = 0; i < count; ++i) {
        if (mode == 0) {
            values[i] = rnd.next(1, 9);
        } else if (mode == 1) {
            values[i] = rnd.next(MAX_VALUE - 20, MAX_VALUE);
        } else {
            values[i] = rnd.next(1, MAX_VALUE);
        }
    }
    return values;
}

void printSequence(const vector<int>& indices, const vector<int>& values) {
    println((int)indices.size());
    for (int i = 0; i < (int)indices.size(); ++i) {
        println(indices[i], values[i]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 4 ? 80 : 24);
    int m = rnd.next(1, mode == 4 ? 80 : 24);
    vector<int> xs, ys;
    int a = 0, b = 0;

    if (mode == 0) {
        int hi = rnd.next(max(n, m), 70);
        xs = uniqueSortedIndices(n, 0, hi);
        ys = uniqueSortedIndices(m, 0, hi);
        a = rnd.next(-15, 3);
        b = rnd.next(max(a, -3), 15);
    } else if (mode == 1) {
        int xBase = rnd.next(0, 200);
        int shift = rnd.next(-30, 30);
        int yBase = max(0, xBase + shift);
        int span = rnd.next(max(n, m) + 5, 90);
        xs = uniqueSortedIndices(n, xBase, min(MAX_INDEX, xBase + span));
        ys = uniqueSortedIndices(m, yBase, min(MAX_INDEX, yBase + span));
        a = shift - rnd.next(0, 8);
        b = shift + rnd.next(0, 8);
    } else if (mode == 2) {
        int span = rnd.next(max(n, m) + 10, 120);
        xs = uniqueSortedIndices(n, 0, span);
        ys = uniqueSortedIndices(m, MAX_INDEX - span, MAX_INDEX);
        a = rnd.next(MAX_SHIFT - 200, MAX_SHIFT);
        b = MAX_SHIFT;
    } else if (mode == 3) {
        int span = rnd.next(max(n, m) + 10, 120);
        xs = uniqueSortedIndices(n, MAX_INDEX - span, MAX_INDEX);
        ys = uniqueSortedIndices(m, 0, span);
        a = -MAX_SHIFT;
        b = rnd.next(-MAX_SHIFT, -MAX_SHIFT + 200);
    } else {
        int step = rnd.next(2, 11);
        int offset = rnd.next(0, step - 1);
        for (int i = 0; i < n; ++i) xs.push_back(offset + i * step);
        int yOffset = rnd.next(0, step - 1);
        for (int i = 0; i < m; ++i) ys.push_back(yOffset + i * step);
        a = rnd.next(-40, 0);
        b = rnd.next(0, 40);
    }

    int valueMode = rnd.next(0, 2);
    vector<int> xValues = randomValues(n, valueMode);
    vector<int> yValues = randomValues(m, rnd.next(0, 2));

    printSequence(xs, xValues);
    printSequence(ys, yValues);
    println(a);
    println(b);

    return 0;
}
