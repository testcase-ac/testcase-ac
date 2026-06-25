#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<string> adj(n, string(n, 'N'));

    if (mode == 0) {
        double density = rnd.next(0.05, 0.45);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < density) {
                    adj[i][j] = 'Y';
                }
            }
        }
    } else if (mode == 1) {
        int cycleLen = rnd.next(2, n);
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < cycleLen; ++i) {
            adj[order[i]][order[(i + 1) % cycleLen]] = 'Y';
        }
        double extraProb = rnd.next(0.0, 0.25);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next() < extraProb) {
                    adj[i][j] = 'Y';
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int to = rnd.next(0, n - 2);
            if (to >= i) {
                ++to;
            }
            adj[i][to] = 'Y';
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next() < 0.12) {
                    adj[i][j] = 'Y';
                }
            }
        }
    } else if (mode == 3) {
        double density = rnd.next(0.55, 0.95);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next() < density) {
                    adj[i][j] = 'Y';
                }
            }
        }
    } else if (mode == 4) {
        int left = rnd.next(1, n - 1);
        double forwardProb = rnd.next(0.25, 0.8);
        double backwardProb = rnd.next(0.05, 0.45);
        for (int i = 0; i < left; ++i) {
            for (int j = left; j < n; ++j) {
                if (rnd.next() < forwardProb) {
                    adj[i][j] = 'Y';
                }
                if (rnd.next() < backwardProb) {
                    adj[j][i] = 'Y';
                }
            }
        }
    } else {
        double density = rnd.next(0.10, 0.70);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next() < density) {
                    adj[i][j] = 'Y';
                }
            }
        }
    }

    int k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = rnd.next(2, 8);
    } else if (kMode == 1) {
        k = rnd.next(9, 60);
    } else if (kMode == 2) {
        k = rnd.next(100, 2000);
    } else if (kMode == 3) {
        k = 1000000;
    } else {
        k = rnd.next(2, 1000000);
    }

    int m;
    int mMode = rnd.next(0, 4);
    if (mMode == 0) {
        m = 1;
    } else if (mMode == 1) {
        m = rnd.next(2, 20);
    } else if (mMode == 2) {
        m = rnd.next(21, 1000);
    } else if (mMode == 3) {
        m = 1000000000;
    } else {
        m = rnd.next(1001, 1000000000);
    }

    println(n, k, m);
    for (const string& row : adj) {
        println(row);
    }

    return 0;
}
