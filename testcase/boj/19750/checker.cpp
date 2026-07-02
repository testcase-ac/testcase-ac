#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    int m;
    vector<string> words;
};

bool hasDoubleSpace(const string& s) {
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i - 1] == ' ' && s[i] == ' ') {
            return true;
        }
    }
    return false;
}

string expectedSuffix(int index, int total) {
    return "(" + to_string(index) + "/" + to_string(total) + ")";
}

vector<string> splitWords(const string& s) {
    vector<string> words;
    int pos = 0;
    while (pos < (int)s.size()) {
        while (pos < (int)s.size() && s[pos] == ' ') {
            ++pos;
        }
        if (pos == (int)s.size()) {
            break;
        }
        int start = pos;
        while (pos < (int)s.size() && s[pos] != ' ') {
            ++pos;
        }
        words.push_back(s.substr(start, pos - start));
    }
    return words;
}

void appendContentWords(vector<string>& allWords, const string& line, const string& suffix) {
    string content = line.substr(0, line.size() - suffix.size());
    if (!content.empty()) {
        if (content.back() != ' ') {
            quitf(_fail, "internal parser error: missing separator before suffix");
        }
        content.pop_back();
    }
    vector<string> words = splitWords(content);
    allWords.insert(allWords.end(), words.begin(), words.end());
}

vector<string> readInitialWords() {
    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    vector<string> words;
    for (int i = 1; i <= n; ++i) {
        string line = inf.readLine();
        string suffix = expectedSuffix(i, n);
        if (line.size() < suffix.size() || line.substr(line.size() - suffix.size()) != suffix) {
            quitf(_fail, "input twint %d does not end with expected suffix %s", i, suffix.c_str());
        }
        if (line.size() > 140) {
            quitf(_fail, "input twint %d has length %d exceeding 140", i, (int)line.size());
        }
        appendContentWords(words, line, suffix);
    }
    inf.readEof();
    return words;
}

Claim readClaim(InStream& stream, const vector<string>& expectedWords) {
    int m = stream.readInt(1, 5000, "m");
    stream.readEoln();

    vector<string> words;
    for (int i = 1; i <= m; ++i) {
        string line = stream.readLine();
        string suffix = expectedSuffix(i, m);

        if ((int)line.size() > 280) {
            stream.quitf(_wa, "twint %d has length %d exceeding 280", i, (int)line.size());
        }
        if (line.empty()) {
            stream.quitf(_wa, "twint %d is empty", i);
        }
        if (line[0] == ' ') {
            stream.quitf(_wa, "twint %d starts with a space", i);
        }
        if (hasDoubleSpace(line)) {
            stream.quitf(_wa, "twint %d contains two sequential spaces", i);
        }
        if (line.size() < suffix.size() || line.substr(line.size() - suffix.size()) != suffix) {
            stream.quitf(_wa, "twint %d does not end with expected suffix %s", i, suffix.c_str());
        }
        if (line.size() > suffix.size() && line[line.size() - suffix.size() - 1] != ' ') {
            stream.quitf(_wa, "twint %d has no space before suffix %s", i, suffix.c_str());
        }

        appendContentWords(words, line, suffix);
    }
    stream.readEof();

    if (words != expectedWords) {
        stream.quitf(_wa,
                     "word sequence differs: expected %d words, found %d words",
                     (int)expectedWords.size(),
                     (int)words.size());
    }

    return {m, words};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    vector<string> initialWords = readInitialWords();
    Claim jury = readClaim(ans, initialWords);
    Claim participant = readClaim(ouf, initialWords);

    if (participant.m < jury.m) {
        quitf(_fail,
              "participant found a shorter valid chain: jury=%d participant=%d",
              jury.m,
              participant.m);
    }
    if (participant.m > jury.m) {
        quitf(_wa, "jury has fewer twints: jury=%d participant=%d", jury.m, participant.m);
    }

    quitf(_ok, "valid shortest chain with %d twints", participant.m);
}
