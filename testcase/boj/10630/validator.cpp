#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

namespace {

vector<string> splitSpaces(const string& line, const string& name) {
    ensuref(!line.empty(), "%s line must not be empty", name.c_str());
    ensuref(line.front() != ' ', "%s line has leading space", name.c_str());
    ensuref(line.back() != ' ', "%s line has trailing space", name.c_str());

    vector<string> tokens;
    string current;
    for (char ch : line) {
        ensuref(ch == ' ' || ch == '$' || (ch >= 'A' && ch <= 'Z') || isdigit(static_cast<unsigned char>(ch)),
                "%s line has invalid character", name.c_str());
        if (ch == ' ') {
            ensuref(!current.empty(), "%s line has repeated spaces", name.c_str());
            tokens.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    ensuref(!current.empty(), "%s line has repeated spaces", name.c_str());
    tokens.push_back(current);
    return tokens;
}

long long parseLength(const string& token, const string& name, int pairIndex) {
    ensuref(!token.empty(), "%s length at pair %d is empty", name.c_str(), pairIndex);
    ensuref(token == "0" || token[0] != '0', "%s length at pair %d has leading zero", name.c_str(), pairIndex);
    long long value = 0;
    for (char ch : token) {
        ensuref(isdigit(static_cast<unsigned char>(ch)),
                "%s length at pair %d is not a decimal integer", name.c_str(), pairIndex);
        value = value * 10 + (ch - '0');
        ensuref(value <= 100000000LL, "%s length at pair %d exceeds 100000000", name.c_str(), pairIndex);
    }
    ensuref(value >= 1LL, "%s length at pair %d is less than 1", name.c_str(), pairIndex);
    return value;
}

void readRleLine(const string& name) {
    string line = inf.readLine("[^]+", name.c_str());
    vector<string> tokens = splitSpaces(line, name);

    ensuref(tokens.back() == "$", "%s line must end with $", name.c_str());
    ensuref(tokens.size() >= 3, "%s line must contain at least one pair", name.c_str());
    ensuref(tokens.size() % 2 == 1, "%s line must contain letter-length pairs followed by $", name.c_str());

    int pairs = static_cast<int>((tokens.size() - 1) / 2);
    ensuref(pairs >= 1 && pairs <= 1000, "%s pair count must be between 1 and 1000", name.c_str());

    string previous = "";
    for (int i = 0; i < pairs; ++i) {
        const string& letter = tokens[2 * i];
        ensuref(letter.size() == 1 && letter[0] >= 'A' && letter[0] <= 'Z',
                "%s letter at pair %d is not an uppercase English letter", name.c_str(), i + 1);
        ensuref(letter != previous, "%s has equal adjacent letters at pair %d", name.c_str(), i + 1);
        parseLength(tokens[2 * i + 1], name, i + 1);
        previous = letter;
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readRleLine("A");
    readRleLine("B");
    readRleLine("C");
    inf.readEof();
}
