#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomLine(int len, const string& alphabet) {
    string line;
    line.reserve(len);
    for (int i = 0; i < len; ++i) {
        line += rnd.any(alphabet);
    }
    return line;
}

void addLetterRun(string& line, char letter, int count) {
    for (int i = 0; i < count && int(line.size()) < 72; ++i) {
        line += letter;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string punctuation = " .,!?:;[]{}()<>+-=*/_#@$%^&|~";
    const string printable = letters + digits + punctuation;

    vector<string> lines(4);
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        char dominant = rnd.any(letters);
        char secondary = rnd.any(letters);
        while (secondary == dominant) {
            secondary = rnd.any(letters);
        }
        for (int i = 0; i < 4; ++i) {
            lines[i] = randomLine(rnd.next(1, 12), punctuation + digits);
            addLetterRun(lines[i], dominant, rnd.next(1, 6));
            addLetterRun(lines[i], secondary, rnd.next(0, 3));
            shuffle(lines[i].begin(), lines[i].end());
        }
    } else if (mode == 1) {
        for (int i = 0; i < 4; ++i) {
            int len = rnd.next(20, 72);
            lines[i] = randomLine(len, printable);
        }
    } else if (mode == 2) {
        string pool = letters.substr(0, rnd.next(1, 26));
        for (int i = 0; i < 4; ++i) {
            int len = rnd.next(1, 30);
            lines[i] = randomLine(len, pool + "     " + digits + ".,!?");
        }
    } else if (mode == 3) {
        for (int i = 0; i < 4; ++i) {
            lines[i] = randomLine(rnd.next(1, 72), digits + punctuation);
        }
        int lineIndex = rnd.next(0, 3);
        int position = rnd.next(0, int(lines[lineIndex].size()) - 1);
        lines[lineIndex][position] = rnd.any(letters);
    } else {
        string shuffled = letters;
        shuffle(shuffled.begin(), shuffled.end());
        for (int i = 0; i < 4; ++i) {
            lines[i] = shuffled.substr(i * 6, 6);
            lines[i] += randomLine(rnd.next(1, 18), "   " + punctuation + digits);
            addLetterRun(lines[i], shuffled[i], rnd.next(0, 4));
            shuffle(lines[i].begin(), lines[i].end());
        }
    }

    for (const string& line : lines) {
        println(line);
    }

    return 0;
}
