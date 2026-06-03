#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

const int MIN_COORD = -200000;
const int MAX_COORD = 200000;

int pickCoord(int span) {
    return rnd.next(-span, span);
}

void addPoint(vector<pair<int, int>>& points, int x, int y) {
    points.push_back({x, y});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> points;
    int mode = rnd.next(6);

    if (mode == 0) {
        addPoint(points, rnd.any(vector<int>{MIN_COORD, 0, MAX_COORD}), rnd.any(vector<int>{MIN_COORD, 0, MAX_COORD}));
    } else if (mode == 1) {
        int n = rnd.next(4, 24);
        int y = pickCoord(30);
        for (int i = 0; i < n; ++i) addPoint(points, pickCoord(30), y);
    } else if (mode == 2) {
        int n = rnd.next(4, 24);
        int x = pickCoord(30);
        for (int i = 0; i < n; ++i) addPoint(points, x, pickCoord(30));
    } else if (mode == 3) {
        int width = rnd.next(2, 7);
        int height = rnd.next(2, 5);
        int x0 = rnd.next(-20, 20);
        int y0 = rnd.next(-20, 20);
        int dx = rnd.next(1, 4);
        int dy = rnd.next(1, 4);
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (rnd.next(100) < 75) addPoint(points, x0 + x * dx, y0 + y * dy);
            }
        }
    } else if (mode == 4) {
        int clusters = rnd.next(2, 5);
        for (int i = 0; i < clusters; ++i) {
            int x = pickCoord(12);
            int y = pickCoord(12);
            int copies = rnd.next(2, 6);
            for (int j = 0; j < copies; ++j) addPoint(points, x, y);
        }
    } else {
        int n = rnd.next(3, 35);
        int span = rnd.any(vector<int>{5, 30, 200000});
        for (int i = 0; i < n; ++i) addPoint(points, pickCoord(span), pickCoord(span));
    }

    if (points.empty()) addPoint(points, 0, 0);
    shuffle(points.begin(), points.end());

    println(int(points.size()));
    for (auto [x, y] : points) println(x, y);

    return 0;
}
