#!/usr/bin/perl -w

use warnings;
use diagnostics;

$^I = ".out";

while (<>) {
	s/Fred/Larry/ig;
	print;
}

