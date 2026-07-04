#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int t = 1; t <= tc; ++t) {
        setTestCase(t);

        int n = inf.readInt(2, 70000, "n");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            string current = inf.readToken("[0-9]{2}:[0-9]{2}:[0-9]{2}", "T_i");
            int hour = (current[0] - '0') * 10 + (current[1] - '0');
            int minute = (current[3] - '0') * 10 + (current[4] - '0');
            int second = (current[6] - '0') * 10 + (current[7] - '0');

            ensuref(hour < 24, "hour out of range at clock %d: %d", i, hour);
            ensuref(minute < 60, "minute out of range at clock %d: %d", i, minute);
            ensuref(second < 60, "second out of range at clock %d: %d", i, second);

            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }

        for (int i = 1; i <= n; ++i) {
            inf.readInt(-1000000000, 1000000000, "D_i");
            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
