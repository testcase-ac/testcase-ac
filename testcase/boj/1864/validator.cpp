#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    while (true) {
        string line = inf.readLine("[\\-\\\\\\(@\\?>&%/]{1,8}|#", "octopus_number_or_end");
        if (line == "#") {
            break;
        }
    }

    inf.readEof();
    return 0;
}
