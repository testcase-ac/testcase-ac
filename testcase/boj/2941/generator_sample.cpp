#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> croatian = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};
    const vector<string> ambiguous = {"d", "z=", "dz=", "ddz=", "z", "lj", "l", "j", "nj", "n", "j"};
    const string plain = "abcdefghijklmnopqrstuvwxyz";

    int mode = rnd.next(0, 5);
    int targetLength = (mode == 5) ? rnd.next(80, 100) : rnd.next(1, 30);
    string word;

    while ((int)word.size() < targetLength) {
        string token;
        if (mode == 0) {
            token = rnd.any(croatian);
        } else if (mode == 1) {
            token = rnd.any(ambiguous);
        } else if (mode == 2) {
            token = string(1, rnd.any(plain));
        } else if (mode == 3) {
            token = (rnd.next(0, 99) < 65) ? rnd.any(croatian) : string(1, rnd.any(plain));
        } else if (mode == 4) {
            const vector<string> run = {"dz=", "z=", "s=", "c=", "c-", "d-", "d", "z"};
            token = rnd.any(run);
        } else {
            token = (rnd.next(0, 99) < 75) ? rnd.any(croatian) : string(1, rnd.any(plain));
        }

        int remaining = targetLength - (int)word.size();
        if ((int)token.size() <= remaining) {
            word += token;
        } else if (remaining == 1) {
            word += rnd.any(plain);
        }
    }

    println(word);
    return 0;
}
