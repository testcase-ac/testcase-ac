#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: target string of length 1 to 10, uppercase letters only
    inf.readLine("[A-Z]{1,10}", "target");

    // Second line: integer N, 1 <= N <= 100
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Next N lines: each is a ring string of exactly 10 uppercase letters
    for (int i = 0; i < N; i++) {
        inf.readLine("[A-Z]{10}", "ring");
    }

    // No extra input
    inf.readEof();
    return 0;
}
