#include "testlib.h"

#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_COORD = -1000000000LL;
    const long long MAX_COORD = 1000000000LL;

    long long sx = inf.readLong(MIN_COORD, MAX_COORD, "S_x");
    inf.readSpace();
    long long sy = inf.readLong(MIN_COORD, MAX_COORD, "S_y");
    inf.readEoln();

    long long ex = inf.readLong(MIN_COORD, MAX_COORD, "E_x");
    inf.readSpace();
    long long ey = inf.readLong(MIN_COORD, MAX_COORD, "E_y");
    inf.readEoln();

    long long px = inf.readLong(MIN_COORD, MAX_COORD, "P_x");
    inf.readSpace();
    long long py = inf.readLong(MIN_COORD, MAX_COORD, "P_y");
    inf.readEoln();

    pair<long long, long long> s = {sx, sy};
    pair<long long, long long> e = {ex, ey};
    pair<long long, long long> p = {px, py};
    ensuref(s != e, "home and SPC locations must be distinct");
    ensuref(s != p, "home and Geunsu locations must be distinct");
    ensuref(e != p, "SPC and Geunsu locations must be distinct");

    inf.readEof();
}
