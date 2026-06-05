#include "testlib.h"

#include <set>
#include <tuple>
#include <vector>

using namespace std;

using Triangle = tuple<int, int, int>;

Triangle makeTriangleWithSide(int side, set<int>& used, bool reserveAllSides) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int a, b, c;
        int mode = rnd.next(3);

        if (mode == 0) {
            a = side;
            b = rnd.next(a + 1, min(1000000, a + 80));
            c = rnd.next(b + 1, min(1000000, a + b - 1));
        } else if (mode == 1) {
            b = side;
            a = rnd.next(2, b - 1);
            c = rnd.next(b + 1, min(1000000, a + b - 1));
        } else {
            c = side;
            b = rnd.next((c + 3) / 2, c - 1);
            a = rnd.next(c - b + 1, b - 1);
        }

        if (!(a < b && b < c && a + b > c)) continue;
        if (reserveAllSides && (used.count(a) || used.count(b) || used.count(c))) continue;

        if (reserveAllSides) {
            used.insert(a);
            used.insert(b);
            used.insert(c);
        }
        return {a, b, c};
    }

    int a = side;
    int b = side + 1;
    int c = side + 2;
    if (reserveAllSides) {
        used.insert(a);
        used.insert(b);
        used.insert(c);
    }
    return {a, b, c};
}

Triangle makeUniqueTriangle(set<int>& used, int low, int high) {
    for (int attempt = 0; attempt < 10000; ++attempt) {
        int a = rnd.next(low, high - 4);
        int firstGap = rnd.next(1, min(25, high - a - 2));
        int secondGap = rnd.next(1, min(a - 1, high - a - firstGap));
        int b = a + firstGap;
        int c = b + secondGap;

        if (!(a < b && b < c && a + b > c)) continue;
        if (used.count(a) || used.count(b) || used.count(c)) continue;

        used.insert(a);
        used.insert(b);
        used.insert(c);
        return {a, b, c};
    }

    for (int a = low; a + 2 <= high; ++a) {
        int b = a + 1;
        int c = a + 2;
        if (!used.count(a) && !used.count(b) && !used.count(c)) {
            used.insert(a);
            used.insert(b);
            used.insert(c);
            return {a, b, c};
        }
    }

    quitf(_fail, "could not construct a unique triangle");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, mode == 3 ? 60 : 16);
    vector<Triangle> triangles;
    set<int> used;

    if (mode == 0) {
        int low = rnd.next(1, 120);
        int high = low + 3 * n + 60;
        for (int i = 0; i < n; ++i) triangles.push_back(makeUniqueTriangle(used, low, high));
    } else {
        int shared = rnd.next(4, 200);
        triangles.push_back(makeTriangleWithSide(shared, used, false));
        triangles.push_back(makeTriangleWithSide(shared, used, false));

        if (mode == 2 && n >= 4) {
            int secondShared = rnd.next(201, 400);
            triangles.push_back(makeTriangleWithSide(secondShared, used, false));
            triangles.push_back(makeTriangleWithSide(secondShared, used, false));
        }

        int low = rnd.next(401, 700);
        int high = low + 3 * n + 90;
        while ((int)triangles.size() < n) triangles.push_back(makeUniqueTriangle(used, low, high));
    }

    shuffle(triangles.begin(), triangles.end());

    println(n);
    for (auto [a, b, c] : triangles) {
        println(a, b, c);
    }

    return 0;
}
