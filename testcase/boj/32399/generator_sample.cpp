#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s = "(1)";
    shuffle(s.begin(), s.end());
    println(s);

    return 0;
}
