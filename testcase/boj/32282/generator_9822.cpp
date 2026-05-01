#include "testlib.h"
using namespace std;

long long isqrt(long long x) {
    long long r = 0;
    while ((r + 1) * (r + 1) <= x) ++r;
    return r;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int X = 0, Y = 0, c = 1;

    // Pythagorean triples (a, b, hypotenuse)
    vector<tuple<int,int,int>> triples = {
        {3, 4, 5},
        {5, 12, 13},
        {8, 15, 17},
        {7, 24, 25},
        {9, 40, 41},
        {20, 21, 29},
        {12, 35, 37},
        {28, 45, 53},
        {11, 60, 61},
        {16, 63, 65}
    };

    int modeRand = rnd.next(1, 100);
    int type;
    if (modeRand <= 10) type = 0;          // origin
    else if (modeRand <= 25) type = 1;     // exactly one step
    else if (modeRand <= 40) type = 2;     // d < c
    else if (modeRand <= 55) type = 3;     // d > c and multiple
    else if (modeRand <= 75) type = 4;     // d > c and not multiple
    else if (modeRand <= 90) type = 5;     // random extreme
    else type = 6;                         // boundary large d, small c

    if (type == 0) {
        // Target at origin, answer = 0
        X = 0;
        Y = 0;
        c = rnd.next(1, 10000);
    } else if (type == 1) {
        // Distance exactly c (one flutter)
        while (true) {
            auto t = rnd.any(triples);
            int a = get<0>(t), b = get<1>(t), h = get<2>(t);
            int maxk = min(10000 / max(a, b), 10000 / h);
            if (maxk <= 0) continue;
            int k = rnd.next(1, maxk);
            long long A = 1LL * a * k;
            long long B = 1LL * b * k;
            long long H = 1LL * h * k;
            if (rnd.next(0, 1)) swap(A, B);
            int sx = rnd.next(0, 1) ? 1 : -1;
            int sy = rnd.next(0, 1) ? 1 : -1;
            X = (int)(A * sx);
            Y = (int)(B * sy);
            c = (int)H;
            break;
        }
    } else if (type == 2) {
        // d < c, but target not origin
        while (true) {
            X = rnd.next(-10, 10);
            Y = rnd.next(-10, 10);
            if (X == 0 && Y == 0) continue;
            long long dsq = 1LL * X * X + 1LL * Y * Y;
            long long root = isqrt(dsq); // floor(sqrt)
            c = (int)(root + 1); // strictly greater than actual distance
            if (c >= 1 && c <= 10000) break;
        }
    } else if (type == 3) {
        // d > c and d is an integer multiple of c (answer = integer > 1)
        while (true) {
            auto t = rnd.any(triples);
            int a = get<0>(t), b = get<1>(t), h = get<2>(t);
            int maxk = min(10000 / max(a, b), 10000 / h);
            if (maxk <= 0) continue;
            int k = rnd.next(1, maxk);
            long long A = 1LL * a * k;
            long long B = 1LL * b * k;
            long long H = 1LL * h * k; // distance
            // Find proper divisors of H (m >= 2, m < H)
            vector<int> divs;
            for (int m = 2; 1LL * m * m <= H; ++m) {
                if (H % m == 0) {
                    if (m < H) divs.push_back(m);
                    long long other = H / m;
                    if (other != m && other < H) divs.push_back((int)other);
                }
            }
            if (divs.empty()) continue;
            int m = rnd.any(divs); // steps > 1
            c = (int)(H / m);
            if (c < 1 || c > 10000) continue;
            if (rnd.next(0, 1)) swap(A, B);
            int sx = rnd.next(0, 1) ? 1 : -1;
            int sy = rnd.next(0, 1) ? 1 : -1;
            X = (int)(A * sx);
            Y = (int)(B * sy);
            break;
        }
    } else if (type == 4) {
        // d > c and d is not a multiple of c (non-square distance)
        while (true) {
            X = rnd.next(-50, 50);
            Y = rnd.next(-50, 50);
            if (X == 0 && Y == 0) continue;
            long long dsq = 1LL * X * X + 1LL * Y * Y;
            long long root = isqrt(dsq);
            if (root * root == dsq) continue; // avoid perfect squares
            if (root < 1) continue;
            c = rnd.next(1, (int)root); // ensures c < distance
            break;
        }
    } else if (type == 5) {
        // Random extreme values
        while (true) {
            X = rnd.next(-10000, 10000);
            Y = rnd.next(-10000, 10000);
            if (X == 0 && Y == 0) continue;
            break;
        }
        c = rnd.next(1, 10000);
    } else {
        // Large distance, small c (many steps)
        int pattern = rnd.next(0, 2);
        if (pattern == 0) {
            X = 10000; Y = 10000;
        } else if (pattern == 1) {
            X = 10000; Y = 0;
        } else {
            X = 9999; Y = 9999;
        }
        c = rnd.next(1, 5);
    }

    println(X, Y, c);
    return 0;
}
