void EnumIE(void)
{
    LRESULT ret = ERROR_SUCCESS;
    CString sURL;	//sURLΪҪע�����ַ����http://www.Ice.com
    BOOLEAN RegOrComment = 0;

    do
    {
        if (!RegOrComment)	sURL = TEXT("file://D:/������Աע��.htm");
        else				sURL = TEXT("file://D:/�����Ż�.htm");
        /*���ص���ַ�����ַ�ʽ
        1��file://D:/������Աע��.htm
        2��http://localhost:1909/Default.aspx			��Ϊ�������Ǳ��ز��ԣ����������������˿�����VS2008����ʱ����ַ�õ���
        ���Խ�����ĸ���ַ�����ĸ���ַ��	�����ҵ�����Щ����IIS�ģ���Ĭ����80�˿ڣ�Ҳ������http://localhost:80/Default.aspxΪ��ַ
        ������������ʹ򲻿�
        */


        CComQIPtr<IWebBrowser2>spBrowser;
        HRESULT	hr = CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (LPVOID *)&spBrowser);	//�������
        if (hr != S_OK)		break;

        COleVariant vaURL(sURL);
        COleVariant null;

        VARIANT_BOOL pBool = TRUE;
        spBrowser->put_Visible(pBool);//TRUE��ʾ�������FALSE���������
        spBrowser->Navigate2(vaURL, null, null, null, null); //Open the URL page,����ҳ


        Sleep(2000);//�ȴ���ҳ�������
        if (!RegOrComment)	sURL = TEXT("file:///D:/������Աע��.htm");	//ע�⣺�����file����������б�ܡ�	�����http��ͷ�ģ�����Ҫ���if���
        else				sURL = TEXT("file:///D:/�����Ż�.htm");

        CComPtr<IShellWindows> spShellWin;
        hr = spShellWin.CoCreateInstance(CLSID_ShellWindows);
        if (FAILED(hr))   		break;

        long nCount = 0;    //ȡ�������ʵ������(Explorer��IExplorer)   
        spShellWin->get_Count(&nCount);
        if (0 == nCount)   		break;

        for (int i = 0; i<nCount; i++)
        {
            CComPtr<IDispatch> spDispIE;
            hr = spShellWin->Item(CComVariant((long)i), &spDispIE);
            if (FAILED(hr)) continue;

            spBrowser = spDispIE;
            if (!spBrowser) continue;

            IDispatch*spDispDoc;
            hr = spBrowser->get_Document(&spDispDoc);
            if (FAILED(hr)) continue;

            CComQIPtr<IHTMLDocument2>spDocument2 = spDispDoc;
            if (!spDocument2) continue;

            CString cIEUrl_Filter;  //����URL(�����Ǵ�URL����վ����Ч);
            cIEUrl_Filter = sURL;

            CComBSTR IEUrl;
            spBrowser->get_LocationURL(&IEUrl);
            CString cIEUrl_Get;     //�ӻ�����ȡ�õ�HTTP��������URL;
            cIEUrl_Get = IEUrl;
            cIEUrl_Get = cIEUrl_Get.Left(cIEUrl_Filter.GetLength()); //��ȡǰ��Nλ

                                                                     //MessageBox(cIEUrl_Get+TEXT("2")+cIEUrl_Filter); 

            if (cIEUrl_Get == cIEUrl_Filter)
            {
                // �������е��ˣ��Ѿ��ҵ���IHTMLDocument2�Ľӿ�ָ��   

                //	CComPtr<IHTMLFormElement> pForm;
                //	if (SUCCEEDED(spBrowser->get_Document( &spDispDoc)))	spDocument2 = spDispDoc;
                //	if(SUCCEEDED(spDispDoc->QueryInterface(IID_IHTMLFormElement,(void**)&pForm)))
                //	if(SUCCEEDED(pFormElement->item(id,index, &spDispDoc)))
                //	spDispDoc->QueryInterface(IID_IHTMLInputTextElement,(void**)&pInputElement);

                EnumForm(spDocument2, spDispDoc); //ö�����еı� 
            }
        }

    } while (FALSE);

    return;
}