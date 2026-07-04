#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomUpperWord(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('A' + rnd.next(26));
    }
    return s;
}

string randomSecret() {
    string s;
    do {
        s = randomUpperWord(5);
    } while (s == "LINGO");
    return s;
}

string mutateSecret(const string& secret) {
    string guess = secret;
    int changes = rnd.next(1, 3);
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(5);
        char c;
        do {
            c = char('A' + rnd.next(26));
        } while (c == guess[pos]);
        guess[pos] = c;
    }
    return guess;
}

string invalidGuess(const string& secret) {
    int mode = rnd.next(4);
    if (mode == 0) {
        string s = secret;
        s[rnd.next(5)] = char('a' + rnd.next(26));
        return s;
    }
    if (mode == 1) {
        return randomUpperWord(rnd.next(1, 4));
    }
    if (mode == 2) {
        return randomUpperWord(rnd.next(6, 9));
    }

    string s = randomUpperWord(5);
    s[rnd.next(5)] = char('a' + rnd.next(26));
    return s;
}

vector<string> buildGuesses(const string& secret, int mode) {
    vector<string> guesses;

    if (mode == 0) {
        int before = rnd.next(0, 2);
        for (int i = 0; i < before; ++i) {
            guesses.push_back(mutateSecret(secret));
        }
        guesses.push_back(secret);
        return guesses;
    }

    if (mode == 1) {
        int count = rnd.next(1, 6);
        for (int i = 0; i < count; ++i) {
            guesses.push_back(i % 2 == 0 ? invalidGuess(secret) : mutateSecret(secret));
        }
        return guesses;
    }

    if (mode == 2) {
        int count = rnd.next(7, 9);
        for (int i = 0; i < count; ++i) {
            guesses.push_back(mutateSecret(secret));
        }
        return guesses;
    }

    return guesses;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int games = rnd.next(2, 5);
    for (int game = 0; game < games; ++game) {
        string secret = randomSecret();
        println(secret);

        vector<string> guesses = buildGuesses(secret, game % 4);
        if (game == games - 1 && guesses.empty()) {
            guesses.push_back(invalidGuess(secret));
        }
        for (const string& guess : guesses) {
            println(guess);
        }
        println("");
    }

    println("LINGO");
    return 0;
}
