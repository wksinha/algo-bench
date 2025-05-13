import random
import sys

TEST_CASES = int(sys.argv[1])
assert TEST_CASES > 0

ARR_LEN_MIN = int(sys.argv[2])
ARR_LEN_MAX = int(sys.argv[3])
assert ARR_LEN_MIN > 0 and ARR_LEN_MAX >= ARR_LEN_MIN

VAL_MIN = int(sys.argv[4])
VAL_MAX = int(sys.argv[5])
assert VAL_MIN >= 0 and VAL_MAX >= VAL_MIN


def print_random_arr(length):
    arr = [random.randint(VAL_MIN, VAL_MAX) for _ in range(length)]
    print(len(arr))
    print(*arr)

print(TEST_CASES)
for t in range(TEST_CASES):
    print_random_arr(random.randint(ARR_LEN_MIN, ARR_LEN_MAX))