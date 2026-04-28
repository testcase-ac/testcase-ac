ten_gan = range(10)
twelve_ji = "ABCDEFGHIJKL"

import sys
r = sys.stdin.readline
n = int(r())
print("{}{}".format(twelve_ji[(n-4)%12], ten_gan[(n-4)%10]))