#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of disks
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the string s of length N, consisting only of 'J', 'O', 'I'
    string s = inf.readToken("[JOI]+", "s");
    ensuref((int)s.length() == N,
            "The length of string s must be exactly N (%d), but got %d", N, (int)s.length());
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
