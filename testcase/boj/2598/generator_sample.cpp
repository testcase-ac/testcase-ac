#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string shuffledPalette() {
    string colors = "RGBY";
    shuffle(colors.begin(), colors.end());
    return colors;
}

string randomCube() {
    string cube;
    for (int i = 0; i < 6; ++i) {
        cube += rnd.any(string("RGBY"));
    }
    return cube;
}

string patternedCube(int mode, const string& palette, int cubeIndex) {
    string cube;
    if (mode == 0) {
        for (int i = 0; i < 6; ++i) {
            cube += palette[rnd.next(4)];
        }
    } else if (mode == 1) {
        char dominant = palette[cubeIndex % 4];
        for (int i = 0; i < 6; ++i) {
            cube += rnd.next(100) < 70 ? dominant : palette[rnd.next(4)];
        }
    } else if (mode == 2) {
        cube = palette + palette.substr(0, 2);
        shuffle(cube.begin(), cube.end());
    } else if (mode == 3) {
        char a = palette[cubeIndex % 4];
        char b = palette[(cubeIndex + rnd.next(1, 3)) % 4];
        for (int i = 0; i < 6; ++i) {
            cube += rnd.next(2) == 0 ? a : b;
        }
    } else {
        string base = palette;
        shuffle(base.begin(), base.end());
        cube = base.substr(0, 3) + base.substr(0, 3);
        shuffle(cube.begin(), cube.end());
    }
    return cube;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    string palette = shuffledPalette();
    vector<string> cubes;

    for (int i = 0; i < 4; ++i) {
        string cube = rnd.next(100) < 15 ? randomCube() : patternedCube(mode, palette, i);
        cubes.push_back(cube);
    }

    if (rnd.next(100) < 30) {
        shuffle(cubes.begin(), cubes.end());
    }

    for (const string& cube : cubes) {
        println(cube);
    }

    return 0;
}
