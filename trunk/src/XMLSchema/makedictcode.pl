#! /usr/bin/perl -w
use strict;

# gather data

my (%pre, %in, %post);
readOperators(\%pre, \%in, \%post);

my (@preatts, @inatts, @postatts);
getAtts(\@preatts, \%pre);
getAtts(\@inatts, \%in);
getAtts(\@postatts, \%post);

my %types;
getTypes(\%types, \@preatts);
getTypes(\%types, \@inatts);
getTypes(\%types, \@postatts);

my %typvals;
getTypVals(\%typvals, \%types, \%pre); 
getTypVals(\%typvals, \%types, \%in); 
getTypVals(\%typvals, \%types, \%post); 

# print data

# print header for mmlmodict.h
open (FH, ">mmlmodict.h") or die;
print FH<<EOF;
#ifndef MMLMODICT_H
#define MMLMODICT_H

#include "mathml.h"
#include <map>
class MMLmoDict {
public:
	static void lookupOperator(const DOMString &, const MMLAttribute **att);
private:
	static bool ready;
	static void init();
EOF

foreach (keys %typvals) {
	my $typ = $_;
	my $valref = $typvals{$_};
	foreach (keys %$valref) {
		print FH "\tstatic const MML$typ ".$valref->{$_}.";\n";
	}
	print FH "\n";
}
my $numpreatts = @preatts;
my $numinatts = @inatts;
my $numpostatts = @postatts;
my $numpreops = keys %pre;
my $numinops = keys %in;
my $numpostops = keys %post;
print FH<<EOF;
	static const short presize;
	static const short insize;
	static const short postsize;
	static const short prepos[$numpreatts];
	static const short inpos[$numinatts];
	static const short postpos[$numpostatts];
	static const char * presyms[$numpreops];
	static const char * insyms[$numinops];
	static const char * postsyms[$numpostops];
	static const MMLAttribute *const pre[$numpreops][$numpreatts];
	static const MMLAttribute *const in[$numinops][$numinatts];
	static const MMLAttribute *const post[$numpostops][$numpostatts];
	static std::map<DOMString, short> prerefs;
	static std::map<DOMString, short> inrefs;
	static std::map<DOMString, short> postrefs;
	static void setPre(const MMLAttribute **a, short row);
	static void setIn(const MMLAttribute **a, short row);
	static void setPost(const MMLAttribute **a, short row);
};
#endif
EOF
close(FH);

open(FH, ">mmlmodict.cpp") or die;
print FH<<EOF;
#include "mmlmodict.h"
using namespace MML;
bool MMLmoDict::ready = false;
const short MMLmoDict::presize = $numpreatts;
const short MMLmoDict::insize = $numinatts;
const short MMLmoDict::postsize = $numpostatts;
std::map<DOMString, short> MMLmoDict::prerefs;
std::map<DOMString, short> MMLmoDict::inrefs;
std::map<DOMString, short> MMLmoDict::postrefs;
/* If the operator does not occur in the dictionary with the specified form,
   the renderer should use one of the forms that is available there, in the 
   order of preference: infix, postfix, prefix; */
void
MMLmoDict::lookupOperator(const DOMString &op, const MMLAttribute **a) {
	if (!ready) {
		init();
	}
	std::map<DOMString, short>::const_iterator i;
        i = inrefs.find(op);
        if (i != inrefs.end()) {
		setIn(a, i->second);
	} else {
		i = postrefs.find(op);
		if (i != postrefs.end()) {
			setPost(a, i->second);
		} else {
			i = prerefs.find(op);
			if (i != prerefs.end()) {
				setPre(a, i->second);
			}
		}
	}
}
void
MMLmoDict::setPre(const MMLAttribute **a, short row) {
	for (short i=0; i<presize; ++i) {
		a[prepos[i]] = pre[row][i];
	}
}
void
MMLmoDict::setIn(const MMLAttribute **a, short row) {
	for (short i=0; i<insize; ++i) {
		a[inpos[i]] = in[row][i];
	}
}
void
MMLmoDict::setPost(const MMLAttribute **a, short row) {
	for (short i=0; i<postsize; ++i) {
		a[postpos[i]] = post[row][i];
	}
}
void
MMLmoDict::init() {
	ready = true;
	for (short i=0; i<$numpreops; ++i) {
		DOMString op = presyms[i];
		op.resolveEntities();
		prerefs.insert(std::pair<DOMString, short>(op, i));
	}
	for (short i=0; i<$numinops; ++i) {
		DOMString op = insyms[i];
		op.resolveEntities();
		inrefs.insert(std::pair<DOMString, short>(op, i));
	}
	for (short i=0; i<$numpostops; ++i) {
		DOMString op = postsyms[i];
		op.resolveEntities();
		postrefs.insert(std::pair<DOMString, short>(op, i));
	}
}
EOF
foreach (keys %typvals) {
	my $typ = $_;
	foreach (keys %{$typvals{$typ}}) {
		my $val = $_;
		my $n = $typvals{$typ}{$val};
		if ($typ ne "bool") {
			$val = "DOMString(\"$val\")";
		}
		print FH "const MML$typ MMLmoDict::$n($val);\n";
	}
}

printCode("pre", \%pre, \@preatts);
printCode("in", \%in, \@inatts);
printCode("post", \%post, \@postatts);

close(FH);
exit;

# printing function that can be called for pre, in, and post

sub printCode {
	my $name = shift;
	my $allref = shift;
	my $attsref = shift;

	my $numops = keys %$allref;
	my $numatts = @$attsref;
	my @all = keys %$allref;
	print FH "const short MMLmoDict::".$name."pos[$numatts] = {\n";
	my $i=0;
	foreach (@$attsref) {
		print FH "mo".uc($_);
		if ($i++ != $numatts) { print FH ", "; }
	}
	print FH "\n};\n";

	print FH "const char *MMLmoDict::".$name."syms[$numops] = {\n";
	$i=0;
	foreach (@all) {
		if ($i != 0 && $i%3 == 0) { print FH " //".($i-3)."\n"; }
		print FH "\"$_\"";
		if (++$i != $numops) { print FH ","; }
	} 
	print FH "};\n";
	print FH "const MMLAttribute *const MMLmoDict::".$name."[$numops][$numatts] = {\n";
	$i = 0;
	foreach (@all) {
		my $op = $_;
		print FH "{";
		my $j = 0;
		foreach (@$attsref) {
			my $val = $allref->{$op}{$_};
			if (!defined($val)) {
				print FH "0";
			} else {
				my $ref = $typvals{$types{$_}}{$val};
				print FH "&$ref";
			}
			if ($j != $numatts) { print FH ", "; }
			$j++;
		}
		if ($i != $#all) { print FH "},//$i\n"; }
		$i++;
	}
	print FH "}\n};\n";
}



# functions gathering the data

sub getAtts {
	my $attsref = shift;
	my $allref = shift;

	my %atts;
	foreach (keys %$allref) {
		foreach (keys %{$allref->{$_}}) {
			$atts{$_} = 1;
		}
	}
	@$attsref = sort keys %atts;
}

# read the operators and their names from the file 'operatordictionary'
sub readOperators {
	my $preref = shift;
	my $inref = shift;
	my $postref = shift;
	open (FH, "< operatordictionary") or die;
	foreach (<FH>) {
		if (m/="prefix"/) {
			readLine($_, $preref);
		} elsif (m/="infix"/) {
			readLine($_, $inref);
		} elsif (m/="postfix"/) {
			readLine($_, $postref);
		} elsif (m/\S/) {
			print;
			die;
		}
	}
	close(FH);
}

sub readLine {
	my $line = shift;
	my $allref = shift;

	# read the operator itself which is at the start of the line and in
	# quotes
	my ($op) = $line =~ m/^"([^"]*)"/;
	# if the operator is not defined, the line must be empty (only white)
	if (!defined($op)) {
		if ($line =~ m/^\s*$/) {
			return;
		} else {
			print $line."\n";
			die;
		}
	}
	# add each attribute pair to the hash (att="value") (perl is so cool!)
	while ($line =~ m/(\w*)="(\w*)"/g) {
		if ($1 ne "form") {
			$allref->{$op}{$1} = $2;
		}
	}
}

sub getCasedType {
	my $typ = shift;
	my @cstyp = `grep -i 'class mml$typ : ' mathml.h`;
	if ($#cstyp != 0) { die; }
	my $cstyp = $cstyp[0];
	if ($cstyp =~ m/class MML(\S+) : /) {
		$cstyp = $1;
	} else {
		print "no match for $typ\n";
		die;
	}
	return $cstyp;
}

# obtain the types of the attributes from the file mathml.cpp
sub getTypes {
	my $types = shift;
	my $attribs = shift;
	
	open (FH, "< mathml.cpp") or die;
	my $open = 0;
	my $atts;
	my $typs;
	foreach (<FH>) {
		if (m/};/) {
			$open = 0;
		} elsif ($open == 1) {
			$atts .= $_;
		} elsif ($open == 3) {
			$typs .= $_;
		} elsif (m/attributeTag\[/) {
			$open = 1;
		} elsif (m/attTypes\[/) {
			$open = 3;
		}
	}
	close(FH);
	# remove all whitespace
	$atts =~ s/\s*//g;
	$typs =~ s/\s*//g;
	# split line at ',' into the separate attributes
	my @atts = split(',', $atts);
	my @typs = split(',', $typs);
	# check that the arrays are equally sized;
	my %typs;
	if ($#atts != $#typs) { die; }
	for (my $i=0; $i<=$#atts; ++$i) {
		my $att = $atts[$i];
		$att =~ s/"//g;
		my $typ = lc($typs[$i]);
		$typ =~ s/_t$//;
		$typ = getCasedType($typ);
		$typs{$att} = $typ;
	}
	for (my $i=0; $i<=$#$attribs; ++$i) {
		my $att = $attribs->[$i];
		$types->{$att} = $typs{$att};
	}
}

sub getTypVals {
	my $typvalsref = shift;
	my $typesref = shift;
	my $allref = shift;

	foreach (keys %$allref) {
		my $attref = $allref->{$_};
		foreach (keys %$attref) {
			my $att = $_;
			my $typ = $typesref->{$att};
			my $val = $attref->{$att};
			$typvalsref->{$typ}{$val} = 1;
		}
	}
	my $i = 0;
	foreach (keys %$typvalsref) {
		my $typ = $_;
		my $j = 0;
		foreach (keys %{$typvalsref->{$typ}}) {
			$typvalsref->{$typ}{$_} = "a$i\_$j";
			$j++;
		}
		$i++;
	}
}
