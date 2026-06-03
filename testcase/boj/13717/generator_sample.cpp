#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int candiesForEvolutions(int k, int evolutions) {
    if (evolutions <= 0) return rnd.next(1, k - 1);
    int exact = k + (evolutions - 1) * (k - 2);
    int next = exact + (k - 2);
    int hi = min(10000, next - 1);
    return rnd.next(exact, hi);
}

string makeName(int index, int mode) {
    if (mode == 0) return string(1, char('A' + index % 26));
    if (mode == 1) return "Poke" + to_string(index + 1);

    string name;
    int len = rnd.next(1, 20);
    for (int i = 0; i < len; ++i) {
        if (i == 0 || rnd.next(0, 3) != 0)
            name += char('A' + rnd.next(0, 25));
        else
            name += char('0' + rnd.next(0, 9));
    }
    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(40, 70);
    } else {
        n = rnd.next(2, 12);
    }

    println(n);

    int targetTie = rnd.next(0, 20);
    int nameMode = rnd.next(0, 2);
    for (int i = 0; i < n; ++i) {
        int k;
        int m;

        if (mode == 0) {
            k = rnd.next(12, 400);
            m = rnd.next(1, 10000);
        } else if (mode == 1) {
            k = rnd.next(12, 25);
            int evolutions = rnd.next(0, 12);
            m = candiesForEvolutions(k, evolutions);
        } else if (mode == 2) {
            k = rnd.next(12, 400);
            m = rnd.next(1, k - 1);
        } else if (mode == 3) {
            k = rnd.next(12, 400);
            int evolutions = (i < 2) ? targetTie : rnd.next(0, targetTie);
            m = candiesForEvolutions(k, evolutions);
        } else if (mode == 4) {
            k = rnd.next(350, 400);
            m = rnd.next(9000, 10000);
        } else {
            k = rnd.next(12, 400);
            m = rnd.next(1, 10000);
        }

        println(makeName(i, nameMode));
        println(k, m);
    }

    return 0;
}
