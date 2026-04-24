# This test targets the wrong solution's use of float for the sum, which loses precision
# for large N and causes the rounded mean to be incorrect. Here, the true average rounds to 3999,
# but the wrong code rounds to 4000 due to float quantization when converting the exact double sum
# to float (ULP ~128 at this magnitude).

import sys
w = sys.stdout.write

N = 499999  # odd
w(str(N) + "\n")
# 250000 times 3999, then 249999 times 4000
w(("3999\n") * 250000)
w(("4000\n") * 249999)
