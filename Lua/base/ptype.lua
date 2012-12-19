print(type("hello world!"))
print(type(10.4*3))
print(type(print))
print(type(type))
print(type(true))
print(type(nil))
print(type(type(X)))

a = "hello world!"
b = a.gsub(a, "hello", "goodbye ")
print(a)
print(b)

c = a..b
print(c)

print(1 + "123")
