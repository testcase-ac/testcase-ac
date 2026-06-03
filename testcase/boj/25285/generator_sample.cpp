#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;

int clampWeight(int w) {
    return max(1, min(200, w));
}

int randomWeightNearBmi(int h, double bmi) {
    double exact = bmi * h * h / 10000.0;
    int center = max(1, min(200, static_cast<int>(round(exact))));
    return clampWeight(center + rnd.next(-2, 2));
}

pair<int, int> generatePerson() {
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        return {rnd.next(1, 140), rnd.next(1, 200)};
    }
    if (mode == 1) {
        return {rnd.next(141, 145), rnd.next(1, 200)};
    }
    if (mode == 2) {
        return {rnd.next(146, 158), rnd.next(1, 200)};
    }
    if (mode == 3) {
        int h = rnd.next(159, 160);
        vector<double> bmiTargets = {15.8, 16.0, 17.5, 34.8, 35.0, 36.5};
        return {h, randomWeightNearBmi(h, rnd.any(bmiTargets))};
    }

    int h = rnd.next(161, 200);
    vector<double> bmiTargets = {15.8, 16.0, 17.0, 18.5, 19.2, 20.0,
                                 22.0, 25.0, 27.5, 30.0, 33.0, 35.0, 37.0};
    if (mode == 4) {
        return {h, randomWeightNearBmi(h, rnd.any(bmiTargets))};
    }
    if (mode == 5) {
        return {h, clampWeight(rnd.next(1, 45))};
    }
    if (mode == 6) {
        return {h, rnd.next(46, 95)};
    }
    return {h, rnd.next(96, 200)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode == 0) {
        t = 1;
    } else if (sizeMode == 1) {
        t = 200;
    } else {
        t = rnd.next(2, 30);
    }

    println(t);
    for (int i = 0; i < t; ++i) {
        auto person = generatePerson();
        println(person.first, person.second);
    }

    return 0;
}
