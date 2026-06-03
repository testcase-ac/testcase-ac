#include "testlib.h"
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

string formatTime(int seconds) {
    int h = seconds / 3600;
    seconds %= 3600;
    int m = seconds / 60;
    int s = seconds % 60;

    ostringstream out;
    out << setfill('0') << setw(2) << h << ':' << setw(2) << m << ':' << setw(2) << s;
    return out.str();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int day = 24 * 60 * 60;
    int current = rnd.next(0, day - 1);
    int wait = 1;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        wait = day;
    } else if (mode == 1) {
        wait = rnd.next(1, 10);
    } else if (mode == 2) {
        wait = rnd.next(day - 10, day);
    } else if (mode == 3) {
        current = rnd.next(day - 30, day - 1);
        wait = rnd.next(1, 120);
    } else if (mode == 4) {
        current = rnd.next(0, 30);
        wait = rnd.next(1, 120);
    } else {
        wait = rnd.next(1, day);
    }

    int explosion = (current + wait) % day;
    println(formatTime(current));
    println(formatTime(explosion));

    return 0;
}
