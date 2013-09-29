<?php
$connection = mysqli_connect('localhost','riscaldapi','riscaldapi','riscaldapi')
        or die("Connection refused");
    $query = "SELECT `inside` FROM `history`";
    $result=mysqli_query($connection,$query);
    $past= array();
    while($row = mysqli_fetch_row($result)) {
  		array_push($past, $row);
  	}
  	print(json_encode($past));
    mysqli_close($connection);
?>
