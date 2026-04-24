#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L
    long long L = inf.readLong(1LL, 100000000LL, "L");
    inf.readEoln();

    // Read N
    int N = inf.readInt(0, 1000, "N");
    inf.readEoln();

    // Read each rotation instruction
    for (int i = 1; i <= N; i++) {
        // t_i: time until this rotation
        char name_t[20];
        snprintf(name_t, sizeof(name_t), "t_%d", i);
        long long t = inf.readLong(1LL, 200000000LL, name_t);
        inf.readSpace();

        // dir_i: 'L' or 'R'
        char name_dir[20];
        snprintf(name_dir, sizeof(name_dir), "dir_%d", i);
        // regex "L|R" matches exactly L or R
        inf.readToken("L|R", name_dir);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
