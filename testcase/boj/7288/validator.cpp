#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Rule {
    long long year;
    int type;
    string areaName;
    string arg;
};

static vector<string> splitItems(const string& line) {
    vector<string> items;
    string item;
    istringstream iss(line);
    while (iss >> item) {
        items.push_back(item);
    }
    return items;
}

static string readLimitedLine(const string& name) {
    string line = inf.readLine("[ ]*[^]{0,50}", name);
    ensuref(line.size() <= 50, "%s is longer than 50 characters", name.c_str());
    return line;
}

static long long parsePositiveYear(const string& token, const string& name) {
    ensuref(!token.empty(), "%s is empty", name.c_str());
    ensuref(token[0] != '0', "%s must be a positive canonical integer", name.c_str());
    long long value = 0;
    for (char ch : token) {
        ensuref('0' <= ch && ch <= '9', "%s must contain only digits", name.c_str());
        value = value * 10 + (ch - '0');
        ensuref(value < 1000000000LL, "%s must be less than 10^9", name.c_str());
    }
    return value;
}

static int parseIntToken(const string& token, int low, int high, const string& name) {
    ensuref(!token.empty(), "%s is empty", name.c_str());
    if (token.size() > 1) {
        ensuref(token[0] != '0', "%s must not have leading zeroes", name.c_str());
    }
    int value = 0;
    for (char ch : token) {
        ensuref('0' <= ch && ch <= '9', "%s must contain only digits", name.c_str());
        value = value * 10 + (ch - '0');
        ensuref(value <= high, "%s is too large", name.c_str());
    }
    ensuref(low <= value && value <= high, "%s out of range", name.c_str());
    return value;
}

static bool isDigits(const string& token) {
    return !token.empty() && all_of(token.begin(), token.end(), [](char ch) {
        return '0' <= ch && ch <= '9';
    });
}

static bool isLetters(const string& token) {
    return !token.empty() && all_of(token.begin(), token.end(), [](char ch) {
        return ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z');
    });
}

static void ensureNoPrefixCodes(const map<string, string>& codeToName) {
    string previous;
    for (const auto& [code, name] : codeToName) {
        if (!previous.empty()) {
            ensuref(code.rfind(previous, 0) != 0,
                    "area code %s has prefix area code %s",
                    code.c_str(), previous.c_str());
        }
        previous = code;
    }
}

static pair<string, string> findArea(const map<string, string>& codeToName,
                                     const string& number) {
    string matchedCode;
    string matchedName;
    for (const auto& [code, name] : codeToName) {
        if (number.rfind(code, 0) == 0) {
            ensuref(matchedCode.empty(),
                    "number %s matches multiple area codes",
                    number.c_str());
            matchedCode = code;
            matchedName = name;
        }
    }
    ensuref(!matchedCode.empty(), "number %s has no known area code", number.c_str());
    ensuref(number.size() > matchedCode.size(),
            "number %s must include a local number after the area code",
            number.c_str());
    return {matchedCode, matchedName};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string firstLine = readLimitedLine("A line");
    vector<string> firstItems = splitItems(firstLine);
    ensuref(firstItems.size() == 1, "A line must contain exactly one item");
    int areaCount = parseIntToken(firstItems[0], 1, 1000, "A");

    map<string, string> initialCodeToName;
    map<string, string> initialNameToCode;
    for (int i = 0; i < areaCount; ++i) {
        string line = readLimitedLine("area line");
        vector<string> items = splitItems(line);
        ensuref(items.size() == 2, "area line %d must contain two items", i + 1);

        const string& code = items[0];
        const string& name = items[1];
        ensuref(isDigits(code), "area code %d must contain only digits", i + 1);
        ensuref(1 <= code.size() && code.size() <= 6,
                "area code %d length out of range", i + 1);
        ensuref(isLetters(name), "area name %d must contain only letters", i + 1);
        ensuref(1 <= name.size() && name.size() <= 20,
                "area name %d length out of range", i + 1);
        ensuref(initialCodeToName.emplace(code, name).second,
                "duplicate area code %s", code.c_str());
        ensuref(initialNameToCode.emplace(name, code).second,
                "duplicate area name %s", name.c_str());
    }
    ensureNoPrefixCodes(initialCodeToName);

    string ruleCountLine = readLimitedLine("R line");
    vector<string> ruleCountItems = splitItems(ruleCountLine);
    ensuref(ruleCountItems.size() == 1, "R line must contain exactly one item");
    int ruleCount = parseIntToken(ruleCountItems[0], 0, 10000, "R");

    vector<Rule> rules;
    set<long long> ruleYears;
    for (int i = 0; i < ruleCount; ++i) {
        string line = readLimitedLine("rule line");
        vector<string> items = splitItems(line);
        ensuref(items.size() == 4, "rule line %d must contain four items", i + 1);

        long long year = parsePositiveYear(items[0], "rule year");
        ensuref(ruleYears.insert(year).second,
                "more than one rule in year %lld", year);
        int type = parseIntToken(items[1], 1, 3, "rule type");
        ensuref(initialNameToCode.count(items[2]) != 0,
                "rule line %d uses unknown area name %s", i + 1, items[2].c_str());

        if (type == 1 || type == 2) {
            // CHECK: the statement does not bound local-number length; line length
            // limits make indices above 50 unusable for any query number.
            parseIntToken(items[3], 1, 50, "rule index");
        } else {
            ensuref(isDigits(items[3]), "new area code must contain only digits");
            ensuref(1 <= items[3].size() && items[3].size() <= 6,
                    "new area code length out of range");
        }
        rules.push_back({year, type, items[2], items[3]});
    }
    sort(rules.begin(), rules.end(), [](const Rule& lhs, const Rule& rhs) {
        return lhs.year < rhs.year;
    });

    map<string, string> codeToName = initialCodeToName;
    map<string, string> nameToCode = initialNameToCode;
    for (const Rule& rule : rules) {
        if (rule.type != 3) {
            continue;
        }
        string oldCode = nameToCode[rule.areaName];
        codeToName.erase(oldCode);
        ensuref(codeToName.count(rule.arg) == 0,
                "new area code %s duplicates an existing code in year %lld",
                rule.arg.c_str(), rule.year);
        codeToName[rule.arg] = rule.areaName;
        nameToCode[rule.areaName] = rule.arg;
        ensureNoPrefixCodes(codeToName);
    }

    for (int queryIndex = 1;; ++queryIndex) {
        string line = readLimitedLine("query line");
        vector<string> items = splitItems(line);
        ensuref(items.size() == 3, "query line %d must contain three items", queryIndex);

        if (items[0] == "0" && items[1] == "0" && items[2] == "0") {
            break;
        }

        long long year1 = parsePositiveYear(items[0], "year_1");
        long long year2 = parsePositiveYear(items[1], "year_2");
        ensuref(year1 <= year2, "query line %d has year_1 > year_2", queryIndex);
        ensuref(isDigits(items[2]), "query number must contain only digits");

        codeToName = initialCodeToName;
        nameToCode = initialNameToCode;
        for (const Rule& rule : rules) {
            if (rule.year > year1) {
                break;
            }
            if (rule.type == 3) {
                string oldCode = nameToCode[rule.areaName];
                codeToName.erase(oldCode);
                codeToName[rule.arg] = rule.areaName;
                nameToCode[rule.areaName] = rule.arg;
            }
        }

        auto [areaCode, areaName] = findArea(codeToName, items[2]);
        string localNumber = items[2].substr(areaCode.size());

        for (const Rule& rule : rules) {
            if (rule.year <= year1) {
                continue;
            }
            if (rule.year > year2) {
                break;
            }
            if (rule.areaName != areaName) {
                continue;
            }
            if (rule.type == 1) {
                int index = parseIntToken(rule.arg, 1, 50, "repeat index");
                ensuref(index <= (int)localNumber.size(),
                        "repeat index %d out of range for query %d", index, queryIndex);
                localNumber.insert(localNumber.begin() + index - 1, localNumber[index - 1]);
            } else if (rule.type == 2) {
                int index = parseIntToken(rule.arg, 1, 50, "swap index");
                ensuref(index + 1 <= (int)localNumber.size(),
                        "swap index %d out of range for query %d", index, queryIndex);
                swap(localNumber[index - 1], localNumber[index]);
            } else {
                areaCode = rule.arg;
            }
        }
    }

    inf.readEof();
}
