#!/usr/bin/env python

import json
from pathlib import Path
import sys

class Product:
	def __init__(self, name, quantity, price):
		self.name = name
		self.quantity = quantity
		self.price = price

	def getQuantity():
		return self.quantity

	def decrement():
		self.quantity -= 1

	def getPrice():
		return self.price

with open(sys.argv[1]) as inventory_json:    
    inventory_data = json.load(inventory_json)


productList = []

for key in inventory_data.keys():
	name = str(key)
	print(key)
	quantity = inventory_json[name]['quantity']
	print(quantity)
	price = inventory_json[name]['price']
	print(price)
	prod = Product(name, quantity, price)
	productList.append(prod)

with open(sys.argv[2]) as transactions_json:    
    transactions_data = json.load(transactions_json)

print("""
[
    {
        "product_delivered": true,
        "change": []
    }
]
""")

