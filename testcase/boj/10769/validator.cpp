#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly one line of input, 1 to 255 characters (anything except newline)
    string s = inf.readLine("[^]{1,255}", "s");
    // Just in case, double-check length
    ensuref((int)s.size() >= 1 && (int)s.size() <= 255,
            "Input length must be between 1 and 255, found %d", (int)s.size());

    // No more tokens or lines after this
    inf.readEof();
    return 0;
}
