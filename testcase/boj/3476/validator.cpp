#include "testlib.h"

#include <cctype>
#include <set>
#include <string>
#include <vector>

using namespace std;

namespace {

const int kMaxLineLength = 100;
const int kMaxStatementsPerDialogue = 100;
const int kMaxDialogues = 100000;
// CHECK: The statement does not cap the number of lines in a dialogue. This
// keeps primarily string input below the local practical size limit.
const int kMaxTotalDialogueLines = 100000;

bool isWord(const string& s) {
    if (s.empty()) return false;
    for (char ch : s) {
        if (!isalpha(static_cast<unsigned char>(ch))) return false;
    }
    return true;
}

bool hasCleanSpacing(const string& s) {
    if (s.empty() || s.front() == ' ' || s.back() == ' ') return false;
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i - 1] == ' ' && s[i] == ' ') return false;
    }
    return true;
}

bool isPrintableAscii(const string& s) {
    for (char ch : s) {
        if (ch < 32 || ch > 126) return false;
    }
    return true;
}

vector<string> splitWords(const string& s) {
    vector<string> words;
    size_t pos = 0;
    while (pos < s.size()) {
        size_t next = s.find(' ', pos);
        if (next == string::npos) next = s.size();
        words.push_back(s.substr(pos, next - pos));
        pos = next + 1;
    }
    return words;
}

string tailAfterWords(const string& s, int wordCount) {
    size_t pos = 0;
    for (int i = 0; i < wordCount; ++i) {
        size_t next = s.find(' ', pos);
        if (next == string::npos) return "";
        pos = next + 1;
    }
    return s.substr(pos);
}

bool isThirdPersonSubject(const string& subject) {
    return subject != "I" && subject != "you";
}

bool auxMatchesSubject(const string& aux, const string& subject) {
    if (subject == "I" || subject == "you") return aux == "do" || aux == "don't";
    return aux == "does" || aux == "doesn't";
}

void validateObject(const string& object, char terminator, const char* context) {
    if (object.empty()) return;
    ensuref(object.find('.') == string::npos, "%s object contains dot", context);
    ensuref(object.find('?') == string::npos, "%s object contains question mark", context);
    ensuref(object.find('!') == string::npos, "%s object contains exclamation mark", context);
    ensuref(object.back() != terminator, "%s object includes sentence terminator", context);
}

void validatePositiveVerb(const string& subject, const string& verb, const char* context) {
    ensuref(isWord(verb), "%s predicate is not a word", context);
    if (isThirdPersonSubject(subject)) {
        ensuref(verb.size() >= 2 && verb.back() == 's',
                "%s third-person predicate must end with s", context);
    }
}

bool validateStatement(const string& body) {
    vector<string> words = splitWords(body);
    ensuref(words.size() >= 2, "statement has too few words: %s", body.c_str());

    const string& subject = words[0];
    ensuref(isWord(subject), "statement subject is not a word: %s", subject.c_str());

    if (words[1] == "don't" || words[1] == "doesn't") {
        ensuref(subject != "everybody" && subject != "nobody",
                "generic subjects cannot use explicit negative form");
        ensuref(auxMatchesSubject(words[1], subject),
                "negative auxiliary does not match subject: %s %s",
                subject.c_str(), words[1].c_str());
        ensuref(words.size() >= 3, "negative statement has no predicate");
        ensuref(isWord(words[2]), "negative statement predicate is not a word");
        validateObject(tailAfterWords(body, 3), '.', "statement");
        return true;
    }

    validatePositiveVerb(subject, words[1], "statement");
    validateObject(tailAfterWords(body, 2), '.', "statement");
    return true;
}

bool validateQuestion(const string& body) {
    vector<string> words = splitWords(body);
    ensuref(!words.empty(), "empty question body");

    if (words[0] == "do" || words[0] == "does") {
        ensuref(words.size() >= 3, "do/does question has too few words");
        ensuref(isWord(words[1]), "do/does question subject is not a word");
        ensuref(auxMatchesSubject(words[0], words[1]),
                "question auxiliary does not match subject: %s %s",
                words[0].c_str(), words[1].c_str());
        ensuref(isWord(words[2]), "do/does question predicate is not a word");
        validateObject(tailAfterWords(body, 3), '?', "question");
        return true;
    }

    if (words[0] == "who") {
        ensuref(words.size() >= 2, "who question has no predicate");
        validatePositiveVerb("who", words[1], "who question");
        validateObject(tailAfterWords(body, 2), '?', "question");
        return true;
    }

    if (words[0] == "what") {
        ensuref(words.size() == 4, "what question must have form: what do/does subject do");
        ensuref(words[1] == "do" || words[1] == "does",
                "what question must use do or does");
        ensuref(isWord(words[2]), "what question subject is not a word");
        ensuref(auxMatchesSubject(words[1], words[2]),
                "what question auxiliary does not match subject: %s %s",
                words[1].c_str(), words[2].c_str());
        ensuref(words[3] == "do", "what question must end with do");
        return true;
    }

    quitf(_wa, "unknown question form: %s", body.c_str());
}

void validateLineBasics(const string& line) {
    ensuref(!line.empty(), "dialogue line must not be empty");
    ensuref(static_cast<int>(line.size()) <= kMaxLineLength,
            "dialogue line exceeds %d characters", kMaxLineLength);
    ensuref(isPrintableAscii(line), "dialogue line contains non-printable ASCII");
    ensuref(hasCleanSpacing(line), "dialogue line has leading, trailing, or repeated spaces");
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, kMaxDialogues, "T");
    inf.readEoln();

    int totalDialogueLines = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);
        int statements = 0;

        while (true) {
            string line = inf.readLine("[^]{1,100}", "dialogue_line");
            validateLineBasics(line);
            ++totalDialogueLines;
            ensuref(totalDialogueLines <= kMaxTotalDialogueLines,
                    "too many total dialogue lines");

            char terminator = line.back();
            ensuref(terminator == '.' || terminator == '?' || terminator == '!',
                    "dialogue line must end with '.', '?', or '!'");

            string body = line.substr(0, line.size() - 1);
            ensuref(!body.empty(), "sentence body must not be empty");
            ensuref(body.find('.') == string::npos, "sentence body contains dot");
            ensuref(body.find('?') == string::npos, "sentence body contains question mark");
            ensuref(body.find('!') == string::npos, "sentence body contains exclamation mark");

            if (terminator == '!') {
                break;
            }
            if (terminator == '.') {
                validateStatement(body);
                ++statements;
                ensuref(statements <= kMaxStatementsPerDialogue,
                        "more than %d statements in one dialogue",
                        kMaxStatementsPerDialogue);
            } else {
                validateQuestion(body);
            }
        }
    }

    inf.readEof();
}
