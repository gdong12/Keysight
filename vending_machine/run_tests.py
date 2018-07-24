#!/usr/bin/env python

import json
import logging
import os.path
from pathlib import Path
import re
import subprocess
import sys
import traceback

class TestRunner(object):
    # Update this list as needed to execute your application.
    exe_and_args = ["py", "src/vending2.py"]
    timeout_seconds = 10

    def __init__(self, test_path):
        self.test_path = test_path
        
    def run(self):
        logging.info("----->>>  Starting test %s ----->>>", self.test_path)
        try:
            self.execute_test()
            self.check_results()
            result = True
        except:
            logging.info("Error running test %s: %s", self.test_path, traceback.format_exc())
            result = False
        logging.info("<<<----- Finishing test %s <<<----- %s", self.test_path, self._pass_or_fail(result))
        return result

    def execute_test(self):
        args = self.exe_and_args.copy()
        args.append(str(self.test_path / "inventory.json"))
        args.append(str(self.test_path / "transactions.json"))
        result = subprocess.run(args, check=True, shell=True, stdout=subprocess.PIPE, timeout=self.timeout_seconds)
        (self.test_path / "output.json").write_bytes(result.stdout)

    def check_results(self):
        actual_results = json.load((self.test_path / "output.json").open())
        expected_results = json.load((self.test_path / "expected.json").open())
        if len(actual_results) != len(expected_results):
            raise Exception("output did not match expected in number of results")
        for actual_result, expected_result in zip(actual_results, expected_results):
            self.check_result(actual_result, expected_result)

    def check_result(self, actual_result, expected_result):
        if actual_result["product_delivered"] != expected_result["product_delivered"]:
            raise Exception('output did not match expected on product_delivered')
        actual_change_total = sum(actual_result["change"])
        expected_change_total = sum(expected_result["change"])
        if actual_change_total != expected_change_total:
            raise Exception("output did not match expected on change returned")

    def _pass_or_fail(self, result):
        return "pass" if result else "FAIL"

def run_tests(test_names):
    results = [TestRunner(test_name).run() for test_name in test_names]
    return all(results)

def is_test_dir(d):
    return d.is_dir() and re.match(r'\d\d', d.name)

def enumerate_test_dirs(test_root):
    return [x for x in test_root.iterdir() if is_test_dir(x)]

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    if len(sys.argv) > 1:
        tests = [Path(x) for x in sys.argv[1:]]
    else:
        tests = enumerate_test_dirs(Path(__file__).parent / "test")
    result = run_tests(tests)
    sys.exit(0 if result else 1)
