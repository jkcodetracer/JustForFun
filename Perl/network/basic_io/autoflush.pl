#!/usr/bin/perl -w

use IO::Handle;

open FH, ">>test.txt";

FH->autoflush(1);

close FH;
