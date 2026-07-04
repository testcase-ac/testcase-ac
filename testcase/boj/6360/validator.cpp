#include "testlib.h"

#include <string>

using namespace std;

const int kMaxGames = 10000;
const int kMaxGuessesPerGame = 10000;
const int kMaxGuessLength = 1000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int games = 0;
    bool expectSecret = true;
    bool sawTerminator = false;

    while (!inf.eof()) {
        string secret = inf.readLine("[A-Z]{5}", "secret");
        ensuref(secret != "LINGO" || !sawTerminator, "multiple terminators");

        if (secret == "LINGO") {
            sawTerminator = true;
            break;
        }

        ++games;
        ensuref(games <= kMaxGames, "too many games: %d", games);
        expectSecret = false;

        int guesses = 0;
        while (!inf.eof()) {
            string line = inf.readLine("[A-Za-z]{0,1000}", "guess_or_separator");
            if (line.empty()) {
                expectSecret = true;
                break;
            }

            ++guesses;
            // CHECK: the statement gives no upper bound on supplied guess lines;
            // cap count and length to keep validation finite while accepting
            // invalid alphabetic guesses such as lowercase or six-letter words.
            ensuref(guesses <= kMaxGuessesPerGame,
                    "too many guesses in game %d: %d", games, guesses);
            ensuref((int)line.size() <= kMaxGuessLength,
                    "guess too long in game %d at guess %d", games, guesses);
        }

        if (inf.eof()) {
            ensuref(false, "missing terminating LINGO dataset");
        }

        ensuref(expectSecret, "internal dataset separator state error");
    }

    ensuref(sawTerminator, "missing terminating LINGO dataset");
    inf.readEof();
}
