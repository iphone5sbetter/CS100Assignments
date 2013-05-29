#!/software/common/bin/perl
use strict;
use warnings;

my $notOK = 0;
my $count = 0;
open my $sfh, '<', 'SIGNATURE' or die "Unable to open SIGNATURE file";
my $sig = <$sfh>;
chomp $sig;
close($sfh);

#my @files = grep {/\.(hpp|cpp)$/i} glob("*");
my @files = @ARGV;
print "Checking signatures in files:", join(",",@files),"\n";

foreach my $fp (@files){
#  printf "%s\n", $fp;
# Signature
#// Jane Doe <janedoe@ucsd.edu>, John Doe <janedoe@ucsd.edu>
  open my $fh, '<', $fp or die "Unable to open $fp: $!";
  my $firstline = <$fh>;
  chomp($firstline);
#  printf "The first line is %s\n",$firstline;
  if ($sig ne $firstline){
      printf "Firstline of %s \n\t%s\n   didn't match the signature\n", $fp, $firstline;
      $notOK++;
      }
  else{
    $count++;
  }
}

if ($notOK != 0){
    printf "%d of your headings don't match the SIGNATURE FILE\n",$notOK;
    exit 1;
    }

else{
    printf "All %d signatures matched\n",$count;
    exit 0;
}
