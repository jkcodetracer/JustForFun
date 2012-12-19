--利用lua返回值的特性 ，也就是可以返回多个值，通过设置dummy变量，可以只获取其中某几个

s = "this is a good idea for changes, do it!"
p = "is"
local _, x = string.find(s, p)

print(_ .. x)

print(string.find(s, p))


