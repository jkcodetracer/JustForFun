#!/usr/bin/perl

@line = `perldoc -u -f atan2`;
foreach(@line) {
	s/\w<([^>]+)>/\U$1/g;
	print;
}

