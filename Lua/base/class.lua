function user_create(name, id)
	local obj = {name = name, id = id}
	function obj:set_name(name)
		self.name = name 
	end

	function obj:set_id(id)
		self.id = id
	end

	function obj:get_name()
		return self.name
	end

	function obj:get_id()
		return self.id
	end

	return obj
end

o1 = user_create("Joker", 001)
print("O1's name:", o1:get_name(), "o1's id:", o1:get_id())
o1:set_id(100)
o1:set_name("miller")
print("O1's name:", o1:get_name(), "o1's id:", o1:get_id())




