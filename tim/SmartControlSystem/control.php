<?php
$pin = $_GET['pin'];
$state = $_GET['state'];
echo "pin:$pin, state:$state";
echo system("echo $state > /dev/ttyAMA0");
##echo system("gpio mode $pin OUTPUT");
##echo system("gpio write $pin $state");
?>
