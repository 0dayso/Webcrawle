<?php  //�������
include("conn.php");
$tim=date('Y-m-d H:i:s',time());
$psotip=$_SERVER["REMOTE_ADDR"];   #��ȡ�ύ��������IP
//http://xxxx.com/ftppassword.php?IP=www.baidu.com&user=1111&password=2222&root=2
//http://www.999kankan.com/cms.php?url=baidu.com&cms=33333


$sql="insert into cms(url,cms,postIP,time) VALUES('$_REQUEST[url]','$_REQUEST[cms]','$psotip','$tim')";
//print $sql;
mysql_query($sql)or die("������ݴ���!!!33333333");
print "������ݳɹ�����333";

?>


