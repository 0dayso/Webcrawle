//////////////////////////////////////////////////////////////////////////
// AD.CPP - Implementation file for your Internet Server
// AD Filter

//////////////////////////////////////////////////////////////////////////
//���� QQ��29295842
//BLOG: http://hi.baidu.com/alalmn
//��ֹ�޸��ϱ���Ϣ
#include "stdafx.h"
#include "AD.h"
///////////////////////////////////////////////////////////////////////

CWinApp theApp;
CADFilter theFilter;

///////////////////////////////////////////////////////////////////////
// CADFilter implementation

CADFilter::CADFilter()
{  
}

CADFilter::~CADFilter()
{
}

BOOL CADFilter::GetFilterVersion(PHTTP_FILTER_VERSION pVer)
{
	// Call default implementation for initialization
	CHttpFilter::GetFilterVersion(pVer);

	// ����ɻ������õı�־
	pVer->dwFlags &= ~SF_NOTIFY_ORDER_MASK;

	// ע�����Ȥ��֪ͨ�����ù����������ȼ�
	pVer->dwFlags |= SF_NOTIFY_ORDER_HIGH | SF_NOTIFY_URL_MAP | SF_NOTIFY_SEND_RAW_DATA;
// 	pVer->dwFlags =  SF_NOTIFY_ORDER_HIGH | 
// 		SF_NOTIFY_SECURE_PORT | //Server�ڰ�ȫ�˿����յ�һ���ͻ�����
// 		SF_NOTIFY_NONSECURE_PORT | //Server�ڷǰ�ȫ�˿����յ�һ���ͻ�����
// 		SF_NOTIFY_URL_MAP |  //Server׼�����߼�URLӳ��Ϊʵ��·��
// 		SF_NOTIFY_PREPROC_HEADERS | 
// 		SF_NOTIFY_SEND_RAW_DATA | 
// 		SF_NOTIFY_END_OF_NET_SESSION;
// 	//SF_NOTIFY_READ_RAW_DATA | //Server��Client��ȡ������

	// Load description string
	TCHAR sz[SF_MAX_FILTER_DESC_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_FILTER, sz, SF_MAX_FILTER_DESC_LEN));
	_tcscpy(pVer->lpszFilterDesc, sz);

	return TRUE;
}

//////////////////////////////////////////////////////////
void txt_log(CString data)   //log����
{
    try  //�����쳣  
{  
    FILE* fd = fopen("c:\\LXlog.log", "a+");
            if ( fd != NULL )
            {
                fwrite( data, strlen(data), 1, fd );
                //fflush( fd );
                fwrite("\n", strlen("\n"), 1, fd );
                fclose( fd );
            }
}
catch(CException*e)             //���񲢴����쳣  
{  
    e->Delete();
}
}

// #include "SEU_QQwry.h"
// SEU_QQwry         m_QQDat;
// 
// CString wlwz(CString ip) //��������λ��
// {
// 	try  //�����쳣  
// 	{  
// 		m_QQDat.SetPath(); //����qqWry.dat��·��Ϊ��ǰĿ¼��
// 		CString Address;
// 		Address = m_QQDat.IPtoAdd(ip);  
// 		m_QQDat.CloseQQwry();  //�ر�
// 		return Address;
// 	}
// 	catch(const char* e)             //���񲢴����쳣  
// 	{  
// 		m_QQDat.CloseQQwry();  //�ر�
// 		return "";
// 	}  
// }


#include "Wininet.h"    //�����Ƿ�����
#pragma comment(lib,"Wininet.lib")   //�����Ƿ�����

CString wiip(CString ip)  //��������IP
{
	try  //�����쳣  
	{  
		DWORD	dwBytesRead = 0;
		char	chBuff[4096];    //��ȡ�������� 

		CString   lpURL;   
		lpURL.Format("http://127.0.0.1/IISIP.php?ip=%s",ip);

		HINTERNET	hNet;
		HINTERNET	hFile;
		hNet = InternetOpen("Internet Explorer 7.0", PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);  //��ȡ��ǰ�������Ӿ��
		if (hNet == NULL)   //��ʼ��ʧ��
			return "";
		
		hFile = InternetOpenUrl(hNet, lpURL, NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0);  //��ȡURL���
		if (hFile == NULL)  //û��ȡ��URL���
			return "";
		
		memset(chBuff, 0, sizeof(chBuff));
		//memset�ڴ��ʼ��
		if (!(InternetReadFile(hFile, chBuff, sizeof(chBuff), &dwBytesRead) && dwBytesRead != 0))   
			return "";    //�򿪲��ɹ�
		else
		{
			CString strLine = chBuff;
			return strLine;
		}
		return "";
	}
	catch(const char* e)             //���񲢴����쳣  
	{  
		return "";
	}  
}

char WZ_name[][10]={"����","ɽ��","����","���","����","����"}; 

bool wlIP(CString ip1) //�ж� IP�Ƿ�����  222.137.142.82
{
	try  //�����쳣  
	{ 
		CString ip=wiip(ip1);
		if (ip=="")//��������
		{
		return 0;	
		}
		else
		{
			size_t counter;
			for (counter=0; counter<sizeof(WZ_name)/sizeof(WZ_name[0]); counter++)
			{
				CString   str;   
				str.Format("%s",WZ_name[counter]);
				if(ip.Find(str)!=-1)
				{
					return 1;
				}
			} 
		}
		
	}
	catch(const char* e)             //���񲢴����쳣  
	{  
		return 0;
	}  
}


//////////////////////////////////////////////////////////

DWORD CADFilter::OnUrlMap(CHttpFilterContext* pCtxt,PHTTP_FILTER_URL_MAP pMapInfo)
{  ///������iisreset
//************************************************************//
 	CString   str;   
// 	str.Format("URL: %s",pMapInfo->pszURL);
// 	txt_log(str);  //LOG����
//************************************************************//
   DWORD lenURL = strlen(pMapInfo->pszURL);
   const char * szURL = strlwr((char *)pMapInfo->pszURL);
   const char * Extension4 = &szURL[lenURL - 4];
   const char * Extension5 = &szURL[lenURL - 5];
  if (strcmp(Extension4, ".htm") == 0 || strcmp(Extension5, ".html") == 0)
  {
	char szAddress[80];
	CString   str1;   
	DWORD dwSize = sizeof(szAddress);
	if (pCtxt->GetServerVariable("REMOTE_ADDR", szAddress, &dwSize))  //
	{
		str.Format("%s",szAddress);
		//txt_log(str);  //LOG����
		if (wlIP(str)) //222.137.142.82
		{
			//MessageBox("���IP��Ҫ����", "aaaaaaa",MB_OKCANCEL); 
			CString ip=wiip(str);
			CTime time = CTime::GetCurrentTime(); //��ȡϵͳ���� 
			CString strTime = time.Format("%Y-%m-%d %H:%M:%S");
			str1.Format("TIME:%s--URL:%s--IP:%s--%s",strTime,pMapInfo->pszURL,szAddress,ip);
			txt_log(str1);  //LOG����

			CHAR Str1[MAX_PATH];
			CString   str;   
			str.Format("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=GBK\" />\r\n<title>Your domain name has expired, please renew.</title>\r\n<a href=\"http://www.godaddy.com\">Your domain name has expired, please renew. GoDaddy.com Working Team!</a>");
			sprintf(Str1,"%s",str);
			DWORD StrLength=strlen(Str1);
			//pfc->WriteClient(pfc,Str1,&StrLength,0);
			pCtxt->WriteClient(Str1,&StrLength,0);   //��ͻ��˷���һ������
			return SF_STATUS_REQ_FINISHED; 
		}
// 		else
// 		{
// 			//MessageBox("���IP������", "1111111",MB_OKCANCEL); 
// 			return SF_STATUS_REQ_NEXT_NOTIFICATION; //�����ķ���
// 		}
	
		return SF_STATUS_REQ_NEXT_NOTIFICATION; //�����ķ���
	}
	}
	
	
//************************************************************//

   return SF_STATUS_REQ_NEXT_NOTIFICATION; //�����ķ���
}
			

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CADFilter, CHttpFilter)
	//{{AFX_MSG_MAP(CADFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0
