#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int previous = 0;
    int count = 0;

    while (true) {
        int luminosity = inf.readInt(-1, 250000, "luminosity");
        inf.readEoln();

        if (luminosity == -1) {
            break;
        }

        ensuref(luminosity > previous,
                "luminosity values must be strictly increasing: previous=%d, current=%d",
                previous, luminosity);
        previous = luminosity;
        ++count;
    }

    ensuref(count <= 250000, "too many luminosity values: %d", count);
    inf.readEof();
}
