import random
import math
import os
import numpy

to_curr_dir = os.path.dirname(os.path.realpath(__file__))

count_tests = 10
max_determinant = 1000000

for test_num in range(count_tests) :
    #prepare
    N = random.randint(100, 150)
    shuffle_steps = N * (int(math.sqrt(N)) // 2 + 1)
    NN = N * N
    matrix = [0] * NN

    # generate diagonal
    determinant = random.randint(max_determinant / 2, max_determinant)
    if (random.randint(0, 1)) :
        determinant *= -1

    part_det = abs(determinant) ** (1 / N)
    min_elem = part_det - part_det * 0.3
    max_elem = part_det + part_det * 0.35

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

        coef = random.uniform(0.7, 1.37)
        if (random.randint(0, 1)) :
            coef *= -1
        
        Nrow1 = N * row1
        Nrow2 = N * row2
        for k in range(N) :
            matrix[Nrow2 + k] += coef * matrix[Nrow1 + k]

    # write answer
    matrix_numpy1D = numpy.array(matrix)
    matrix_numpy2D = numpy.reshape(matrix_numpy1D, (-1, N))

    file_name = to_curr_dir + "/answers/answer_" + f'{test_num+1:03}' + ".ans"
    file = open(file_name, 'w')
    file.write(str(numpy.linalg.det(matrix_numpy2D))) # numpy for more accuracy (we loose a lot in shuffling diagonals)
    file.close()

    # write matrix
    file_name = to_curr_dir + "/tests_dat/test_" + f'{test_num+1:03}' + ".in"
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
