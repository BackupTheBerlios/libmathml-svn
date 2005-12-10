#! /usr/bin/perl
use strict;

# this script finds all xml files in the directory $indir and strips the first
# embedded mathml content from it and writes it to a file with the same name
# in the directory $outdir. The corresponding png file that shows a sample
# rendering is copied to $outdir.


my $indir = "testsuite/Presentation/GeneralLayout";
my $outdir = "test";

my @files = `find $indir -name '*.xml'`;

foreach (@files) {
	chomp;
	stripmathml($_);
}

sub stripmathml {
	my $in = shift;
	my ($out) = $in =~ m/([^\/]*)$/;
	$out = $outdir."/".$out;
	my $start = 0;
	open(IN, "< $in");
	foreach (<IN>) {
		last if m/<\/math/;
		if ($start) {
		  	print OUT;
		} else {  
			$start = m/\<math/;
			if ($start) {
				open(OUT, "> $out");
			}
		}
	}
	$in =~ s/xml$/png/;
	if ( -e $in) {
		`cp $in $outdir`;
	}
}
