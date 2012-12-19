
mytable = {{name = "joker", vice_name = "new town"},
		   {name = "jimmy", vice_name = "larry"},
		   {name = "milk", vice_name = "halmer"},
		   {name = "lee", vice_name = "dummy"}}

table.sort(mytable, function (a, b)
			return (a.name > b.name)
			end)

for i,v in pairs(mytable) do
	print(tostring(i), v.name, v.vice_name)
end
