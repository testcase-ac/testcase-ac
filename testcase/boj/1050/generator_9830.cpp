#include "testlib.h"
using namespace std;

struct Recipe {
    string out;
    vector<pair<int, string>> in;
};

bool existsName(const vector<string>& v, const string& s) {
    for (const auto& x : v)
        if (x == s) return true;
    return false;
}

string genUniqueName(vector<string>& existing) {
    while (true) {
        int len = rnd.next(1, 4);
        string s;
        for (int i = 0; i < len; ++i)
            s += char('A' + rnd.next(0, 25));
        if (s == "LOVE") continue;
        if (!existsName(existing, s)) {
            existing.push_back(s);
            return s;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<string,int>> market;
    vector<Recipe> recipes;
    vector<string> allNames;

    int caseType = rnd.next(0, 6);

    if (caseType == 5) {
        // Hard-coded overflow case (similar to example 6)
        market.clear();
        recipes.clear();

        market.push_back({"HONEYBIT", 100});

        recipes.push_back({"LOVE", { {6, "HONEYMEGABYTE"} }});
        recipes.push_back({"HONEYMEGABYTE", { {2, "HONEYFIFTYTWELVEKBYTES"} }});
        recipes.push_back({"HONEYFIFTYTWELVEKBYTES", { {8, "HONEYSIXTYFOURKBYTES"} }});
        recipes.push_back({"HONEYSIXTYFOURKBYTES", { {8, "HONEYEIGHTKBYTES"} }});
        recipes.push_back({"HONEYEIGHTKBYTES", { {8, "HONEYKBYTE"} }});
        recipes.push_back({"HONEYKBYTE", { {2, "EIGHTBYEIGHTWORDS"} }});
        recipes.push_back({"EIGHTBYEIGHTWORDS", { {8, "EIGHTWORDS"} }});
        recipes.push_back({"EIGHTWORDS", { {8, "HONEYWORD"} }});
        recipes.push_back({"HONEYWORD", { {8, "HONEYBYTE"} }});
        recipes.push_back({"HONEYBYTE", { {8, "HONEYBIT"} }});

    } else if (caseType == 0) {
        // LOVE only as market item; formulas (if any) do not produce LOVE
        allNames.push_back("LOVE");
        int lovePrice = rnd.next(1, 100);
        market.push_back({"LOVE", lovePrice});

        int extraBasics = rnd.next(0, 3);
        for (int i = 0; i < extraBasics; ++i) {
            string nm = genUniqueName(allNames);
            int pr = rnd.next(1, 100);
            market.push_back({nm, pr});
        }

        int F = rnd.next(0, 3);
        for (int i = 0; i < F; ++i) {
            Recipe r;
            // Ensure out is not LOVE
            string outName;
            if ((int)allNames.size() <= 1) {
                outName = genUniqueName(allNames);
            } else {
                // choose from existing excluding LOVE with some chance, or new
                vector<string> cand;
                for (auto &s : allNames)
                    if (s != "LOVE") cand.push_back(s);
                if (cand.empty() || rnd.next(0, 2) == 0) {
                    outName = genUniqueName(allNames);
                } else {
                    outName = rnd.any(cand);
                }
            }
            r.out = outName;

            int k = rnd.next(1, 3);
            for (int j = 0; j < k; ++j) {
                string ing = rnd.any(allNames);
                int coef = rnd.next(1, 9);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

    } else if (caseType == 1) {
        // Acyclic chain: basics -> intermediates -> LOVE
        allNames.push_back("LOVE");
        vector<string> basics;
        vector<string> inter;

        int B = rnd.next(1, 3);
        for (int i = 0; i < B; ++i) {
            string nm = genUniqueName(allNames);
            basics.push_back(nm);
        }
        int P = rnd.next(0, 3);
        for (int i = 0; i < P; ++i) {
            string nm = genUniqueName(allNames);
            inter.push_back(nm);
        }

        // Market
        for (auto &b : basics) {
            int pr = rnd.next(1, 20);
            market.push_back({b, pr});
        }
        for (auto &pname : inter) {
            if (rnd.next(0, 1) == 1) {
                int pr = rnd.next(5, 40);
                market.push_back({pname, pr});
            }
        }
        if (rnd.next(0, 1) == 1) {
            int pr = rnd.next(20, 100);
            market.push_back({"LOVE", pr});
        }

        // Recipes for intermediates from basics only
        for (auto &iname : inter) {
            Recipe r;
            r.out = iname;
            int k = rnd.next(1, 3);
            for (int j = 0; j < k; ++j) {
                string ing = rnd.any(basics);
                int coef = rnd.next(1, 5);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

        // Recipes for LOVE from basics and intermediates
        vector<string> cand = basics;
        cand.insert(cand.end(), inter.begin(), inter.end());
        int Rc = rnd.next(1, 3);
        for (int i = 0; i < Rc; ++i) {
            Recipe r;
            r.out = "LOVE";
            int k = rnd.next(1, 3);
            for (int j = 0; j < k; ++j) {
                string ing = rnd.any(cand);
                int coef = rnd.next(1, 4);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

    } else if (caseType == 2) {
        // Multiple recipes per potion, some with cycles but overall acyclic paths exist
        allNames.push_back("LOVE");
        vector<string> basics;
        vector<string> inter;

        int B = rnd.next(1, 3);
        for (int i = 0; i < B; ++i) {
            string nm = genUniqueName(allNames);
            basics.push_back(nm);
        }
        int P = rnd.next(1, 3);
        for (int i = 0; i < P; ++i) {
            string nm = genUniqueName(allNames);
            inter.push_back(nm);
        }

        // Market
        for (auto &b : basics) {
            int pr = rnd.next(1, 20);
            market.push_back({b, pr});
        }
        for (auto &pname : inter) {
            if (rnd.next(0, 1) == 1) {
                int pr = rnd.next(5, 40);
                market.push_back({pname, pr});
            }
        }
        if (rnd.next(0, 2) == 0) { // sometimes direct LOVE
            int pr = rnd.next(30, 100);
            market.push_back({"LOVE", pr});
        }

        vector<string> candAll = basics;
        candAll.insert(candAll.end(), inter.begin(), inter.end());

        // For each intermediate, at least one recipe from basics, maybe another with more variety
        for (auto &iname : inter) {
            // First acyclic recipe from basics
            {
                Recipe r;
                r.out = iname;
                int k = rnd.next(1, 3);
                for (int j = 0; j < k; ++j) {
                    string ing = rnd.any(basics);
                    int coef = rnd.next(1, 5);
                    r.in.push_back({coef, ing});
                }
                recipes.push_back(r);
            }
            // Optional second recipe, possibly involving other intermediates
            if (rnd.next(0, 1) == 1) {
                Recipe r;
                r.out = iname;
                int k = rnd.next(1, 3);
                bool hasOther = false;
                for (int j = 0; j < k; ++j) {
                    string ing = rnd.any(candAll);
                    int coef = rnd.next(1, 5);
                    if (ing != iname) hasOther = true;
                    r.in.push_back({coef, ing});
                }
                if (!hasOther && !basics.empty()) {
                    // ensure not all ingredients are self; swap one to a basic
                    r.in[0].second = basics[0];
                }
                recipes.push_back(r);
            }
        }

        // Multiple recipes for LOVE from basics and intermediates
        vector<string> candLove = candAll; // excludes LOVE
        int Rc = rnd.next(2, 4);
        for (int i = 0; i < Rc; ++i) {
            Recipe r;
            r.out = "LOVE";
            int k = rnd.next(1, 3);
            for (int j = 0; j < k; ++j) {
                string ing = rnd.any(candLove);
                int coef = rnd.next(1, 4);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

    } else if (caseType == 3) {
        // Cycle between two potions but resolvable via an acyclic recipe
        allNames.push_back("LOVE");
        vector<string> basics;

        int B = rnd.next(1, 2);
        for (int i = 0; i < B; ++i) {
            string nm = genUniqueName(allNames);
            basics.push_back(nm);
        }

        string P1 = genUniqueName(allNames);
        string P2 = genUniqueName(allNames);

        // Market: basics only
        for (auto &b : basics) {
            int pr = rnd.next(1, 20);
            market.push_back({b, pr});
        }

        // Optional direct LOVE (expensive)
        if (rnd.next(0, 3) == 0) {
            int pr = rnd.next(50, 100);
            market.push_back({"LOVE", pr});
        }

        // P1 acyclic recipe from basics
        {
            Recipe r;
            r.out = P1;
            int k = rnd.next(1, 2);
            for (int j = 0; j < k; ++j) {
                string ing = rnd.any(basics);
                int coef = rnd.next(1, 4);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

        // P1 cyclic recipe using P2 + basics
        {
            Recipe r;
            r.out = P1;
            int k = rnd.next(1, 2);
            // ensure P2 appears
            r.in.push_back({rnd.next(1, 2), P2});
            for (int j = 1; j < k; ++j) {
                string ing = rnd.any(basics);
                int coef = rnd.next(1, 3);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

        // P2 recipe using P1 + basics (creates cycle)
        {
            Recipe r;
            r.out = P2;
            r.in.push_back({rnd.next(1, 3), P1});
            int extra = rnd.next(0, (int)basics.size());
            for (int j = 0; j < extra; ++j) {
                string ing = basics[j];
                int coef = rnd.next(1, 3);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

        // LOVE recipe uses P1 + basics
        {
            Recipe r;
            r.out = "LOVE";
            r.in.push_back({rnd.next(1, 3), P1});
            int extra = rnd.next(0, (int)basics.size());
            for (int j = 0; j < extra; ++j) {
                string ing = basics[j];
                int coef = rnd.next(1, 4);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

    } else if (caseType == 4) {
        // Self-cycle for LOVE: impossible to produce LOVE
        allNames.push_back("LOVE");
        vector<string> basics;

        int B = rnd.next(1, 3);
        for (int i = 0; i < B; ++i) {
            string nm = genUniqueName(allNames);
            basics.push_back(nm);
        }

        // Market: basics only
        for (auto &b : basics) {
            int pr = rnd.next(1, 30);
            market.push_back({b, pr});
        }

        // LOVE self-referential formula
        {
            Recipe r;
            r.out = "LOVE";
            // either LOVE=1LOVE or LOVE=1LOVE+1BASIC
            r.in.push_back({1, "LOVE"});
            if (!basics.empty() && rnd.next(0, 1) == 1) {
                string ing = basics[0];
                int coef = rnd.next(1, 3);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

        // Optional unrelated formulas
        int extraF = rnd.next(0, 2);
        for (int i = 0; i < extraF; ++i) {
            Recipe r;
            string outName = genUniqueName(allNames);
            r.out = outName;
            int k = rnd.next(1, 3);
            for (int j = 0; j < k; ++j) {
                string ing = rnd.any(basics);
                int coef = rnd.next(1, 5);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

    } else if (caseType == 6) {
        // LOVE depends on an ingredient that cannot be obtained at all
        allNames.push_back("LOVE");
        vector<string> basics;

        int B = rnd.next(1, 3);
        for (int i = 0; i < B; ++i) {
            string nm = genUniqueName(allNames);
            basics.push_back(nm);
        }

        string missing = "MISSING";
        allNames.push_back(missing);

        // Market: basics only
        for (auto &b : basics) {
            int pr = rnd.next(1, 50);
            market.push_back({b, pr});
        }

        // LOVE recipe includes MISSING (unobtainable)
        {
            Recipe r;
            r.out = "LOVE";
            int k = rnd.next(1, 3);
            // ensure MISSING is included
            r.in.push_back({rnd.next(1, 3), missing});
            for (int j = 1; j < k; ++j) {
                string ing = rnd.any(basics);
                int coef = rnd.next(1, 4);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }

        // Optional unrelated recipes that don't define MISSING or LOVE
        int extraF = rnd.next(0, 2);
        for (int i = 0; i < extraF; ++i) {
            Recipe r;
            string outName = genUniqueName(allNames);
            r.out = outName;
            int k = rnd.next(1, 2);
            for (int j = 0; j < k; ++j) {
                string ing = rnd.any(basics);
                int coef = rnd.next(1, 5);
                r.in.push_back({coef, ing});
            }
            recipes.push_back(r);
        }
    }

    // Output
    int N = (int)market.size();
    int M = (int)recipes.size();
    println(N, M);

    for (auto &p : market) {
        println(p.first, p.second);
    }

    for (auto &r : recipes) {
        string line = r.out + "=";
        for (int i = 0; i < (int)r.in.size(); ++i) {
            if (i) line += "+";
            line += char('0' + r.in[i].first);
            line += r.in[i].second;
        }
        println(line);
    }

    return 0;
}
