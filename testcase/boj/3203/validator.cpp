#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read all lines, ensure <= 50 lines and each line length 1..100
    vector<string> lines;
    while (!inf.eof()) {
        string line = inf.readLine("[^]{1,100}", "line");
        lines.push_back(line);
        ensuref((int)lines.size() <= 50,
                "Too many lines: %d (max 50)", (int)lines.size());
    }
    int nLines = lines.size();
    ensuref(nLines >= 2, "Too few lines: %d (need at least BEGIN and STOP)", nLines);

    // Stack to track BEGIN/REPEAT nesting, and prefix products for REPEAT counts
    vector<bool> isRepeat;         // true if REPEAT, false if BEGIN
    vector< __int128 > prodStack;  // prodStack.back() = product of active REPEATs
    prodStack.push_back(1);

    __int128 totalPrints = 0;

    for (int i = 0; i < nLines; i++) {
        const string &line = lines[i];
        int len = line.size();
        // count leading spaces
        int sp = 0;
        while (sp < len && line[sp] == ' ') sp++;
        string content = line.substr(sp);
        int depth = (int)isRepeat.size(); // number of open blocks (BEGIN + REPEAT)
        int lineNo = i + 1;

        // First line must be "BEGIN" with no indent
        if (i == 0) {
            ensuref(sp == 0, "Line %d: BEGIN must have no indent (got %d spaces)", 
                    lineNo, sp);
            ensuref(content == "BEGIN", "Line %d: expected 'BEGIN', got '%s'", 
                    lineNo, content.c_str());
            // push BEGIN marker
            isRepeat.push_back(false);
            prodStack.push_back(prodStack.back());
            continue;
        }

        // Try matching STOP
        if (content == "STOP") {
            ensuref(depth >= 1, "Line %d: STOP without matching BEGIN/REPEAT", lineNo);
            int expectedIndent = (depth - 1) * 3;
            ensuref(sp == expectedIndent,
                    "Line %d: STOP indent %d != expected %d", 
                    lineNo, sp, expectedIndent);
            // pop
            isRepeat.pop_back();
            prodStack.pop_back();
            continue;
        }

        // Try matching REPEAT
        if (content.rfind("REPEAT ", 0) == 0) {
            // indent must equal depth*3
            int expectedIndent = depth * 3;
            ensuref(sp == expectedIndent,
                    "Line %d: REPEAT indent %d != expected %d", 
                    lineNo, sp, expectedIndent);
            // parse integer after "REPEAT "
            string num = content.substr(7);
            ensuref(!num.empty(), "Line %d: REPEAT missing repeat count", lineNo);
            // no extra spaces
            ensuref((int)num.find(' ') == -1,
                    "Line %d: REPEAT has extra spaces", lineNo);
            // digits only
            for (char c : num) {
                ensuref(isdigit(c), "Line %d: REPEAT count '%s' is not a number", 
                        lineNo, num.c_str());
            }
            // no leading zeros
            ensuref(num.size() == 1 || num[0] != '0',
                    "Line %d: REPEAT count has leading zeros: '%s'", 
                    lineNo, num.c_str());
            long long n = stoll(num);
            ensuref(1 <= n && n <= 100000,
                    "Line %d: REPEAT count %lld out of range [1,100000]", 
                    lineNo, n);
            // push REPEAT
            isRepeat.push_back(true);
            __int128 cur = prodStack.back() * n;
            // clamp to >20 to detect overflow in PRINT counting
            if (cur > (__int128)21) cur = (__int128)21;
            prodStack.push_back(cur);
            continue;
        }

        // For other commands, indent must be depth*3
        {
            int expectedIndent = depth * 3;
            ensuref(sp == expectedIndent,
                    "Line %d: indent %d != expected %d", 
                    lineNo, sp, expectedIndent);
        }

        // Try matching PRINT
        if (content.rfind("PRINT ", 0) == 0) {
            // must be exactly "PRINT <var>" with single lowercase var
            ensuref((int)content.size() == 7,
                    "Line %d: PRINT syntax error or extra chars: '%s'", 
                    lineNo, content.c_str());
            char var = content[6];
            ensuref('a' <= var && var <= 'z',
                    "Line %d: PRINT variable '%c' not in [a-z]", 
                    lineNo, var);
            // count executions
            __int128 mult = prodStack.back();
            totalPrints += mult;
            ensuref(totalPrints <= (__int128)20,
                    "Total PRINT executions exceed 20 (got %lld)", 
                    (long long)totalPrints);
            continue;
        }

        // Try matching assignment: <var> = <expr>
        // pattern: var (a-z), space, '=', space, expression
        if (content.size() >= 5 && 
            content[0] >= 'a' && content[0] <= 'z' &&
            content[1] == ' ' && content[2] == '=' && content[3] == ' ') {
            string expr = content.substr(4);
            ensuref(!expr.empty(), "Line %d: empty expression", lineNo);
            // tokenize by single spaces
            vector<string> toks;
            {
                stringstream ss(expr);
                string tk;
                while (ss >> tk) toks.push_back(tk);
            }
            ensuref((int)toks.size() % 2 == 1,
                    "Line %d: malformed expression token count %d", 
                    lineNo, (int)toks.size());
            for (int j = 0; j < (int)toks.size(); j++) {
                if (j % 2 == 1) {
                    // operator
                    ensuref(toks[j] == "+" || toks[j] == "-",
                            "Line %d: unexpected operator '%s'", 
                            lineNo, toks[j].c_str());
                } else {
                    // term
                    const string &t = toks[j];
                    int L = t.size();
                    ensuref(L >= 1, "Line %d: empty term", lineNo);
                    if (L == 1) {
                        char c = t[0];
                        if (isdigit(c)) {
                            // single-digit constant
                            // OK if '0'..'9'
                        } else {
                            // single variable
                            ensuref('a' <= c && c <= 'z',
                                    "Line %d: invalid term '%s'", 
                                    lineNo, t.c_str());
                        }
                    } else {
                        // either multi-digit constant or const*var like "23x"
                        if (isdigit(t[L-1])) {
                            // pure constant
                            for (char c : t) 
                                ensuref(isdigit(c),
                                        "Line %d: invalid constant '%s'", 
                                        lineNo, t.c_str());
                            // no leading zeros
                            ensuref(t.size() == 1 || t[0] != '0',
                                    "Line %d: leading zeros in constant '%s'", 
                                    lineNo, t.c_str());
                            // value <= 999
                            long long v = stoll(t);
                            ensuref(0 <= v && v <= 999,
                                    "Line %d: constant %lld out of range [0,999]", 
                                    lineNo, v);
                        } else {
                            // constant*variable
                            char var = t[L-1];
                            ensuref('a' <= var && var <= 'z',
                                    "Line %d: invalid term '%s'", 
                                    lineNo, t.c_str());
                            string num = t.substr(0, L-1);
                            ensuref(!num.empty(), "Line %d: empty coefficient", 
                                    lineNo);
                            for (char c : num) 
                                ensuref(isdigit(c),
                                        "Line %d: invalid digits in '%s'", 
                                        lineNo, t.c_str());
                            ensuref(num.size() == 1 || num[0] != '0',
                                    "Line %d: leading zeros in coefficient '%s'", 
                                    lineNo, num.c_str());
                            long long v = stoll(num);
                            ensuref(0 <= v && v <= 999,
                                    "Line %d: coefficient %lld out of range [0,999]", 
                                    lineNo, v);
                        }
                    }
                }
            }
            continue;
        }

        // If none matched
        ensuref(false, "Line %d: unrecognized or invalid command: '%s'", 
                lineNo, content.c_str());
    }

    // After all lines, stack must be empty (all blocks closed)
    ensuref(isRepeat.empty(), "Unclosed BEGIN/REPEAT blocks at end of file");

    inf.readEof();
    return 0;
}
