#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string hex = inf.readLine("[0-9A-F]{1,6}", "hex");
    ensuref(hex == "0" || hex[0] != '0', "hex has leading zero: %s", hex.c_str());
    inf.readEof();
}
