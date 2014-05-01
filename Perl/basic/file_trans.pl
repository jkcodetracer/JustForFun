#!/usr/bin/perl -w

use warnings;
use diagnostics;

my $in = $ARGV[0];
unless (defined $in) {
	die "Usage: $0 filename\n";
}

my $out = $in;
$out =~ s/(\.\w+)?$/.out/;

unless (open IN, "<$in") {
	die "open $in failed! $!\n";
}

unless (open OUT, ">$out") {
	die "open $out failed! $!\n";
}

while (<IN>) {
	s/Joker/Larry/gi;
	s/Larry/Joker/gi;
	print OUT $_;
}

close IN;
close OUT;


