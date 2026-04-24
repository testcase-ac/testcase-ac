import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for bounds
MIN_N = 4
MAX_N = 10
MIN_M = 3
MAX_M = 10

def generate_chain_case():
    """
    Creates a test case where parties form a chain connecting truth-knowers to others.
    """
    N = random.randint(MIN_N, MAX_N)
    M = random.randint(MIN_M, MAX_M)
    K = random.randint(1, N - 1)
    know_truth = random.sample(range(1, N + 1), K)
    parties = []

    all_people = list(range(1, N + 1))
    remaining_people = [p for p in all_people if p not in know_truth]
    random.shuffle(remaining_people)
    connected_people = set(know_truth)

    for i in range(M):
        party_size = random.randint(2, min(5, N))
        if remaining_people:
            new_person = remaining_people.pop()
            overlap_person = random.choice(list(connected_people))
            attendees = [overlap_person, new_person]
            connected_people.add(new_person)
        else:
            attendees = random.sample(all_people, party_size)
        parties.append(attendees)

    return N, M, K, know_truth, parties

def generate_cycle_case():
    """
    Creates a test case where parties form a cycle.
    """
    N = random.randint(MIN_N, MAX_N)
    M = N  # To form a cycle, we'll use N parties
    K = random.randint(1, N - 1)
    know_truth = random.sample(range(1, N + 1), K)
    parties = []

    people = list(range(1, N + 1))
    random.shuffle(people)
    for i in range(N):
        attendees = [people[i], people[(i + 1) % N]]
        parties.append(attendees)

    return N, M, K, know_truth, parties

def generate_disconnected_case():
    """
    Creates a test case with multiple disconnected components.
    """
    N = random.randint(MIN_N, MAX_N)
    M = random.randint(MIN_M, MAX_M)
    K = random.randint(1, N - 1)
    know_truth = random.sample(range(1, N + 1), K)
    parties = []

    all_people = list(range(1, N + 1))
    random.shuffle(all_people)
    group_size = N // 2
    group1 = all_people[:group_size]
    group2 = all_people[group_size:]

    # Parties in group1
    for _ in range(M // 2):
        party_size = random.randint(2, min(5, len(group1)))
        attendees = random.sample(group1, party_size)
        parties.append(attendees)

    # Parties in group2
    for _ in range(M - M // 2):
        party_size = random.randint(2, min(5, len(group2)))
        attendees = random.sample(group2, party_size)
        parties.append(attendees)

    return N, M, K, know_truth, parties

def generate_edge_case():
    """
    Creates an edge case with minimal or maximal values.
    """
    N = MIN_N
    M = MIN_M
    K = N - 1  # Almost everyone knows the truth
    know_truth = list(range(1, N))
    parties = []

    all_people = list(range(1, N + 1))
    for _ in range(M):
        party_size = N  # Everyone attends
        attendees = all_people.copy()
        parties.append(attendees)

    return N, M, K, know_truth, parties

def generate_random_case():
    """
    Creates a random test case that may include various complexities.
    """
    N = random.randint(MIN_N, MAX_N)
    M = random.randint(MIN_M, MAX_M)
    K = random.randint(0, N)
    know_truth = random.sample(range(1, N + 1), K)
    parties = []

    for _ in range(M):
        party_size = random.randint(2, min(5, N))
        attendees = random.sample(range(1, N + 1), party_size)
        parties.append(attendees)

    return N, M, K, know_truth, parties

def generate_test_case():
    case_generators = [
        generate_chain_case,
        generate_cycle_case,
        generate_disconnected_case,
        generate_edge_case,
        generate_random_case
    ]
    # Randomly select a case generator
    case_generator = random.choice(case_generators)
    N, M, K, know_truth, parties = case_generator()

    # Output the test case
    print(f"{N} {M}")
    if K > 0:
        print(f"{K} {' '.join(map(str, know_truth))}")
    else:
        print("0")
    for party in parties:
        print(f"{len(party)} {' '.join(map(str, party))}")

if __name__ == "__main__":
    generate_test_case()
