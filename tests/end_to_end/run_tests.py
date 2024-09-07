import os
import glob
import subprocess

matrix_exe = "../../build/src/matrix"

test_files = list(map(str, glob.glob("tests_dat/test_*.in")))
test_files.sort()

ans_files = list(map(str, glob.glob("answers/answer_*.ans")))
ans_files.sort()

test_failed = 0
test_num = 0
for file in test_files :
    ans_file = open(ans_files[test_num], 'r')
    real_ans = float(ans_file.read())
    ans_file.close()

    test_str = str(file) + "\n"

    command = matrix_exe + " < " + file
    matrix_answer = float(subprocess.check_output(command, shell=True).decode("utf-8"))

    if (abs(matrix_answer - real_ans) > 1e-3) :
        print("Test", test_num + 1, "failed, expectation:", real_ans, "received:", matrix_answer)
        test_failed += 1

    test_num += 1

print("Passed: ", test_num - test_failed)
print("Failed: ", test_failed)