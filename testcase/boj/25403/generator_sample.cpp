#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);
    int xMax = rnd.next(6, 20);
    int yMax = rnd.next(6, 20);
    int w = rnd.next(1, 30);
    int h = rnd.next(1, 30);

    vector<pair<int, int>> points;
    for (int x = 1; x <= xMax; ++x)
        for (int y = 1; y <= yMax; ++y)
            points.emplace_back(x, y);
    shuffle(points.begin(), points.end());

    println(n, m, w, h);
    for (int i = 0; i < n + m; ++i)
        println(points[i].first, points[i].second);
}
