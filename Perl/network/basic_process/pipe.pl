#!/usr/bin/perl -w

use IO::File;
use IO::Handle;
use FileHandle;

open (WC, "| wc -lw") or die "Can't open wordcount :$!";
print WC "This is the first line.\n";
print WC "s 1111 the test count.\n";
print WC "Oops, over!\n";
close WC;

#$wc = FileHandle::open("| wc -lw") or die "...";
$wc = FileHandle->new("| wc -lw") or die "...";
$wc->print("test over!\n");
$wc->print("try again!\n");
