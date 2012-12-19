line = io.read()
n = tonumber(line)

if n == nil then
	error(line .. " is not a number!")
else
	print(n*2)
end

line = io.read()
n = tostring(line)

print(n .. "  " .. line )

