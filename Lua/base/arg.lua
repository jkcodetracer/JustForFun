-- lua 支持可变参数的操作，默认都存放在arg中

function avg (...)
	local total
	local n

	total = 0
	n = 0
	for i,v in ipairs(arg) do
		total = total + tonumber(v) 	
		n = n + 1
	end
	print(tostring(total))
	
	return tonumber(total)/tonumber(n)
end

-- 如果使用avg{}传参数，就会被识别为一个参数...
average = avg(1,2,3,4,5,6,7,8)
print("average: " .. tostring(average))

--使用unpack 可以将一个table的所有元素拆分，作为输入或者输出
num_set = {2,3,4,5,6,7,8,9}
average = avg(unpack(num_set))
print("average: " .. tostring(average))


