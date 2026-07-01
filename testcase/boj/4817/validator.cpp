#include "testlib.h"

#include <string>

using namespace std;

class Parser {
 public:
  explicit Parser(const string& s) : s_(s) {}

  bool parseExpression() {
    if (!parseProduct()) return false;
    if (consume('+')) return parseExpression();
    return true;
  }

  bool atEnd() const {
    return pos_ == s_.size();
  }

 private:
  bool parseProduct() {
    if (!parseFactor()) return false;
    if (!atEnd() && (isVariable(peek()) || peek() == '(')) return parseProduct();
    return true;
  }

  bool parseFactor() {
    if (atEnd()) return false;
    if (isVariable(peek())) {
      ++pos_;
      return true;
    }
    if (consume('(')) {
      if (!parseExpression()) return false;
      return consume(')');
    }
    return false;
  }

  bool consume(char c) {
    if (!atEnd() && peek() == c) {
      ++pos_;
      return true;
    }
    return false;
  }

  char peek() const {
    return s_[pos_];
  }

  static bool isVariable(char c) {
    return 'a' <= c && c <= 'z';
  }

  const string& s_;
  size_t pos_ = 0;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int case_count = 0;
  while (!inf.eof()) {
    string expression = inf.readLine("[a-z()+]{1,1000}", "expression");
    ++case_count;
    setTestCase(case_count);

    Parser parser(expression);
    ensuref(parser.parseExpression() && parser.atEnd(),
            "expression does not match the grammar: %s", expression.c_str());
  }

  ensuref(case_count >= 1, "input must contain at least one case");
  inf.readEof();
}
