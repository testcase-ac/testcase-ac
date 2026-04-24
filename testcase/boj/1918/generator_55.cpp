#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Constants for clarity and potential modification
const int MIN_OPERANDS = 2;
const int MAX_OPERANDS = 6;

struct Node {
    string val; // Value: operand or operator
    Node *left, *right;
    bool is_operand; // True if the node is an operand
    Node(string v, bool is_op) : val(v), is_operand(is_op), left(nullptr), right(nullptr) {}
};

// Function to get the precedence of an operator or operand
int get_precedence(Node* node) {
    if (node->is_operand) {
        return 3; // Highest precedence for operands
    }
    char op = node->val[0];
    if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return 0; // Should not occur
    }
}

// Function to check if an operator is associative
bool is_operator_associative(char op) {
    return op == '+' || op == '*';
}

// Function to convert the expression tree to an infix expression
string to_infix(Node* node) {
    if (node->is_operand) {
        return node->val;
    } else {
        string left_expr = to_infix(node->left);
        string right_expr = to_infix(node->right);
        int curr_prec = get_precedence(node);
        int left_prec = get_precedence(node->left);
        int right_prec = get_precedence(node->right);
        char curr_op = node->val[0];
        // Determine if parentheses are needed for correctness
        bool need_paren_left = false;
        if (!node->left->is_operand && (left_prec < curr_prec)) {
            need_paren_left = true;
        } else if (!node->left->is_operand && left_prec == curr_prec && !is_operator_associative(curr_op)) {
            need_paren_left = true;
        }
        bool need_paren_right = false;
        if (!node->right->is_operand && (right_prec < curr_prec)) {
            need_paren_right = true;
        } else if (!node->right->is_operand && right_prec == curr_prec && !is_operator_associative(curr_op)) {
            need_paren_right = true;
        }
        // Randomly add extra parentheses for variation
        if (rnd.next(0, 1) || need_paren_left) {
            left_expr = "(" + left_expr + ")";
        }
        if (rnd.next(0, 1) || need_paren_right) {
            right_expr = "(" + right_expr + ")";
        }
        return left_expr + node->val + right_expr;
    }
}

// Function to build a random expression tree
Node* build_tree(vector<string>& tokens) {
    if (tokens.size() == 1) {
        return new Node(tokens[0], true);
    } else {
        int N = tokens.size();
        int split;
        int tree_type = rnd.next(0, 2);
        if (tree_type == 0) {
            // Balanced split
            split = N / 2;
        } else if (tree_type == 1) {
            // Left-skewed
            split = 1;
        } else {
            // Right-skewed
            split = N - 1;
        }
        if (split == 0 || split == N) split = rnd.next(1, N - 1); // Ensure valid split
        vector<string> left_tokens(tokens.begin(), tokens.begin() + split);
        vector<string> right_tokens(tokens.begin() + split, tokens.end());
        char op = "+-*/"[rnd.next(0, 3)]; // Random operator
        Node* node = new Node(string(1, op), false);
        node->left = build_tree(left_tokens);
        node->right = build_tree(right_tokens);
        return node;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate unique operands
    vector<char> operands;
    for (char c = 'A'; c <= 'Z'; ++c) {
        operands.push_back(c);
    }
    int N = rnd.next(MIN_OPERANDS, MAX_OPERANDS);
    operands.resize(N);
    vector<string> tokens;
    for (char c : operands) {
        tokens.push_back(string(1, c));
    }
    // Build the expression tree and generate the infix expression
    Node* root = build_tree(tokens);
    string expr = to_infix(root);
    // Output the generated expression
    cout << expr << endl;
    return 0;
}
