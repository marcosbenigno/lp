package lingProgTrabalho;

use 5.024001;
use strict;
use warnings;
use Carp;

require Exporter;
#use AutoLoader;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use lingProgTrabalho ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
	
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );





our @EXPORT = qw( tagsHtml5 numeroKeywords scriptCss numeroTags audioVideo transformaDocEmString
	
);

our $VERSION = '0.01';

#FUNCOES


sub tagsHtml5 { 
	my @arrayArquivo = @_;
	my @arrayTags = ("<nav", "<article", "<header", "<footer", "<section", "<aside", "<mark", "<time", "<video", "<audio");
	for(my $j = 0; $j<=$#_;$j=$j+1){
		for (my $i = 0; $i <= $#arrayTags; $i = $i + 1){
			if ($_[$j] =~ /$arrayTags[$i]/i){
				return 1;
			}
		}
	}
	return -1;
}
sub numeroKeywords { 
	my @arrayArquivo = @_;
	my @arrayMetaKeywords;
	for(my $j = 0; $j<=$#_;$j=$j+1){
		if ($_[$j] =~ /<meta +((name=(["'])?keywords(["'])? +content=(["'])?(\w(,| , |, )?)+(["'])?)|(content=(["'])?(\w(,| , |, )?)+(["'])? +name=(["'])?keywords(["'])? +))/i){
			@arrayMetaKeywords = split /,/, $_[$j];
			return $#arrayMetaKeywords+1;
		}
	}
	return -1;
}
sub scriptCss { 
	my @arrayArquivo = @_;
	my $result = -1;
	for(my $j = 0; $j<=$#_;$j=$j+1){
		if ($_[$j] =~ /<style/){
			$result = 1;		
		} elsif ($_[$j] =~ /<link +(((type=(["'])?text\/css(["'])?)?( +)?(href=(["'])?.*(["'])?)?)?|((href=(["'])?.*(["'])?)?( +)?(type=(["'])?text\/css(["'])?)?)?)?( +)?rel=(["'])?stylesheet(["'])?/i){
			if ($_[$j] =~ /\.css/i){
				$result = 1;
			}
		} 
		if ($_[$j] =~ /<script/){
			if ($result == 1){
				$result = 2;
			} elsif ($result == -1){
				$result = 1;
			}
		}
	}
	return $result;
}
sub numeroTags { 
	my @arrayArquivo = @_;
	my @tagsDistintas = (transformaDocEmString(@arrayArquivo) =~ /<[A-Za-z0-9]*\b/ig);
	my @tagsResultado;
	foreach my $x (@tagsDistintas){
		next unless defined $x;
		push @tagsResultado, $x if !grep{/^$x/}@tagsResultado;
	}
	return $#tagsResultado + 1;
}
sub audioVideo{
	my @arrayArquivo = @_;
	my @tagsResultadoVideo;
	my @tagsResultadoAudio;
	my $resultAudio = 0;
	my $resultVideo = 0;
	my @arrayExtensoesVideo;
	my @arrayExtensoesAudio;
	@arrayExtensoesAudio = (transformaDocEmString(@arrayArquivo) =~ /type="audio\/[A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9]?[A-Za-z0-9]?[A-Za-z0-9]?/ig);
	foreach my $x (@arrayExtensoesAudio){
		next unless defined $x;
		push @tagsResultadoAudio, $x if !grep{/^$x$/}@tagsResultadoAudio;
		}
	if($#tagsResultadoAudio == 0){
		$resultAudio = -1;
	}elsif ($#tagsResultadoAudio > 0){
		$resultAudio = $#tagsResultadoAudio+1;
	}
	@arrayExtensoesVideo = (transformaDocEmString(@arrayArquivo) =~ /type="video\/[A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9]?[A-Za-z0-9]?[A-Za-z0-9]?/ig);
	foreach my $x (@arrayExtensoesVideo){
		next unless defined $x;
		push @tagsResultadoVideo, $x if !grep{/^$x$/}@tagsResultadoVideo;
		}
	if($#tagsResultadoVideo == 0){
		$resultVideo = -1;
	}elsif ($#tagsResultadoVideo > 0){
		$resultVideo = $#tagsResultadoVideo+1;
	}
	return $resultVideo, $resultAudio;
}
sub transformaDocEmString{
	my $arrayArquivo = @_;
	our $docComoString = "";
	for(my $j = 0; $j<=$#_;$j=$j+1){
		$docComoString = $docComoString . "" . $_[$j];
	}
	return $docComoString;
}

sub AUTOLOAD {
    # This AUTOLOAD is used to 'autoload' constants from the constant()
    # XS function.

    my $constname;
    our $AUTOLOAD;
    ($constname = $AUTOLOAD) =~ s/.*:://;
    croak "&lingProgTrabalho::constant not defined" if $constname eq 'constant';
    my ($error, $val) = constant($constname);
    if ($error) { croak $error; }
    {
	no strict 'refs';
	# Fixed between 5.005_53 and 5.005_61
#XXX	if ($] >= 5.00561) {
#XXX	    *$AUTOLOAD = sub () { $val };
#XXX	}
#XXX	else {
	    *$AUTOLOAD = sub { $val };
#XXX	}
    }
    goto &$AUTOLOAD;
}

require XSLoader;
XSLoader::load('lingProgTrabalho', $VERSION);

# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__
# Below is stub documentation for your module. You'd better edit it!

=head1 NAME

lingProgTrabalho - Perl extension for blah blah blah

=head1 SYNOPSIS

  use lingProgTrabalho;
  blah blah blah

=head1 DESCRIPTION

Stub documentation for lingProgTrabalho, created by h2xs. It looks like the
author of the extension was negligent enough to leave the stub
unedited.

Blah blah blah.

=head2 EXPORT

None by default.



=head1 SEE ALSO

Mention other useful documentation such as the documentation of
related modules or operating system documentation (such as man pages
in UNIX), or any relevant external documentation such as RFCs or
standards.

If you have a mailing list set up for your module, mention it here.

If you have a web site set up for your module, mention it here.

=head1 AUTHOR

osboxes.org, E<lt>osboxes@E<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2017 by osboxes.org

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.24.1 or,
at your option, any later version of Perl 5 you may have available.


=cut
