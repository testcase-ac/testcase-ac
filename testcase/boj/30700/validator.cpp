#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("[KOREA]{10,1000}", "S");
    inf.readEof();
}
