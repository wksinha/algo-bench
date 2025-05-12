import random
import sys

n = len(sys.argv)
TEST_CASES = int(sys.argv[1])
assert TEST_CASES > 0

TEXT_LENGTH_MIN = int(sys.argv[2])
TEXT_LENGTH_MAX = int(sys.argv[3])
assert TEXT_LENGTH_MIN > 0 and TEXT_LENGTH_MAX >= TEXT_LENGTH_MIN

PATTERN_LENGTH_MIN = int(sys.argv[4])
PATTERN_LENGTH_MAX = int(sys.argv[5])
assert PATTERN_LENGTH_MIN > 0 and PATTERN_LENGTH_MAX >= PATTERN_LENGTH_MIN

ALPHABET_SIZE_MIN = int(sys.argv[6])
ALPHABET_SIZE_MAX = int(sys.argv[7])
assert ALPHABET_SIZE_MIN > 0 and ALPHABET_SIZE_MAX >= ALPHABET_SIZE_MIN


ALPHABET = ''.join([chr(i) for i in range(ord('a'), ord('z') + 1)])
def print_random_string(length, alphabet_size):
    alphabet = ALPHABET[:alphabet_size]
    print(''.join(random.choice(alphabet) for _ in range(length)))


print(TEST_CASES)
for t in range(TEST_CASES):
    ALPHABET_SIZE = random.randint(ALPHABET_SIZE_MIN, ALPHABET_SIZE_MAX)
    TEXT_LENGTH = random.randint(TEXT_LENGTH_MIN, TEXT_LENGTH_MAX)
    PATTERN_LENGTH = random.randint(PATTERN_LENGTH_MIN, PATTERN_LENGTH_MAX)
    print_random_string(TEXT_LENGTH, ALPHABET_SIZE) # text
    print_random_string(PATTERN_LENGTH, ALPHABET_SIZE) # pattern