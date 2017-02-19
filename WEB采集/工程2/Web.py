# -*- coding: cp936 -*-
import threading
import GetUrl
import urllib

g_mutex = threading.Lock()
g_pages = []      #�߳�����ҳ��󣬽�ҳ��������ӵ����list��
g_dledUrl = []    #�������ع���url
g_toDlUrl = []    #��ǰҪ���ص�url
g_failedUrl = []  #����ʧ�ܵ�url
g_totalcount = 0  #���ع���ҳ����

class web_url:  #ָ��ʶ��
    def __init__(self,url,th,max): #url   �߳�   ���
        self.url=url  #url
        self.th=th  #�߳�
        self.max=max  #���
        #self.logfile = file('#log.txt','a+')

    def open_file(self,data):
        try:
            file_object = open('log.txt','a+')
            file_object.writelines(data)
            file_object.writelines("\n")
            file_object.close()
        except Exception,e:
            print e
            pass

    def run1(self):
        try:
            g_toDlUrl.append(self.url)  #��ǰҪ���ص�url
            self.open_file('>>>open:\n')
            self.open_file(self.url)
            depth = 0
            while len(g_toDlUrl) != 0 and depth <= self.max:
            #��ǰҪ���ص�url                    #���
                depth += 1
                print u'������� ',depth,'...\n\n'
                self.downloadAll()
                self.updateToDl()
                content = '\n>>>Depth ' + str(depth)+':\n'
                print content
                i = 0
                while i < len(g_toDlUrl):  #��ǰҪ���ص�url
                    content = str(g_totalcount + i + 1) + '->' + g_toDlUrl[i] + '\n'  #���ع���ҳ����
                    print content
                    #self.open_file(content)                  #��ǰҪ���ص�url
                    i += 1
        except Exception,e:
            print e
            return 0

    def download(self,url):
        Cth = CrawlerThread(url)
        self.threadPool.append(Cth)
        Cth.start()

    def downloadAll(self):
        global g_toDlUrl  #��ǰҪ���ص�url
        global g_totalcount  #���ع���ҳ����
        i = 0
        while i < len(g_toDlUrl):  #��ǰҪ���ص�url
            j = 0
            while j < self.th and i + j < len(g_toDlUrl):  #��ǰҪ���ص�url
            #  �߳�
                g_totalcount += 1    #����ѭ��������ҳ������1  #���ع���ҳ����
                self.download(g_toDlUrl[i+j])
                print u'�߳̿�ʼ:',i+j,u'--�ļ���=',g_totalcount
                j += 1
            i += j
            for th in self.threadPool:
                th.join(30)     #�ȴ��߳̽�����30�볬ʱ
            self.threadPool = []    #����̳߳�
        g_toDlUrl = []    #����б�

    def updateToDl(self):
        global g_toDlUrl  #��ǰҪ���ص�url
        global g_dledUrl  #�������ع���url
        newUrlList = []
        for s in g_pages:  #�߳�����ҳ��
            newUrlList += GetUrl.GetUrl(s)   #GetUrlҪ����ʵ��
        g_toDlUrl = list(set(newUrlList) - set(g_dledUrl))    #��ʾunhashable
                                            #�������ع���url






class CrawlerThread(threading.Thread):
    def __init__(self, url):
        threading.Thread.__init__(self)
        self.url = url    #���߳����ص�url

    def run(self):    #�̹߳���-->����htmlҳ��
        global g_mutex
        global g_failedUrl
        global g_dledUrl  #�������ع���url
        try:
            f = urllib.urlopen(self.url)
            s = f.read()
        except:
            g_mutex.acquire()    #�߳���-->����
            g_dledUrl.append(self.url)  #�������ع���url
            g_failedUrl.append(self.url)
            g_mutex.release()    #�߳���-->�ͷ�
            print 'Failed downloading and saving',self.url
            return None    #���ŷ���!

        g_mutex.acquire()    #�߳���-->����
        g_pages.append(s)  #�߳�����ҳ��
        g_dledUrl.append(self.url)  #�������ع���url
        g_mutex.release()    #�߳���-->�ͷ�