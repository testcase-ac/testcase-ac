#include "testlib.h"
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There must be exactly 5 cards
    set<pair<char,int>> used;
    for (int i = 0; i < 5; i++) {
        // Each line must be exactly "C N" where C ∈ {R,B,Y,G} and N ∈ [1-9], with exactly one space.
        // We escape the space in the regex so it's matched literally.
        string line = inf.readLine("[RBYG]\\ [1-9]", "card");
        // Parse color and number
        char color = line[0];
        int number = line[2] - '0';
        // Check uniqueness
        pair<char,int> card = make_pair(color, number);
        ensuref(!used.count(card),
                "Duplicate card at line %d: '%c %d'", i + 1, color, number);
        used.insert(card);
    }

    // No extra data
    inf.readEof();
    return 0;
}
