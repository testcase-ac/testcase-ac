#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

static string randomWord(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string s;
    for (int i = 0; i < len; i++) {
        char c = char('a' + rnd.next(0, 25));
        s.push_back(c);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of test cases
    int T = rnd.next(1, 5);
    println(T);

    // Pool of possible animal names
    vector<string> animalNames = {
        "dog", "cat", "cow", "sheep", "duck",
        "frog", "lion", "tiger", "mouse", "horse",
        "goat", "pig", "bear", "wolf", "rabbit"
    };

    for (int tc = 0; tc < T; tc++) {
        // Number of other animals
        int A = rnd.next(1, 5);
        // Shuffle and pick distinct animals
        shuffle(animalNames.begin(), animalNames.end());
        vector<string> selAnimals(animalNames.begin(), animalNames.begin() + A);

        // Generate distinct sounds for other animals
        set<string> usedSounds;
        vector<string> knownSounds;
        while ((int)knownSounds.size() < A) {
            string w = randomWord(1, 5);
            if (!usedSounds.count(w)) {
                usedSounds.insert(w);
                knownSounds.push_back(w);
            }
        }

        // Generate distinct fox sounds
        int Fd = rnd.next(1, 3);
        vector<string> foxSounds;
        while ((int)foxSounds.size() < Fd) {
            string w = randomWord(1, 5);
            if (!usedSounds.count(w)) {
                usedSounds.insert(w);
                foxSounds.push_back(w);
            }
        }

        // Build the recording sequence
        vector<string> seq;
        // Ensure each known sound appears
        for (auto &w : knownSounds) seq.push_back(w);
        // Ensure each fox sound appears
        for (auto &w : foxSounds) seq.push_back(w);

        // Additional repeats
        int totalMin = seq.size();
        int N = rnd.next(totalMin, totalMin + 5);
        vector<string> allSounds = knownSounds;
        allSounds.insert(allSounds.end(), foxSounds.begin(), foxSounds.end());
        int extra = N - (int)seq.size();
        for (int i = 0; i < extra; i++) {
            seq.push_back(rnd.any(allSounds));
        }

        // Shuffle the recording
        shuffle(seq.begin(), seq.end());

        // Output the test case
        println(seq);
        for (int i = 0; i < A; i++) {
            println(selAnimals[i], "goes", knownSounds[i]);
        }
        println("what does the fox say?");
    }

    return 0;
}
