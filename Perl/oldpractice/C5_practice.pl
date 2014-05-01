#!/usr/bin/perl

use 5.010;
use utf8;

#chomp($line = <STDIN>);

#while(defined($line = <STDIN>)){
#	print "I saw $line";
#}

## print line ...  
#while(<STDIN>)
#{
#	print "I saw $_";
#}

## print all ...
#foreach (<STDIN>) {
#	print "I saw $_";
#}


#while(defined($line = <>)){
#	chomp($line);
#	print "It was $line that I saw!\n";
#}

print "all begin";
@array=qw /sdf sdfa asdf/;
print "@array ..\n";

#print <>;
#print sort <>;
#
#while(<>) {
#	chomp;
#	print "I saw $_ ...\n";
#}5

printf "Hello, %s; your password expires in %d days!\n", $users, $days_to_die;

printf "%0.1g %01g %g\n", 5/2, 51/174, 51**17;

printf "%12f\n", 6*7+2/3;

my @items = qw (wilma dino pebbles );
my $format = "The iterms are: \n" .  "%10s\n" x @items ;
printf $format, @items;

my $select_file = 'my_output';
open LOG, " > $select_file";

##指定编码格式： 
open TMP, ">:encoding(UTF-8)", "fix";


if(!open CT, ">>", "./test"){
	die "Open file failed...($!)";
}

print CT "joker make a big joke!\n";

##将stdout重定向到LOG
select LOG;
$| = 1; ## flush
print LOG "THis is written to the LOG at aonce!\n";
$| = 1;
print "dddddd\n";

select CT;
print "to ct\n";

select CT;
$| = 1;
print "real ct\n";

close CT;

