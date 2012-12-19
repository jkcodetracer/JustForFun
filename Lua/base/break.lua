
local i = 1

a = {1,2,3,4,5}
v = 4

while a[i] do
	if a[i] == v then 
		print(a[i])
	else
		print(nil)
	end

	i = i+1
end
