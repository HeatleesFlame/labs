import subprocess
import unittest
import os

import misc

#we want to run the task_1.cpp with one arg - testcase path, we must separate all cases from each other
# to separate we can create file write all lines unlit we meet separator and then create new file again
# and we have to validate out we can call sprs.run() after we have to look at file named like out_n.txt
# match only md hash without reading
# if all corrent return true else false
# how to assingn 
# testcase execution: call the task_1.cpp pass path to case and compare result with expectations


class TestRootWord(unittest.TestCase):
    def test_1(self):
        tests_quantity = len(os.listdir(r'./tests/'))
        for i in range(1, tests_quantity+1):
            args = [r"./task_2.exe", rf"./tests/test_{i}/input.txt"]
            _ = subprocess.run(args=args)
            
            longest_root_res = misc.OutCommon(r"output_longest_root.txt")
            important_root_res = misc.OutCommon(r"output_cool_root.txt")
            longest_expected = misc.OutLongest(rf"./tests/test_{i}/out_longest_expected.txt")
            important_expected = misc.MostImportant(rf"./tests/test_{i}/out_cool_expected.txt")
            self.assertEqual(longest_expected, longest_root_res)
            self.assertEqual(important_expected, important_root_res)
            os.remove('output_longest_root.txt')
            os.remove("output_cool_root.txt")