x = 10
local i = 1

while i <= x do
	local x = i*2
	print(x)
	i = i+1
end

if i > 20 then
	local x = 20
	print(x + 20)
else
	print(x)
end

print(x)
print("i=" .. i)
