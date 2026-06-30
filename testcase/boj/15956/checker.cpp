#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

struct Comparison {
    string left;
    bool equal;
    string right;
};

struct ParsedExpression {
    string text;
    vector<Comparison> comparisons;
    vector<string> terms;
};

struct Signature {
    bool impossible = false;
    vector<vector<int>> equal;
    set<pair<int, int>> notEqual;
};

static bool isVariableStart(char c) {
    return isalpha(static_cast<unsigned char>(c));
}

static bool isDigitChar(char c) {
    return isdigit(static_cast<unsigned char>(c));
}

static bool isIntegerTerm(const string& term) {
    return isDigitChar(term.back());
}

static long long integerValue(const string& term) {
    return stoll(term);
}

static string readOutputLine(InStream& stream) {
    string line = stream.readLine();
    stream.readEof();
    return line;
}

static string parseTerm(InStream& stream, TResult invalidResult, const string& text, int& pos) {
    const int n = static_cast<int>(text.size());
    if (pos >= n) {
        stream.quitf(invalidResult, "expected term at position %d", pos + 1);
    }

    if (isVariableStart(text[pos])) {
        int start = pos;
        while (pos < n && isVariableStart(text[pos])) {
            ++pos;
        }
        return text.substr(start, pos - start);
    }

    int sign = 1;
    if (text[pos] == '-') {
        sign = -1;
        ++pos;
        if (pos >= n) {
            stream.quitf(invalidResult, "minus without digits at position %d", pos);
        }
        if (text[pos] == '0') {
            stream.quitf(invalidResult, "invalid integer -0 at position %d", pos + 1);
        }
    }

    if (pos >= n || !isDigitChar(text[pos])) {
        stream.quitf(invalidResult, "expected term at position %d", pos + 1);
    }

    int start = pos;
    if (text[pos] == '0') {
        ++pos;
    } else {
        long long value = 0;
        while (pos < n && isDigitChar(text[pos])) {
            value = value * 10 + (text[pos] - '0');
            if (value > 1000000000LL) {
                stream.quitf(invalidResult, "integer literal exceeds 1e9 at position %d", start + 1);
            }
            ++pos;
        }
    }

    if (sign == -1) {
        return text.substr(start - 1, pos - start + 1);
    }
    return text.substr(start, pos - start);
}

static ParsedExpression parseExpression(InStream& stream, TResult invalidResult, const string& text) {
    if (text.empty()) {
        stream.quitf(invalidResult, "empty condition");
    }

    ParsedExpression parsed;
    parsed.text = text;
    int pos = 0;
    const int n = static_cast<int>(text.size());
    while (pos < n) {
        string left = parseTerm(stream, invalidResult, text, pos);
        if (pos + 1 >= n || !((text[pos] == '=' && text[pos + 1] == '=') ||
                              (text[pos] == '!' && text[pos + 1] == '='))) {
            stream.quitf(invalidResult, "expected comparison operator at position %d", pos + 1);
        }
        bool equal = text[pos] == '=';
        pos += 2;

        string right = parseTerm(stream, invalidResult, text, pos);
        parsed.comparisons.push_back({left, equal, right});
        parsed.terms.push_back(left);
        parsed.terms.push_back(right);

        if (pos == n) {
            break;
        }
        if (pos + 1 >= n || text[pos] != '&' || text[pos + 1] != '&') {
            stream.quitf(invalidResult, "expected && at position %d", pos + 1);
        }
        pos += 2;
        if (pos == n) {
            stream.quitf(invalidResult, "trailing &&");
        }
    }
    return parsed;
}

static Signature buildSignature(const ParsedExpression& expression,
                                const map<string, int>& termIndex,
                                const vector<string>& allTerms) {
    const int n = static_cast<int>(allTerms.size());
    Dsu dsu(n);
    vector<pair<int, int>> inequalities;

    for (const Comparison& comparison : expression.comparisons) {
        int left = termIndex.at(comparison.left);
        int right = termIndex.at(comparison.right);
        if (comparison.equal) {
            dsu.unite(left, right);
        } else {
            inequalities.push_back({left, right});
        }
    }

    map<int, long long> classConstant;
    map<int, int> canonicalRoot;
    for (int i = 0; i < n; ++i) {
        int root = dsu.find(i);
        auto insertedRoot = canonicalRoot.emplace(root, i);
        if (!insertedRoot.second) {
            insertedRoot.first->second = min(insertedRoot.first->second, i);
        }
        if (!isIntegerTerm(allTerms[i])) {
            continue;
        }
        long long value = integerValue(allTerms[i]);
        auto inserted = classConstant.emplace(root, value);
        if (!inserted.second && inserted.first->second != value) {
            Signature signature;
            signature.impossible = true;
            return signature;
        }
    }

    Signature signature;
    signature.equal.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            signature.equal[i][j] = dsu.find(i) == dsu.find(j);
        }
    }

    for (auto [left, right] : inequalities) {
        int a = dsu.find(left);
        int b = dsu.find(right);
        if (a == b) {
            Signature signature;
            signature.impossible = true;
            return signature;
        }
        bool tautology = classConstant.count(a) && classConstant.count(b) &&
                         classConstant[a] != classConstant[b];
        if (!tautology) {
            a = canonicalRoot[a];
            b = canonicalRoot[b];
            if (a > b) {
                swap(a, b);
            }
            signature.notEqual.insert({a, b});
        }
    }
    return signature;
}

static bool sameSignature(const Signature& a, const Signature& b) {
    if (a.impossible || b.impossible) {
        return a.impossible == b.impossible;
    }
    return a.equal == b.equal && a.notEqual == b.notEqual;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    ParsedExpression input = parseExpression(inf, _fail, inf.readLine());
    inf.readEof();

    ParsedExpression jury = parseExpression(ans, _fail, readOutputLine(ans));
    ParsedExpression participant = parseExpression(ouf, _wa, readOutputLine(ouf));

    vector<string> allTerms;
    allTerms.insert(allTerms.end(), input.terms.begin(), input.terms.end());
    allTerms.insert(allTerms.end(), jury.terms.begin(), jury.terms.end());
    allTerms.insert(allTerms.end(), participant.terms.begin(), participant.terms.end());
    sort(allTerms.begin(), allTerms.end());
    allTerms.erase(unique(allTerms.begin(), allTerms.end()), allTerms.end());

    map<string, int> termIndex;
    for (int i = 0; i < static_cast<int>(allTerms.size()); ++i) {
        termIndex[allTerms[i]] = i;
    }

    Signature expected = buildSignature(input, termIndex, allTerms);
    Signature jurySignature = buildSignature(jury, termIndex, allTerms);
    Signature participantSignature = buildSignature(participant, termIndex, allTerms);

    if (!sameSignature(expected, jurySignature)) {
        quitf(_fail, "jury output is not equivalent to the input condition");
    }
    if (!sameSignature(expected, participantSignature)) {
        quitf(_wa, "participant output is not equivalent to the input condition");
    }

    if (participant.text.size() < jury.text.size()) {
        quitf(_fail, "participant output is shorter than jury output: participant=%d jury=%d",
              static_cast<int>(participant.text.size()), static_cast<int>(jury.text.size()));
    }
    if (participant.text.size() > jury.text.size()) {
        quitf(_wa, "participant output is longer than jury output: participant=%d jury=%d",
              static_cast<int>(participant.text.size()), static_cast<int>(jury.text.size()));
    }

    quitf(_ok, "equivalent shortest condition with length %d",
          static_cast<int>(participant.text.size()));
}
