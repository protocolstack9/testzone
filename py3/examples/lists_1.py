def _print(lists) :
	for s in lists:
		print(s)


# LISTS
names = [ "Dave", "Mark", "Ann", "Phil" ]

print("Before Change")
_print(names)

print("")

a = names[2]
names[0] = "Jeff"

print("After Change")
_print(names)

print("")

names.append("Paula")
print("After Append")
_print(names)

print("")

names.insert(2, "Thomas")
print("After Insert")
_print(names)

print("")

b = names[:2]
print("slicing")
_print(b)

print("")

names[1:] = ['poe','dow']
print("replace")
_print(names)

