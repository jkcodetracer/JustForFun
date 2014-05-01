#!/usr/bin/perl -w 

use warnings;
use diagnostics;

my %file_list;
foreach (@ARGV) {
	$file_list{$_} = 1;	
}

while (<>) {
	if (/^(## CopyRight)/) {
		delete $file_list{$ARGV};	
	}
}

@ARGV = sort keys %file_list;
$^I = ".bak";
unless (defined @ARGV) {
	print "all down\n";
	exit 0;
}
while (<>) {
	if (/^#!/) {
		$_ .= "## CopyRight joker 2010~2013\n";	
	}	
	print;
}


