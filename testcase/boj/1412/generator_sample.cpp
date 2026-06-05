#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 15 : 12);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i;
    shuffle(p.begin(), p.end());

    vector<string> a(n, string(n, 'N'));

    if (mode == 0) {
        double prob = rnd.next(0.0, 0.25);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < prob) {
                    a[i][j] = a[j][i] = 'Y';
                }
            }
        }
    } else if (mode == 1) {
        double prob = rnd.next(0.45, 1.0);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < prob) {
                    a[i][j] = a[j][i] = 'Y';
                }
            }
        }
    } else if (mode == 2) {
        double prob = rnd.next(0.15, 0.7);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < prob) {
                    a[p[i]][p[j]] = 'Y';
                }
            }
        }
    } else if (mode == 3) {
        int cycle = rnd.next(2, n);
        for (int i = 0; i < cycle; ++i) {
            a[p[i]][p[(i + 1) % cycle]] = 'Y';
        }
        double extraProb = rnd.next(0.0, 0.25);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && a[i][j] == 'N' && rnd.next() < extraProb) {
                    a[i][j] = 'Y';
                }
            }
        }
    } else if (mode == 4) {
        double bidirProb = rnd.next(0.15, 0.55);
        double oneWayProb = rnd.next(0.1, 0.55);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < bidirProb) {
                    a[p[i]][p[j]] = a[p[j]][p[i]] = 'Y';
                } else if (rnd.next() < oneWayProb) {
                    a[p[i]][p[j]] = 'Y';
                }
            }
        }
    } else {
        double pairProb = rnd.next(0.3, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() >= pairProb) continue;
                int type = rnd.next(0, 2);
                if (type == 0) {
                    a[i][j] = a[j][i] = 'Y';
                } else if (type == 1) {
                    a[i][j] = 'Y';
                } else {
                    a[j][i] = 'Y';
                }
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
