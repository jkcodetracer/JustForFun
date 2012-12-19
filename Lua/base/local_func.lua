-- one
lib = {}
lib.foo = function (x,y) return x+y end
lib.goo = function (x,y) return x*y end

-- two
lib = {
	foo = function(x,y) return x+y end
	goo = function(x,y) return x-y end
}

-- three
lib = {}
function lib.foo(x,y)
	return x+y
end
function lib.goo(x,y)
	return x-y
end

--chunk 1
local f = function (x, y)
	return x + y	
end

local g = function (x, y)
	local m = f(x,y)
	return m
end

--chunk 2
local function f(x,y)
	return x+y
end

--chunk 3
local f
f = function (x,y)
	if x > y and x < 10 then
		return x * f(x+1,y)		--涉及到递归的问题，必须先声明一个
	end
end


	

