<?php
$day = $_GET['day'];
$connection = mysqli_connect('localhost','riscaldapi','riscaldapi','riscaldapi')
        or die("Connection refused");
    $query=("SELECT `temperature` FROM `schedule` WHERE `timestamp` >= '". 60*15*4*24*$day. "' AND `timestamp` < '". 60*15*4*24*($day+1)."'");
    $result=mysqli_query($connection,$query);
    while($row = mysqli_fetch_row($result)) {
  		print($row[0].",");
  	}
    mysqli_close($connection);
?>