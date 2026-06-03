#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 0; i < 2; ++i) {
        string t = inf.readToken("[0-9]{2}:[0-9]{2}:[0-9]{2}", i == 0 ? "current_time" : "explosion_time");
        inf.readEoln();

        int h = (t[0] - '0') * 10 + (t[1] - '0');
        int m = (t[3] - '0') * 10 + (t[4] - '0');
        int s = (t[6] - '0') * 10 + (t[7] - '0');

        ensuref(h <= 23, "hour out of range at time %d: %d", i + 1, h);
        ensuref(m <= 59, "minute out of range at time %d: %d", i + 1, m);
        ensuref(s <= 59, "second out of range at time %d: %d", i + 1, s);
    }

    inf.readEof();
}
