#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// generate a random plain-text fragment (letters and spaces)
string randomPlain(int len) {
    static const string letters = "abcdefghijklmnopqrstuvwxyz";
    string s;
    for (int i = 0; i < len; i++) {
        if (rnd.next(0, 5) == 0)
            s += ' ';
        else
            s += letters[rnd.next((int)letters.size() - 1)];
    }
    return s;
}

// recursively generate a balanced bracket sequence of K pairs
string genBrackets(int K) {
    if (K <= 0) return "";
    if (K == 1) {
        char o = rnd.any(string("()[]"));
        char c = (o == '(' ? ')' : (o == '[' ? ']' : o == ')' ? ')' : ']'));
        // ensure matching
        if (o == ')' || o == ']') o = (o == ')' ? '(' : '['), c = (o == '(' ? ')' : ']');
        return string(1, o) + string(1, c);
    }
    if (rnd.next(0, 1) == 0) {
        // nested
        char o = rnd.any(string("()[]"));
        char c = (o == '(' ? ')' : ']');
        return string(1, o) + genBrackets(K - 1) + string(1, c);
    } else {
        // split into two sequences
        int k1 = rnd.next(1, K - 1);
        return genBrackets(k1) + genBrackets(K - k1);
    }
}

// generate a balanced line with length up to maxLen
string generateBalanced(int maxLen) {
    int maxPairs = min(5, maxLen / 2);
    int K = rnd.next(1, maxPairs);
    string b = genBrackets(K);
    string s;
    // intersperse small plain fragments between brackets
    for (char c : b) {
        if (rnd.next(0.0, 1.0) < 0.3) {
            s += randomPlain(rnd.next(1, 3));
        }
        s += c;
    }
    // prefix/suffix
    s = randomPlain(rnd.next(1, min(5, maxLen / 10))) + s
      + randomPlain(rnd.next(1, min(5, maxLen / 10)));
    if ((int)s.size() > maxLen) s.resize(maxLen);
    return s;
}

// generate an unbalanced line by mutating a balanced one
string generateUnbalanced(int maxLen) {
    string s = generateBalanced(maxLen);
    vector<int> closes;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == ')' || s[i] == ']') closes.push_back(i);
    }
    int mode = rnd.next(0, 2);
    if (mode == 0 || closes.empty()) {
        // extra closing
        int pos = rnd.next(0, (int)s.size());
        char extra = rnd.any(string(")]"));
        s.insert(s.begin() + pos, extra);
    } else if (mode == 1) {
        // remove a closing
        int idx = rnd.any(closes);
        s.erase(s.begin() + idx);
    } else {
        // mismatched bracket
        vector<int> allb;
        for (int i = 0; i < (int)s.size(); i++)
            if (s[i]=='('||s[i]==')'||s[i]=='['||s[i]==']')
                allb.push_back(i);
        if (allb.empty()) {
            char extra = rnd.any(string(")]"));
            s += extra;
        } else {
            int pos = rnd.any(allb);
            char c = s[pos];
            if (c == '(' || c == ')') s[pos] = rnd.any(string("]"));
            else s[pos] = rnd.any(string(")"));
        }
    }
    if ((int)s.size() > maxLen) s.resize(maxLen);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 8);
    double pBal = rnd.next(30, 70) / 100.0;
    int maxLineLen = 80;
    for (int i = 0; i < N; i++) {
        bool wantBal = rnd.next() < pBal;
        string line = wantBal ? generateBalanced(maxLineLen)
                              : generateUnbalanced(maxLineLen);
        // avoid accidental termination line
        if (line == ".") line = "x";
        // end with a dot
        if ((int)line.size() >= 100) line.resize(99);
        line += ".";
        println(line);
    }
    // terminating line
    println(".");
    return 0;
}
