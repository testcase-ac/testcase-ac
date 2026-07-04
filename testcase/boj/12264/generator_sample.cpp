#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string massToken(int value, bool trimZeros) {
    ostringstream out;
    out << "0." << setw(5) << setfill('0') << value;
    string token = out.str();
    if (trimZeros) {
        while (token.size() > 3 && token.back() == '0') {
            token.pop_back();
        }
    }
    return token;
}

int reserveMass(set<int>& used, int lo, int hi) {
    vector<int> candidates;
    for (int value = lo; value <= hi; ++value) {
        if (!used.count(value)) {
            candidates.push_back(value);
        }
    }
    ensuref(!candidates.empty(), "no available mass in requested range");
    int value = rnd.any(candidates);
    used.insert(value);
    return value;
}

void maybeShuffle(vector<int>& values) {
    int order = rnd.next(0, 2);
    if (order == 0) {
        sort(values.begin(), values.end());
    } else if (order == 1) {
        sort(values.rbegin(), values.rend());
    } else {
        shuffle(values.begin(), values.end());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 10);
        vector<int> naomi;
        vector<int> ken;
        set<int> used;

        if (mode == 0) {
            n = rnd.next(1, 4);
            for (int i = 0; i < n; ++i) {
                naomi.push_back(reserveMass(used, 1, 25000));
                ken.push_back(reserveMass(used, 75000, 99999));
            }
        } else if (mode == 1) {
            n = rnd.next(1, 4);
            for (int i = 0; i < n; ++i) {
                naomi.push_back(reserveMass(used, 75000, 99999));
                ken.push_back(reserveMass(used, 1, 25000));
            }
        } else if (mode == 2) {
            n = rnd.next(2, 10);
            int start = rnd.next(1000, 80000);
            int step = rnd.next(2, 900);
            for (int i = 0; i < 2 * n; ++i) {
                int value = min(99999, start + i * step);
                used.insert(value);
                if (i % 2 == 0) {
                    naomi.push_back(value);
                } else {
                    ken.push_back(value);
                }
            }
        } else if (mode == 3) {
            n = rnd.next(2, 8);
            int center = rnd.next(15000, 85000);
            int radius = rnd.next(n + 2, 300);
            for (int i = 0; i < n; ++i) {
                naomi.push_back(reserveMass(used, max(1, center - radius),
                                            min(99999, center + radius)));
                ken.push_back(reserveMass(used, max(1, center - radius),
                                          min(99999, center + radius)));
            }
        } else if (mode == 4) {
            n = rnd.next(6, 10);
            for (int i = 0; i < n; ++i) {
                naomi.push_back(reserveMass(used, 1, 99999));
                ken.push_back(reserveMass(used, 1, 99999));
            }
        } else {
            n = rnd.next(2, 8);
            for (int i = 0; i < n; ++i) {
                int lo = 1000 + i * 11000;
                int hi = lo + 4999;
                int nextLo = hi + 1;
                int nextHi = lo + 9999;
                if (i % 2 == 0) {
                    naomi.push_back(reserveMass(used, lo, hi));
                    ken.push_back(reserveMass(used, nextLo, nextHi));
                } else {
                    ken.push_back(reserveMass(used, lo, hi));
                    naomi.push_back(reserveMass(used, nextLo, nextHi));
                }
            }
        }

        maybeShuffle(naomi);
        maybeShuffle(ken);

        println(n);
        bool trimZeros = rnd.next(0, 1) == 1;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << massToken(naomi[i], trimZeros);
        }
        cout << '\n';
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << massToken(ken[i], trimZeros);
        }
        cout << '\n';
    }

    return 0;
}
