#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 5000;
    vector<int> sum(maxN + 1, 0), kind(maxN + 1, 0);
    for (int d = 1; d <= maxN; ++d) {
        for (int x = d + d; x <= maxN; x += d) {
            sum[x] += d;
        }
    }

    vector<int> deficient, perfect, beautiful, otherAbundant;
    for (int n = 1; n <= maxN; ++n) {
        if (sum[n] > n) {
            kind[n] = 1;
        } else if (sum[n] < n) {
            kind[n] = -1;
        }
    }

    for (int n = 1; n <= maxN; ++n) {
        if (kind[n] == -1) {
            deficient.push_back(n);
        } else if (kind[n] == 0) {
            perfect.push_back(n);
        } else {
            bool hasAbundantDivisor = false;
            for (int d = 1; d < n; ++d) {
                if (n % d == 0 && kind[d] == 1) {
                    hasAbundantDivisor = true;
                    break;
                }
            }
            if (hasAbundantDivisor) {
                otherAbundant.push_back(n);
            } else {
                beautiful.push_back(n);
            }
        }
    }

    vector<int> cases;
    auto add = [&](int n) {
        if (1 <= n && n <= maxN) {
            cases.push_back(n);
        }
    };
    auto addAny = [&](const vector<int>& values) {
        add(values[rnd.next(static_cast<int>(values.size()))]);
    };

    int mode = rnd.next(6);
    int t = (mode == 5 ? rnd.next(120, 500) : rnd.next(12, 45));

    add(1);
    add(maxN);
    add(6);
    add(12);
    add(2022);
    add(2023);
    add(2044);

    while (static_cast<int>(cases.size()) < t) {
        int pick = rnd.next(100);
        if (pick < 18) {
            addAny(beautiful);
        } else if (pick < 36) {
            addAny(otherAbundant);
        } else if (pick < 50) {
            addAny(perfect);
        } else if (pick < 68) {
            addAny(deficient);
        } else if (pick < 82) {
            int center = rnd.next(2) == 0 ? 2022 : 2044;
            add(center + rnd.next(-8, 8));
        } else if (pick < 91) {
            add(rnd.next(1, 40));
        } else {
            add(rnd.next(maxN - 80, maxN));
        }
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (int n : cases) {
        println(n);
    }
    return 0;
}
