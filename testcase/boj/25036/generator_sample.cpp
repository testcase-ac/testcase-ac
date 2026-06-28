#include "testlib.h"
#include <cstdio>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // The local validator mirrors this no-stdin problem as one empty line.
    std::printf("\n");
    return 0;
}
