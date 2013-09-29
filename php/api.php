<?php
$connection = mysqli_connect('localhost','riscaldapi','riscaldapi','riscaldapi')
        or die("Connection refused");
    $query = "SELECT UNIX_TIMESTAMP(`timestamp`) FROM `history`";
    $result=mysqli_query($connection,$query);
    while($row = mysqli_fetch_row($result)) {
  		print($row[0] . "<br>");
	}
    mysqli_close($connection);
?>
