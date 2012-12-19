
title = "test string base"

if title ~= "string" then
	print(title)
elseif type(title) == "string" then
	print(title)
else
	error("no thing...")
end


