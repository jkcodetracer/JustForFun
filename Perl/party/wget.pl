#!/usr/bin/perl -w

use strict;
use warnings;
use diagnostics;

use LWP::Simple qw(get);

# 请求一个url，类似于wget
my $url = shift || "http://www.baidu.com";
my $content = get($url);

print $content;

exit 0;
