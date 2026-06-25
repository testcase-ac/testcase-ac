#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomRegions(int n, int minSize, int maxSize) {
    vector<int> regions;
    for (int i = 1; i <= n; ++i) {
        regions.push_back(i);
    }
    shuffle(regions.begin(), regions.end());
    int size = rnd.next(minSize, maxSize);
    regions.resize(size);
    sort(regions.begin(), regions.end());
    return regions;
}

void printEquipment(const vector<vector<int>>& equipment) {
    for (const vector<int>& regions : equipment) {
        printf("%d", static_cast<int>(regions.size()));
        for (int region : regions) {
            printf(" %d", region);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    int k = rnd.next(1, 10);
    vector<vector<int>> equipment;

    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        int m = rnd.next(1, n);
        vector<int> labels;
        for (int i = 1; i <= n; ++i) {
            labels.push_back(i);
        }
        shuffle(labels.begin(), labels.end());
        for (int i = 0; i < m; ++i) {
            equipment.push_back(vector<int>{labels[i]});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        int m = rnd.next(1, min(n, 10));
        vector<int> order;
        for (int i = 1; i <= n; ++i) {
            order.push_back(i);
        }
        shuffle(order.begin(), order.end());
        for (int len = 1; len <= m; ++len) {
            vector<int> regions(order.begin(), order.begin() + len);
            sort(regions.begin(), regions.end());
            equipment.push_back(regions);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 10);
        int m = rnd.next(1, 10);
        int maxSize = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            equipment.push_back(randomRegions(n, 1, maxSize));
        }
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        int m = rnd.next(1, min(n, 10));
        for (int missing = 1; missing <= m; ++missing) {
            vector<int> regions;
            for (int region = 1; region <= n; ++region) {
                if (region != missing) {
                    regions.push_back(region);
                }
            }
            equipment.push_back(regions);
        }
    } else {
        n = 10;
        k = rnd.next(2, 10);
        int m = 10;
        for (int i = 0; i < m; ++i) {
            int minSize = (i % 3 == 0 ? 1 : 2);
            equipment.push_back(randomRegions(n, minSize, n));
        }
    }

    vector<int> colors;
    int colorMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (colorMode == 0) {
            colors.push_back(1);
        } else if (colorMode == 1) {
            colors.push_back((i % k) + 1);
        } else if (colorMode == 2) {
            colors.push_back(rnd.next(1, min(k, 3)));
        } else {
            colors.push_back(rnd.next(1, k));
        }
    }
    if (colorMode == 1 && rnd.next(0, 1) == 1) {
        shuffle(colors.begin(), colors.end());
    }

    println(n, k, static_cast<int>(equipment.size()));
    println(colors);
    printEquipment(equipment);

    return 0;
}
