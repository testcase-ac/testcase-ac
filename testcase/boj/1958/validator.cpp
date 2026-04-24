#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three strings, each consisting of lowercase letters, length <= 100
    inf.readLine("[a-z]{0,100}", "s1");
    inf.readLine("[a-z]{0,100}", "s2");
    inf.readLine("[a-z]{0,100}", "s3");

    // No extra characters
    inf.readEof();
    return 0;
}
