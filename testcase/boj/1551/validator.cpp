#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int K = inf.readInt(0, N - 1, "K");
    inf.readEoln();

    // Read the sequence line
    string s = inf.readLine("[^]+", "sequence");
    // Check allowed characters and no whitespace
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        bool ok = (c == ',') || (c == '-') || ('0' <= c && c <= '9');
        ensuref(ok, "Invalid character in sequence at pos %d: '%c'", i, c);
    }
    // Split by commas
    vector<string> toks;
    string cur;
    for (char c : s) {
        if (c == ',') {
            toks.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    toks.push_back(cur);
    ensuref((int)toks.size() == N,
            "Expected %d numbers in sequence, but got %d", N, (int)toks.size());
    // Validate each token and its value
    for (int i = 0; i < N; i++) {
        const string &tok = toks[i];
        ensuref(!tok.empty(), "Empty token at index %d", i);
        // Check format: optional '-' then digits
        int start = 0;
        if (tok[0] == '-') {
            ensuref((int)tok.size() > 1, "Token '-' alone is not a valid integer at index %d", i);
            start = 1;
        }
        for (int j = start; j < (int)tok.size(); j++) {
            ensuref(isdigit(tok[j]), "Non-digit character '%c' in number at index %d pos %d", tok[j], i, j);
        }
        // Parse value
        long long val = 0;
        try {
            val = stoll(tok);
        } catch (...) {
            ensuref(false, "Integer value out of range for 64-bit at index %d: '%s'", i, tok.c_str());
        }
        ensuref(-100LL <= val && val <= 100LL,
                "Integer at index %d out of allowed range [-100,100]: %lld", i, val);
    }

    inf.readEof();
    return 0;
}
