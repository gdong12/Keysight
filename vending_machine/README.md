Vending Machine
===============

Introduction
------------
This software development exercise is part of the interview process
for Keysight Technologies.  This is an opportunity for you to show
us your skill in software engineering.

Assignment
----------
Create software for a vending machine.  Your program will be given two JSON
files as input:

* Inventory: specifies how the vending machine is stocked, with product names,
  and a quantity and price (in dollars) for each product
* Transactions: a list of purchase transactions, with the product name, and the
  value (in cents) of coins deposited

Your software should take two command-line arguments.  The first argument is the
path to the inventory JSON file.  The second argument is the path to the transactions
JSON file.

Your software should produce a JSON document, on stdout, containing a list of
transaction results.  Each result should identify the product name, whether a
product was delivered, and the change given, as a list of coin values.

See the `test` directory for examples.

To run the tests, use the run_tests.py script with Python 3.x.

Implementation
--------------
Use any language and tools you'd like to construct your solution.

Document the assumptions and design decisions you've made.

A stub example is provided in Python, mainly to illustrate running the test
harness.  This is not meant to be a starting point for your implementation.

Deliver source code, and any instructions needed for a reviewer to run your
program.
