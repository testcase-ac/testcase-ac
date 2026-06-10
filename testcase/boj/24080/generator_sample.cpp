#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "ABCDE";

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
    } else if (mode == 3) {
        n = rnd.next(4, 20);
    } else if (mode == 4) {
        n = rnd.next(21, 60);
    } else {
        n = rnd.next(61, 100);
    }

    vector<char> letters(alphabet.begin(), alphabet.end());
    shuffle(letters.begin(), letters.end());

    int distinct;
    if (mode == 0) {
        distinct = 1;
    } else if (mode == 1) {
        distinct = 2;
    } else if (mode == 2) {
        distinct = 3;
    } else if (mode == 3) {
        distinct = rnd.next(3, 5);
    } else {
        distinct = rnd.next(1, 5);
    }
    distinct = min(distinct, n);

    string s;
    for (int i = 0; i < distinct; ++i) {
        s += letters[i];
    }
    while ((int)s.size() < n) {
        s += letters[rnd.next(0, distinct - 1)];
    }
    shuffle(s.begin(), s.end());

    println(n);
    println(s);

    return 0;
}
