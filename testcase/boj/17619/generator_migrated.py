import random
import sys

def generate_test_case(n, q, coord_range=(0, 10**9), y_range=(0, 10**9)):
    """
    Generate a test case for the problem.

    Parameters:
        n (int): Number of logs.
        q (int): Number of queries.
        coord_range (tuple): Range for x1 and x2 coordinates of logs.
        y_range (tuple): Range for y coordinate of logs.

    Returns:
        tuple: A tuple containing the logs and queries.
    """
    logs = []
    queries = []

    # Generate N logs
    for _ in range(n):
        x1 = random.randint(*coord_range)
        x2 = random.randint(*coord_range)
        if x1 > x2:
            x1, x2 = x2, x1  # Ensure x1 < x2
        y = random.randint(*y_range)
        logs.append((x1, x2, y))

    # Generate Q queries
    for _ in range(q):
        log1 = random.randint(1, n)
        log2 = random.randint(1, n)
        while log1 == log2:
            log2 = random.randint(1, n)  # Ensure different logs
        queries.append((log1, log2))

    return logs, queries

def format_test_case(logs, queries):
    """
    Format the test case into a string that matches the input format.

    Parameters:
        logs (list): List of logs.
        queries (list): List of queries.

    Returns:
        str: Formatted test case.
    """
    n = len(logs)
    q = len(queries)
    result = [f"{n} {q}"]
    for x1, x2, y in logs:
        result.append(f"{x1} {x2} {y}")
    for log1, log2 in queries:
        result.append(f"{log1} {log2}")
    return "\n".join(result)

# Example usage
if __name__ == "__main__":
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))

    # Example parameters
    n = 10  # Number of logs
    q = 5   # Number of queries

    # Generate and format test case
    logs, queries = generate_test_case(n, q, coord_range=(0, 100), y_range=(0, 100))
    test_case = format_test_case(logs, queries)

    # Output the test case
    print(test_case)
