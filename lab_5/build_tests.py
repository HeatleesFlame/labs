import os
import re




if not os.path.exists(r"./tests"):
            os.mkdir(r"./tests")

with open('all_tests.txt', 'r') as all_tests:
    line = all_tests.readline()
    while True:
        while not re.match('Test [1-4]', line) and line:
            line = all_tests.readline()
        if not line:
              break
        else: case = line[-2]
       
                
        line = all_tests.readline()

        if not os.path.exists(rf'./tests/test_{case}'):  
            os.mkdir(rf'./tests/test_{case}')

        with open(rf"./tests/test_{case}/input.txt", 'w') as input_data:
                while True:
                    line = all_tests.readline()
                    if line.startswith("="):
                          break
                    input_data.write(line)
            
        with open(rf'./tests/test_{case}/out_longest_expected.txt', 'w')  as out_1:
                while True:
                    line = all_tests.readline()
                    if line == "\n":
                          break
                    out_1.write(line)

        with open(rf"./tests/test_{case}/out_cool_expected.txt", 'w') as out_2:
                while True:
                        line = all_tests.readline()
                        if line == "\n" or not line:
                            break
                        out_2.write(line)