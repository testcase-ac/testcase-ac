#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of disks / length of the lock
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read current state: exactly N digits [0-9]
    string curr = inf.readToken("[0-9]+", "current");
    ensuref((int)curr.length() == N,
            "The length of the current state (%d) does not match N (%d)",
            curr.length(), N);
    inf.readEoln();

    // Read password: exactly N digits [0-9]
    string pass = inf.readToken("[0-9]+", "password");
    ensuref((int)pass.length() == N,
            "The length of the password (%d) does not match N (%d)",
            pass.length(), N);
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
