<?php
//=================================
$conn = @mysql_connect('localhost','xiaoshu','k4e5t5') or die("�������ݿ����!!!");  //�������ݿ�
mysql_select_db('xiaoshu',$conn) or die("�����ݴ���!!!");  //������
mysql_query("set names 'GBK'"); //ʹ��GBK���ı���;

//=================================
?>
