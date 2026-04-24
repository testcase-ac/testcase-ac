# Generates a crafted TSP instance (N=16) that forces the wrong solution into massive recomputation
# due to memoization sentinel bug (uses float('inf') as both default and computed value),
# leading to severe performance degradation (likely TLE).
#
# Graph structure (layered):
# - Node 0 is the start.
# - L1 = {1..7}, L2 = {8..15}.
# - Edges:
#   * From 0 to all L1 and L2: cost 1
#   * Within L1: fully connected (except self): cost 1
#   * From L1 to L2: cost 1
#   * Within L2: fully connected (except self): cost 1
#   * From L2 to 0: cost 1
#   * All other edges (not listed) are 0 (unreachable)
#
# This instance has many dead-end DP states (cur in L2 while some L1 unvisited),
# each reachable via many different parents, but their DP values are INF.
# Because the wrong solution uses INF as the uninitialized sentinel, it will recompute
# those states repeatedly instead of memoizing them, causing exponential blow-up.

n = 16
print(n)
L1 = set(range(1, 8))
L2 = set(range(8, 16))
for i in range(n):
    row = []
    for j in range(n):
        if i == j:
            row.append(0)
            continue
        if i == 0:
            # From start to everyone else
            row.append(1)
        elif i in L1:
            # L1 -> L1 and L1 -> L2
            if j in L1 or j in L2:
                row.append(1)
            else:
                row.append(0)  # no L1 -> 0
        else:  # i in L2
            if j in L2:
                row.append(1)  # L2 -> L2
            elif j == 0:
                row.append(1)  # L2 -> 0 (to allow completing the tour)
            else:
                row.append(0)  # no L2 -> L1
    print(' '.join(map(str, row)))
