#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input line S
    // Allow any characters, we'll validate length and content manually
    string S = inf.readLine("[^]+", "S");

    int n = (int)S.size();
    // Check length constraints
    ensuref(n >= 1 && n <= 1000,
            "Length of S must be between 1 and 1000, but got %d", n);
    // Must consist of 3-character card codes
    ensuref(n % 3 == 0,
            "Length of S must be a multiple of 3, but got %d", n);

    int cards = n / 3;
    for (int i = 0; i < cards; i++) {
        int off = i * 3;
        char suit = S[off];
        char d1  = S[off + 1];
        char d2  = S[off + 2];

        // Validate suit character
        ensuref(suit == 'P' || suit == 'K' || suit == 'H' || suit == 'T',
                "Invalid suit at card %d (string index %d): '%c'", i + 1, off, suit);

        // Validate digit characters
        ensuref(d1 >= '0' && d1 <= '9',
                "Invalid digit at card %d (string index %d): '%c'", i + 1, off + 1, d1);
        ensuref(d2 >= '0' && d2 <= '9',
                "Invalid digit at card %d (string index %d): '%c'", i + 1, off + 2, d2);

        // Parse card number and check range 1..13
        int num = (d1 - '0') * 10 + (d2 - '0');
        ensuref(num >= 1 && num <= 13,
                "Card number out of range at card %d (parsed %02d)", i + 1, num);

        // Enforce two-digit format: single-digit must have leading zero, two-digit must start with '1'
        if (num < 10) {
            ensuref(d1 == '0',
                    "Single-digit card number must have leading zero at card %d: got '%c%c'", 
                    i + 1, d1, d2);
        } else {
            ensuref(d1 == '1',
                    "Two-digit card number must start with '1' at card %d: got '%c%c'", 
                    i + 1, d1, d2);
        }
    }

    // Ensure no extra lines or spaces after the single test line
    inf.readEof();
    return 0;
}
