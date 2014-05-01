list = nil
i = 0
for line in io.lines() do
	list = {next=list, value=line}
	i = i + 1
	if i > 20 then
		break
	end
end 

tmplist = list
while tmplist do
	print(tmplist.value)
	tmplist = tmplist.next
end




