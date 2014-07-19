a = "Hello, world"
b = "Good Bye, world"

print("Partial: %s" % a[:5])

x = "1000"

s = "The value of x is " + str(x)
print(s)

t = "The value of x is " + repr(x)
print (t)

u = "The value of x is " + format(x)
print (u)

print (a + ", " + b)
