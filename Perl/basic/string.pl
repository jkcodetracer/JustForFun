#!/usr/bin/env perl


print ("fred \n");
print ("joker \\ 'has a great value!\n'");
print ('joker \\ has \'a great value!\'\\n');
print ("\n");

print ('joker \n \\ ');

print ("\a \a \a\a \lA \n");

$number = 1.20E+12;

print ("\U This is a simplE Test! \n\E");
print ("\U this is A te " . $number . "st! try E...\E \n");

$string = "What a mazing!";

print ("$string  $number\n");

$string = $string . " " x 3;

print ("current string: $string \n");
