# Maximum testcase generation for the “union of segments” problem
# N at its upper bound, all segments identical and spanning the full allowed range.
N = 10**6
print(N)
for _ in range(N):
    # Each segment goes from the minimum x to the maximum y
    print(-10**9, 10**9)
