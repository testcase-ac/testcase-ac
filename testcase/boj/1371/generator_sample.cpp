#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

namespace {

char randomLetter(char maxLetter) {
    return char('a' + rnd.next(0, maxLetter - 'a'));
}

string makeLine(int length, const string& alphabet, int spaceWeight) {
    string line;
    line.reserve(length);
    for (int i = 0; i < length; ++i) {
        if (rnd.next(100) < spaceWeight) {
            line.push_back(' ');
        } else {
            line.push_back(rnd.any(alphabet));
        }
    }
    return line;
}

void ensureLetter(vector<string>& lines) {
    bool hasLetter = false;
    for (const string& line : lines) {
        for (char c : line) {
            if ('a' <= c && c <= 'z') {
                hasLetter = true;
            }
        }
    }

    if (hasLetter) return;

    int row = rnd.next(0, int(lines.size()) - 1);
    if (lines[row].empty()) {
        lines[row] = string(1, char('a' + rnd.next(0, 25)));
    } else {
        lines[row][rnd.next(0, int(lines[row].size()) - 1)] = char('a' + rnd.next(0, 25));
    }
}

vector<string> randomLines(int lineCount, int maxLen, const string& alphabet, int spaceWeight) {
    vector<string> lines;
    lines.reserve(lineCount);
    for (int i = 0; i < lineCount; ++i) {
        int length = rnd.next(0, maxLen);
        lines.push_back(makeLine(length, alphabet, spaceWeight));
    }
    ensureLetter(lines);
    return lines;
}

vector<string> tiedLeaders() {
    int winners = rnd.next(2, 6);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    shuffle(alphabet.begin(), alphabet.end());
    alphabet.resize(winners);
    sort(alphabet.begin(), alphabet.end());

    string bag;
    int targetCount = rnd.next(2, 5);
    for (char c : alphabet) {
        bag.append(targetCount, c);
    }

    int fillerKinds = rnd.next(0, 6);
    for (int i = 0; i < fillerKinds; ++i) {
        char c = randomLetter('z');
        if (alphabet.find(c) != string::npos) continue;
        bag.append(rnd.next(1, targetCount - 1), c);
    }

    shuffle(bag.begin(), bag.end());

    int lineCount = rnd.next(1, 8);
    vector<string> lines(lineCount);
    for (char c : bag) {
        string& line = lines[rnd.next(0, lineCount - 1)];
        if (!line.empty() && rnd.next(100) < 35 && int(line.size()) < 50) line.push_back(' ');
        if (int(line.size()) < 50) line.push_back(c);
    }

    for (string& line : lines) {
        while (int(line.size()) < 50 && rnd.next(100) < 25) {
            line.insert(line.begin() + rnd.next(0, int(line.size())), ' ');
        }
    }
    return lines;
}

vector<string> boundaryLines() {
    int lineCount = rnd.next(35, 50);
    vector<string> lines;
    lines.reserve(lineCount);
    char dominant = randomLetter('z');
    for (int i = 0; i < lineCount; ++i) {
        int length = rnd.next(0, 50);
        string line;
        line.reserve(length);
        for (int j = 0; j < length; ++j) {
            int roll = rnd.next(100);
            if (roll < 45) line.push_back(' ');
            else if (roll < 75) line.push_back(dominant);
            else line.push_back(randomLetter('z'));
        }
        lines.push_back(line);
    }
    ensureLetter(lines);
    return lines;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<string> lines;

    if (mode == 0) {
        int lineCount = rnd.next(1, 6);
        char maxLetter = char('a' + rnd.next(0, 5));
        string alphabet;
        for (char c = 'a'; c <= maxLetter; ++c) alphabet.push_back(c);
        lines = randomLines(lineCount, 20, alphabet, rnd.next(0, 35));
    } else if (mode == 1) {
        lines = tiedLeaders();
    } else if (mode == 2) {
        int lineCount = rnd.next(3, 12);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        lines = randomLines(lineCount, 50, alphabet, rnd.next(55, 90));
    } else if (mode == 3) {
        int lineCount = rnd.next(1, 10);
        char c = randomLetter('z');
        lines.assign(lineCount, "");
        lines[rnd.next(0, lineCount - 1)] = string(1, c);
    } else {
        lines = boundaryLines();
    }

    for (const string& line : lines) {
        println(line);
    }

    return 0;
}
