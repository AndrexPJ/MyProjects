
sub IntRand{
        my $n = shift;
        return (1+int(rand($n-1)))  
}


sub generateTables {
my %Clstrs = ();
my %Fat = ();
for (my $i = 0;$i<65536;$i++){
 $Fat{$i} = 0;
}

my $p = 1.0;
my ($recordsLn,$maxRecordSize,$fatTableName,$directoryTableName) = @_;
open Ffat, '>', $fatTableName or die "bad fat!\n";
open Fdir, '>', $directoryTableName or die "bad dir!\n";
binmode Ffat,Fdir;
for (my $i = 0; $i < $recordsLn ; $i++){

       for (my $j = 0; $j < 11; $j++){
           my $ch = pack 'C', (IntRand(255));
           print Fdir $ch;
        }

        for (my $j = 0; $j < 11; $j++){
           print Fdir (pack 'C',0);
        }

           print Fdir (pack 'S', IntRand(65535));
           print Fdir (pack 'S', IntRand(65535));
           
           my $firstClstr;
           do {
               $firstClstr = IntRand(65535);
           } while  ( exists $Clstrs{$firstClstr});
           $Clstrs{$firstClstr} = 1;

           print Fdir (pack 'S', $firstClstr);

           my $fClstrSize = IntRand($maxRecordSize);
           print Fdir (pack 'L',$fClstrSize);    
           my $ClstrN = $firstClstr;
           for (my $j = 0;$j < $fClstrSize-1;$j++){
                my $ClstrNnew;
                do {
                    if (rand() > $p){
                      $ClstrNnew = $ClstrN+1;
                    }
                    else{
                    $ClstrNnew = IntRand(65534);
                    }
                   } while  ( exists $Clstrs{$ClstrNnew});
                   $Clstrs{$ClstrNnew} = 1;
                $Fat{$ClstrN} = $ClstrNnew;
                $ClstrN = $ClstrNnew;
           }
           $Fat{$ClstrN} = hex 'FFFFh'; #65535
     }

for (my $i = 0;$i<65536;$i++){
    print Ffat (pack 'SS', ($i,$Fat{$i}));
}

close Ffat,Fdir;
}

generateTables(100,20,"ftable","dtable");

