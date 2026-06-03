#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Sensor {
    long long column;
    string direction;
};

vector<Sensor> makeRandomBoundary(long long m) {
    int x = rnd.wnext(3, -1);
    vector<long long> columns;

    while ((int)columns.size() < x) {
        long long c;
        int columnMode = rnd.next(0, 5);
        if (columnMode == 0) {
            c = 1;
        } else if (columnMode == 1) {
            c = m;
        } else if (m <= 30) {
            c = rnd.next(1LL, m);
        } else {
            c = rnd.next(1LL, min(m, 30LL));
        }

        if (find(columns.begin(), columns.end(), c) == columns.end()) {
            columns.push_back(c);
        }
    }

    sort(columns.begin(), columns.end());
    vector<Sensor> sensors;
    for (long long c : columns) {
        sensors.push_back({c, rnd.next(0, 1) == 0 ? "L" : "R"});
    }
    return sensors;
}

vector<Sensor> makeTightBoundary(long long m) {
    if (m == 2) {
        return {{1, rnd.next(0, 1) == 0 ? "L" : "R"},
                {2, rnd.next(0, 1) == 0 ? "L" : "R"}};
    }

    long long left = rnd.next(1LL, min(m - 1, 20LL));
    if (rnd.next(0, 4) == 0) {
        left = m - 1;
    }

    string first = rnd.next(0, 1) == 0 ? "L" : "R";
    string second = rnd.next(0, 1) == 0 ? "L" : "R";
    return {{left, first}, {left + 1, second}};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 15);
    long long m;
    if (mode == 4) {
        m = rnd.any(vector<long long>{1000000000LL, 999999937LL, 1000003LL});
        n = rnd.next(2, 8);
    } else {
        m = rnd.next(2LL, 20LL);
    }

    vector<vector<Sensor>> boundaries(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        if (mode == 0) {
            boundaries[i] = {};
        } else if (mode == 1) {
            boundaries[i] = makeRandomBoundary(m);
        } else if (mode == 2) {
            boundaries[i] = (rnd.next(0, 2) == 0 ? makeTightBoundary(m) : makeRandomBoundary(m));
        } else if (mode == 3) {
            if (i % 3 == 0) {
                boundaries[i] = {{1, "R"}, {m, "L"}};
            } else if (i % 3 == 1) {
                boundaries[i] = {{rnd.next(1LL, m), rnd.next(0, 1) == 0 ? "L" : "R"}};
            } else {
                boundaries[i] = {};
            }
        } else {
            if (rnd.next(0, 2) == 0) {
                boundaries[i] = {{1, rnd.next(0, 1) == 0 ? "L" : "R"},
                                 {m, rnd.next(0, 1) == 0 ? "L" : "R"}};
            } else {
                boundaries[i] = makeRandomBoundary(m);
            }
        }
    }

    println(n, m);
    for (const auto& boundary : boundaries) {
        printf("%d", (int)boundary.size());
        for (const Sensor& sensor : boundary) {
            printf(" %lld %s", sensor.column, sensor.direction.c_str());
        }
        printf("\n");
    }

    return 0;
}
