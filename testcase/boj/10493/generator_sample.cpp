#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

using Curve = vector<double>;

double randomValue(double scale) {
    int integerScale = max(1, static_cast<int>(scale));
    double value = rnd.next(-integerScale, integerScale) + rnd.next(-999, 999) / 1000.0;
    return max(-50000.0, min(50000.0, value));
}

Curve randomCurve(double scale) {
    Curve curve(4);
    for (double& coefficient : curve) {
        coefficient = randomValue(scale);
    }
    return curve;
}

Curve addDifference(const Curve& base, const Curve& diff) {
    Curve result(4);
    for (int i = 0; i < 4; ++i) {
        result[i] = max(-50000.0, min(50000.0, base[i] + diff[i]));
    }
    return result;
}

void printCurve(const Curve& curve) {
    for (int i = 0; i < 4; ++i) {
        if (i) {
            cout << ' ';
        }
        cout << fixed << setprecision(6) << curve[i];
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCaseCount = rnd.next(3, 12);
    for (int tc = 0; tc < testCaseCount; ++tc) {
        int mode = rnd.next(0, 5);
        Curve bottom;
        Curve top;

        if (mode == 0) {
            bottom = randomCurve(10);
            Curve diff = {randomValue(30), 0.0, 0.0, 0.0};
            top = addDifference(bottom, diff);
        } else if (mode == 1) {
            bottom = randomCurve(25);
            Curve diff = {randomValue(20), randomValue(80), 0.0, 0.0};
            top = addDifference(bottom, diff);
        } else if (mode == 2) {
            bottom = randomCurve(100);
            Curve diff = {randomValue(50), randomValue(250), randomValue(250), randomValue(250)};
            top = addDifference(bottom, diff);
        } else if (mode == 3) {
            double scale = rnd.next(1000, 50000);
            bottom = randomCurve(scale);
            top = randomCurve(scale);
        } else if (mode == 4) {
            bottom = randomCurve(200);
            Curve diff = {
                randomValue(5),
                randomValue(200),
                -2.0 * randomValue(200),
                randomValue(200),
            };
            top = addDifference(bottom, diff);
        } else {
            bottom = {
                rnd.any(vector<double>{-50000.0, -1.0, 0.0, 1.0, 50000.0}),
                randomValue(500),
                randomValue(500),
                rnd.any(vector<double>{-50000.0, 0.0, 50000.0}),
            };
            top = randomCurve(50000);
        }

        printCurve(bottom);
        printCurve(top);
    }

    return 0;
}
