#!/usr/bin/perl -w

use warnings;
use diagnostics;

my $debug = $ENV{DEBUG} // 1;
my $secrete = int(1 + rand 100);
print "Don't tell anyone, but the secret number is $secrete.\n"
	if $debug;

print ("input your answer:\n");
while (<STDIN>) {
	chomp;
	if (/[0-9]+/) {
		print ("Too high!\n") if $_ > $secrete;
		print ("Too low!\n") if $_ < $secrete;
		if ($_ == $secrete) {
			print ("beego!\n");	
			last;
		}
	}

	if ($_ eq "quit" || $_ eq "exit") {
		print ("end\n");	
		last;
	}
}

