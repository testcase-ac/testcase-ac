#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[a-z]{1,1000000}", "S");
    string p = inf.readLine("[a-z]{1,1000000}", "P");
    (void)s;
    (void)p;

    inf.readEof();
    return 0;
}
