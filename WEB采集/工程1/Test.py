# -*- coding: cp936 -*-  
import WebCrawler
#http://blog.csdn.net/fbd2011/article/details/7208194
url ='http://www.bbs020.net'  #�������url(��-->http://www.baidu.com): \n
thNumber = int(5)    #֮ǰ����δת����bug  �����߳���:
Maxdepth = int(5)  #���������ȣ�
  
wc = WebCrawler.WebCrawler(thNumber, Maxdepth)  
wc.Craw(url) 