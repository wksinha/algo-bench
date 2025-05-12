import matplotlib.pyplot as plt

pattern_methods = ["searchPatternRK", "searchPatternKMP", "searchPatternZ"]
palindrome_methods = ["subpalindromesRK", "subpalindromesManacher"]
testSizes = ["small", "medium", "large", "huge"]

def read_integers_from_file(filename):
    integers = []
    with open(filename, 'r') as file:
        for line in file:
            stripped = line.strip()
            if stripped:
                integers.append(int(stripped))
    return integers

def print_markdown_table(data):
    sizes = list(data.keys())
    algorithms = list(data[sizes[0]].keys())

    header = "|           | " + " | ".join(f"{algo:<23}" for algo in algorithms) + " |"
    separator = "|-----------|" + "|".join(["-" * 25 for _ in algorithms]) + "|"

    print(header)
    print(separator)

    for size in sizes:
        row = f"| {size:<9} | " + " | ".join(f"{str(data[size][algo]):<23}" for algo in algorithms) + " |"
        print(row)
    print()

def get_stats():
    methods = pattern_methods + palindrome_methods
    statistics = {}
    for testSize in testSizes:
        statistics[testSize] = {}
        for method in methods:
            extenstion = "." + testSize + ".times.txt"
            filename = method + extenstion
            running_times = read_integers_from_file(filename)
            least_running_time = min(running_times)
            highest_running_time = max(running_times)
            statistics[testSize][method] = (least_running_time, highest_running_time)
    return statistics

def plot(statistics, filename):
    sizes = list(statistics.keys())
    algorithms = list(statistics['small'].keys())
    x = range(len(sizes))  # for plotting

    # Plotting
    plt.figure(figsize=(10, 6))

    for algo in algorithms:
        min_times = [statistics[size][algo][0] for size in sizes]
        max_times = [statistics[size][algo][1] for size in sizes]
        plt.plot(x, min_times, label=f'{algo} (min)', linestyle='--')
        plt.plot(x, max_times, label=f'{algo} (max)')
        plt.fill_between(x, min_times, max_times, alpha=0.2)

    plt.xticks(x, sizes)
    plt.xlabel('Input Size')
    plt.ylabel('Running Time (ns)')
    plt.title('Running Time Ranges by Algorithm and Input Size')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(filename, dpi=300)

def show_results(statistics):
    pattern_stats = {}
    palindrome_stats = {}
    for testSize in testSizes:
        pattern_stats[testSize] = {}
        palindrome_stats[testSize] = {}
        for pattern_method in pattern_methods:
            pattern_stats[testSize][pattern_method] = statistics[testSize][pattern_method]
        for palindrome_method in palindrome_methods:
            palindrome_stats[testSize][palindrome_method] = statistics[testSize][palindrome_method]


    print_markdown_table(pattern_stats)
    print_markdown_table(palindrome_stats)

    plot(pattern_stats, "pattern-stats.png")
    plot(palindrome_stats, "palindrome-stats.png")

statistics = get_stats()
show_results(statistics)