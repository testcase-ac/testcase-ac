#include "testlib.h"

#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 33333, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    int note_count = 3 * n;
    ensuref(k <= note_count, "K must be at most 3N: K=%d, 3N=%d", k, note_count);

    for (int day = 1; day <= n; ++day) {
        unordered_set<string> notes;
        for (int entry = 1; entry <= 3; ++entry) {
            string note = inf.readLine("[^]{1,50}", "note");
            for (char ch : note) {
                ensuref(32 <= ch && ch <= 126,
                        "note at day %d entry %d contains non-printable ASCII character",
                        day,
                        entry);
            }
            ensuref(any_of(note.begin(), note.end(), [](char ch) { return ch != ' '; }),
                    "note at day %d entry %d must not be whitespace-only",
                    day,
                    entry);
            ensuref(notes.insert(note).second,
                    "duplicate note within day %d at entry %d: %s",
                    day,
                    entry,
                    note.c_str());
        }
    }

    inf.readEof();
}
