#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string line = inf.readLine("[^]+", "numbers");
    ensuref(!line.empty(), "input line must contain at least one integer");
    ensuref(line.front() != ' ', "line must not start with a space");
    ensuref(line.back() != ' ', "line must not end with a space");

    int count = 0;
    for (int i = 0; i < (int)line.size();) {
        ++count;
        ensuref(count <= 1000000, "too many integers");

        bool negative = false;
        if (line[i] == '-') {
            negative = true;
            ++i;
            ensuref(i < (int)line.size(), "minus sign must be followed by digits");
        }

        ensuref(i < (int)line.size() && line[i] >= '0' && line[i] <= '9',
                "integer %d must contain digits", count);
        ensuref(line[i] != '0' || (i + 1 == (int)line.size()) || line[i + 1] == ' ',
                "integer %d has leading zeroes", count);
        ensuref(!negative || line[i] != '0', "integer %d is negative zero", count);

        long long value = 0;
        while (i < (int)line.size() && line[i] >= '0' && line[i] <= '9') {
            if (value <= 1000000) {
                value = value * 10 + (line[i] - '0');
            }
            ensuref(value <= 1000000, "integer %d is out of range", count);
            ++i;
        }

        if (negative) {
            value = -value;
        }
        ensuref(-1000000 <= value && value <= 1000000,
                "integer %d is out of range", count);

        if (i == (int)line.size()) {
            break;
        }
        ensuref(line[i] == ' ', "integers must be separated by a single space");
        ++i;
        ensuref(i < (int)line.size() && line[i] != ' ',
                "integers must be separated by a single space");
    }

    inf.readEof();
    return 0;
}
