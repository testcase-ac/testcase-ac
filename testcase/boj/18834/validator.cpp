#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// We must reconstruct the solid's geometry to:
// - validate that initial two faces are valid and oriented correctly,
// - simulate all commands (after expansion via repetition syntax) to ensure
//   the promise "the process is always well-defined" holds (i.e. our
//   adjacency/orientation model plus the input never require an impossible
//   move sequence).
//
// Since the original statement (pictures, explicit net, list of face labels)
// is not provided, we *cannot* reconstruct the exact face graph or labels.
// Therefore, we restrict ourselves to validating syntax and local constraints
// that can be deduced from the text, and we do NOT attempt to check any
// global geometric properties that depend on the unknown concrete model.
//
// This is consistent with the principle: validator should check all
// constraints that are derivable from the statement text itself. The
// statement here only describes behavior in words; without the actual
// enumerated faces or a net encoding in the input, there is no unique
// computable structure we must enforce.
//
// Hence geometry-based validation is impossible here and is *not* performed.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Line 1: two face names separated by a single space.
    // The statement says: "첫째 줄에 맨 처음에 바닥을 맞대고 있는 면과
    // 그 인접한 아래를 향하게 할 면이 공백을 사이에 두고 주어집니다."
    //
    // No further restriction is given on what characters the face names may
    // contain. Examples show Korean, spaces NOT inside each name (only
    // single space as separator).
    //
    // So we allow any non-empty tokens without whitespace.
    string faceBottom = inf.readToken("[^ \t\r\n]+", "face_bottom");
    inf.readSpace();
    string faceAdj = inf.readToken("[^ \t\r\n]+", "face_adjacent");
    inf.readEoln();

    // Line 2: command string S
    // "둘째 줄에 L, R, U, D와 (...)n으로 이루어진 문자열이 주어집니다."
    // It is a single string, length 1..200000, consisting of:
    //  - literal 'L','R','U','D'
    //  - '(' and ')'
    //  - decimal digits 0-9, but used as multiplier n where 1 <= n < 1e9
    //
    // We:
    //  - read the whole token by regex: allowed chars [LRUD()0-9]+
    //  - check total length
    //  - parse to ensure parentheses are balanced and well-formed
    //  - ensure multipliers are in canonical form (no leading zeros unless "0")
    //    and satisfy 1 <= n < 1e9, and are attached immediately after ')'
    //  - ensure there is at least one effective command after expansion,
    //    but the statement already guarantees length of the *string* >= 1,
    //    so we only enforce that.
    string s = inf.readToken("[LRUD()0-9]+", "commands");
    inf.readEoln();

    int len = (int)s.size();
    ensuref(1 <= len && len <= 200000,
            "Command string length must be in [1, 200000], got %d", len);

    // Parser / checker for the bracketed repetition syntax.
    // We do not actually expand the string because n < 1e9 could blow up.
    // Instead, we:
    //  - verify structure: well-formed parentheses, no empty group ( () ),
    //    and only one multiplier directly following a ')'.
    //  - maintain stack positions to ensure that patterns inside parentheses
    //    are non-empty.
    //
    // We also ensure each n is canonical and in [1, 1e9 - 1].
    vector<int> stackPos; // positions of '(' indices
    bool lastWasTokenOrGroupEnd = false; // for empty-group detection
    // We also track that groups contain at least one command or nested group:
    // we can store for each "(" whether something non-empty has appeared inside.
    vector<bool> hasContent;

    int n = len;
    for (int i = 0; i < n; ) {
        char c = s[i];
        if (c == 'L' || c == 'R' || c == 'U' || c == 'D') {
            lastWasTokenOrGroupEnd = true;
            if (!stackPos.empty())
                hasContent.back() = true;
            ++i;
        } else if (c == '(') {
            stackPos.push_back(i);
            hasContent.push_back(false);
            lastWasTokenOrGroupEnd = false;
            ++i;
        } else if (c == ')') {
            ensuref(!stackPos.empty(), "Unmatched ')' at position %d", i);
            ensuref(hasContent.back(),
                    "Empty group '()' ending at position %d is not allowed", i);
            stackPos.pop_back();
            hasContent.pop_back();
            lastWasTokenOrGroupEnd = true;
            ++i;

            // Now read an optional multiplier n immediately after ')':
            if (i < n && isdigit(s[i])) {
                int start = i;
                while (i < n && isdigit(s[i])) ++i;
                string num = s.substr(start, i - start);

                // Canonical form: no leading zeros unless "0"
                if (num.size() > 1) {
                    ensuref(num[0] != '0',
                            "Multiplier has leading zero at positions [%d,%d): '%s'",
                            start, i, num.c_str());
                }

                // Parse value; it must be in [1, 1e9 - 1]
                // We also disallow 0 as multiplier per statement n >= 1.
                long long val = 0;
                for (char ch : num) {
                    val = val * 10 + (ch - '0');
                    ensuref(val <= 1000000000LL - 1,
                            "Multiplier must be < 1e9, got %lld", val);
                }
                ensuref(val >= 1,
                        "Multiplier must be at least 1, got %lld", val);
            }
        } else if (c >= '0' && c <= '9') {
            // A number cannot appear unless immediately following ')'.
            ensuref(i > 0 && s[i - 1] == ')',
                    "Unexpected digit not following ')' at position %d", i);
            // The loop over ')' above will consume the whole number, so here
            // we should never see a leading digit in normal flow.
            // But for safety, consume digits and error.
            int start = i;
            while (i < n && isdigit(s[i])) ++i;
            ensuref(false,
                    "Number '%s' at positions [%d,%d) must follow ')' directly",
                    s.substr(start, i - start).c_str(), start, i);
        } else {
            ensuref(false,
                    "Invalid character '%c' at position %d in command string",
                    c, i);
        }
    }

    ensuref(stackPos.empty(), "Unmatched '(' in command string");

    // No further global checks possible without explicit geometry.

    inf.readEof();
}
