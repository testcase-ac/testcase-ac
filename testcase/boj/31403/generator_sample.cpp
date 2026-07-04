#include "testlib.h"
#include <array>

using namespace std;

int randomByDigits(int digits) {
    if (digits == 1) return rnd.next(1, 9);
    if (digits == 2) return rnd.next(10, 99);
    if (digits == 3) return rnd.next(100, 999);
    return 1000;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    array<int, 3> values{};
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        for (int& value : values) value = rnd.next(1, 9);
    } else if (mode == 1) {
        for (int& value : values) value = rnd.next(990, 1000);
    } else if (mode == 2) {
        array<int, 4> digits = {1, 2, 3, 4};
        for (int& value : values) value = randomByDigits(rnd.any(digits));
    } else if (mode == 3) {
        values = {1, rnd.next(1, 1000), 1000};
        shuffle(values.begin(), values.end());
    } else {
        values = {1000, rnd.next(1, 1000), 1};
        shuffle(values.begin(), values.end());
    }

    for (int value : values) println(value);
    return 0;
}
