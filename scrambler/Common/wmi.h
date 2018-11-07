#pragma once
#include <atlbase.h>
#include <atlstr.h>
#include <WbemIdl.h>
#include <map>
#include <comutil.h>
#pragma comment(lib,"WbemUuid.lib")

using namespace std;
BOOL GetFirstHardDiskSerialNumber(__inout char* pvSerialNumber,__in ULONG ulBufferLen);
BOOL GetWmiObjectJson(_bstr_t bstrWmiObject,_bstr_t& bstrJson);
class CWmiInfo
{
public:
	CWmiInfo(void);
	~CWmiInfo(void);

public:
	HRESULT InitWmi();    //��ʼ��WMI
	HRESULT ReleaseWmi(); //�ͷ�

    BOOL GetWMIQueryResult(CString strSQL,map<CStringA, CSimpleArray<CStringA>> &table);
#if 0
	BOOL GetSingleItemInfo(CString,CString,CString&);
	BOOL GetGroupItemInfo(CString,CString[],int,CString&);
	BOOL GetHDID(PCHAR pIDBufer);
#endif
private:
	void VariantToString(const LPVARIANT,CString &) const;//��Variant���͵ı���ת��ΪCString
private:
	IEnumWbemClassObject* m_pEnumClsObj;
	IWbemClassObject* m_pWbemClsObj;
	IWbemServices* m_pWbemSvc;
	IWbemLocator* m_pWbemLoc;
};

