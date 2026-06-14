#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static void appendRepeat(string& path, char move, int count) {
    path.append(count, move);
}

static void appendRectangle(string& path, int width, int height) {
    appendRepeat(path, 'N', height);
    appendRepeat(path, 'E', width);
    appendRepeat(path, 'S', height);
    appendRepeat(path, 'W', width);
}

static void appendRandomWalk(string& path, int steps, bool backtrackOften) {
    const string moves = "NESW";
    for (int i = 0; i < steps; ++i) {
        if (backtrackOften && !path.empty() && rnd.next(0, 3) == 0) {
            char last = path.back();
            if (last == 'N') path.push_back('S');
            if (last == 'S') path.push_back('N');
            if (last == 'E') path.push_back('W');
            if (last == 'W') path.push_back('E');
        } else {
            path.push_back(rnd.any(moves));
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string path;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int n = rnd.next(1, 30);
        appendRepeat(path, rnd.any(string("NESW")), n);
    } else if (mode == 1) {
        appendRectangle(path, rnd.next(1, 12), rnd.next(1, 12));
    } else if (mode == 2) {
        int loops = rnd.next(2, 8);
        int width = rnd.next(1, 8);
        int height = rnd.next(1, 8);
        for (int i = 0; i < loops; ++i) appendRectangle(path, width, height);
    } else if (mode == 3) {
        int loops = rnd.next(2, 6);
        for (int i = 0; i < loops; ++i) {
            appendRectangle(path, rnd.next(1, 10), rnd.next(1, 10));
            if (i + 1 < loops) {
                appendRepeat(path, 'E', rnd.next(1, 3));
                appendRepeat(path, 'N', rnd.next(0, 2));
            }
        }
    } else if (mode == 4) {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            int width = rnd.next(1, 8);
            int height = rnd.next(1, 8);
            appendRepeat(path, 'N', height);
            appendRepeat(path, 'E', width);
            appendRepeat(path, 'S', rnd.next(1, height));
            appendRepeat(path, 'W', rnd.next(1, width));
        }
    } else if (mode == 5) {
        appendRandomWalk(path, rnd.next(20, 180), true);
    } else {
        appendRandomWalk(path, rnd.next(181, 1000), false);
    }

    if ((int)path.size() > 1000) path.resize(1000);
    if (path.empty()) path.push_back('N');

    println((int)path.size());
    println(path);

    return 0;
}
