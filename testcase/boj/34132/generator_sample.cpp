#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Machine {
    long long a;
    long long b;
    long long initial;
    long long m;
};

Machine makeMachine(long long m, int mode) {
    Machine machine{0, 0, 0, m};

    if (m == 1) {
        return machine;
    }

    if (mode == 0) {
        machine.a = 0;
        machine.b = rnd.next(0LL, m - 1);
        machine.initial = rnd.next(0LL, m - 1);
    } else if (mode == 1) {
        machine.a = 1;
        machine.b = rnd.next(0LL, m - 1);
        machine.initial = rnd.next(0LL, m - 1);
    } else if (mode == 2) {
        machine.a = rnd.next(0LL, m - 1);
        machine.b = 0;
        machine.initial = rnd.next(0LL, m - 1);
    } else {
        machine.a = rnd.next(0LL, m - 1);
        machine.b = rnd.next(0LL, m - 1);
        machine.initial = rnd.next(0LL, m - 1);
    }

    return machine;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);
    int n;
    int r;

    if (scenario == 0) {
        n = rnd.next(1, 3);
        r = rnd.next(1, 8);
    } else if (scenario == 1) {
        n = rnd.next(4, 8);
        r = rnd.next(1, 80);
    } else if (scenario == 2) {
        n = 10;
        r = rnd.next(1000, 17012);
    } else if (scenario == 3) {
        n = rnd.next(1, 10);
        r = rnd.any(vector<int>{1, 2, 17, 17012});
    } else {
        n = rnd.next(6, 10);
        r = rnd.next(100, 2000);
    }

    vector<Machine> machines;
    machines.reserve(n);

    for (int i = 0; i < n; ++i) {
        long long m;
        if (scenario == 0) {
            m = rnd.next(1LL, 12LL);
        } else if (scenario == 1) {
            m = rnd.next(2LL, 1000LL);
        } else if (scenario == 2) {
            m = rnd.next(999999900LL, 1000000000LL);
        } else if (scenario == 3) {
            vector<long long> candidates = {1, 2, 3, 10, 97, 1000000000LL};
            m = rnd.any(candidates);
        } else {
            m = rnd.next(2LL, 1000000LL);
        }

        machines.push_back(makeMachine(m, rnd.next(0, 3)));
    }

    if (n >= 2 && rnd.next(0, 1)) {
        machines[0] = makeMachine(1, 0);
        machines[1] = makeMachine(1000000000LL, rnd.next(0, 3));
    }

    shuffle(machines.begin(), machines.end());

    println(n, r);
    for (const Machine& machine : machines) {
        println(machine.a, machine.b, machine.initial, machine.m);
    }

    return 0;
}
