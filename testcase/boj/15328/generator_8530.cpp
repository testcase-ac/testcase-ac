#include "testlib.h"
using namespace std;

struct Point {
    int x, y, z;
};

long double distPoint(const Point &a, const Point &b) {
    long double dx = (long double)a.x - (long double)b.x;
    long double dy = (long double)a.y - (long double)b.y;
    long double dz = (long double)a.z - (long double)b.z;
    return sqrtl(dx * dx + dy * dy + dz * dz);
}

long double totalDist(Point p[4]) {
    Point cur{0, 0, 0};
    long double d = 0.0L;
    for (int i = 0; i < 4; i++) {
        d += distPoint(cur, p[i]);
        cur = p[i];
    }
    return d;
}

long double manhattanTotal(Point p[4]) {
    Point cur{0, 0, 0};
    long double d = 0.0L;
    for (int i = 0; i < 4; i++) {
        d += llabs((long long)p[i].x - cur.x)
           + llabs((long long)p[i].y - cur.y)
           + llabs((long long)p[i].z - cur.z);
        cur = p[i];
    }
    return d;
}

void genRandomPointsLargeD(Point p[4]) {
    while (true) {
        for (int i = 0; i < 4; i++) {
            p[i].x = rnd.next(-20, 20);
            p[i].y = rnd.next(-20, 20);
            p[i].z = rnd.next(-20, 20);
        }
        long double D = totalDist(p);
        if (D >= 2.0L) return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = 5;
    println(T);

    // Test case 1: all houses at origin, trivially YES
    {
        Point p[4];
        for (int i = 0; i < 4; i++) p[i] = {0, 0, 0};
        int X = rnd.next(1, 5); // any positive time, distance = 0
        println(X);
        for (int i = 0; i < 4; i++)
            println(p[i].x, p[i].y, p[i].z);
    }

    // Test case 2: Manhattan vs Euclidean trap, answer YES
    {
        Point p[4];
        int dim = rnd.next(2, 3); // 2D or 3D diagonal
        int d = rnd.next(1, 5);
        Point v;
        if (dim == 2) v = {d, d, 0};
        else v = {d, d, d};

        for (int i = 0; i < 4; i++) {
            p[i].x = v.x * (i + 1);
            p[i].y = v.y * (i + 1);
            p[i].z = v.z * (i + 1);
        }

        long double D = totalDist(p);
        long double M = manhattanTotal(p);
        long long lo = (long long)floorl(D); // D < X
        long long hi = (long long)M;         // X < M

        int X;
        if (hi - lo >= 3) {
            X = rnd.next((int)lo + 1, (int)hi - 1);
        } else {
            // Fallback, but still keep X > D and < M
            X = (int)lo + 1;
        }

        println(X);
        for (int i = 0; i < 4; i++)
            println(p[i].x, p[i].y, p[i].z);
    }

    // Test case 3: exact integer total distance boundary, answer YES when equal
    {
        Point p[4];
        Point v = {3, 4, 0}; // each segment length = 5
        for (int i = 0; i < 4; i++) {
            p[i].x = v.x * (i + 1);
            p[i].y = v.y * (i + 1);
            p[i].z = v.z * (i + 1);
        }
        long double D = totalDist(p); // should be 20 exactly
        int X = (int)floorl(D + 0.5L); // round to nearest int (=20)
        println(X);
        for (int i = 0; i < 4; i++)
            println(p[i].x, p[i].y, p[i].z);
    }

    // Test case 4: random NO case, X slightly less than needed
    {
        Point p[4];
        genRandomPointsLargeD(p);
        long double D = totalDist(p);
        int X = (int)floorl(D - 0.5L);
        if (X < 1) X = 1;
        if ((long double)X >= D) X = (int)floorl(D - 1.0L);
        if (X < 1) X = 1; // still safe; with D >= 2 this ensures X < D

        println(X);
        for (int i = 0; i < 4; i++)
            println(p[i].x, p[i].y, p[i].z);
    }

    // Test case 5: random YES or NO case
    {
        Point p[4];
        genRandomPointsLargeD(p);
        long double D = totalDist(p);

        bool wantYes = rnd.next(0, 1) == 1;

        int X;
        if (wantYes) {
            int extra = rnd.next(0, 3);
            X = (int)ceill(D + (long double)extra);
            if (X < 1) X = 1;
        } else {
            X = (int)floorl(D - 0.5L);
            if (X < 1) X = 1;
            if ((long double)X >= D) X = (int)floorl(D - 1.0L);
            if (X < 1) X = 1;
        }

        println(X);
        for (int i = 0; i < 4; i++)
            println(p[i].x, p[i].y, p[i].z);
    }

    return 0;
}
