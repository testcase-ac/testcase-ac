#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static char randomLetter() {
    return rnd.any(string("DKSH"));
}

static void appendRandomLetters(string& s, int count) {
    for (int i = 0; i < count; ++i) {
        s += randomLetter();
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        appendRandomLetters(s, rnd.next(1, 30));
    } else if (mode == 1) {
        int copies = rnd.next(1, 8);
        for (int i = 0; i < copies; ++i) {
            appendRandomLetters(s, rnd.next(0, 3));
            s += "DKSH";
        }
        appendRandomLetters(s, rnd.next(0, 3));
    } else if (mode == 2) {
        vector<string> chunks = {"DKS", "KSH", "DKH", "DSH", "DKKH", "SSHH"};
        int chunkCount = rnd.next(1, 8);
        for (int i = 0; i < chunkCount; ++i) {
            s += rnd.any(chunks);
            appendRandomLetters(s, rnd.next(0, 2));
        }
    } else if (mode == 3) {
        int length = rnd.next(1, 30);
        while ((int)s.size() < length) {
            s += rnd.any(vector<string>{"D", "DK", "DKS", "KSH", "SH", "H"});
        }
        s.resize(length);
    } else if (mode == 4) {
        int length = rnd.next(25, 80);
        appendRandomLetters(s, length);
        int insertions = rnd.next(1, 5);
        for (int i = 0; i < insertions; ++i) {
            int pos = rnd.next(0, (int)s.size());
            s.insert(pos, "DKSH");
        }
        s.resize(min<int>(s.size(), 1000));
    } else {
        int length = rnd.next(900, 1000);
        while ((int)s.size() + 4 <= length) {
            s += "DKSH";
        }
        appendRandomLetters(s, length - (int)s.size());
    }

    println(s);
    return 0;
}
