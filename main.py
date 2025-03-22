import timeit



def backtrack_solve(puzzle, row, col):
    if row == 8 and col == 9:
        return True
    
    if col == 9:
        row += 1 
        col = 0

    if (puzzle[row][col] != 0):
        return backtrack_solve(puzzle, row, col+1)
    
    for entry in range(1, 10):
        if place_check(puzzle, row, col, entry):
            puzzle[row][col] = entry
            if backtrack_solve(puzzle, row, col+1):
                return True 
            puzzle[row][col] = 0

    return False 


def place_check(puzzle, row, col, num):
    #chekc row 
    for i in range(9):
        if (puzzle[row][i] == num):
            return False

    #check col 
    for j in range(9):
            if (puzzle[j][col]) == num:
                return False 
    
    #check subgroup 
    startRow = row - (row % 3)
    startCol = col - (col % 3)

    for i in range(3):
        for j in range(3):
            if puzzle[i + startRow][j + startCol] == num:
                return False
    return True 


def check_puzzle(puzzle):
    valid_sol = True 

    #check rows 
    for row in puzzle:
        if (check_list(row) == False):
            valid_sol = False

    #check col    
    for col in range(9):
        columns = []
        for row in puzzle:
            columns.append(row[col])
        if (check_list(columns) == False):
            valid_sol = False
    
    #check subgrids
    #not sure if checking rows and cols is already sufficient for the puzzle to be solved
    subgrids = [[] for _ in range(9)]  

    for row in range(9):
        for col in range(9):
            # Find which subgrid this cell belongs to using modulo
            subgrid_index = (row // 3) * 3 + (col // 3)
            subgrids[subgrid_index].append(puzzle[row][col])
    for subgrid in subgrids:
        if (check_list(subgrid) == False):
            valid_sol = False 

    return valid_sol
        
def check_list(subset):
    valid_list = True
    for num in range(1, 10):
        if num not in subset:
            valid_list = False
            break  
    return valid_list 

def main():
    puzzle = [
    [1, 7, 9, 0, 6, 4, 0, 0, 0],
    [4, 0, 0, 0, 1, 0, 0, 9, 5],
    [6, 0, 0, 9, 0, 0, 0, 7, 1],
    [3, 4, 6, 0, 0, 0, 0, 0, 2],
    [5, 0, 1, 0, 9, 0, 0, 6, 7],
    [0, 0, 0, 6, 3, 5, 0, 8, 0],
    [2, 0, 3, 7, 8, 0, 0, 0, 0],
    [0, 5, 7, 0, 4, 6, 2, 0, 0],
    [9, 6, 0, 2, 5, 3, 0, 1, 0]
    ]

    solved_puzzle = [
    [1, 7, 9, 5, 6, 4, 8, 2, 3],
    [4, 2, 8, 3, 1, 7, 6, 9, 5],
    [6, 3, 5, 9, 2, 8, 4, 7, 1],
    [3, 4, 6, 8, 7, 1, 9, 5, 2],
    [5, 8, 1, 4, 9, 2, 3, 6, 7],
    [7, 9, 2, 6, 3, 5, 1, 8, 4],
    [2, 1, 3, 7, 8, 9, 5, 4, 6],
    [8, 5, 7, 1, 4, 6, 2, 3, 9],
    [9, 6, 4, 2, 5, 3, 7, 1, 8]
    ]
    

    backtrack_solve(puzzle, 0, 0)

    print(check_puzzle(puzzle))

    for row in puzzle:
        print(" ".join(map(str, row)))


if __name__ == "__main__":
    execution_time = timeit.timeit("main()", setup="from __main__ import main", number=1)
    print(f"Execution time: {execution_time} seconds")
