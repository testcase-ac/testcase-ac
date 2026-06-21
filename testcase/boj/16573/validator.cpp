#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[01]{1,2000}", "S");
    inf.readEoln();
    inf.readEof();
}
