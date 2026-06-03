#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedWeight(int value) {
    return max(0, min(150000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 5) {
        n = rnd.next(10, 18);
    } else {
        n = rnd.next(3, 12);
    }

    vector<vector<int>> w(n, vector<int>(n, 0));

    if (mode == 0) {
        int value = rnd.any(vector<int>{0, 1, 149999, 150000, rnd.next(0, 150000)});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    w[i][j] = value;
                }
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(0, 149950);
        int span = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    w[i][j] = base + rnd.next(0, span);
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    w[i][j] = rnd.next(0, 150000);
                }
            }
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        int low = rnd.next(0, 1000);
        int middle = rnd.next(50000, 90000);
        int high = rnd.next(140000, 150000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                bool sameBlock = (i < split) == (j < split);
                if (sameBlock) {
                    w[i][j] = boundedWeight(low + rnd.next(0, 30));
                } else if (i < split) {
                    w[i][j] = boundedWeight(middle + rnd.next(-200, 200));
                } else {
                    w[i][j] = boundedWeight(high - rnd.next(0, 500));
                }
            }
        }
    } else if (mode == 4) {
        int cycleBase = rnd.next(1, 1000);
        int noiseBase = rnd.next(80000, 150000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    w[i][j] = boundedWeight(noiseBase - rnd.next(0, 1000));
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            w[i][(i + 1) % n] = boundedWeight(cycleBase + rnd.next(0, 20));
        }
        int extra = rnd.next(0, n);
        for (int k = 0; k < extra; ++k) {
            int from = rnd.next(n);
            int to = rnd.next(n - 1);
            if (to >= from) {
                ++to;
            }
            w[from][to] = boundedWeight(cycleBase + rnd.next(0, 100));
        }
    } else {
        vector<int> values = {0, 1, 2, 149998, 149999, 150000};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    w[i][j] = rnd.any(values);
                }
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(w[i]);
    }

    return 0;
}
