function enum(array)
	local index = 1
	return function()
		local ret = array[index]
		index = index + 1
		return ret
	end
end

function show_double(array)
	local index = 1
	return function ()
		local ret = array[index] 
		if ret then
			ret = ret * 2
		end
		index = index + 1
		return ret
	end
end

function foreach(array, action)
	for v in enum(array) do
		action(v)	
	end
	for v in show_double(array) do
		action(v)
	end
end

foreach({1,2,3,4,5}, print)
