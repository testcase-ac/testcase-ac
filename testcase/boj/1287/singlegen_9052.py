# Deeply nested parentheses to trigger Python eval parser/recursion limits in the wrong solution
# Valid expression per grammar, no division involved, expected result is 1
# Length <= 1000: 499 '(' + '1' + 499 ')' = 999 characters
n = 499
print('(' * n + '1' + ')' * n)
