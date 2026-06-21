#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<string> notes = {
        "A", "A#", "Bb", "B", "C", "C#", "Db", "D", "D#", "Eb",
        "E", "F", "F#", "Gb", "G", "G#", "Ab",
    };
    const set<string> tonalities = {"major", "minor"};

    int cases = 0;
    while (!inf.eof()) {
        string note = inf.readToken("[A-G]#?|[A-G]b?", "note");
        ensuref(notes.count(note) == 1, "invalid note name: %s", note.c_str());
        inf.readSpace();

        string tonality = inf.readToken("[a-z]{5}", "tonality");
        ensuref(tonalities.count(tonality) == 1,
                "invalid tonality: %s", tonality.c_str());
        inf.readEoln();

        ++cases;
        // CHECK: the statement gives EOF-terminated cases with no case-count bound.
        ensuref(cases <= 100000, "too many test cases: %d", cases);
    }

    ensuref(cases >= 1, "input must contain at least one test case");
    inf.readEof();
}
