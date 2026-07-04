#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Za-z]{1,100000}", "s");
    inf.readEoln();
    inf.readEof();
}
