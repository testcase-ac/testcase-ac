#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readLine("[0-9]{1,249999}", "N");
    ensuref(n[0] != '0', "N must not start with zero");

    inf.readEof();
}
