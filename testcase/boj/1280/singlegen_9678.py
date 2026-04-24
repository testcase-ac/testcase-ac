# Large alternating extremes to trigger deterministic 64-bit overflow in wrong solution
# N = 200000, coordinates alternate between 0 and 199999.
# The product terms grow roughly like (k/2)*200000 and cause multiple overflows.
N = 200000
print(N)
for i in range(N):
    if i % 2 == 0:
        print(0)
    else:
        print(199999)
