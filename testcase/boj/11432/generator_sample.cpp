#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> randomSubset(int m, int limit) {
    vector<int> planes;
    for (int plane = 1; plane <= m; ++plane) {
        planes.push_back(plane);
    }
    shuffle(planes.begin(), planes.end());
    planes.resize(limit);
    sort(planes.begin(), planes.end());
    return planes;
}

static vector<int> neighborhood(int mode, int pilot, int m, int n) {
    if (m == 0) {
        return {};
    }

    if (mode == 0) {
        return {};
    }

    if (mode == 1) {
        int degree = rnd.next(0, min(m, 2));
        return randomSubset(m, degree);
    }

    if (mode == 2) {
        int degree = rnd.next(max(0, m - 2), m);
        return randomSubset(m, degree);
    }

    if (mode == 3) {
        int width = rnd.next(1, min(m, 4));
        vector<int> planes;
        for (int offset = 0; offset < width; ++offset) {
            planes.push_back((pilot + offset - 1) % m + 1);
        }
        sort(planes.begin(), planes.end());
        planes.erase(unique(planes.begin(), planes.end()), planes.end());
        return planes;
    }

    int shared = rnd.next(1, m);
    vector<int> planes;
    planes.push_back(shared);
    if (n > m || rnd.next(0, 1) == 1) {
        int extra = rnd.next(0, min(m - 1, 2));
        vector<int> more = randomSubset(m, extra);
        planes.insert(planes.end(), more.begin(), more.end());
    }
    sort(planes.begin(), planes.end());
    planes.erase(unique(planes.begin(), planes.end()), planes.end());
    return planes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(1, 6);
    println(k);

    for (int tc = 0; tc < k; ++tc) {
        int mode = rnd.next(0, 4);
        int m = rnd.next(0, 12);
        int n = rnd.next(0, 12);

        if (mode == 2) {
            m = rnd.next(1, 12);
            n = rnd.next(1, 12);
        } else if (mode == 3) {
            m = rnd.next(1, 10);
            n = rnd.next(1, 14);
        } else if (mode == 4) {
            m = rnd.next(1, 8);
            n = rnd.next(1, 14);
        }

        println(m, n);
        for (int pilot = 1; pilot <= n; ++pilot) {
            vector<int> planes = neighborhood(mode, pilot, m, n);
            cout << planes.size();
            for (int plane : planes) {
                cout << ' ' << plane;
            }
            cout << '\n';
        }
    }

    return 0;
}
