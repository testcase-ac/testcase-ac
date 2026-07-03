#include "testlib.h"
#include <map>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    map<char, int> colorCount;
    for (int row = 0; row < 4; ++row) {
        string line = inf.readLine("[RGBY]{4}", "row");
        for (char color : line) {
            ++colorCount[color];
        }
    }

    for (char color : string("RGBY")) {
        ensuref(colorCount[color] == 4,
                "color %c appears %d times instead of 4",
                color,
                colorCount[color]);
    }

    inf.readEof();
    return 0;
}
