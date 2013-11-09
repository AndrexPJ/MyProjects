sub findWindow{
    my ($Ft,$wndSize,$max) = @_;
    my %Fat = %$Ft;
    my $i = 0;
    my $ch = 0;
    while ($i + $wndSize < $max) {
    for(my $j = $i;$j < $i + $wndSize;$j++)
        {
         if( $Fat{$j} != 0 ) {
                $i = $j + 1;
                $ch = 1;
                
                }
        }
    if($ch == 1)
      {
        $ch = 0;
        }
    else
       {
        return $i;
        }
    }
    return (-1);
}

sub checkFragmintation{
my ($Ft,$n) = @_;
my %Fat = %$Ft;
my $fragm = 0;
my $size = 0;
my $oldn = $n;
do {
    $n = $Fat{$oldn};
    if($n != $oldn + 1 && $n != hex 'FFFFh') {
        $fragm++;
    }
    $size++;
    $oldn = $n;
    }
while ($n != hex 'FFFFh');
return ($fragm/$size);
}

sub copy{
    my ($old,$new) = @_;
    print $old," has copied to ",$new,"\n";
    return 0;
}

sub defrag{
        my ($fatName,$dirName) = @_;
        my %Fat = ();
        my %newFat = ();
        
        $fatSize = -s "$fatName";
        $dirSize = -s "$dirName";
        open Ffat, '<', $fatName or die "bad fat!\n";
        open FfatNew, '>', $fatName."New" or die "bad fat!\n";
        open Fdir, '<', $dirName or die "bad dir!\n";
        open FdirNew, '>', $dirName."New" or die "bad dir!\n";  
        binmode Ffat,Fdir;
        binmode FdirNew,FfatNew;
        
        for (1..$fatSize/4){
                read Ffat,$data,4;
                ($k,$v) = unpack 'SS' ,$data;                
                $Fat{$k} = $v;
        }

        for (1..$dirSize/32){
               ####################
               read Fdir,$inf,26;
               print FdirNew $inf;
               ####################
               
               read Fdir,$firstClstrp,2;
               my $n = unpack 'S',$firstClstrp;
               
               
               my $sizeP,$sizeCls;
               read Fdir,$sizeP,4;
               $sizeCls = unpack 'L',$sizeP;
               my $fragm = checkFragmintation(\%Fat,$n);
               print "file ",$n," cluster fragmintation : ",$fragm*100," %\n";
               if($fragm < 0.02){
                print FdirNew (pack 'S',$n);
                print FdirNew $sizeP;
                next;
               }
         
               my $pos = findWindow (\%Fat,$sizeCls,65535);
               print FdirNew (pack 'S',$pos);
               print FdirNew $sizeP;

               my $it = 0;
               do {
                 my $nold = $n;
                 $n = $Fat{$n};
                 $Fat{$nold} = 0;
                 # copy clstr $n to clstr $pos+$it
                 $Fat{$pos+$it} = $pos+$it+1;
                 copy ($nold,$pos+$it);
                 $it++;
               } while ($n != hex 'FFFFh');
                 $Fat{$nold} = 0;
                 $Fat{$pos+$it} = hex 'FFFFh';

               
         }
        for (my $i = 0;$i<65536;$i++){
        print FfatNew (pack 'SS', ($i,$Fat{$i}));
        }
        close Ffat,Fdir,FfatNew,FdirNew;
}


defrag("ftable","dtable");
