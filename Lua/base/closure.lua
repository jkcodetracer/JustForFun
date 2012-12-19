
int = 124


function digit(digit)
	local x = digit
	return function()
		x = x * 2 + digit
		digit = digit+1
		return x
		end
end

c1 = digit(1)
print(c1())
print(c1())
c2 = digit(10)
print(c2())
print(c2())

status = {"begin", "step1", "step2", "end"}
function selfmachine()
	local x = 0;	
	return function (k)
		if k == 1 and x == 0 then
			x = 1	
			print(status[x])
			return x
		end

		if k == 2 and x == 1 then
			x = 3
			print(status[x])
			return x
		end

		if k == 3 and x == 2 then
			x = 4
			print(status[x])
			return x
		else 
			x = 2
			print(status[x])
			return x
		end
	end	
end

status_func = selfmachine()

status_func(1)
status_func(2)
status_func(3)
status_func(4)
status_func(3)


