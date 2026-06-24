#include "testlib.h"

#include <cmath>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

struct IntValue {
    int value;
};

struct LongLongValue {
    long long value;
};

struct FloatValue {
    float value;
};

struct DoubleValue {
    double value;
};

using Value = variant<IntValue, LongLongValue, FloatValue, DoubleValue>;

struct Answer {
    vector<Value> values;
};

template <class T>
T parseTypedValue(InStream& stream, const string& token, const char* name) {
    istringstream input(token);
    T value;
    if (!(input >> value)) {
        stream.quitf(_wa, "%s is not readable as the declared type", name);
    }
    return value;
}

Value readValue(InStream& stream, const string& type, const string& token, int index) {
    const string name = format("value[%d]", index + 1);
    if (type == "int") {
        return IntValue{parseTypedValue<int>(stream, token, name.c_str())};
    }
    if (type == "long long") {
        return LongLongValue{parseTypedValue<long long>(stream, token, name.c_str())};
    }
    if (type == "float") {
        return FloatValue{parseTypedValue<float>(stream, token, name.c_str())};
    }
    if (type == "double") {
        return DoubleValue{parseTypedValue<double>(stream, token, name.c_str())};
    }
    stream.quitf(_wa, "type[%d] must be int, long long, float, or double", index + 1);
}

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.values.reserve(3);

    for (int i = 0; i < 3; ++i) {
        string first = stream.readWord();
        string type = first;
        if (first == "long") {
            string second = stream.readWord();
            if (second != "long") {
                stream.quitf(_wa, "type[%d] starts with long but is not long long", i + 1);
            }
            type = "long long";
        }

        string token = stream.readWord();
        answer.values.push_back(readValue(stream, type, token, i));
        stream.readEoln();
    }

    stream.readEof();
    return answer;
}

bool isFloating(const Value& value) {
    return holds_alternative<FloatValue>(value) || holds_alternative<DoubleValue>(value);
}

bool isDoubleLike(const Value& value) {
    return holds_alternative<DoubleValue>(value);
}

double asDouble(const Value& value) {
    if (auto intValue = get_if<IntValue>(&value)) {
        return intValue->value;
    }
    if (auto longLongValue = get_if<LongLongValue>(&value)) {
        return static_cast<double>(longLongValue->value);
    }
    if (auto floatValue = get_if<FloatValue>(&value)) {
        return floatValue->value;
    }
    return get<DoubleValue>(value).value;
}

float asFloat(const Value& value) {
    if (auto intValue = get_if<IntValue>(&value)) {
        return intValue->value;
    }
    if (auto longLongValue = get_if<LongLongValue>(&value)) {
        return static_cast<float>(longLongValue->value);
    }
    if (auto floatValue = get_if<FloatValue>(&value)) {
        return floatValue->value;
    }
    return static_cast<float>(get<DoubleValue>(value).value);
}

long long asLongLong(const Value& value) {
    if (auto intValue = get_if<IntValue>(&value)) {
        return intValue->value;
    }
    return get<LongLongValue>(value).value;
}

bool equalLikeCpp17(const Value& lhs, const Value& rhs) {
    if (isDoubleLike(lhs) || isDoubleLike(rhs)) {
        return asDouble(lhs) == asDouble(rhs);
    }
    if (isFloating(lhs) || isFloating(rhs)) {
        return asFloat(lhs) == asFloat(rhs);
    }
    return asLongLong(lhs) == asLongLong(rhs);
}

bool satisfiesCondition(const Answer& answer) {
    const Value& a = answer.values[0];
    const Value& b = answer.values[1];
    const Value& c = answer.values[2];
    return equalLikeCpp17(a, b) && equalLikeCpp17(b, c) && !equalLikeCpp17(c, a);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    if (!satisfiesCondition(jury)) {
        quitf(_fail, "jury answer does not make the condition true");
    }

    Answer participant = readAnswer(ouf);
    if (!satisfiesCondition(participant)) {
        quitf(_wa, "participant answer does not make the condition true");
    }

    quitf(_ok, "valid certificate");
}
