use XML::Simple;
use LWP::UserAgent;
use Tk;
use Tk::JPEG;
use Switch;
use utf8;

my $id = 3034;
if(@ARGV)
{
   $id = $ARGV[0];
}
my $browser = LWP::UserAgent->new;
my $url = 'http://rp5.ru/xml/'.$id.'/00000/ru';
my $response = $browser->get($url) or die "can`t get url";
my $xml =  $response->decoded_content;
my $ref = XMLin($xml);
my $info1 = $ref->{'point'};


my $pw = 140;
my $ph = 110;

my $px = 0;
my $py = 10;

my $xi = 0;
my $yi = 0;

my $mw = MainWindow->new(-title => "Погодка",-background => "white");
my $image = $mw->Photo('-format' => 'jpeg', -file => 'weather.jpg');

my $cityInfo = "Город: ".$info1->{'point_name'};
my $city = $mw->Label(-textvariable => \$cityInfo,-background => "white",-font => "Courier 20 bold")->pack(-fill =>'x');
for(my $i = 0;$i<4;$i++)
{
my $info2 = $info1->{'timestep'}[$i];
#########################
my $dataInfo = $info2 ->{'datetime'};
my $pressureInfo = "Давление: ".$info2->{'pressure'}." мм.р.ст.";
my $temperatureInfo = "Темература: ".$info2->{'temperature'}." °C";
my $wind_directionInfo = "Направление ветра: ".$info2->{'wind_direction'};
my $wind_velocityInfo = "Скорость ветра: ".$info2->{'wind_velocity'}." м/с";
########################

########################
my $typeFalls = $info2 -> {'falls'};
my $cloud_cover = $info2 -> {'cloud_cover'};
my $temperature_1 = $info2->{'temperature'};

switch($typeFalls) {
   case 0 {
      if($cloud_cover < 30){
         $xi = 0;
         $yi = 0;      
      }
      else  {
         if($cloud_cover < 60){
            if($temperature_1 > 10){
               $xi = 0;
               $yi = 1; 
            }
            else {
               $xi = 2;
               $yi = 0; 
            } 
         }
        else{
            if($temperature_1 > 10){
               $xi = 0;
               $yi = 2; 
            }
            else {
               $xi = 2;
               $yi = 0; 
            } 
        }
      }
   }
   case 1 {
    if($cloud_cover < 30){
         $xi = 1;
         $yi = 2;      
      }
   else  {
      $xi = 1;
      $yi = 1;  
   }
   }
   case [2,3] {
       if($temperature_1 > 10){
               $xi = 2;
               $yi = 2; 
            }
            else {
               $xi = 2;
               $yi = 3; 
            } 
   }
}
#########################



my $mf = $mw->Frame(-background => "white",-border=>1)->pack(-side => "left");

my $weatherImg = $mw->Photo();
   $weatherImg->copy($image,-from => $xi*$pw+$px,$yi*$ph+$py,$xi*$pw+$px+$pw,$yi*$ph+$py+$ph);
my $data = $mf->Label(-textvariable => \$dataInfo ,-background => "white")->pack(-fill =>'x');
my $img = $mf->Label(-image => $weatherImg ,-background => "white")->pack(-fill =>'x');
my $pressure = $mf->Label(-textvariable => \$pressureInfo,-background => "white")->pack(-fill =>'x');
my $temperature = $mf->Label(-textvariable => \$temperatureInfo,-background => "white")->pack(-fill =>'x');
my $wind_direction = $mf->Label(-textvariable => \$wind_directionInfo,-background => "white")->pack(-fill =>'x');
my $wind_velocity = $mf->Label(-textvariable => \$wind_velocityInfo,-background => "white")->pack(-fill =>'x');

}

MainLoop;

