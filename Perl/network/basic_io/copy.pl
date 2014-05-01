#!/usr/bin/perl -w

use IO::File;
use IO::Handle;

my $src = shift;
my $dst = shift;

my $src_fh = IO::File->new("< " . $src);
my $dst_fh = IO::File->new("+>" . $dst);

STDOUT->open("+>log.txt") or die "Can't reopen STDOUT: $!";

if (!$src_fh or !$dst_fh) {
	die "open file failed! %!\n";
}

while (defined (my $line = $src_fh->getline)){
	print $dst_fh $line;
	print;
}

$src_fh->close;
$dst_fh->close;

