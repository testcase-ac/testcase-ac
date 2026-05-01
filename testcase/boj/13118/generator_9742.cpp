#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> p(4);
    long long x, y, r;

    // Helper: generate 4 increasing positions with gaps >= 2, in a small range
    auto genSmallPeople = [&]() -> vector<long long> {
        vector<long long> res(4);
        long long p0 = rnd.next(-10, -5);          // starting point
        long long g1 = rnd.next(2, 5);
        long long g2 = rnd.next(2, 5);
        long long g3 = rnd.next(2, 5);
        res[0] = p0;
        res[1] = p0 + g1;
        res[2] = res[1] + g2;
        res[3] = res[2] + g3; // all in [-10, 10], strictly increasing, gaps >= 2
        return res;
    };

    int type = rnd.next(1, 6);

    if (type == 1) {
        // Small coordinates, direct hit on exactly one person
        p = genSmallPeople();
        int hit = rnd.next(0, 3);
        x = p[hit];
        r = rnd.next(1, 5);
        y = r + rnd.next(1, 5); // y > r, small

    } else if (type == 2) {
        // Small coordinates, near miss: |p_j - x| = r = 1, but x != any p_i
        p = genSmallPeople();
        int j = rnd.next(0, 3);
        r = 1;
        int dir = rnd.next(0, 1) ? 1 : -1;
        x = p[j] + dir;         // since gaps >= 2, this can't equal any p_i
        y = r + rnd.next(1, 5); // y > r

    } else if (type == 3) {
        // Small coordinates, guaranteed no collision, and even naive |p-x|<=r finds none
        p = genSmallPeople();
        r = 2;
        x = p[0] - 10;          // far to the left of all people
        y = r + rnd.next(1, 5); // y > r

    } else if (type == 4) {
        // Small coordinates, x between people, large r so everyone is within distance r (naive)
        p = genSmallPeople();
        x = p[1] + 1; // strictly between p[1] and p[2] because gap >= 2

        auto dist = [](long long a, long long b) -> long long {
            return (a >= b) ? (a - b) : (b - a);
        };
        r = max(dist(x, p[0]), dist(x, p[3])); // covers all four in naive logic
        if (r < 1) r = 1;
        y = r + rnd.next(1, 5); // y > r

    } else if (type == 5) {
        // Extreme positions, direct hit with large coordinates
        p[0] = -1000000000LL;
        p[1] = -999999000LL;   // -1e9 + 1000
        p[2] =  999999000LL;   //  1e9 - 1000
        p[3] =  1000000000LL;
        int hit = rnd.next(0, 3);
        x = p[hit];

        r = rnd.next(1LL, 1000000000LL - 1);          // 1 <= r <= 1e9-1
        long long maxDeltaY = 1000000000LL - r;       // >= 1
        y = r + rnd.next(1LL, maxDeltaY);             // r < y <= 1e9

    } else { // type == 6
        // Huge radius near miss: everyone within naive radius, but x != any p_i
        p[0] = -3;
        p[1] = -1;
        p[2] =  1;
        p[3] =  3;

        x = 1000000000LL;       // far to the right, not matching any p_i
        r = 1000000000LL - 1;   // very large radius
        y = r + 1;              // y = 1e9, still > r and within bounds
    }

    println(p[0], p[1], p[2], p[3]);
    println(x, y, r);

    return 0;
}
