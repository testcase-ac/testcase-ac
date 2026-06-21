#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> uniqueNotes = {"A", "B", "C", "D", "E", "F", "G"};
    const vector<pair<string, string>> alternatePairs = {
        {"A#", "Bb"}, {"C#", "Db"}, {"D#", "Eb"}, {"F#", "Gb"}, {"G#", "Ab"},
    };
    const vector<string> tonalities = {"major", "minor"};

    vector<string> notes;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        notes = uniqueNotes;
    } else if (mode == 1) {
        for (const auto& p : alternatePairs) {
            notes.push_back(p.first);
        }
    } else if (mode == 2) {
        for (const auto& p : alternatePairs) {
            notes.push_back(p.second);
        }
    } else {
        notes = uniqueNotes;
        for (const auto& p : alternatePairs) {
            notes.push_back(p.first);
            notes.push_back(p.second);
        }
    }

    shuffle(notes.begin(), notes.end());

    int cases = rnd.next(1, min<int>(30, notes.size() + rnd.next(0, 13)));
    for (int i = 0; i < cases; ++i) {
        string note = notes[i % notes.size()];
        if (i >= static_cast<int>(notes.size()) && rnd.next(0, 3) == 0) {
            note = rnd.any(uniqueNotes);
        } else if (i >= static_cast<int>(notes.size())) {
            const auto& p = rnd.any(alternatePairs);
            note = rnd.next(0, 1) == 0 ? p.first : p.second;
        }

        string tonality;
        if (mode == 4) {
            tonality = tonalities[i % 2];
        } else {
            tonality = rnd.any(tonalities);
        }
        println(note, tonality);
    }

    return 0;
}
