#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct Attack {
    long long aura;
    int life;
};

int n;
long long initialAura;
int initialLife;
vector<Attack> attacks;

string upperToken(string token) {
    for (char& ch : token) {
        ch = char(toupper((unsigned char)ch));
    }
    return token;
}

struct Answer {
    bool possible;
    string choices;
};

Answer readAnswer(InStream& stream) {
    string verdict = upperToken(stream.readWord("[A-Za-z]+", "verdict"));

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, ""};
    }

    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    string choices = upperToken(stream.readWord("[AaLl]+", "choices"));
    if ((int)choices.size() != n) {
        stream.quitf(_wa, "choices length must be %d, found %d", n, (int)choices.size());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after choices");
    }

    long long aura = initialAura;
    int life = initialLife;

    for (int i = 0; i < n; ++i) {
        char choice = choices[i];
        long long x = attacks[i].aura;
        int y = attacks[i].life;

        if (x == -1) {
            if (choice != 'L') {
                stream.quitf(_wa, "attack %d must be taken as life damage", i + 1);
            }
            life -= y;
        } else if (y == -1) {
            if (choice != 'A') {
                stream.quitf(_wa, "attack %d must be taken as aura damage", i + 1);
            }
            aura = max(0LL, aura - x);
        } else if (choice == 'A') {
            if (aura < x) {
                stream.quitf(_wa,
                             "attack %d cannot be taken as aura damage: aura=%lld, required=%lld",
                             i + 1,
                             aura,
                             x);
            }
            aura -= x;
        } else {
            life -= y;
        }

        if (life <= 0) {
            stream.quitf(_wa, "life is %d after attack %d", life, i + 1);
        }
    }

    return {true, choices};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialAura = inf.readLong();
    initialLife = inf.readInt();
    attacks.resize(n);
    for (int i = 0; i < n; ++i) {
        attacks[i].aura = inf.readLong();
        attacks[i].life = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury provides a survival witness, participant says NO");
        }
        quitf(_ok, "valid survival witness");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid survival witness while jury says NO");
    }

    quitf(_ok, "both outputs say NO");
}
