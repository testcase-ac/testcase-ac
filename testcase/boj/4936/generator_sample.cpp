#include "testlib.h"

#include <array>
#include <set>
#include <string>
#include <vector>

using namespace std;

array<int, 4> normEdge(int x, int y, int nx, int ny) {
    array<int, 4> edge = {x, y, nx, ny};
    if (edge[2] < edge[0] || (edge[2] == edge[0] && edge[3] < edge[1])) {
        swap(edge[0], edge[2]);
        swap(edge[1], edge[3]);
    }
    return edge;
}

void addMove(string& path, set<array<int, 4>>& used, int& x, int& y, char dir) {
    int nx = x;
    int ny = y;
    if (dir == 'U') {
        ++ny;
    } else if (dir == 'D') {
        --ny;
    } else if (dir == 'L') {
        --nx;
    } else {
        ++nx;
    }

    bool inserted = used.insert(normEdge(x, y, nx, ny)).second;
    ensuref(inserted, "generator tried to reuse an edge");
    path += dir;
    x = nx;
    y = ny;
}

string rectangleCase(int width, int height) {
    string path;
    set<array<int, 4>> used;
    int x = 0;
    int y = 0;
    for (int i = 0; i < height; ++i) addMove(path, used, x, y, 'U');
    for (int i = 0; i < width; ++i) addMove(path, used, x, y, 'R');
    for (int i = 0; i < height; ++i) addMove(path, used, x, y, 'D');
    for (int i = 0; i < width; ++i) addMove(path, used, x, y, 'L');
    return path;
}

string spiralCase(int turns) {
    string path;
    set<array<int, 4>> used;
    int x = 0;
    int y = 0;
    int len = 1;
    const string dirs = "RULD";
    for (int i = 0; i < turns; ++i) {
        char dir = dirs[i % 4];
        for (int step = 0; step < len; ++step) {
            addMove(path, used, x, y, dir);
        }
        if (i % 2 == 1) {
            ++len;
        }
    }
    return path;
}

string randomWalkCase(int moves, int bound) {
    string path;
    set<array<int, 4>> used;
    int x = 0;
    int y = 0;
    const string dirs = "UDLR";

    for (int i = 0; i < moves; ++i) {
        vector<char> candidates;
        for (char dir : dirs) {
            int nx = x;
            int ny = y;
            if (dir == 'U') {
                ++ny;
            } else if (dir == 'D') {
                --ny;
            } else if (dir == 'L') {
                --nx;
            } else {
                ++nx;
            }
            if (abs(nx) <= bound && abs(ny) <= bound && !used.count(normEdge(x, y, nx, ny))) {
                candidates.push_back(dir);
            }
        }
        if (candidates.empty()) {
            break;
        }
        addMove(path, used, x, y, rnd.any(candidates));
    }

    if (path.empty()) {
        return rectangleCase(1, 1);
    }
    return path;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 7);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 3);
        string path;
        if (mode == 0) {
            path = rectangleCase(rnd.next(1, 5), rnd.next(1, 5));
        } else if (mode == 1) {
            path = spiralCase(rnd.next(5, 14));
        } else {
            path = randomWalkCase(rnd.next(4, 30), rnd.next(3, 7));
        }
        println(path + "Q");
    }
    println("Q");

    return 0;
}
