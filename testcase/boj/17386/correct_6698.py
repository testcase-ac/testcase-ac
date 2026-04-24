def ccw(p, q, r):
    return (q[0]-p[0])*(r[1]-p[1]) - (q[1]-p[1])*(r[0]-p[0])

def intersect(seg1, seg2):
    p1, p2 = seg1
    p3, p4 = seg2
    
    o1 = ccw(p1, p2, p3)
    o2 = ccw(p1, p2, p4)
    o3 = ccw(p3, p4, p1)
    o4 = ccw(p3, p4, p2)
    
    if o1 * o2 < 0 and o3 * o4 < 0:
        return True
    
    return False


def main():
    import sys
    input_data = sys.stdin.read().strip().split()
    nums = list(map(int, input_data))
    
    x1, y1, x2, y2 = nums[0:4]
    x3, y3, x4, y4 = nums[4:8]
    
    segment1 = ((x1, y1), (x2, y2))
    segment2 = ((x3, y3), (x4, y4))
    
    if intersect(segment1, segment2):
        print(1)
    else:
        print(0)

if __name__ == "__main__":
    main()
