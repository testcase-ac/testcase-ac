#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string keys = "asdfjkl;";
    const vector<string> namedPatterns = {
        "fdsajkl;",
        "jkl;fdsa",
        "asdf;lkj",
        ";lkjasdf",
        "asdfjkl;",
        ";lkjfdsa",
    };

    string s;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        s = rnd.any(namedPatterns);
    } else if (mode == 1) {
        s = rnd.any(namedPatterns);
        int swaps = rnd.next(1, 4);
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, 7);
            int b = rnd.next(0, 7);
            swap(s[a], s[b]);
        }
    } else if (mode == 2) {
        s = keys;
        if (rnd.next(0, 1) == 1) {
            reverse(s.begin(), s.end());
        }
        int shift = rnd.next(0, 7);
        rotate(s.begin(), s.begin() + shift, s.end());
    } else {
        s = keys;
        shuffle(s.begin(), s.end());
    }

    println(s);
    return 0;
}
