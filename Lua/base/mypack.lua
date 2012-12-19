module(..., package.seeall)

ver = "0.1 alpha"

function print_pack()
	print("hello!")
end

_G.print_pack = print_pack
