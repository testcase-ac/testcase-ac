#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string c = inf.readToken("[1-9][0-9]{0,9999}", "C");
    ensuref(!c.empty(), "C must be non-empty");
    inf.readEoln();
    inf.readEof();
}
