use Tk;

my $clstrs = 65535;

sub randColor{
  for ($x = 0; $x < 3; $x++) {
    $rand = rand(255);
    $hex[$x] = sprintf ("%x", $rand);
    if ($rand < 9) {
      $hex[$x] = "0" . $hex[$x];
    }
    if ($rand > 9 && $rand < 16) {
      $hex[$x] = "0" . $hex[$x];
    }
  }
  return"\#" . $hex[0] . $hex[1] . $hex[2];

}

sub viewTables{
        my ($fatName,$dirName) = @_;
        my %Fat = ();
        my $fragmentation = 0;
        my $clstCount = 0;
        $fatSize = -s "$fatName";
        $dirSize = -s "$dirName";
        open Ffat, '<', $fatName or die "bad fat!\n";
        open Fdir, '<', $dirName or die "bad dir!\n";  
        binmode Ffat,Fdir;
        my ($heigth,$width) = (500,500);
        
        my $mw = MainWindow->new(-title => "Fragmentation ".$fatName,-background => "white");
        my $cnv = $mw -> Canvas(-height => $heigth, -width => $width,-background => "white")->pack;


        my $dx = 0;
        my $size = 1/$clstrs;
        my $k,$v,$data;

        my $controlSum = 0;
        for (1..$fatSize/4){
                read Ffat,$data,4;
                ($k,$v) = unpack 'SS' ,$data;
                $Fat{$k} = $v;
                $controlSum++;

        }
        
        print "controlsum : ",$controlSum,"\n";
        my $colorsSize = $dirSize/32;
        my $dy = $heigth/$colorsSize;
        my $y = 0;
        for    (1..$colorsSize){
               read Fdir,$_,26; 
               read Fdir,$firstClstrp,2;
               my $n = unpack 'S',$firstClstrp;
               my $nold = $n;
               $color = randColor();
               do {
                 $cnv -> createRectangle ($width*$size*$n,$y,$width*$size*($n)+$dy,$y+$dy, -fill => $color);
                 $n = $Fat{$n};
                 if ($nold != $n - 1 && $n != 65535) {
                       $fragmentation++;
                  }
                 $clstCount++;
                 $nold = $n;
               } while ($n != hex 'FFFFh' && $nold != hex 'FFFFh');
               read Fdir,$_,4;
               $y += $dy;
         }
        close Ffat,Fdir;
        print "fragmentation : ",($fragmentation/$clstCount)*100," %\n";
        MainLoop;
}

sub main {
        my ($fatName,$dirName) = @ARGV;
        viewTables($fatName,$dirName);
}
main();
