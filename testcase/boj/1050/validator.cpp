#include "testlib.h"
#include <set>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(0, 50, "M");
    inf.readEoln();

    // 2. Read N market ingredients
    set<string> market_names;
    map<string, int> market_price;
    for (int i = 0; i < N; ++i) {
        string name = inf.readToken("[A-Z]{1,50}", "ingredient_name");
        inf.readSpace();
        int price = inf.readInt(1, 100, "ingredient_price");
        inf.readEoln();

        ensuref(market_names.count(name) == 0, "Duplicate market ingredient name: %s", name.c_str());
        market_names.insert(name);
        market_price[name] = price;
    }

    // 3. Read M recipes
    // For each recipe, store: output_potion, vector<pair<count, ingredient>>
    struct Recipe {
        string output;
        vector<pair<int, string>> ingredients;
        string original_line;
    };
    vector<Recipe> recipes;
    set<string> all_recipe_outputs;
    for (int i = 0; i < M; ++i) {
        string line = inf.readLine("[^]{1,50}", "recipe_line");
        string s = line;
        // Find '='
        size_t eq = s.find('=');
        ensuref(eq != string::npos, "Recipe line %d missing '=': %s", i+1, s.c_str());
        string output = s.substr(0, eq);
        string rhs = s.substr(eq+1);

        // Validate output name
        ensuref(!output.empty(), "Recipe line %d: output potion name is empty", i+1);
        ensuref(output.size() <= 50, "Recipe line %d: output potion name too long", i+1);
        for (char c : output)
            ensuref(isupper(c), "Recipe line %d: output potion name contains non-uppercase: %s", i+1, output.c_str());

        // Parse right hand side: N1S1+N2S2+...+NkSk
        vector<pair<int, string>> ingredients;
        size_t pos = 0;
        while (pos < rhs.size()) {
            // Parse number: 1-9
            ensuref(isdigit(rhs[pos]), "Recipe line %d: expected digit at pos %zu: %s", i+1, pos, rhs.c_str());
            int cnt = rhs[pos] - '0';
            ensuref(cnt >= 1 && cnt <= 9, "Recipe line %d: ingredient count not in 1..9 at pos %zu: %s", i+1, pos, rhs.c_str());
            ++pos;
            // Parse ingredient name
            size_t name_start = pos;
            while (pos < rhs.size() && isupper(rhs[pos])) ++pos;
            ensuref(pos > name_start, "Recipe line %d: missing ingredient name after count at pos %zu: %s", i+1, name_start, rhs.c_str());
            string ing = rhs.substr(name_start, pos - name_start);
            ensuref(ing.size() <= 50, "Recipe line %d: ingredient name too long at pos %zu: %s", i+1, name_start, rhs.c_str());
            ingredients.emplace_back(cnt, ing);
            // Next: either '+' or end
            if (pos < rhs.size()) {
                ensuref(rhs[pos] == '+', "Recipe line %d: expected '+' at pos %zu: %s", i+1, pos, rhs.c_str());
                ++pos;
            }
        }
        ensuref(!ingredients.empty(), "Recipe line %d: no ingredients found", i+1);
        recipes.push_back({output, ingredients, line});
        all_recipe_outputs.insert(output);
    }

    // 4. Validate all potion/ingredient names
    // - All names must be uppercase, length 1..50 (already checked)
    // - Market ingredient names are unique (already checked)
    // - Recipe output names can overlap (e.g. multiple recipes for same potion)
    // - Ingredient names in recipes can be any name (including market or recipe outputs, or new names)
    // - No further constraints on names

    // 5. Validate recipe output names: can overlap with market names (e.g. LOVE can be both market and recipe output)
    // - No restriction in statement

    // 6. Validate recipe length: already checked by line regex and parsing

    // 7. Validate that all lines are consumed and file ends with EOF
    inf.readEof();
}
