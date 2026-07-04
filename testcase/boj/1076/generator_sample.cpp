#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const array<string, 10> colors = {
        "black", "brown", "red", "orange", "yellow",
        "green", "blue", "violet", "grey", "white",
    };

    int first = rnd.next(0, 9);
    int second = rnd.next(0, 9);
    int multiplier = rnd.next(0, 9);

    const int mode = rnd.next(0, 5);
    if (mode == 0) {
        first = 0;
        second = rnd.next(0, 9);
        multiplier = rnd.next(0, 2);
    } else if (mode == 1) {
        first = rnd.next(8, 9);
        second = rnd.next(8, 9);
        multiplier = rnd.next(7, 9);
    } else if (mode == 2) {
        first = rnd.next(1, 9);
        second = 0;
    }

    println(colors[first]);
    println(colors[second]);
    println(colors[multiplier]);

    return 0;
}
