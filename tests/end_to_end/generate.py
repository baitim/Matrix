import random
import math

count_tests = 10
max_determinant = 100000

for test_num in range(count_tests) :
    #prepare
    N = random.randint(70, 100)
    shuffle_steps = N * int(math.sqrt(N))
    NN = N * N
    matrix = [0] * NN

    # generate diagonal
    determinant = random.randint(max_determinant / 2, max_determinant)
    if (random.randint(0, 1)) :
        determinant *= -1

    part_det = abs(determinant) ** (1 / N)
    min_elem = part_det - part_det * 0.4
    max_elem = part_det + part_det * 0.45

    last_elem = determinant
    for j in range(N-1) :
        index = j * N + j
        matrix[index] = random.uniform(min_elem, max_elem)

        if (random.randint(0, 1)) :
            matrix[index] *= -1
        last_elem /= matrix[index]

    matrix[NN - 1] = last_elem

    # shuffle diagonal
    for j in range(shuffle_steps) :
        row1 = random.randint(0, N - 1)
        row2 = row1
        while (row1 == row2) :
            row2 = random.randint(0, N - 1)

        coef = random.uniform(0.5, 1.6)
        if (random.randint(0, 1)) :
            coef *= -1
        
        Nrow1 = N * row1
        Nrow2 = N * row2
        for k in range(N) :
            matrix[Nrow2 + k] += coef * matrix[Nrow1 + k]

    ## write answer
    file_name = "answers/answer_" + f'{test_num+1:03}' + ".ans"
    file = open(file_name, 'w')
    file.write(str(determinant))
    file.close()

    # write matrix
    file_name = "tests_dat/test_" + f'{test_num+1:03}' + ".in"
    file = open(file_name, 'w')
    test_str = str(N) + " " + "\n"

    for j in range(N) :
        row = j * N
        for k in range(N) : 
            test_str += str(matrix[row + k]) + "\t"
        test_str += "\n"
    file.write(test_str)

    file.close()
    print("test ", test_num + 1, " generated")
