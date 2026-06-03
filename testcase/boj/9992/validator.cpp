#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Z]{2,100}", "S");
    inf.readEoln();

    inf.readEof();
    return 0;
}
