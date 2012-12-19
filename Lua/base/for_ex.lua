day = {"sun", "mon", "tus", "wen", "thu", "fri", "sat"}

--ipairs只能用于数字下标的table的迭代
reverse = { }
for i,v in ipairs(day) do
	reverse[v] = i	
end

for i,v in ipairs(day) do
	print(i, v)
end
print("-------")
--pairs 适用范围更广， 可以用于键值对的迭代
for i,v in  pairs(reverse) do
	print(i, v)
end
