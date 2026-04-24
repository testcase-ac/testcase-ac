import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random
import sys
import sys
import sys
import sys
from typing import List, Optional

# Constants for bounds
T_MIN = 1
T_MAX = 1  # Keeping T small for easy verification

N_MIN = 1
N_MAX = 20  # Keeping n small for easy verification

# Seed for reproducibility (optional)
# random.seed(42)

# Define tree node
class TreeNode:
    def __init__(self, val: int):
        self.val = val
        self.left: Optional['TreeNode'] = None
        self.right: Optional['TreeNode'] = None

# Tree Types
def generate_balanced_tree(nodes: List[int]) -> Optional[TreeNode]:
    if not nodes:
        return None
    mid = len(nodes) // 2
    root = TreeNode(nodes[mid])
    root.left = generate_balanced_tree(nodes[:mid])
    root.right = generate_balanced_tree(nodes[mid+1:])
    return root

def generate_left_skewed_tree(nodes: List[int]) -> Optional[TreeNode]:
    if not nodes:
        return None
    root = TreeNode(nodes[0])
    root.left = generate_left_skewed_tree(nodes[1:])
    return root

def generate_right_skewed_tree(nodes: List[int]) -> Optional[TreeNode]:
    if not nodes:
        return None
    root = TreeNode(nodes[0])
    root.right = generate_right_skewed_tree(nodes[1:])
    return root

def generate_random_tree(nodes: List[int]) -> Optional[TreeNode]:
    if not nodes:
        return None
    root_val = nodes[0]
    root = TreeNode(root_val)
    left_nodes = []
    right_nodes = []
    # Randomly split the remaining nodes
    for val in nodes[1:]:
        if random.choice([True, False]):
            left_nodes.append(val)
        else:
            right_nodes.append(val)
    root.left = generate_random_tree(left_nodes)
    root.right = generate_random_tree(right_nodes)
    return root

# Traversal functions
def preorder_traversal(root: Optional[TreeNode], traversal: List[int]):
    if root:
        traversal.append(root.val)
        preorder_traversal(root.left, traversal)
        preorder_traversal(root.right, traversal)

def inorder_traversal(root: Optional[TreeNode], traversal: List[int]):
    if root:
        inorder_traversal(root.left, traversal)
        traversal.append(root.val)
        inorder_traversal(root.right, traversal)

# Main generator function
def generate_testcase():
    T = random.randint(T_MIN, T_MAX)
    testcases = []
    for _ in range(T):
        n = random.randint(N_MIN, N_MAX)
        nodes = list(range(1, n+1))
        random.shuffle(nodes)  # Shuffle to assign unique values randomly

        # Define tree types
        TREE_TYPES = ['balanced', 'left_skewed', 'right_skewed', 'random']
        tree_type = random.choice(TREE_TYPES)

        if tree_type == 'balanced':
            sorted_nodes = sorted(nodes)
            root = generate_balanced_tree(sorted_nodes)
        elif tree_type == 'left_skewed':
            sorted_nodes = sorted(nodes, reverse=True)
            root = generate_left_skewed_tree(sorted_nodes)
        elif tree_type == 'right_skewed':
            sorted_nodes = sorted(nodes)
            root = generate_right_skewed_tree(sorted_nodes)
        else:  # random
            root = generate_random_tree(nodes)

        preorder = []
        inorder = []
        preorder_traversal(root, preorder)
        inorder_traversal(root, inorder)

        testcase = {
            'n': n,
            'preorder': preorder,
            'inorder': inorder
        }
        testcases.append(testcase)
    return T, testcases

# Function to print the testcase in the required format
def print_testcase(T: int, testcases: List[dict]):
    print(T)
    for tc in testcases:
        print(tc['n'])
        print(' '.join(map(str, tc['preorder'])))
        print(' '.join(map(str, tc['inorder'])))

# Generate and print the testcase
if __name__ == "__main__":
    T, testcases = generate_testcase()
    print_testcase(T, testcases)
