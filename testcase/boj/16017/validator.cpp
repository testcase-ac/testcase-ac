#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input consists of exactly 4 lines, each with exactly one digit [0-9].
    inf.readLine("[0-9]", "digit_1");
    inf.readLine("[0-9]", "digit_2");
    inf.readLine("[0-9]", "digit_3");
    inf.readLine("[0-9]", "digit_4");

    inf.readEof();
    return 0;
}
