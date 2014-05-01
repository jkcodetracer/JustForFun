base = {1, 2, 4, 5, 6}
polyline = { ["base"] = base, "add", "sub", "mul", "div"} 

tmpbase = polyline["base"]
i = 0
while i < 4 do
	print("base value" .. tmpbase[i + 1])
	print("operation :" .. polyline[i+1])
	i = i + 1
end

