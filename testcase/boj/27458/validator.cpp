#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readEoln();

    string s = to_string(n);
    ensuref(s.find("666") != string::npos, "n must contain 666 consecutively: %lld", n);

    inf.readEof();
}
