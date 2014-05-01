#!/usr/bin/perl -w

use warnings;
use diagnostics;
use 5.010;

while (<STDIN>) {
	chomp;
	if (/(?<word>\b\w*a\b)/) {
		print "Matched: |$`<$&>$'|\n";	
		print "'word' contains: $+{word}\n";
	} else {
		print "missing\n";	
	}
}
