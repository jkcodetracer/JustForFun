#!/usr/bin/perl -w

$normal_type = "hi there!";
$type_ref = \$normal_type;

@array = qw /this is an array/ ;
$array_ref = \@array;

%hash = { first_name => 'joker', second_name => 'Wang'};
$hash_ref = \%hash;


$a = $$type_ref;
print "type ref: $a \n";

print "array ref:\n";
@b = @$array_ref;
foreach (@b) {
	print;
	print "\n";
}

%c = %$hash_ref;
print "hash ref: %c{first_name} \n";
$test = $hash_ref->{'first_name'};
print "hash: $test\n";

