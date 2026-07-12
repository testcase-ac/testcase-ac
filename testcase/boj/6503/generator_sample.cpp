#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomText(int length, const string& alphabet) {
    string text;
    text.reserve(length);
    for (int i = 0; i < length; ++i) {
        text += rnd.any(alphabet);
    }
    return text;
}

string runText(const vector<char>& chars, int minRun, int maxRun, int targetLength) {
    string text;
    int pos = 0;
    while (static_cast<int>(text.size()) < targetLength) {
        int runLength = rnd.next(minRun, maxRun);
        for (int i = 0; i < runLength && static_cast<int>(text.size()) < targetLength; ++i) {
            text += chars[pos % static_cast<int>(chars.size())];
        }
        ++pos;
    }
    return text;
}

string printableAscii() {
    string chars;
    for (char ch = 32; ch <= 126; ++ch) {
        chars += ch;
    }
    return chars;
}

string normalizeSentence(const string& input) {
    string result;
    for (char ch : input) {
        if (ch == ' ' && (result.empty() || result.back() == ' ')) continue;
        result += ch;
    }
    if (!result.empty() && result.back() == ' ') result.pop_back();
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string mixed = "AaBbCcDdEeFfGg0123456789     .,!?";
    const string printable = printableAscii();

    vector<pair<int, string>> cases;

    int smallM = rnd.next(1, 4);
    cases.push_back({smallM, randomText(rnd.next(8, 22), lower.substr(0, rnd.next(smallM + 1, 8)))});

    cases.push_back({1, runText({' ', 'a', 'b', 'c'}, rnd.next(1, 3), rnd.next(3, 7), rnd.next(18, 35))});

    string nearLimitAlphabet = lower.substr(0, rnd.next(5, 12));
    cases.push_back({static_cast<int>(nearLimitAlphabet.size()) - rnd.next(1, 3),
                     randomText(rnd.next(24, 45), nearLimitAlphabet)});

    cases.push_back({rnd.next(2, 6), randomText(rnd.next(20, 40), mixed)});

    string fullAscii = printable;
    shuffle(fullAscii.begin(), fullAscii.end());
    int asciiLength = rnd.next(35, 95);
    cases.push_back({rnd.next(20, 128), fullAscii.substr(0, asciiLength)});

    int blockKinds = rnd.next(3, 7);
    vector<char> blockChars;
    for (int i = 0; i < blockKinds; ++i) {
        blockChars.push_back(static_cast<char>('A' + i));
    }
    blockChars.push_back(' ');
    cases.push_back({rnd.next(1, blockKinds), runText(blockChars, 2, 8, rnd.next(25, 55))});

    if (rnd.next(0, 1) == 1) {
        cases.push_back({128, randomText(rnd.next(40, 80), printable)});
    }

    for (const auto& testCase : cases) {
        println(testCase.first);
        println(normalizeSentence(testCase.second));
    }
    println(0);

    return 0;
}
