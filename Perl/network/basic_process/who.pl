#!/usr/bin/perl -w

my %who;

open (WHOFH, "who |") or die "open who failed!";
while (<WHOFH>) {
	next unless /^(\S+)/;
	$who {$1}++;
}

foreach (sort {$who{$b} <=>  $who{$a}} keys %who) {
	printf "%10s %d\n", $_, $who{$_};
}

close WHOFH or die "Close error: $!";

