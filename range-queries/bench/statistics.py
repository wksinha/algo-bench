import matplotlib.pyplot as plt
import numpy as np
from copy import deepcopy

methods = ["insertionSort", "quickSort", "mergeSort", "hybridSort"]
testTypes = ["small", "medium", "large"]

def read_integers_from_file(filename):
    integers = []
    with open(filename, 'r') as file:
        for line in file:
            stripped = line.strip()
            if stripped:
                integers.append(int(stripped))
    return integers

def print_markdown_table(data):
    data_copy = deepcopy(data)
    sizes = list(data_copy.keys())
    algorithms = methods

    for size in sizes:
        for algo in methods:
            if algo not in data_copy[size]:
                data_copy[size][algo] = ("NA", "NA")

    header = "|           | " + " | ".join(f"{algo:<23}" for algo in algorithms) + " |"
    separator = "|-----------|" + "|".join(["-" * 25 for _ in algorithms]) + "|"

    print(header)
    print(separator)

    for size in sizes:
        row = f"| {size:<9} | " + " | ".join(
            f"({data_copy[size][algo][0]}, {data_copy[size][algo][1]})".ljust(23)
            for algo in algorithms
        ) + " |"
        print(row)
    print()

def get_stats():
    statistics = {}
    for testType in testTypes:
        statistics[testType] = {}
        for method in methods:
            if method != "insertionSort" or (testType in ["small", "medium"]):
                filename = f"{method}.{testType}.times.txt"
                running_times = read_integers_from_file(filename)
                least = min(running_times)
                highest = max(running_times)
                statistics[testType][method] = (least, highest)
    return statistics

def plot(statistics, filename_prefix="sorting-stats"):
    for testType in testTypes:
        current_data = statistics.get(testType, {})
        valid_algorithms = [algo for algo in methods if algo in current_data]
        
        if not valid_algorithms:
            continue
        
        min_times = [current_data[algo][0] for algo in valid_algorithms]
        max_times = [current_data[algo][1] for algo in valid_algorithms]

        x = np.arange(len(valid_algorithms))
        width = 0.35

        plt.figure(figsize=(10, 6))
        plt.bar(x - width/2, min_times, width=width, label='Min Time', alpha=0.7, hatch='//')
        plt.bar(x + width/2, max_times, width=width, label='Max Time', alpha=0.5)

        plt.title(f'Running Time Ranges for {testType.capitalize()} Inputs')
        plt.xlabel('Sorting Algorithm')
        plt.ylabel('Running Time (ns)')
        plt.xticks(x, valid_algorithms)
        plt.legend()
        plt.grid(True, axis='y', linestyle='--', alpha=0.7)
        plt.tight_layout()
        plt.savefig(f"{filename_prefix}-{testType}.png", dpi=300)
        plt.close()

def show_results(statistics):
    print_markdown_table(statistics)
    plot(statistics)

if __name__ == "__main__":
    stats = get_stats()
    show_results(stats)