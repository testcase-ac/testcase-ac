#include "testlib.h"

#include <array>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

string source;
array<char, 256> mirrored;

struct Answer {
    bool impossible;
    int length;
};

char lowerAscii(char ch) {
    return static_cast<char>(tolower(static_cast<unsigned char>(ch)));
}

bool containsSourceIgnoringCase(const string& candidate) {
    if (candidate.size() < source.size()) {
        return false;
    }

    vector<int> prefix(source.size(), 0);
    for (size_t i = 1; i < source.size(); ++i) {
        int matched = prefix[i - 1];
        while (matched > 0 && lowerAscii(source[i]) != lowerAscii(source[matched])) {
            matched = prefix[matched - 1];
        }
        if (lowerAscii(source[i]) == lowerAscii(source[matched])) {
            ++matched;
        }
        prefix[i] = matched;
    }

    int matched = 0;
    for (char ch : candidate) {
        while (matched > 0 && lowerAscii(ch) != lowerAscii(source[matched])) {
            matched = prefix[matched - 1];
        }
        if (lowerAscii(ch) == lowerAscii(source[matched])) {
            ++matched;
        }
        if (matched == int(source.size())) {
            return true;
        }
    }
    return false;
}

void setMirror(char from, char to) {
    mirrored[static_cast<unsigned char>(from)] = to;
}

void initMirror() {
    mirrored.fill(0);

    setMirror('A', 'A');
    setMirror('E', '3');
    setMirror('H', 'H');
    setMirror('I', 'I');
    setMirror('M', 'M');
    setMirror('O', 'O');
    setMirror('S', '2');
    setMirror('T', 'T');
    setMirror('U', 'U');
    setMirror('V', 'V');
    setMirror('W', 'W');
    setMirror('X', 'X');
    setMirror('Y', 'Y');
    setMirror('Z', '5');

    setMirror('b', 'd');
    setMirror('d', 'b');
    setMirror('i', 'i');
    setMirror('l', 'l');
    setMirror('m', 'm');
    setMirror('n', 'n');
    setMirror('o', 'o');
    setMirror('p', 'q');
    setMirror('q', 'p');
    setMirror('r', '7');
    setMirror('u', 'u');
    setMirror('v', 'v');
    setMirror('w', 'w');
    setMirror('x', 'x');

    setMirror('0', '0');
    setMirror('1', '1');
    setMirror('2', 'S');
    setMirror('3', 'E');
    setMirror('5', 'Z');
    setMirror('7', 'r');
    setMirror('8', '8');
}

Answer readAnswer(InStream& stream) {
    string token = stream.readToken("[-A-Za-z0-9]{1,2000000}", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "-1") {
        return {true, -1};
    }
    if (!token.empty() && token[0] == '-') {
        stream.quitf(_wa, "invalid negative answer '%s'", token.c_str());
    }

    for (size_t i = 0; i < token.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(token[i]);
        if (!isalnum(ch)) {
            stream.quitf(_wa, "answer contains non-alphanumeric character at position %d", int(i + 1));
        }
        if (mirrored[ch] == 0) {
            stream.quitf(_wa, "character '%c' at position %d has no mirror image", token[i], int(i + 1));
        }
    }

    for (size_t i = 0; i < token.size(); ++i) {
        unsigned char left = static_cast<unsigned char>(token[i]);
        char want = mirrored[left];
        char got = token[token.size() - 1 - i];
        if (want != got) {
            stream.quitf(_wa,
                         "answer is not a quilindrome: position %d mirrors to '%c', found '%c'",
                         int(i + 1),
                         want,
                         got);
        }
    }

    if (!containsSourceIgnoringCase(token)) {
        stream.quitf(_wa, "answer does not contain the original nickname ignoring case");
    }

    return {false, int(token.size())};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    initMirror();

    source = inf.readToken("[A-Za-z0-9]{1,1000000}", "S");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers are impossible");
        }
        quitf(_fail, "participant found a valid answer of length %d while jury says impossible", participant.length);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid answer of length %d, participant says impossible", jury.length);
    }
    if (participant.length < jury.length) {
        quitf(_fail,
              "participant found a shorter valid answer: jury=%d participant=%d",
              jury.length,
              participant.length);
    }
    if (participant.length > jury.length) {
        quitf(_wa,
              "participant answer is longer than jury answer: jury=%d participant=%d",
              jury.length,
              participant.length);
    }

    quitf(_ok, "valid shortest quilindrome of length %d", participant.length);
}
