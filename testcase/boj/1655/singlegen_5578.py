# Generate a “maximum” stress test for the median-of-stream problem:
# – N at its upper limit (100 000)
# – values cycling through the full range [−10000,10000] so the median
#   is constantly shifting
N = 100000
print(N)
for i in range(N):
    # will print: -10000, -9999, …, 9999, 10000, -10000, -9999, …
    print(-10000 + (i % 20001))
