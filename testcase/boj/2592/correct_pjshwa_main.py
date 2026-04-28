num_dict={}
for _ in range(10):
    n=int(input())
    if n in num_dict: num_dict[n] += 1
    else: num_dict[n] = 1

mode_fr=0;mode=0;s=0
for n in num_dict:
    s += (n * num_dict[n])
    if num_dict[n] > mode_fr:
        mode_fr = num_dict[n]
        mode=n
print(s//10);print(mode)