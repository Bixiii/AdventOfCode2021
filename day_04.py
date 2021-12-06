def load_input(file_name):
    input_file = open(file_name)
    boards = []
    numbers = []
    for line_num, line in enumerate(input_file):
        if line_num == 0:
            numbers = line[:-1].split(',')
            continue
        if line == '\n':
            boards.append([])  # add new board
            continue
        line = line[:-1]
        if line[0] == ' ':
            line = line[1:]
        line = line.replace('  ', ' ')
        nums = line.split(' ')
        fields = []
        for num in nums:
            fields.append({'num': num, 'mark': False})
        boards[-1].append(fields)

    return numbers, boards


def win(board):
    # check lines
    for line in board:
        num_marked = 0
        for field in line:
            if field['mark']:
                num_marked = num_marked + 1
        if num_marked == 5:
            return True
    # check columns
    for i in range(0, 5):
        num_marked = 0
        for line in board:
            if line[i]['mark']:
                num_marked = num_marked + 1
        if num_marked == 5:
            return True
    return False


def calculate_score(board, winning_number):
    sum_unmarked = 0
    for line in board:
        for field in line:
            if field['mark']:
                continue
            sum_unmarked = sum_unmarked + int(field['num'])
    return sum_unmarked * winning_number


def reset(boards):
    for board in boards:
        for line in board:
            for field in line:
                field['mark'] = False


def main():
    input_file_name = 'data/input_day_4.txt'
    numbers, boards = load_input(input_file_name)

    # PART 1
    game_finished = False
    for next_number in numbers:
        if game_finished:
            break
        for idx, board in enumerate(boards):
            for line in board:
                for field in line:
                    if field['num'] == next_number:
                        field['mark'] = True
            if win(board):
                print('Day 4 - Part 1: ' + str(calculate_score(board, int(next_number))))
                game_finished = True

    # PART 2
    reset(boards)
    remaining_boards = len(boards)
    boards = [{'fin': False, 'board': board} for board in boards]
    for next_number in numbers:
        for idx, board in enumerate(boards):
            if board['fin']:
                continue
            for line in board['board']:
                for field in line:
                    if field['num'] == next_number:
                        field['mark'] = True
            if win(board['board']):
                board['fin'] = True
                remaining_boards = remaining_boards - 1
                if remaining_boards == 0:
                    print('Day 4 - Part 2: ' + str(calculate_score(board['board'], int(next_number))))


if __name__ == "__main__":
    main()
