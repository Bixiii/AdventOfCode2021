import datetime

def load_input(file_name):
    input_file = open(file_name)
    lines = []
    for line in input_file:
        if line[-1] == '\n':
            lines.append(line[:-1])
        else:
            lines.append(line)
    return lines


def calculate_score(letters):
    max_count = 0.0
    min_count = float('inf')

    for value in letters.values():
        if value > max_count:
            max_count = value
        if value < min_count:
            min_count = value

    return max_count - min_count


def main():

    t1 = datetime.datetime.now()

    input_file_name = 'data/input_day_14.txt'
    lines = load_input(input_file_name)

    start_sequence = lines[0]
    rules = {} # stores for each pair the two pairs that will be created
    for i in range(2, len(lines)):
        if lines[i][-1] == '\n':
            rule = lines[i][:-1].split(' ')
        else:
            rule = lines[i].split(' ')
        if rule[0] not in rules:
            rules[0] = []
        rules[rule[0]] = [rule[0][0] + rule[2], rule[2] + rule[0][1]]

    letters = {} # keeps track of the letter count
    # count letters in start sequence
    for letter in start_sequence:
        if letter not in letters:
            letters[letter] = 0
        letters[letter] = letters[letter] + 1

    # count pairs in start sequence
    pairs = {} # stores how often each pair occurs
    for idx in range(0, len(start_sequence)-1):
        if start_sequence[idx:idx+2] not in pairs:
            pairs[start_sequence[idx:idx+2]] = 0
        pairs[start_sequence[idx:idx+2]] = pairs[start_sequence[idx:idx+2]] + 1


    # run simulation
    for iteration in range(1,41):
        new_pairs = {}
        for pair in pairs:
            added_letter = '' # letter that will be added in the current step
            count_added_letter = 0 # number how often the new letter will be added
            for new_pair in rules[pair]:
                if new_pair not in new_pairs:
                    new_pairs[new_pair] = 0
                new_pairs[new_pair] = new_pairs[new_pair] + pairs[pair]
                added_letter = new_pair[0]
                count_added_letter = pairs[pair]

            if added_letter not in letters:
                letters[added_letter] = 0
            letters[added_letter] = letters[added_letter] + count_added_letter

        pairs = new_pairs.copy()
        if iteration == 10:
            print('\n>>> Result part 1: ' + str(calculate_score(letters)))

    calculate_score(letters)

    t2 = datetime.datetime.now()
    print('>>> Result part 2: ' + str(calculate_score(letters)) + ' (computed all results in ' + str((t2-t1).total_seconds() * 1000) + 'ms)')


if __name__ == "__main__":
    main()
