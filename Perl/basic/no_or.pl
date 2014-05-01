#!/usr/bin/perl -w

use warnings;
use diagnostics;

#use 5.010;
#my $someone = "Lee";
#my $last_name = $last_name{$someone} // '{No last name}';
#
#print ("$last_name\n");

use 5.010;

foreach $try (0, undef, '0', 1, 25) {
	print "Trying [$try] ---> ";
	my $value = $try || 'default';
	say "\tgot [$value]";
}




