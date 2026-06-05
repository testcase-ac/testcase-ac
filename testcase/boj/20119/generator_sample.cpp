#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Recipe {
    vector<int> ingredients;
    int result;
};

static void addRecipe(vector<Recipe>& recipes, vector<int> ingredients, int result) {
    recipes.push_back({ingredients, result});
}

static vector<int> shuffledPotions(int n) {
    vector<int> potions(n);
    for (int i = 0; i < n; ++i) {
        potions[i] = i + 1;
    }
    shuffle(potions.begin(), potions.end());
    return potions;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 14);
    vector<int> p = shuffledPotions(n);
    vector<Recipe> recipes;
    set<int> initialSet;

    if (mode == 0) {
        int l = rnd.next(1, min(3, n - 1));
        for (int i = 0; i < l; ++i) {
            initialSet.insert(p[i]);
        }
        int lastKnown = p[rnd.next(0, l - 1)];
        int chainLen = rnd.next(1, n - l);
        for (int i = 0; i < chainLen; ++i) {
            int result = p[l + i];
            addRecipe(recipes, {lastKnown}, result);
            lastKnown = result;
        }
    } else if (mode == 1) {
        int l = rnd.next(2, min(4, n - 1));
        for (int i = 0; i < l; ++i) {
            initialSet.insert(p[i]);
        }
        int produced = l;
        while (produced < n && (int)recipes.size() < rnd.next(3, 8)) {
            int result = p[produced++];
            int k = rnd.next(2, min(4, produced - 1));
            vector<int> ingredients;
            for (int j = 0; j < k; ++j) {
                ingredients.push_back(p[rnd.next(0, produced - 2)]);
            }
            addRecipe(recipes, ingredients, result);
        }
    } else if (mode == 2) {
        int l = rnd.next(1, min(3, n - 1));
        for (int i = 0; i < l; ++i) {
            initialSet.insert(p[i]);
        }
        int result = p[l];
        int duplicate = p[rnd.next(0, l - 1)];
        int repeats = rnd.next(2, min(5, n - 1));
        vector<int> ingredients(repeats, duplicate);
        addRecipe(recipes, ingredients, result);
        if (l + 1 < n) {
            addRecipe(recipes, {result}, p[l + 1]);
        }
    } else if (mode == 3) {
        int l = rnd.next(1, min(3, n - 1));
        for (int i = 0; i < l; ++i) {
            initialSet.insert(p[i]);
        }
        int blockedA = p[n - 1];
        int blockedB = p[n - 2];
        addRecipe(recipes, {blockedA}, blockedB);
        addRecipe(recipes, {blockedB}, blockedA);
        if (l < n - 2) {
            addRecipe(recipes, {p[0]}, p[l]);
        }
        if (l + 1 < n - 2) {
            addRecipe(recipes, {p[l], blockedA}, p[l + 1]);
        }
    } else {
        int l = rnd.next(1, min(4, n - 1));
        for (int i = 0; i < l; ++i) {
            initialSet.insert(p[i]);
        }
        int target = p[l];
        addRecipe(recipes, {p[0]}, target);
        if (l >= 2) {
            addRecipe(recipes, {p[1]}, target);
        }
        if (l + 1 < n) {
            addRecipe(recipes, {target, p[rnd.next(0, l - 1)]}, p[l + 1]);
        }
    }

    while (recipes.empty()) {
        addRecipe(recipes, {p[0]}, p[1]);
        initialSet.insert(p[0]);
    }

    int extra = rnd.next(0, 4);
    for (int i = 0; i < extra; ++i) {
        int result = rnd.next(1, n);
        int k = rnd.next(1, min(4, n - 1));
        vector<int> ingredients;
        for (int j = 0; j < k; ++j) {
            int x = rnd.next(1, n);
            if (x == result) {
                x = x % n + 1;
            }
            ingredients.push_back(x);
        }
        addRecipe(recipes, ingredients, result);
    }

    vector<int> initial(initialSet.begin(), initialSet.end());
    shuffle(initial.begin(), initial.end());
    shuffle(recipes.begin(), recipes.end());

    println(n, (int)recipes.size());
    for (const Recipe& recipe : recipes) {
        cout << recipe.ingredients.size();
        for (int x : recipe.ingredients) {
            cout << ' ' << x;
        }
        cout << ' ' << recipe.result << '\n';
    }
    println((int)initial.size());
    println(initial);

    return 0;
}
