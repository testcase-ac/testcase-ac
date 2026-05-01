#include "testlib.h"
using namespace std;

typedef long long ll;

struct Config {
    int maxDepth;
    int maxUnitsRoot;
    int maxUnitsNested;
    int probParen;        // 0..100
    int probEmptyGroup;   // 0..100
    int probMulAtom;      // 0..100
    int probMulGroup;     // 0..100
    int maxMul;           // 2..9
};

int atomMass(char c) {
    if (c == 'H') return 1;
    if (c == 'C') return 12;
    if (c == 'O') return 16;
    return 0;
}

pair<string, ll> buildSequence(const Config &cfg, int depth, bool isRoot);

pair<string, ll> buildUnit(const Config &cfg, int depth) {
    bool canParen = (depth < cfg.maxDepth && cfg.probParen > 0);
    bool chooseParen = canParen && (rnd.next(0, 99) < cfg.probParen);

    if (!chooseParen) {
        // Atom unit: Atom [digit?]
        char atom = rnd.any(string("HCO"));
        int mul = 1;
        if (rnd.next(0, 99) < cfg.probMulAtom) {
            mul = rnd.next(2, cfg.maxMul);
        }
        string res;
        res += atom;
        if (mul > 1) res += char('0' + mul);
        ll mass = 1LL * atomMass(atom) * mul;
        return make_pair(res, mass);
    } else {
        // Parenthesized group: "(" sequence? ")" [digit?]
        string inside;
        ll innerMass = 0;
        bool isEmpty = (rnd.next(0, 99) < cfg.probEmptyGroup);
        if (!isEmpty) {
            auto tmp = buildSequence(cfg, depth + 1, false);
            inside = tmp.first;
            innerMass = tmp.second;
        }
        string res = "(" + inside + ")";
        int mul = 1;
        if (rnd.next(0, 99) < cfg.probMulGroup) {
            mul = rnd.next(2, cfg.maxMul);
        }
        if (mul > 1) res += char('0' + mul);
        ll mass = innerMass * mul;
        return make_pair(res, mass);
    }
}

pair<string, ll> buildSequence(const Config &cfg, int depth, bool isRoot) {
    int maxUnits = isRoot ? cfg.maxUnitsRoot : cfg.maxUnitsNested;
    if (maxUnits < 1) maxUnits = 1;
    int units = rnd.next(1, maxUnits);
    string s;
    ll mass = 0;
    for (int i = 0; i < units; ++i) {
        auto u = buildUnit(cfg, depth);
        s += u.first;
        mass += u.second;
    }
    return make_pair(s, mass);
}

string generateFormula() {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        // Occasionally emit one of the sample formulas directly
        if (rnd.next(0, 9) == 0) {
            vector<string> samples = {
                "H2O",
                "CH(CO2H)3",
                "((CH)2(OH2H)(C(H))O)3"
            };
            return rnd.any(samples);
        }

        int mode = rnd.next(0, 5);
        Config cfg;

        if (mode == 0) {
            // Simple linear formulas without parentheses
            cfg.maxDepth = 0;
            cfg.maxUnitsRoot = rnd.next(2, 8);
            cfg.maxUnitsNested = 3; // unused
            cfg.probParen = 0;
            cfg.probEmptyGroup = 0;
            cfg.probMulAtom = rnd.next(40, 80);
            cfg.probMulGroup = 0;
            cfg.maxMul = rnd.next(3, 5);
        } else if (mode == 1) {
            // Shallow parentheses, like common organic formulas
            cfg.maxDepth = 1;
            cfg.maxUnitsRoot = rnd.next(2, 5);
            cfg.maxUnitsNested = rnd.next(1, 3);
            cfg.probParen = rnd.next(30, 70);
            cfg.probEmptyGroup = rnd.next(10, 40);
            cfg.probMulAtom = rnd.next(30, 70);
            cfg.probMulGroup = rnd.next(40, 80);
            cfg.maxMul = rnd.next(3, 5);
        } else if (mode == 2) {
            // Deeper nesting
            cfg.maxDepth = rnd.next(2, 3);
            cfg.maxUnitsRoot = rnd.next(2, 4);
            cfg.maxUnitsNested = rnd.next(1, 3);
            cfg.probParen = rnd.next(50, 80);
            cfg.probEmptyGroup = rnd.next(0, 30);
            cfg.probMulAtom = rnd.next(20, 60);
            cfg.probMulGroup = rnd.next(50, 90);
            cfg.maxMul = rnd.next(3, 6);
        } else if (mode == 3) {
            // Many empty groups
            cfg.maxDepth = 2;
            cfg.maxUnitsRoot = rnd.next(1, 4);
            cfg.maxUnitsNested = rnd.next(1, 4);
            cfg.probParen = rnd.next(50, 90);
            cfg.probEmptyGroup = rnd.next(50, 90);
            cfg.probMulAtom = rnd.next(20, 40);
            cfg.probMulGroup = rnd.next(50, 90);
            cfg.maxMul = rnd.next(3, 7);
        } else if (mode == 4) {
            // High multipliers, mostly groups
            cfg.maxDepth = 1;
            cfg.maxUnitsRoot = rnd.next(1, 4);
            cfg.maxUnitsNested = rnd.next(1, 3);
            cfg.probParen = rnd.next(60, 90);
            cfg.probEmptyGroup = rnd.next(0, 20);
            cfg.probMulAtom = rnd.next(40, 80);
            cfg.probMulGroup = rnd.next(70, 100);
            cfg.maxMul = 9;
        } else { // mode == 5
            // Balanced random generator
            cfg.maxDepth = rnd.next(1, 3);
            cfg.maxUnitsRoot = rnd.next(2, 5);
            cfg.maxUnitsNested = rnd.next(1, 4);
            cfg.probParen = rnd.next(20, 70);
            cfg.probEmptyGroup = rnd.next(10, 50);
            cfg.probMulAtom = rnd.next(20, 80);
            cfg.probMulGroup = rnd.next(30, 90);
            cfg.maxMul = rnd.next(3, 7);
        }

        auto res = buildSequence(cfg, 0, true);
        string s = res.first;
        ll mass = res.second;

        if (s.empty()) continue;
        if (mass <= 0 || mass > 10000) continue;
        if ((int)s.size() > 100) continue;

        return s;
    }
    // Fallback in the very unlikely event all attempts fail
    return "H2O";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string formula = generateFormula();
    println(formula);

    return 0;
}
