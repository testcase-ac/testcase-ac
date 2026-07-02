#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();
    int d = inf.readInt(1, 25, "d");
    inf.readEoln();
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    vector<pair<int, int>> points;
    points.reserve(n);
    vector<vector<int>> cityAt(1000, vector<int>(1000, -1));

    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 999, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 999, "y_i");
        inf.readEoln();

        ensuref(cityAt[x][y] == -1, "duplicate city coordinate at index %d: (%d, %d)", i + 1, x, y);
        cityAt[x][y] = i;
        points.push_back({x, y});
    }

    vector<pair<int, int>> offsets;
    for (int dx = -d; dx <= d; ++dx) {
        for (int dy = -d; dy <= d; ++dy) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            if (dx * dx + dy * dy <= d * d) {
                offsets.push_back({dx, dy});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int neighborCount = 0;
        int x = points[i].first;
        int y = points[i].second;
        for (auto [dx, dy] : offsets) {
            int nx = x + dx;
            int ny = y + dy;
            if (0 <= nx && nx < 1000 && 0 <= ny && ny < 1000 && cityAt[nx][ny] != -1) {
                ++neighborCount;
            }
        }
        ensuref(neighborCount <= 10, "city %d has %d cities within distance d", i + 1, neighborCount);
    }

    inf.readEof();
}
