# -*- coding: cp936 -*-
#import GetUrl
#print GetUrl.GetUrl("http://www.bbs020.net/thread-140044-1-1.html")   #GetUrlҪ����ʵ��

data="http://connect.php?mod=login&op=init&referer=http://www.bbs020.net/&statfrom=login"
#if "http://" in data:
#    print "1111111"
http=data[0:7]  #��ȡhttp
print http
if http=="http://":
    print "1111111"


