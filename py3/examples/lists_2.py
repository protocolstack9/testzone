def _print(lists) :
	for s in lists:
		print(s)

a = [1,2,3]
b = [4,5]
_print(a + b)

print("max a: %d, min b: %d" % (max(a), min(b)))
