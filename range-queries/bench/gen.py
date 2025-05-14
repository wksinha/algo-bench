import random
import sys

TEST_CASES = int(sys.argv[1])
assert TEST_CASES > 0

ARR_LEN_MIN = int(sys.argv[2])
ARR_LEN_MAX = int(sys.argv[3])
assert ARR_LEN_MIN > 0 and ARR_LEN_MAX >= ARR_LEN_MIN

QUERY_MIN = int(sys.argv[4])
QUERY_MAX = int(sys.argv[5])
assert QUERY_MIN >= 0 and QUERY_MAX >= QUERY_MIN

VAL_MIN = 0
VAL_MAX = 1_000

def print_random_arr(length):
    arr = [random.randint(VAL_MIN, VAL_MAX) for _ in range(length)]
    print(len(arr))
    print(*arr)

print(TEST_CASES)
for t in range(TEST_CASES):
    arrlen = random.randint(ARR_LEN_MIN, ARR_LEN_MAX)
    print_random_arr(arrlen)
    queries = random.randint(QUERY_MIN, QUERY_MAX)
    print(queries)
    for _ in range(queries):
        qtype = random.randint(0, 1)
        if qtype == 0:
            idx = random.randint(0, arrlen - 1)
            val = random.randint(VAL_MIN, VAL_MAX)
            print(qtype, idx, val)
        else:
            left = random.randint(0, arrlen - 1)
            right = random.randint(0, arrlen - 1)
            (left, right) = (min(left, right), max(left, right))
            print(qtype, left, right)