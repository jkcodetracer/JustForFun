#!/usr/bin/perl -w

use strict;
my $arg = shift || 10;
pipe (READER, WRITER) or die "Can't open pipe:$!\n";

if (fork == 0) {
	close READER;
	select WRITER; $| = 1;
	factorial($arg);
	exit 0;
}

if (fork == 0) {
	close READER;
	select WRITER; $| = 1;
	my $result = fibonacci($arg);
	exit 0;
}

close WRITER;
print while <READER>;

sub factorial {
	my $target = shift;
	for (my $result = 1, my $i = 1; $i <= $target; $i++) {
		print "factorial($i) =>" , $result *= $i, "\n";	
	}
}

sub fibonacci{
	my $target = shift;
	my ($a, $b) = (1, 0);
	for (my $i = 1; $i <= $target; $i++) {
		my $c = $a+$b;	
		print "fibonacci ($i) => $c\n";
		($a, $b) = ($b, $c);
	}
}
