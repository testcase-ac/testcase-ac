#include "testlib.h"

#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int TEST_CASES = 100;
    constexpr int SAMPLE_SIZE = 5000;

    for (int tc = 1; tc <= TEST_CASES; ++tc) {
        setTestCase(tc);
        for (int i = 1; i <= SAMPLE_SIZE; ++i) {
            string value = inf.readToken("[0-1][.][0-9]{4}", "x");
            int scaled = (value[0] - '0') * 10000 + atoi(value.c_str() + 2);
            ensuref(scaled <= 10000, "x must be at most 1.0000, got %s", value.c_str());
            inf.readEoln();
        }
    }

    inf.readEof();
}
