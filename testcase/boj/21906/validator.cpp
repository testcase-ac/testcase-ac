#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[01]{1,1000000}", "s");
    inf.readEoln();
    inf.readEof();

    return 0;
}
