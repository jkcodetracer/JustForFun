#!/usr/bin/perl -w

print "PID = $$\n";

my $child = fork();
die "Can't fork: $!" unless defined $child;
open (FH, "+>ddd.txt");

if ($child > 0) {
	print "Parent procee: PID=$$, child=$child\n";
} else {
	my $ppid = getppid();
	print FH "Child process: PID=$$, parent=$ppid\n";
	exec ('ls', '-l');
	die "exec error()\n";
}

close(FH);

