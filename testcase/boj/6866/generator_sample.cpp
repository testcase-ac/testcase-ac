#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

struct Planet {
    array<int, 3> center;
    int radius;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int axis = rnd.next(0, 2);
    int span = rnd.next(20, 180);
    int base1 = rnd.next(-1000, 1000);
    int base2 = rnd.next(-1000, 1000);

    array<int, 3> a{};
    array<int, 3> b{};
    a[axis] = -span;
    b[axis] = span;
    a[(axis + 1) % 3] = b[(axis + 1) % 3] = base1;
    a[(axis + 2) % 3] = b[(axis + 2) % 3] = base2;

    int n = rnd.next(1, 20);
    vector<Planet> planets;

    for (int i = 0; i < n; ++i) {
        int kind = rnd.next(0, 4);
        Planet p{};

        if (kind <= 1) {
            int offset1 = rnd.next(-2, 2);
            int offset2 = rnd.next(-2, 2);
            int distance2 = offset1 * offset1 + offset2 * offset2;
            p.center[axis] = rnd.next(-span + 8, span - 8);
            p.center[(axis + 1) % 3] = base1 + offset1;
            p.center[(axis + 2) % 3] = base2 + offset2;
            p.radius = max(1, rnd.next(1, 6));
            while (p.radius * p.radius <= distance2) {
                ++p.radius;
            }
        } else if (kind == 2) {
            int offset = rnd.next(4, 14);
            if (rnd.next(0, 1) == 0) offset = -offset;
            int gap = rnd.next(2, 8);
            p.radius = rnd.next(0, 6);
            p.center[axis] = rnd.next(-span + 8, span - 8);
            p.center[(axis + 1) % 3] = base1 + offset + (offset > 0 ? p.radius + gap : -p.radius - gap);
            p.center[(axis + 2) % 3] = base2 + rnd.next(-2, 2);
        } else {
            int side = rnd.next(0, 1) == 0 ? -1 : 1;
            int endpointGap = rnd.next(4, 25);
            p.radius = rnd.next(0, endpointGap - 2);
            p.center[axis] = side * (span + endpointGap);
            p.center[(axis + 1) % 3] = base1 + rnd.next(-4, 4);
            p.center[(axis + 2) % 3] = base2 + rnd.next(-4, 4);
        }

        planets.push_back(p);
    }

    println(a[0], a[1], a[2]);
    println(b[0], b[1], b[2]);
    println(n);
    for (const Planet& p : planets) {
        println(p.center[0], p.center[1], p.center[2], p.radius);
    }

    return 0;
}
