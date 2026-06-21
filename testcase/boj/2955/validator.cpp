#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int row = 1; row <= 9; ++row) {
        string line = inf.readLine("[1-9\\.]{9}", format("row_%d", row));
    }

    inf.readEof();
}
