use IO::Socket;
use Storable     qw( thaw );
$socket = new IO::Socket::INET (
    PeerAddr  => '127.0.0.1',
    PeerPort  =>  5000,
    Proto => 'tcp',
)
or die "Couldn't connect to Server\n";
my $line;
my ($dur,$freq);
my $exit_st = 0;
while (1) {
        $socket->recv($line,1024);
        my $ref = thaw($line);        
        while (($dur,$freq) = each %$ref){
        myBeep($dur,$freq);
        if($dur == "qq" && $freq == "qq") {print ("exit..","\n");$exit_st = 1;last;}           
        }
        if($exit_st == 1) {last;}
         
}


sub myBeep{
my  ($dur,$fq) = @_;
print "DUR: ",$dur," FREQ: ",$fq,"\n";
}


