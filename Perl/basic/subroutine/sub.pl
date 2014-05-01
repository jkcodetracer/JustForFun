#!/usr/bin/perl -w

use warnings;
use diagnostics;

# define a sub routine!
sub marine {
	print ("this is marine!\n");
}

# call the sub routine.
&marine;
&marine;
&marine;

# return value:
# the perl function always have a return value.
# it will return the subroutine's last operation's result, if 
# we don't define the "return xxx;"
sub new_str {
	print ("this is a return test!\n");
	$fred . " abc\n";
}

$fred = "return test";
$ret= &new_str;
print ("the return value is :", $ret, "\n");


