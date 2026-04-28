import sys
r = sys.stdin.readline

ch,cm,cs = map(int, r().split(':'))
nh,nm,ns = map(int, r().split(':'))
ns-=cs;nm-=cm;nh-=ch
if ns==0 and nm==0 and nh==0:
    print("24:00:00")
else:
    if ns<0:
        ns+=60
        nm-=1
    if nm<0:
        nm+=60
        nh-=1
    if nh<0:nh+=24
    print("{:02d}:{:02d}:{:02d}".format(nh,nm,ns))