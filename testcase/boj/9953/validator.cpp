#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no scenario count bound; cap it using the local default.
    const int maxScenarios = 100000;
    int scenarios = 0;

    while (true) {
        int shop = inf.readInt(0, 100, "shop");
        inf.readEoln();

        if (shop == 0) {
            break;
        }

        ++scenarios;
        ensuref(scenarios <= maxScenarios, "too many scenarios: %d", scenarios);
    }

    inf.readEof();
}
