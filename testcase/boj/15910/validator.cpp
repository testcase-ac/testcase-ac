#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[BAN]{6,100000}", "s");
    inf.readEof();
}
