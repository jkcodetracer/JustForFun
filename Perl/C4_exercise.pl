#!/usr/bin/perl

use 5.010;
use utf8;

my @fred = 1..1000;
my $fred_total = total(@fred);

print "The total of \@fred is $fred_total.\n";
print "Enter some numbers on separate lines: ";
my $user_total =  total(<STDIN>);
print "The total of those numbers is $user_total.\n";

sub total{
	my $tmptotal = 0;
	
	foreach (@_){
		$tmptotal += $_;	
	}

	 $tmptotal;
}

my @fred = above_average(1..10);
print "\@fred is @fred\n";
print "(should be 6 7 8 9 10)\n";
my @barney = above_average(100, 1..10);
print "\@barney is @barney\n";
print "(Should be just 100)\n";

sub above_average{
	my $div = @_;
	my $sum = 0;

	if( $div == 0 )
	{
		return 0
	}

	foreach(@_){
		$sum += $_;
	}

	$sum/$div;
}

greet("joker");
greet("yue yue");
greet("Fred");
greet(qw/sdf sdf/);
greet("joy");

@te = @bt = @qq = qw /jk zy hh/;
print "@te, @bt, @qq";

sub greet{
	state @namelist;

	if( @namelist) {
		print "Hi @_, @namelist is here!\n";}
	else {
		print "Hi @_, you are the first one here!\n";
		}
	
	foreach(@_){
		push @namelist, ",";
		push @namelist, $_;
	}
	if($namelist[0] eq ",")
	{
		print "$namelist[0]\n";
		shift @namelist;
	}
}
