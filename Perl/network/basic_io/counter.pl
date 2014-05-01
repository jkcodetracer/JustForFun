#!/usr/bin/perl -w 

use strict;
use IO::File;

my $file = shift;
my $counter = 0;
my $fh = IO::File->new($file);

while (defined (my $line = $fh->getline)) {
	$counter++;
}

STDOUT->print("Counted $counter line.\n");

$fh->close;


