#include "testlib.h"
#include <algorithm>
#include <string>

using namespace std;

char randomLetter(int alphabetSize) {
    return char('A' + rnd.next(alphabetSize));
}

string randomString(int length, int alphabetSize) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(randomLetter(alphabetSize));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int length = rnd.next(1, 60);
    int alphabetSize = rnd.next(1, 6);
    string path;

    if (mode == 0) {
        path.assign(length, randomLetter(alphabetSize));
    } else if (mode == 1) {
        string pattern = randomString(rnd.next(2, 5), alphabetSize);
        for (int i = 0; i < length; ++i) {
            path.push_back(pattern[i % int(pattern.size())]);
        }
    } else if (mode == 2) {
        if (length % 2 == 0) {
            ++length;
        }
        string half = randomString(length / 2 + 1, alphabetSize);
        path = half;
        for (int i = int(half.size()) - 2; i >= 0; --i) {
            path.push_back(half[i]);
        }
    } else if (mode == 3) {
        length = 2 * rnd.next(1, 30) + 1;
        path.reserve(length);
        for (int i = 0; i < length; ++i) {
            path.push_back((i % 2 == 0) ? 'A' : randomLetter(alphabetSize));
        }
    } else {
        path = randomString(length, rnd.next(1, 26));
    }

    println(path);
    return 0;
}
