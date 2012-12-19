t = {}
m = {a = "and", b = "lilei", c = "han meimei"}

setmetatable(t, {__index = m})
for k, v in pairs(t) do
	print(k, v)
end

print("------------")
print(t.b, t.a, t.c)
