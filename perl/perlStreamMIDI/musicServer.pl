#!/usr/bin/perl
use MIDI;
use Time::HiRes qw(usleep nanosleep);
use IO::Socket;
use Storable     qw( nfreeze );
$SIG{INT} = \&interrupt;






die "No filename" unless @ARGV;
die "$ARGV[0] doesn't exist" unless -e $ARGV[0];
$opus = MIDI::Opus->new({'from_file' => $ARGV[0]});

my @tracks = $opus -> tracks;

my ($score_r, $end_time) = MIDI::Score::events_r_to_score_r($tracks[0]->events_r);


my $Ticks = $opus->ticks;
my @Score =  @$score_r;
my $score_ln = $#Score+1;


#('note', starttime, duration, channel, note, velocity)

my %music = ();
my $coef = 12;
my %sockets = (); 
my $min_ch = 0;
my $max_ch = 4;
my $active_s = $max_ch - $min_ch + 1;
my $sockets_N = $min_ch;
my $sockets_ln = 0;
print "MIDI preproccesing...","\n";
for(my $i = 0;$i<$score_ln;$i++){
        if($Score[$i][0] == 'note'){
           #$hash{channel}{starttime} = {duration=>note};
           #if( exists $music{$Score[$i][3]}{$Score[$i][1]}){
           #   
           #}
           my $note = int(27.5*(2**(($Score[$i][4] - 33 + $coef)/12)));
           $music{$Score[$i][3]}{$Score[$i][1]} = {$Score[$i][2] => $note};
        }
}
print "Complete!","\n";
print "Waiting for ",$active_s," connection(s)...","\n";

######################################################
$socket = new IO::Socket::INET (
    LocalHost => '127.0.0.1',
    LocalPort => '5000',
    Proto => 'tcp',
    Listen => $active_s,
    Reuse => 1
);
die "Coudn't open socket" unless $socket;


######################################################


while($sockets_ln < $active_s){
        my $client_socket = "";
        $client_socket = $socket->accept();
        $sockets{$sockets_N} = $client_socket;
        $sockets_ln++;
        $sockets_N++;
        print "Waiting for ",$active_s-$sockets_ln," connection(s)...","\n";
}


sub interrupt {
    print STDERR "Caught a control c!\n";
     my %h = {"qq" => "qq"}; 
     my $line = nfreeze(\%h)."\n";
     for(my $i = 0;$i < 16;$i++){
       if(exists $sockets{$i}){
         ($sockets{$i})->send($line);
       }  
    }
    exit;
}

playMusic(\%music,\%sockets);

###########play from musicHash to sockets#############
sub playMusic{
        my ($m,$s) = @_;
        my %music = %$m;
        my %sockets = %$s;

        my $time = 0;
        my $channels = 16;
        my $count = 0;
         
        while ($time <= $end_time){
                for(my $i = 0;$i < $channels;$i++){
                    if(exists $music{$i}{$time}){
                      my $h = $music{$i}{$time};
                      my $line = nfreeze(\%$h)."\n";
                      if( exists $sockets{$i}){
                      ($sockets{$i})->send($line);
                      }
                      print "Sending packet to ",$i," channel\n";
                      $count++;
                    }
                }
        $time++;
        usleep(1000);
        }
 my %h = {"qq" => "qq"}; 
 my $line = nfreeze(\%h)."\n";
 for(my $i = 0;$i < $channels;$i++){
       if(exists $sockets{$i}){
         ($sockets{$i})->send($line);
       }  
    }
}
######################################################
