#!/usr/bin/perl -w

use IO::File;

my $file = shift;
my $fh = IO::File->new($file);
my $line = <$fh>;

print $line;


