#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string prefix = ":chino";
    int mode = rnd.next(0, 5);
    int suffixLength;

    if (mode == 0) {
        suffixLength = 0;
    } else if (mode == 1) {
        suffixLength = rnd.next(1, 5);
    } else if (mode == 2) {
        suffixLength = rnd.next(6, 15);
    } else if (mode == 3) {
        suffixLength = rnd.next(16, 24);
    } else {
        suffixLength = 25;
    }

    int underscoreChance;
    if (mode == 0) {
        underscoreChance = 0;
    } else if (mode == 1) {
        underscoreChance = rnd.next(0, 20);
    } else if (mode == 2) {
        underscoreChance = rnd.next(20, 45);
    } else if (mode == 3) {
        underscoreChance = rnd.next(45, 75);
    } else {
        underscoreChance = rnd.next(0, 100);
    }

    string emoji = prefix;
    for (int i = 0; i < suffixLength; ++i) {
        if (rnd.next(1, 100) <= underscoreChance) {
            emoji += '_';
        } else {
            char c = char('a' + rnd.next(0, 25));
            emoji += c;
        }
    }
    emoji += ':';

    println(emoji);
    return 0;
}
