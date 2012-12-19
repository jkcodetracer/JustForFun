function tail_end (i)
	return i
end

function tail_call(n)
	local a = 1232
	local b = 333
	local c = 134
	local i = 0

	if n < 10000000000 then
		return tail_call(n+1) 
	end

--	return tail_end(i);
	return i
end

tmp = tail_call(0)

print(tmp)

