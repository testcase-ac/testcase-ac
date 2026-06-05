#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_N = 2;
    const int MAX_N = 10633;

    vector<int> fib;
    for (int people = 2, chickens = 1; people <= MAX_N;) {
        fib.push_back(people);
        int next = people + chickens;
        chickens = people;
        people = next;
    }

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(MIN_N, 30);
    } else if (mode == 1) {
        n = rnd.next(MIN_N, MAX_N);
    } else if (mode == 2) {
        int base = rnd.any(fib);
        int delta = rnd.next(-5, 5);
        n = min(MAX_N, max(MIN_N, base + delta));
    } else if (mode == 3) {
        n = rnd.next(max(MIN_N, MAX_N - 100), MAX_N);
    } else {
        int a = rnd.any(fib);
        int b = rnd.any(fib);
        n = min(MAX_N, max(MIN_N, a + b + rnd.next(-3, 3)));
    }

    println(n);
    return 0;
}
