#include "testlib.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const long long SCALE = 100000000LL;
static const long long COORD_LIMIT = 100LL * SCALE;
static const long long THETA_LIMIT = 628318530LL;

static string format_scaled(long long value) {
    bool negative = value < 0;
    if (negative) {
        value = -value;
    }

    long long integer_part = value / SCALE;
    long long fractional_part = value % SCALE;

    ostringstream out;
    if (negative) {
        out << '-';
    }
    out << integer_part << '.' << setw(8) << setfill('0') << fractional_part;
    return out.str();
}

static long long choose_scaled(long long low, long long high) {
    return rnd.next(low, high);
}

static long long choose_from(const vector<long long>& values) {
    return values[rnd.next((int)values.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    println(t);

    vector<long long> cartesian_special = {
        -COORD_LIMIT, -50LL * SCALE, -SCALE, -1, 0, 1, SCALE, 50LL * SCALE, COORD_LIMIT,
    };
    vector<long long> radius_special = {
        0, 1, SCALE, 2LL * SCALE, 50LL * SCALE, COORD_LIMIT,
    };
    vector<long long> theta_special = {
        0, 1, 157079633LL, 314159265LL, 471238898LL, THETA_LIMIT,
    };

    for (int tc = 0; tc < t; ++tc) {
        int system = rnd.next(1, 2);
        if (tc < 2) {
            system = tc + 1;
        }

        println(system);

        int mode = rnd.next(0, 5);
        if (system == 1) {
            long long x;
            long long y;

            if (mode <= 1) {
                x = choose_from(cartesian_special);
                y = choose_from(cartesian_special);
            } else if (mode == 2) {
                x = choose_from(vector<long long>{-COORD_LIMIT, 0, COORD_LIMIT});
                y = choose_scaled(-1000, 1000);
            } else if (mode == 3) {
                x = choose_scaled(-1000, 1000);
                y = choose_from(vector<long long>{-COORD_LIMIT, 0, COORD_LIMIT});
            } else {
                x = choose_scaled(-COORD_LIMIT, COORD_LIMIT);
                y = choose_scaled(-COORD_LIMIT, COORD_LIMIT);
            }

            cout << format_scaled(x) << ' ' << format_scaled(y) << '\n';
        } else {
            long long r;
            long long theta;

            if (mode <= 1) {
                r = choose_from(radius_special);
                theta = choose_from(theta_special);
            } else if (mode == 2) {
                r = choose_scaled(0, 1000);
                theta = choose_from(theta_special);
            } else if (mode == 3) {
                r = choose_from(radius_special);
                theta = choose_scaled(0, THETA_LIMIT);
            } else {
                r = choose_scaled(0, COORD_LIMIT);
                theta = choose_scaled(0, THETA_LIMIT);
            }

            if (r == 0) {
                theta = 0;
            }

            cout << format_scaled(r) << ' ' << format_scaled(theta) << '\n';
        }
    }

    return 0;
}
