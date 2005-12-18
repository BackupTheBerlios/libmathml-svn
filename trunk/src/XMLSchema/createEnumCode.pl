#! /usr/bin/perl -w
use strict;

# read the enum values
my @list = `xsltproc enums.xsl mathml2/mathml2.xsd`;

my %enums;

# parse the input file
foreach (@list) {
	chomp;
	my ($name, $value) = split('\t');
	if (!defined $enums{$name}) {
		$enums{$name} = [];
	}
	my @ref = @{$enums{$name}};
	push @ref, $value;
	$enums{$name} = \@ref;
}

# print header
open (FH, "> mathenums.h");

print FH "#ifndef MATHENUMS_H\n";
print FH "#define MATHENUMS_H\n\n";

foreach (keys %enums) {
	my $name = $_;
	my $ref = $enums{$_};
	my $size = @$ref;
	print FH "namespace $name {\n";
	print FH "\tenum ".ucfirst($name)." {\n\t\t";
	my $first = 1;
	foreach (@$ref) {
		if ($first) {
			$first = 0;
		} else {
			print FH ",\n\t\t";
		}
		$_ =~ s/-/_/g;
		$_ =~ s/\W//g;
		print FH uc($_);
	}
	print FH "\n\t};\n}\n";
	print FH "extern const char *${name}names[$size];\n";
}
print FH "\n#endif\n";
close(FH);

open (FH, "> mathenums.cpp");
print FH "#include \"mathenums.h\"\n\n";

foreach (keys %enums) {
	my $name = $_;
	my $ref = $enums{$_};
	my $size = @$ref;
	print FH "const char *${name}names[$size] = {";
	my $first = 1;
	foreach (@$ref) {
		if ($first) {
			$first = 0;
		} else {
			print FH ", ";
		}
		print FH "\"$_\"";
	}
	print FH "};\n";
}
close(FH);
