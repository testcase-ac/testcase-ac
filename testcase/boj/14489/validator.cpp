#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // First line: two integers A and B
    int A = inf.readInt(0, 1000000000, "A");
    inf.readSpace();
    int B = inf.readInt(0, 1000000000, "B");
    inf.readEoln();

    // Second line: one integer C
    long long C = inf.readLong(0LL, 1000000001LL, "C");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
