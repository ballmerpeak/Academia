#!/usr/bin/python
#-*- coding: utf-8 -*-

# Rules: Sequential counting up to X.
# Is X divisible by 3? Replace with "bizz"
# Is X divisible by 5? Replace with "buzz"
# Is X divisible by 3 and 5? Replace with "bizz buzz"

# Think of [1,51)
for i in range(1,51):

    if i % 3 == 0 and i % 5 == 0:
        print("Bizz Buzz")
    elif i % 3 == 0:
        print("Bizz")
    elif i % 5 == 0:
        print("Buzz")
    else:
        print(i)
