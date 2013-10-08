<?php
$day = $_GET['day'];
$precision = $_GET['prec'];

if ($precision < '0' or $precision > 1 or $day < '0' or $day >'6') {
	die("ERRORE");
}


$connection = mysqli_connect('localhost','riscaldapi','riscaldapi','riscaldapi')
        or die("Connection refused");

    if ($precision == '0') {
	   	$query=("SELECT `temperature` FROM `schedulehourly` WHERE `timestamp` >= '". 60*15*4*24*$day. "' AND `timestamp` < '". 60*15*4*24*($day+1)."'");
	    $result=mysqli_query($connection,$query);
	    while($row = mysqli_fetch_row($result)) {
	  		print($row[0].",");
	  	}
	} elseif ($precision == '1') {
	    $query=("SELECT `temperature` FROM `scheduleprecise` WHERE `timestamp` >= '". 60*15*4*24*$day. "' AND `timestamp` < '". 60*15*4*24*($day+1)."'");
	    $result=mysqli_query($connection,$query);
	    while($row = mysqli_fetch_row($result)) {
	  		print($row[0].",");
	  	}
	}
    mysqli_close($connection);
?>
