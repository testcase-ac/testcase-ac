#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the first line: cowphabet order
    string cowphabet = inf.readLine("[a-z]{26}", "cowphabet");
    ensuref(cowphabet.size() == 26, "Cowphabet must have exactly 26 letters, got %zu", cowphabet.size());

    // Check that all 26 letters are present and unique
    set<char> seen;
    for (int i = 0; i < 26; ++i) {
        char c = cowphabet[i];
        ensuref('a' <= c && c <= 'z', "Cowphabet contains invalid character '%c' at position %d", c, i+1);
        ensuref(seen.insert(c).second, "Cowphabet contains duplicate character '%c' at position %d", c, i+1);
    }

    // Read the second line: heard string
    string heard = inf.readLine("[a-z]{1,1000}", "heard");
    ensuref(heard.size() >= 1 && heard.size() <= 1000, "Heard string length must be between 1 and 1000, got %zu", heard.size());

    // Check that all characters in heard are lowercase and in cowphabet
    set<char> cowphabet_set(cowphabet.begin(), cowphabet.end());
    for (size_t i = 0; i < heard.size(); ++i) {
        char c = heard[i];
        ensuref('a' <= c && c <= 'z', "Heard string contains invalid character '%c' at position %zu", c, i+1);
        ensuref(cowphabet_set.count(c), "Heard string contains character '%c' at position %zu not in cowphabet", c, i+1);
    }

    inf.readEof();
}
