#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string noteName(int pitch) {
    static const vector<string> names = {
        "C", "C#", "D", "D#", "E", "F", "F#",
        "G", "G#", "A", "A#", "B"
    };
    int octave = pitch / 12;
    int semitone = pitch % 12;
    return names[semitone][0] + to_string(octave) + names[semitone].substr(1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 4 ? 35 : 14);
    int lo = 0;
    int hi = 119;

    if (mode == 0) {
        lo = rnd.next(0, 95);
        hi = min(119, lo + rnd.next(1, 18));
    } else if (mode == 1) {
        lo = rnd.next(0, 12);
        hi = rnd.next(107, 119);
    } else if (mode == 2) {
        int center = rnd.next(6, 113);
        int width = rnd.next(1, 6);
        lo = center - width;
        hi = center + width;
    }

    int left = rnd.next(lo, hi);
    int right = rnd.next(lo, hi);
    while (right == left) {
        right = rnd.next(lo, hi);
    }

    vector<int> notes;
    notes.reserve(n);
    for (int i = 0; i < n; ++i) {
        int pitch;
        if (mode == 1) {
            pitch = (i % 2 == 0) ? rnd.next(0, 12) : rnd.next(107, 119);
        } else if (mode == 3) {
            vector<int> choices = {left, right, rnd.next(lo, hi)};
            pitch = rnd.any(choices);
        } else {
            pitch = rnd.next(lo, hi);
        }
        notes.push_back(pitch);
    }

    println(noteName(left), noteName(right));
    println(n);
    vector<string> rendered;
    rendered.reserve(notes.size());
    for (int pitch : notes) {
        rendered.push_back(noteName(pitch));
    }
    println(rendered);

    return 0;
}
