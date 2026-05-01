#include "testlib.h"
#include <string>
using namespace std;

string generateNameExact(int L) {
    static const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
    string s;
    s.reserve(L);

    for (int i = 0; i < L; i++) {
        if (i == 0 || i == L - 1) {
            // First and last character cannot be space
            s += rnd.any(chars);
        } else {
            bool prevSpace = (!s.empty() && s.back() == ' ');
            // With some probability, insert a space (if previous is not space)
            if (!prevSpace && rnd.next(0, 3) == 0) {
                s += ' ';
            } else {
                s += rnd.any(chars);
            }
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose total line length between 2 and 50 (validator requirement)
    int totalLen = rnd.next(2, 50);

    bool hasSub = false;
    if (totalLen >= 7) { // minimum length to allow sub: 2 + 3 + 2 = 7
        hasSub = (rnd.next(0, 1) == 1);
    }

    string line;
    if (!hasSub) {
        // Whole line is just station_name
        string station = generateNameExact(totalLen);
        line = station;
    } else {
        // line = station + " (" + sub + ")"
        // totalLen = |S| + 3 + |T|
        // Choose |S| in [2, totalLen - 5], then |T| determined and >=2
        int sMin = 2;
        int sMax = totalLen - 5; // ensures tLen = totalLen - 3 - sLen >= 2
        int sLen = rnd.next(sMin, sMax);
        int tLen = totalLen - 3 - sLen; // guaranteed >=2

        string station = generateNameExact(sLen);
        string sub = generateNameExact(tLen);
        line = station + " (" + sub + ")";
    }

    println(line);
    return 0;
}
