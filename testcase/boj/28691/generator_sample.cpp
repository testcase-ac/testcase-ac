#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> initials = {"M", "W", "C", "A", "$"};
    println(rnd.any(initials));

    return 0;
}
