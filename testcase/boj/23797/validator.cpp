#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[KP]{1,1000000}", "S");
    inf.readEoln();
    inf.readEof();
}
