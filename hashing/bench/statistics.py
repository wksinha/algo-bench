import numpy as np
import matplotlib.pyplot as plt

def read_data(file_name):
    with open(file_name, 'r') as f:
        data = list(map(int, f.read().split()))
    return data

def calculate_average(deltas):
    return np.sum(np.arange(len(deltas)) * deltas) / np.sum(deltas)

def plot_grouped_histogram(rolling_hash_deltas, std_hash_deltas, xor_hash_deltas):
    bins = np.arange(33)

    bar_width = 0.25

    positions = bins - bar_width
    positions_std = bins
    positions_xor = bins + bar_width

    plt.figure(figsize=(8, 4))

    plt.bar(positions, rolling_hash_deltas, width=bar_width, alpha=0.7, label='Rolling Hash', color='blue', edgecolor='black')
    plt.bar(positions_std, std_hash_deltas, width=bar_width, alpha=0.7, label='std::hash', color='green', edgecolor='black')
    plt.bar(positions_xor, xor_hash_deltas, width=bar_width, alpha=0.7, label='XOR Hash', color='red', edgecolor='black')

    plt.xlabel('Number of Bits Flipped')
    plt.ylabel('Frequency')
    plt.title('Histogram of Bit Flips for Hash Functions')
    plt.xticks(bins)
    plt.legend()

    plt.tight_layout()
    plt.savefig('grouped-histogram.png')

def plot_histogram(deltas):
    bins = np.arange(33)

    bar_width = 0.25

    positions = bins - bar_width
    plt.figure(figsize=(8, 4))

    plt.bar(positions, deltas, width=bar_width, alpha=0.7, label='Random Hash', color='blue', edgecolor='black')

    plt.xlabel('Number of Bits Flipped')
    plt.ylabel('Frequency')
    plt.title('Histogram of Bit Flips for Random Hash Function')
    plt.xticks(bins)
    plt.legend()

    plt.tight_layout()
    plt.savefig('random-hash-histogram.png')


def main():
    rolling_hash_deltas = read_data('rolling-hash.flips.txt')
    std_hash_deltas = read_data('std-hash.flips.txt')
    xor_hash_deltas = read_data('xor-hash.flips.txt')
    random_hash_deltas = read_data('random-hash.flips.txt')

    avg_rolling_hash = calculate_average(rolling_hash_deltas)
    avg_std_hash = calculate_average(std_hash_deltas)
    avg_xor_hash = calculate_average(xor_hash_deltas)
    avg_random_hash = calculate_average(random_hash_deltas)

    print(f"Average bits changed for Rolling Hash: {avg_rolling_hash:.2f}")
    print(f"Average bits changed for std::hash: {avg_std_hash:.2f}")
    print(f"Average bits changed for XOR Hash: {avg_xor_hash:.2f}")
    print(f"Average bits changed for Random Hash: {avg_random_hash:.2f}")

    plot_grouped_histogram(rolling_hash_deltas, std_hash_deltas, xor_hash_deltas)
    plot_histogram(random_hash_deltas)

if __name__ == '__main__':
    main()
