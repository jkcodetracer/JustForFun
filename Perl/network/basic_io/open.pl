#!/usr/bin/perl -w

use IO::File;

open (TEST, '< test.txt') or die "open failed! $!"; 

@lines = <TEST>;
foreach (@lines) {
	print;
}

close(TEST) or die "close failed!";

# redirect!
print ("redirect begin!\n");
open (SAVEOUT, ">&STDOUT");
open (STDOUT, ">test.txt") or die "Can't open test.txt: $!";

print "STDOUT is redirect!\n";
system "date";

open (STDOUT, ">&SAVEOUT");
print ("STDOUT restored!\n");

close (SAVEOUT);

#sysopen
sysopen(FH, "joker.txt", O_CREAT | O_TRUNC | O_WRONLY)
	or die "Can't open: $!";

$interger = fileno(FH);
print ("integer $interger \n");

close(FH);






