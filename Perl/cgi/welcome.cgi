#!/usr/bin/perl -wT

use strict;

my $time = localtime;
my $remote_id = $ENV{REMOTE_HOST} || $ENV{REMOTE_ADDR};
my $admin_email = $ENV{SERVER_ADMIN};

print "Content-type: text/html\n\n";

print <<END_OF_PAGE;
<HTML>
<HEAD>
	<TITLE> $remote_id  $admin_email Welcome to Mike's Mechanics Database</TITLE>
</HEAD>

END_OF_PAGE

