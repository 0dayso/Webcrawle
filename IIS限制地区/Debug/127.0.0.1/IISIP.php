<?php
include("qqwry.php");  //����IP�������ݿ�
@$ip=$_GET["ip"];     //http://127.0.0.1:8888/IISIP.php?ip=127.0.0.1
$wl = convertip($ip);  //��������λ��

echo $wl; 


?>