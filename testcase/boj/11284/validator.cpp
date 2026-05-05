#include "testlib.h"
#include <string>

using namespace std;

// Decode a single UTF-8 sequence starting at position pos.
// Returns Unicode code point, and advances pos.
// On any invalid encoding, calls ensuref(false, ...).
unsigned int readOneUtf8Char(const string &s, int &pos) {
    ensuref(pos < (int)s.size(), "No bytes left when trying to read UTF-8 character");
    unsigned char c = (unsigned char)s[pos];

    if (c < 0x80) {
        // 1-byte ASCII (not expected for this problem but allow structurally)
        pos += 1;
        return c;
    }

    // Determine length
    int len = 0;
    unsigned int code = 0;
    if ((c & 0xE0) == 0xC0) {
        len = 2;
        code = c & 0x1F;
    } else if ((c & 0xF0) == 0xE0) {
        len = 3;
        code = c & 0x0F;
    } else if ((c & 0xF8) == 0xF0) {
        len = 4;
        code = c & 0x07;
    } else {
        ensuref(false, "Invalid UTF-8 leading byte 0x%X", c);
    }

    ensuref(pos + len <= (int)s.size(),
            "Truncated UTF-8 sequence at position %d", pos);

    for (int i = 1; i < len; ++i) {
        unsigned char cc = (unsigned char)s[pos + i];
        ensuref((cc & 0xC0) == 0x80,
                "Invalid UTF-8 continuation byte 0x%X at position %d", cc, pos + i);
        code = (code << 6) | (cc & 0x3F);
    }

    // Check for overlong encodings
    if (len == 2) {
        ensuref(code >= 0x80 && code <= 0x7FF,
                "Overlong or out-of-range 2-byte UTF-8 encoding (U+%X)", code);
    } else if (len == 3) {
        ensuref(code >= 0x800 && code <= 0xFFFF,
                "Overlong or out-of-range 3-byte UTF-8 encoding (U+%X)", code);
    } else if (len == 4) {
        ensuref(code >= 0x10000 && code <= 0x10FFFF,
                "Overlong or out-of-range 4-byte UTF-8 encoding (U+%X)", code);
    }

    pos += len;
    return code;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the entire first line as is (can contain UTF-8 multibyte character)
    string line = inf.readLine("[^]*", "line");

    // There must be exactly one character (in Unicode scalar sense).
    ensuref(!line.empty(), "Input line must not be empty");

    int pos = 0;
    unsigned int codepoint = readOneUtf8Char(line, pos);

    // Ensure no extra bytes after the first character (ignoring nothing).
    ensuref(pos == (int)line.size(),
            "Input must contain exactly one Unicode character, but extra bytes are present");

    // Problem guarantees: the character is always Hangul syllable U+AC00..U+D7A3
    ensuref(codepoint >= 0xAC00 && codepoint <= 0xD7A3,
            "Character U+%04X is not in the required Hangul syllable range U+AC00..U+D7A3",
            codepoint);

    inf.readEof();
}
