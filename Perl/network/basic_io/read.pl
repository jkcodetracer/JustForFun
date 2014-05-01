#!/usr/bin/perl -w

use IO::File;

while (1) {
# the difference between 'sysread' and 'read'
# is 'sysread' return imediately,
# 'read' will store the char in the buffer
	my $bytes = sysread(STDIN, $buffer, 100);
	die "read error" unless defined $bytes;
	last unless $bytes > 0;

	print $buffer; 
}


