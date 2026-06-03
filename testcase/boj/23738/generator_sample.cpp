#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "ABEKMHOPCTYX";
    const string sameSound = "AKMOT";
    const string differentSound = "BEHPCYX";

    int mode = rnd.next(0, 5);
    int length;
    string word;

    if (mode == 0) {
        length = 1;
        word += rnd.any(alphabet);
    } else if (mode == 1) {
        length = rnd.next(2, 24);
        for (int i = 0; i < length; ++i) {
            word += rnd.any(alphabet);
        }
    } else if (mode == 2) {
        length = rnd.next(3, 30);
        for (int i = 0; i < length; ++i) {
            word += rnd.any(i % 3 == 0 ? sameSound : differentSound);
        }
    } else if (mode == 3) {
        length = rnd.next(8, 40);
        vector<char> pattern;
        int patternLength = rnd.next(1, 4);
        for (int i = 0; i < patternLength; ++i) {
            pattern.push_back(rnd.any(alphabet));
        }
        for (int i = 0; i < length; ++i) {
            word += pattern[i % patternLength];
        }
    } else if (mode == 4) {
        length = rnd.next(12, 60);
        for (int i = 0; i < length; ++i) {
            word += rnd.any(differentSound);
        }
    } else {
        length = 100;
        for (int i = 0; i < length; ++i) {
            word += rnd.any(i % 5 == 0 ? alphabet : differentSound);
        }
    }

    println(word);
    return 0;
}
