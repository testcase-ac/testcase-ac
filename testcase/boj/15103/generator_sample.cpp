#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Hearing {
    int s;
    int a;
    int b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode <= 3) {
        n = rnd.next(5, 18);
    } else {
        n = rnd.next(20, 45);
    }

    vector<Hearing> hearings;
    hearings.reserve(n);

    int current = rnd.next(1, 8);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            if (mode == 1 && rnd.next(0, 2) == 0) {
                current += 0;
            } else if (mode == 2) {
                current += rnd.next(1, 3);
            } else if (mode == 3) {
                current += rnd.next(0, 12);
            } else if (mode == 4) {
                current += rnd.next(0, 60);
            } else {
                current += rnd.next(0, 6);
            }
        }

        int a;
        int b;
        if (mode == 0) {
            a = rnd.next(1, 5);
            b = a;
        } else if (mode == 1) {
            a = rnd.next(1, 4);
            b = rnd.next(a, a + rnd.next(0, 8));
        } else if (mode == 2) {
            a = rnd.next(1, 3);
            b = rnd.next(a + 5, a + 30);
        } else if (mode == 3) {
            a = rnd.next(1, 20);
            b = rnd.next(a, min(1000000, a + rnd.next(0, 200)));
        } else if (mode == 4) {
            a = rnd.next(1, 1000);
            b = rnd.next(a, min(1000000, a + rnd.next(0, 50000)));
        } else {
            a = rnd.next(1, 1000000);
            b = rnd.next(a, 1000000);
        }

        hearings.push_back({current, a, b});
    }

    sort(hearings.begin(), hearings.end(), [](const Hearing& lhs, const Hearing& rhs) {
        if (lhs.s != rhs.s) return lhs.s < rhs.s;
        if (lhs.a != rhs.a) return lhs.a < rhs.a;
        return lhs.b < rhs.b;
    });

    println(n);
    for (const Hearing& hearing : hearings) {
        println(hearing.s, hearing.a, hearing.b);
    }

    return 0;
}
