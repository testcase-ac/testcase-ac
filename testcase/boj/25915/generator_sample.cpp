#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    char c = char('A' + rnd.next(26));
    println(c);

    return 0;
}
