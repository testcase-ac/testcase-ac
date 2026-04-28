import sys
r = sys.stdin.readline

deut_bo_jap_dict = {}
real_deut_bo_jap = []

n, m = map(int, r().split())
for _ in range(n):
    name = r().rstrip()
    deut_bo_jap_dict[name] = 1
for _ in range(m):
    name = r().rstrip()
    try:
        deut_bo_jap_dict[name] += 1
        real_deut_bo_jap.append(name)
    except KeyError:
        pass
print(len(real_deut_bo_jap))
for item in sorted(real_deut_bo_jap):
    print(item)