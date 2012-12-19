
function fmtwrite(fmt, ...)
	return io.write(string.format(fmt, unpack(arg)))
end

int = 15
ret = fmtwrite("%04d\n", int)

print(ret)
