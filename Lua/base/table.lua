--[[
下标从1开始， 可以任意装填结构到
数组中，哪怕整个table中都是不同类型的元素
]]--
week = {"sun", "mon", "tus", "wen", "thu", "fri", "sat"}
w = {x=0, y=0, label="console"}
--x = {sin(0), sin(1), sin(2)}
x = {1,2,3,4}
w[1] = "another fieled"
x.f = w

print(w["x"])		-->0
print(w["label"])	-->console
print(x.f[1])		-->another field
print(x.f[2])		-->与w不相关的数据 nil.

w.x = nil
print(w.f)			-->nil
print(w.label)		-->label

--[[
	从0开始的话，就要设定下标了例如 ["0"] = "add"
	或者类似于结构体那种: ｛monday, tusday, wendsday｝
	可以转换成{["one"] = monday, ["two"] = tusday,}
	可以使用;来代替，通常代码里面使用分号来分割不同类型
]]--
opnames = {["+"] = "add", ["-"] = "minues",
			["*"] = "mul", ["/"] = "div",}

print(opnames["*"])

--[[ 单链表 ]]--
list = nil

for line in io.lines() do
	list = {next=list, value = line}
end

l = list
while l do
	print(l.value)
	l = l.next
end


