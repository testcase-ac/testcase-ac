#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int count = 0;
    while (true) {
        string line = inf.readLine("[0-9]{2}:[0-9]{2}|end", "time_or_end");
        if (line == "end") {
            break;
        }

        ++count;
        // CHECK: The statement gives no number-of-times bound; cap it for practical validation.
        ensuref(count <= 100000, "too many time lines: %d", count);

        int hour = (line[0] - '0') * 10 + (line[1] - '0');
        int minute = (line[3] - '0') * 10 + (line[4] - '0');
        ensuref(hour <= 23, "hour out of range on line %d: %02d", count, hour);
        ensuref(minute <= 59, "minute out of range on line %d: %02d", count, minute);
    }

    inf.readEof();
}
