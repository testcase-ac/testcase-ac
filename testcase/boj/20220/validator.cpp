#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of layers h
    int h = inf.readInt(1, 100, "h");
    inf.readSpace();
    // Total people in pyramid is h*(h+1)/2
    long long total = (long long)h * (h + 1) / 2;
    // Read number of strong people s
    long long s = inf.readLong(0LL, total, "s");
    inf.readEoln();
    inf.readEof();

    return 0;
}
