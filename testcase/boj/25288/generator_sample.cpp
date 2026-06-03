#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 10000;
    } else if (mode == 2) {
        n = rnd.next(2, 20);
    } else if (mode == 3) {
        n = rnd.next(21, 200);
    } else {
        n = rnd.next(201, 10000);
    }

    string letters = "abcdefghijklmnopqrstuvwxyz";
    shuffle(letters.begin(), letters.end());

    int alphabetSize;
    if (mode == 0) {
        alphabetSize = 1;
    } else if (mode == 1) {
        alphabetSize = 26;
    } else if (mode == 4) {
        alphabetSize = rnd.next(20, 26);
    } else {
        alphabetSize = rnd.next(1, 10);
    }

    string alphabet = letters.substr(0, alphabetSize);
    if (rnd.next(0, 1) == 0) {
        sort(alphabet.begin(), alphabet.end());
    }

    println(n);
    println(alphabet);

    return 0;
}
