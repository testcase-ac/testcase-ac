#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d_size = inf.readInt(1, 50, "d_size");
    inf.readSpace();
    int m_size = inf.readInt(1, 50, "m_size");
    inf.readEoln();

    inf.readLongs(d_size, 1LL, 1000000000LL, "d_i");
    inf.readEoln();

    inf.readLongs(m_size, 1LL, 1000000000LL, "m_i");
    inf.readEoln();

    inf.readEof();
}
