#!/usr/bin/perl -w

use warnings;
use diagnostics;

print "please input a file name!\n";
chomp ($file_name = <STDIN>);

if (defined $file_name && -e $file_name) {
	print ("the file is leagal!\n");
} else {
	print ("an invalid file!\n");
}

open CONFIG, $file_name
	or die ("open failed! $!\n");
if (-M CONFIG < 28) {
	print ("the file is modified soon!\n");
}
close CONFIG;

# the virsual handler
# if there is a file test between 
# this two opr, the '_' is changed!
# we use this to avoid one thing that the 
# file test will reread the file infomation while
# we do the test again.
if (-r $file_name and -w _) {
	print ("the file $file_name is rw.\n");
} else {
	print ("the file descr is not readable.\n");
}

@file_st = stat($file_name);
foreach (@file_st) {
	print ("$_\n");
}



