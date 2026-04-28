x0, y0, r0 = map(int, input().split())
x1, y1, r1 = map(int, input().split())
x2, y2, r2 = map(int, input().split())

B, ans = 250, 0
for i in range(1, 100 * B + 1):
  for j in range(1, 100 * B + 1):
    in1 = (2 * i - 1 - 2 * B * x0) ** 2 + (2 * j - 1 - 2 * B * y0) ** 2 <= (2 * B * r0) ** 2
    in2 = (2 * i - 1 - 2 * B * x1) ** 2 + (2 * j - 1 - 2 * B * y1) ** 2 <= (2 * B * r1) ** 2
    in3 = (2 * i - 1 - 2 * B * x2) ** 2 + (2 * j - 1 - 2 * B * y2) ** 2 <= (2 * B * r2) ** 2
    if in1 or in2 or in3: ans += 1

print(ans / B ** 2)
