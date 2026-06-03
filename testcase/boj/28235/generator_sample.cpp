#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> chants = {"SONGDO", "CODE", "2023", "ALGORITHM"};
    println(rnd.any(chants));

    return 0;
}
