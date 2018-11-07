#include "stdafx.h"
#include "data_scrambler.h"
#include "data_list_dlg.h"
//#import <mshtml.tlb>
#include <mshtml.h>
#include <comutil.h>
#include <comdef.h>
#include <comdefsp.h>
#include "mshtml_addition.h"
#include <comutil.h>

/**************************************************************
������ͼ�����Ч�ԣ����ܻ�ȡ��һЩ��Ҫ�Բ����ͼƬ��
**************************************************************/

voidDisplayImage(HDC hDC, CString fileName)  
02.   {  
	03.          CString fileExt; //ͼƬ����չ��  
	04.          int len = fileName.GetLength();  
	05.          for(int i=len-1; i>=0; i--) //�õ�ͼƬ����չ��  
		06.          {  
			07.                  if(fileName[ i ] == '.')  
				08.                  {  
					09.                          fileExt=fileName.Mid(i+1);  
					10.                          break;  
					11.                  }  
			12.          }  
	13.          fileExt.MakeLower(); //����չ��תΪСд  
	14.          if(fileExt != _T(""))  
		15.          {  
			16.                  //����CxImage�������о�̬����CxImage::GetTypeIdFromName����������չ�����ͼƬ��ʽ��ID����  
				17.                  CxImage image(fileName,CxImage::GetTypeIdFromName(fileExt));  
			18.                  if(image.IsValid())  
				19.                  {  
					20.                          image.Draw(hDC);  
					21.                          image.Destroy();  
					22.                  }  
			23.          }  
	24.   }  


void DisplayImage(HDC hDC, LPCTSTR szImagePath)  
02.   {  
	03.          HANDLE hFile=CreateFile(szImagePath, GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//��ָ����·��szImagePath�ж�ȡ�ļ����  
	04.          DWORD dwFileSize=GetFileSize(hFile, NULL);//���ͼƬ�ļ��Ĵ�С����������ȫ���ڴ�  
	05.          HGLOBAL hImageMemory=GlobalAlloc(GMEM_MOVEABLE, dwFileSize);//��ͼƬ����ȫ���ڴ�  
	06.          void *pImageMemory=GlobalLock(hImageMemory); //�����ڴ�  
	07.          DWORD dwReadedSize; //����ʵ�ʶ�ȡ���ļ���С  
	08.          ReadFile(hFile, pImageMemory, dwFileSize,&dwReadedSize, NULL); //��ȡͼƬ��ȫ���ڴ浱��  
	09.          GlobalUnlock(hImageMemory); //�����ڴ�  
	10.          CloseHandle(hFile); //�ر��ļ����  
	11.     
		12.          IStream *pIStream;//����һ��IStream�ӿ�ָ�룬��������ͼƬ��  
	13.          IPicture *pIPicture;//����һ��IPicture�ӿ�ָ�룬��ʾͼƬ����  
	14.          CreateStreamOnHGlobal(hImageMemory, false,&pIStream) //��ȫ���ڴ��ʹ��IStream�ӿ�ָ��  
		15.          OleLoadPicture(pIStream, 0, false, IID_IPicture,(LPVOID*)&(pIPicture));//��OleLoadPicture���IPicture�ӿ�ָ��  
	16.     
		17.          //�õ�IPicture COM�ӿڶ������Ϳ��Խ��л��ͼƬ��Ϣ����ʾͼƬ�Ȳ���  
		18.          OLE_XSIZE_HIMETRIC hmWidth;  
	19.          OLE_YSIZE_HIMETRIC hmHeight;  
	20.          pIPicture->get_Width(&hmWidth);//�ýӿڷ������ͼƬ�Ŀ�͸�  
	21.          pIPicture->get_Height(&hmHeight);  
	22.          pIPicture->Render(hDC,0,0,100,100,0,hmHeight,hmWidth,-hmHeight,NULL);//��ָ����DC�ϻ��ͼƬ  
	23.     
		24.          GlobalFree(hImageMemory); //�ͷ�ȫ���ڴ�  
	25.          pIStream->Release(); //�ͷ�pIStream  
	26.          pIPicture->Release(); //�ͷ�pIPicture  
	27.   }  
