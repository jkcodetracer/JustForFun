#!/usr/bin/perl -w

use warnings;
use diagnostics;

print ("input the schema string:\n");
my $what = "";
chomp($what = <STDIN>);
my $tre_str = '(' . $what . ')' . "{3,3}";

print ("input the test string:\n");
while (<>) {
	chomp;
	if (/$tre_str/) {
		print ("matched: |$`<$&>$'|\n");	
	} else {
		print ("miss!\n");	
	}
}




