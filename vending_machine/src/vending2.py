#!/usr/bin/env python

"""vending2.py: This is a vending machine module written for a Keysight Technologies coding challenge.
It is to be used in conjunction with the run_tests.py module provided by the company.  The module opens
two JSONs, one with products detailing their cost and quantity, and one with transactions detailing
the product desired and the coins inserted.  Each transaction is checked for vailidity, and the 
inventory is updated and change dispensed as necessary.  The output is written as a JSON string
giving the results of each transaction.
"""

__author__      = "George Dong"

import json
from pathlib import Path
import sys

with open(sys.argv[1]) as inventory_json:    			#load the JSON data as dictionaries
    inventory_data = json.load(inventory_json)

with open(sys.argv[2]) as transactions_json:    
    transactions_data = json.load(transactions_json)

result = {}				
result_data = []										#This empty array will store transaction dictionaries/results

for dicts in transactions_data:
	delivered = False		
	name = dicts["name"]	
	funds = sum(dicts["funds"])
	price = inventory_data[name]["price"]*100 			#convert the dollar price to cents for easier calculations later
	if funds>=price and inventory_data[name]["quantity"]>0:	
		change = funds - price
		changeList = []									

		quarters = change//25							#I feel like every vending machine I have ever used only dispenses change in quarters..
		while(quarters>0):		
			changeList.append(25)
			quarters -= 1
		change = change%25

		dimes = change//10
		while(dimes>0):
			changeList.append(10)
			dimes -= 1
		change = change%10

		nickels = change//5
		while(nickels>0):
			changeList.append(5)
			nickels -= 1
		
		pennies = change%5
		while(pennies>0):
			changeList.append(1)
			pennies -= 1

		inventory_data[name]["quantity"] -= 1
		delivered = True
	
	else:
		changeList = dicts["funds"]

	result["product_delivered"] = delivered 			#update dictionary
	result["change"] = changeList
	result_data.append(result.copy()) 					#Need to create a new copy because otherwise the result gets overwritten every time.

print(json.dumps(result_data, indent = 2))  			#Dump the list of dictionaries into a JSON formatted string with indents to look like the expected