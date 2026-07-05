#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> uniqueSorted(vector<int> values) {
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    return values;
}

static vector<int> randomIndices(int n, int lo, int hi) {
    vector<int> pool;
    for (int k = lo; k <= hi; ++k) {
        if (k != 3 && k != 4) {
            pool.push_back(k);
        }
    }
    shuffle(pool.begin(), pool.end());
    pool.resize(n);
    return uniqueSorted(pool);
}

static vector<int> withTriangularSquareAnchors(vector<int> extra) {
    extra.push_back(3);
    extra.push_back(4);
    return uniqueSorted(extra);
}

static vector<int> buildIndices(int mode) {
    if (mode == 0) {
        int start = rnd.next(3, 18);
        int n = rnd.next(2, min(8, 1001 - start));
        vector<int> indices;
        for (int i = 0; i < n; ++i) {
            int k = start + i;
            if (k != 3 && k != 4) {
                indices.push_back(k);
            }
        }
        return withTriangularSquareAnchors(indices);
    }

    if (mode == 1) {
        vector<int> base = {5, 6, 8, 10, 13, 36, 124};
        shuffle(base.begin(), base.end());
        int n = rnd.next(0, min<int>(4, base.size()));
        base.resize(n);
        return withTriangularSquareAnchors(base);
    }

    if (mode == 2) {
        int n = rnd.next(0, 5);
        return withTriangularSquareAnchors(randomIndices(n, 3, 60));
    }

    if (mode == 3) {
        int n = rnd.next(0, 4);
        return withTriangularSquareAnchors(randomIndices(n, 80, 1000));
    }

    int n = rnd.next(0, 7);
    vector<int> indices = randomIndices(n, 3, 120);
    indices.push_back(rnd.next(500, 1000));
    return withTriangularSquareAnchors(indices);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int instances = rnd.next(1, 5);
    for (int tc = 0; tc < instances; ++tc) {
        vector<int> indices = buildIndices(rnd.next(0, 4));
        println(static_cast<int>(indices.size()));
        println(indices);

        int startMode = rnd.next(0, 3);
        int s;
        if (startMode == 0) {
            s = rnd.next(1, 30);
        } else if (startMode == 1) {
            s = rnd.next(31, 1000);
        } else if (startMode == 2) {
            s = rnd.next(1001, 5000);
        } else {
            s = rnd.next(5001, 10000);
        }
        println(s);
    }

    println(0);
    return 0;
}
