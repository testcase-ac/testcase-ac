#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

const long long kMaxValue = 1000000000LL;

struct Equation {
    long long a;
    long long b;
    long long c;
};

long long smallOrBoundaryValue() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.next(0, 20);
    if (mode == 1) return rnd.next(0, 1000);
    if (mode == 2) return rnd.next(999999900LL, kMaxValue);
    if (mode == 3) return rnd.next(0LL, kMaxValue);
    return rnd.any(vector<long long>{0, 1, 2, 10, 999999999LL, kMaxValue});
}

Equation makeZeroCoefficient() {
    long long b = smallOrBoundaryValue();
    long long c = b;
    if (rnd.next(0, 1) == 0) {
        do {
            c = smallOrBoundaryValue();
        } while (c == b);
    }
    return {0, b, c};
}

Equation makeIntegerSolution() {
    long long a = rnd.next(1, 1000000);
    long long x = rnd.next(0, 1000);
    long long b = rnd.next(0LL, max(0LL, kMaxValue - a * x));
    return {a, b, b + a * x};
}

Equation makeFractionalSolution() {
    long long a = rnd.next(2, 1000000);
    long long diff = rnd.next(1LL, min(kMaxValue, a * rnd.next(1, 1000) - 1));
    if (diff % a == 0) ++diff;
    long long b = rnd.next(0LL, kMaxValue - diff);
    return {a, b, b + diff};
}

Equation makeNegativeSolution() {
    long long a = rnd.next(1, 1000000);
    long long b = rnd.next(1LL, kMaxValue);
    long long c = rnd.next(0LL, b - 1);
    return {a, b, c};
}

Equation makeBoundaryCase() {
    int mode = rnd.next(0, 3);
    if (mode == 0) return {kMaxValue, rnd.next(0LL, 10LL), kMaxValue};
    if (mode == 1) return {rnd.next(999999900LL, kMaxValue), 0, rnd.next(0LL, kMaxValue)};
    if (mode == 2) return {1, rnd.next(999999900LL, kMaxValue), kMaxValue};
    return {rnd.next(1LL, 10LL), kMaxValue, rnd.next(0LL, kMaxValue)};
}

Equation makeEquation() {
    int mode = rnd.next(0, 9);
    if (mode < 2) return makeZeroCoefficient();
    if (mode < 4) return makeIntegerSolution();
    if (mode < 7) return makeFractionalSolution();
    if (mode < 9) return makeNegativeSolution();
    return makeBoundaryCase();
}

void printEquation(const Equation& equation) {
    println(toString(equation.a) + "x + " + toString(equation.b) + " = " + toString(equation.c));
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(8, 35);
    vector<Equation> equations;
    equations.reserve(p);

    equations.push_back({0, 0, 0});
    equations.push_back({0, kMaxValue, 0});
    equations.push_back({1, 0, kMaxValue});
    equations.push_back({kMaxValue, 0, 1});

    while ((int)equations.size() < p) {
        equations.push_back(makeEquation());
    }

    shuffle(equations.begin(), equations.end());

    println((int)equations.size());
    for (const Equation& equation : equations) {
        printEquation(equation);
    }

    return 0;
}
