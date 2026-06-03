#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string options[4] = {"EI", "SN", "TF", "JP"};
    string mbti;
    for (const string& axis : options) {
        mbti += axis[rnd.next(0, 1)];
    }

    println(mbti);
    return 0;
}
