#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        string line = inf.readLine("[01]{128}|#", "line");
        if (line == "#") {
            break;
        }
        ++datasets;
        ensuref(datasets < 100, "number of datasets must be less than 100");
    }

    inf.readEof();
}
