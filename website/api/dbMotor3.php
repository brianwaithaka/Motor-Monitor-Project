<?php
class motor3{
 public $link='';
 function __construct($Temperature, $Vibration){
  $this->connect();
  $this->storeInDB($Temperature, $Vibration);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','everly1') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'motormr') or die('Cannot select the DB');
 }
 
 function storeInDB($Temperature, $Vibration){
  $query = "insert into motor3 set Temperature='".$Temperature."', Vibration='".$Vibration."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
}

if($_GET['Temperature'] != '' and  $_GET['Vibration'] != ''){
 $motor3=new motor3($_GET['Temperature'],$_GET['Vibration']);
}


?>
