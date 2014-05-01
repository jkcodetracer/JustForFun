#!/usr/bin/perl -w

use Errno qw{EACCES ENOENT};
my $result = open(FH, ">/etc/passwd");

if (!$result) {
	if ($! == EACCES) {
		warn "You do not have permission to open this file.";	
	} elsif ($! == ENOENT) {
		warn "File or directory not found!";	
	} else {
		warn "Some other error occured: $!";	
	}
}

close(FH);
