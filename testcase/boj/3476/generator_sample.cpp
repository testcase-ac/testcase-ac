#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

namespace {

const vector<string> kSubjects = {
    "I", "you", "Alice", "Bob", "Carol", "Dave", "Joe", "Michal"};
const vector<string> kVerbs = {
    "like", "read", "walk", "smile", "help", "trust", "watch", "cook"};
const vector<string> kObjects = {
    "", "books", "hotdogs", "to work", "there", "new products", "red cars",
    "at home"};

bool isThirdPerson(const string& subject) {
    return subject != "I" && subject != "you";
}

string verbForSubject(const string& verb, const string& subject) {
    return isThirdPerson(subject) ? verb + "s" : verb;
}

string auxForSubject(const string& subject, bool negative) {
    if (isThirdPerson(subject)) return negative ? "doesn't" : "does";
    return negative ? "don't" : "do";
}

string withObject(const string& base, const string& object) {
    if (object.empty()) return base;
    return base + " " + object;
}

string statementLine(const string& subject, bool positive, const string& verb,
                     const string& object) {
    if (positive) {
        return withObject(subject + " " + verbForSubject(verb, subject), object) + ".";
    }
    return withObject(subject + " " + auxForSubject(subject, true) + " " + verb,
                      object) + ".";
}

string yesNoQuestion(const string& subject, const string& verb,
                     const string& object) {
    return withObject(auxForSubject(subject, false) + " " + subject + " " + verb,
                      object) + "?";
}

string whoQuestion(const string& verb, const string& object) {
    return withObject("who " + verbForSubject(verb, "who"), object) + "?";
}

string whatQuestion(const string& subject) {
    return "what " + auxForSubject(subject, false) + " " + subject + " do?";
}

struct Dialogue {
    vector<string> lines;
    set<string> statements;

    void addStatement(const string& line) {
        if (statements.insert(line).second) lines.push_back(line);
    }

    void addQuestion(const string& line) {
        lines.push_back(line);
    }
};

string pickSubject(bool allowGeneric) {
    if (allowGeneric && rnd.next(5) == 0) {
        return rnd.next(2) == 0 ? "everybody" : "nobody";
    }
    return rnd.any(kSubjects);
}

void addRandomFact(Dialogue& dialogue, bool allowGeneric) {
    string subject = pickSubject(allowGeneric);
    string verb = rnd.any(kVerbs);
    string object = rnd.any(kObjects);
    bool positive = subject == "everybody" || subject == "nobody" || rnd.next(2) == 0;
    dialogue.addStatement(statementLine(subject, positive, verb, object));
}

Dialogue emptyDialogue() {
    Dialogue dialogue;
    int questions = rnd.next(0, 2);
    for (int i = 0; i < questions; ++i) {
        dialogue.addQuestion(yesNoQuestion(rnd.any(kSubjects), rnd.any(kVerbs),
                                           rnd.any(kObjects)));
    }
    return dialogue;
}

Dialogue directFactsDialogue() {
    Dialogue dialogue;
    int facts = rnd.next(1, 6);
    for (int i = 0; i < facts; ++i) addRandomFact(dialogue, true);
    for (int i = 0; i < rnd.next(2, 5); ++i) {
        string verb = rnd.any(kVerbs);
        string object = rnd.any(kObjects);
        int kind = rnd.next(3);
        if (kind == 0) {
            dialogue.addQuestion(yesNoQuestion(rnd.any(kSubjects), verb, object));
        } else if (kind == 1) {
            dialogue.addQuestion(whoQuestion(verb, object));
        } else {
            dialogue.addQuestion(whatQuestion(rnd.any(kSubjects)));
        }
    }
    return dialogue;
}

Dialogue enumerationDialogue() {
    Dialogue dialogue;
    string verb = rnd.any(kVerbs);
    string object = rnd.any(kObjects);
    vector<string> subjects = kSubjects;
    shuffle(subjects.begin(), subjects.end());
    int count = rnd.next(2, 5);
    for (int i = 0; i < count; ++i) {
        dialogue.addStatement(statementLine(subjects[i], true, verb, object));
    }
    dialogue.addQuestion(whoQuestion(verb, object));
    dialogue.addQuestion(whatQuestion(subjects[rnd.next(count)]));
    return dialogue;
}

Dialogue genericDialogue() {
    Dialogue dialogue;
    string verb = rnd.any(kVerbs);
    string object = rnd.any(kObjects);
    if (rnd.next(2) == 0) {
        dialogue.addStatement(statementLine("everybody", true, verb, object));
    } else {
        dialogue.addStatement(statementLine("nobody", true, verb, object));
    }
    addRandomFact(dialogue, false);
    dialogue.addQuestion(whoQuestion(verb, object));
    dialogue.addQuestion(yesNoQuestion(rnd.any(kSubjects), verb, object));
    dialogue.addQuestion(whatQuestion(rnd.any(kSubjects)));
    return dialogue;
}

Dialogue contradictionDialogue() {
    Dialogue dialogue;
    string subject = rnd.any(kSubjects);
    string verb = rnd.any(kVerbs);
    string object = rnd.any(kObjects);
    dialogue.addStatement(statementLine(subject, true, verb, object));
    dialogue.addStatement(statementLine(subject, false, verb, object));
    for (int i = 0; i < rnd.next(1, 4); ++i) addRandomFact(dialogue, true);
    dialogue.addQuestion(yesNoQuestion(subject, verb, object));
    dialogue.addQuestion(whoQuestion(verb, object));
    return dialogue;
}

Dialogue randomDialogue() {
    int mode = rnd.next(5);
    if (mode == 0) return emptyDialogue();
    if (mode == 1) return directFactsDialogue();
    if (mode == 2) return enumerationDialogue();
    if (mode == 3) return genericDialogue();
    return contradictionDialogue();
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        Dialogue dialogue = randomDialogue();
        for (const string& line : dialogue.lines) println(line);
        println("bye!");
    }

    return 0;
}
