#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[fgx]{1,1000000}", "S");
    ensuref(!s.empty(), "S must be non-empty");

    inf.readEof();
}
