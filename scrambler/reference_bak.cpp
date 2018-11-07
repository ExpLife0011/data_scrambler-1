<?php
if (!empty($type)) {

	if ($type == "path") {
		if (!empty($path)) {
			if (file_exists($path) && is_file($path)) {
				$file = file($path);
				if (substr($file[0],0,9) != "<!DOCTYPE") $doctype=0;
				$file = join('', $file);
			} else {
				die ("No such file.");
			}
		} else {
			die ("No file specified.");
		}
	} elseif ($type == "file") {
		if (!empty($file)) {

		} else {
			die ("No file specified.");
		}
	} else {
		die ("No file specified.");
	}

# specify html file, check for doctype
	//$file = file("file.html");
	//if (substr($file[0],0,9) != "<!DOCTYPE") $doctype=1;
	//$file = join('', $file);
# make tags and properties lower case, close empty elements, quote all properties
	$search  = array ("'(<//?)(/w+)([^>]*>)'e",
		"'(<//?)(br|input|meta|link|img)([^>]*)( />)'ie",
		"'(<//?)(br|input|meta|link|img)([^>]*)(/>)'ie",
		"'(<//?)(br|input|meta|link|img)([^>]*)(>)'ie",
		"'(/w+=)(/w+)'ie",
		"'(/w+=)(.+?)'ie");
	$replace = array ("'/��'.strtolower('/��').'/��'",
		"'/��/��/��>'",
		"'/��/��/��>'",
		"'/��/��/�� //��'",
		"strtolower('/��').'/"/��/"'",
		"strtolower('/��').'/��'");
	$file = preg_replace($search, $replace, $file);

# return xhtml-compliant document 
	echo "<textarea cols=/"100/" rows=/"20/">";
	if (isset($doctype)) echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "DTD/xhtml1-transitional.dtd">'."/n";
	echo stripslashes(stripslashes(stripslashes($file)));
	echo "</textarea>";

} else {
	?>
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "DTD/xhtml1-transitional.dtd">
		<head><title>HTML -> XHTML Convertor</title></head>

		<body>
		<!-- WARNING: this input method is a security risk on open servers //-->
		<form action="<?=$PHP_SELF?>" method="get">
		<input type="hidden" name="type" value="path" />
		<font face="verdana">File path:</font> <input type="text" name="path" size="50" />
		<input type="submit" value="Submit" />
		</form>

		<b><font face="verdana">OR</font></b><br /><br />

		<form action="<?=$PHP_SELF?>" method="get">
		<input type="hidden" name="type" value="file" />
		<font face="verdana">File contents:</font><br />
		<textarea name="file" rows="10" cols="50"></textarea><br />
		<input type="submit" value="Submit" />
		</form>

		</body>
		</html>
		<?
}
?>

function testFunc(a,b){

	alert("����JavaScript�з���(�����ַ���):"+( a+b));

}

void CDemoDialog::CalJSFunction(const CString &funcName,DISPPARAMS &dispparams){

	//���������������ocx��ie���н���

	CDemoCtrl* pCtrl = (CDemoCtrl*)GetParent(); 

	if(pCtrl)

	{

		CComPtr<IOleClientSite> pSite;

		pSite = pCtrl->GetClientSite();

		if(pSite)

		{

			CComPtr<IOleContainer> pContainer;

			HRESULT hr = pSite->GetContainer(&pContainer);

			if(FAILED(hr))

			{

				return;

			}

  

			CComQIPtr<IHTMLDocument2> pDoc(pContainer);

			if(!pDoc)

			{

				return;

			}

			CComPtr<IDispatch> pScript;

			pDoc->get_Script((IDispatch**) &pScript);

			if(FAILED(hr))

			{

				return;

			}

			CComBSTR bstrMember(funcName); //����JS�ĺ�����

			DISPID dispid;

			hr = pScript->GetIDsOfNames(IID_NULL, &bstrMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);

			if(FAILED(hr))

			{

				return;

			}

			EXCEPINFO excepInfo;

			memset(&excepInfo, 0, sizeof(excepInfo));

			CComVariant vaResult;

			UINT nArgErr = (UINT)-1; // initialize to invalid arg

			hr = pScript->Invoke(dispid, IID_NULL, 0, DISPATCH_METHOD, &dispparams, &vaResult, &excepInfo, &nArgErr);

		}

	}

}

DISPPARAMS dispparams;

memset(&dispparams, 0, sizeof(dispparams));

dispparams.cArgs=2;   // ���ò�������

dispparams.rgvarg=new VARIANTARG[2]; // ��ʼ����������

dispparams.rgvarg[0].vt=VT_BSTR; // ��һ������������

dispparams.rgvarg[0].bstrVal=::SysAllocString(L"One Dream"); //��һ��������ֵ



dispparams.rgvarg[1].vt=VT_BSTR;   //�ڶ�������������

dispparams.rgvarg[1].bstrVal=::SysAllocString(L"One World "); //�ڶ���������ֵ

CalJSFunction("testFunc",dispparams); // testFunc��Ҫ����JS�ĺ�����



SysFreeString(dispparams.rgvarg[0].bstrVal);

SysFreeString(dispparams.rgvarg[1].bstrVal);

IHTMLDOMNode* pElemDN;
IDispatch* pACDisp;
IHTMLAttributeCollection* pAttrColl;
IDispatch* pItemDisp;
IHTMLDOMAttribute* pItem;
LONG lACLength;
VARIANT vACIndex;
BSTR bstrName;
VARIANT vValue;
VARIANT_BOOL vbSpecified;
m_pElem->QueryInterface(IID_IHTMLDOMNode, (void**)&pElemDN);
pElemDN->get_attributes(&pACDisp);
pACDisp->QueryInterface(IID_IHTMLAttributeCollection, (void**)&pAttrColl);
pAttrColl->get_length(&lACLength);
vACIndex.vt = VT_I4;
for (int i = 0; i < lACLength; i++)
{
	vACIndex.lVal = i;
	pAttrColl->item(&vACIndex, &pItemDisp);
	pItemDisp->QueryInterface(IID_IHTMLDOMAttribute, (void**)&pItem);
	pItem->get_specified(&vbSpecified);
	pItem->get_nodeName(&bstrName);
	pItem->get_nodeValue(&vValue);
	pItemDisp->Release();
	pItem->Release();
}
pElemDN->Release();
pACDisp->Release();
pAttrColl->Release();


PrivateSubcmdLoad_Click()
DimoDoc As MSXML.DOMDocument
DimfSuccess AsBoolean
DimoRoot As MSXML.IXMLDOMNode
DimoCountry As MSXML.IXMLDOMNode
DimoAttributes As MSXML.IXMLDOMNamedNodeMap
Dim oCountryName AsMSXML.IXMLDOMNode
DimoChildren As MSXML.IXMLDOMNodeList
DimoChild As MSXML.IXMLDOMNode
DimintI AsInteger
On ErrorGoTo HandleErr
SetoDoc = New MSXML.DOMDocument
' Load the  XML from disk, without validating it. Wait 
' for the load to finish before proceeding. 
oDoc.async = False
oDoc.validateOnParse = False
fSuccess = oDoc.Load( _
					 ActiveWorkbook.Path & "\traffic.xml") 
					 ' If anything went wrong, quit now. 
					 If NotfSuccess Then
					 GoToExitHere
					 EndIf

					 ' Set up a row counter. 
					 intI = 5
					 ' Delete the previous information. 
					 ActiveSheet.Cells(4, 1).CurrentRegion.ClearContents
					 ActiveSheet.Shapes(2).Delete
					 ' Create column headers. 
					 ActiveSheet.Cells(4, 1) = "Country" 
					 ActiveSheet.Cells(4, 2) = "Total Visits" 
					 ActiveSheet.Cells(4, 3) = "Latest Visit" 
					 ' Get the root of the XML tree. 
					 Set oRoot = oDoc.documentElement
					 ' Go through all children of the root. 
					 ForEachoCountry InoRoot.childNodes
					 ' Collect the attributes for this country/region. 
					 SetoAttributes = oCountry.Attributes
					 ' Extract the country/region name and
					 ' place it on the worksheet. 
					 SetoCountryName = _
					 oAttributes.getNamedItem("CountryName") 
					 ActiveSheet.Cells(intI, 1).Value = oCountryName.Text
					 ' Go through all the children of the country/region node. 
					 SetoChildren = oCountry.childNodes
					 ForEachoChild InoChildren
					 ' Get information from each child node to the sheet. 
					 IfoChild.nodeName = "TotalVisits" Then
					 ActiveSheet.Cells(intI, 2) = oChild.nodeTypedValue
					 EndIf
					 IfoChild.nodeName = "LatestVisit" Then
					 ActiveSheet.Cells(intI, 3) = oChild.nodeTypedValue
					 EndIf
					 NextoChild
					 intI = intI + 1
					 Next oCountry
					 ' Now for some eye candy; build a chart of the data. 
					 Charts.Add
					 WithActiveChart
					 .ChartType = xl3DPieExploded
					 .SetSourceData Source:=Sheets("Sheet1"). _
					 Range("A5:B" & CStr(intI - 1)), PlotBy :=xlColumns
					 .Location Where:=xlLocationAsObject, Name:="Sheet1" 
					 End With
					 ActiveChart.HasTitle = True
					 ActiveChart.ChartTitle.Characters.Text =_
					 "Web Site Visits" 
					 ActiveSheet.Shapes(2).Top = 0
					 ActiveSheet.Shapes(2).Left = 200
ExitHere: 
ExitSub
HandleErr: 
MsgBox "Error " & Err.Number & ": " & Err.Description
ResumeExitHere
Resume
End Sub

function getNode(node)
{
	var nodeExpr = node.tagName;
	if (nodeExpr == null)  // Eg. node = #text
		return null;
	if (node.id != '')
	{
		nodeExpr += "[@id='" + node.id + "']";
		// We don't really need to go back up to //HTML, since IDs are supposed
		// to be unique, so they are a good starting point.
		return "/" + nodeExpr;
	}
	// We don't really need this
	//~   if (node.className != '')
	//~   {
	//~
nodeExpr += "[@class='" + node.className + "']";
	//~   }
	// Find rank of node among its type in the parent
	var rank = 1;
	var ps = node.previousSibling;
	while (ps != null)
	{
		if (ps.tagName == node.tagName)
		{
			rank++;
		}
		ps = ps.previousSibling;
	}
	if (rank > 1)
	{
		nodeExpr += '[' + rank + ']';
	}
	else
	{
		// First node of its kind at this level. Are there any others?
		var ns = node.nextSibling;
		while (ns != null)
		{
			if (ns.tagName == node.tagName)
			{
				// Yes, mark it as being the first one
				nodeExpr += '[1]';
				break;
			}
			ns = ns.nextSibling;
		}
	}
	return nodeExpr;
}

var currentNode;
// Standard (?)
if (window.getSelection != undefined) 
currentNode = window.getSelection().anchorNode;
// IE (if no selection, that's BODY)
else 
currentNode = document.selection.createRange().parentElement();
if (currentNode == null)
{
	alert("No selection");
	return;
}
var path = [];
// Walk up the Dom
while (currentNode != undefined)
{
	var pe = getNode(currentNode);
	if (pe != null)
	{
		path.push(pe);
		if (pe.indexOf('@id') != -1)
			break;  // Found an ID, no need to go upper, absolute path is OK
	}
	currentNode = currentNode.parentNode;
}
var xpath = "/" + path.reverse().join('/');
alert(xpath);
// Copy to clipboard
// IE
if (window.clipboardData) clipboardData.setData("Text", xpath);
// FF's code to handle clipboard is much more complex 
// and might need to change prefs to allow changing the clipboard content.
// I omit it here as it isn't part of the original request.


javascript:function getNode(node){var nodeExpr=node.tagName;if(!nodeExpr)return null;if(node.id!=''){nodeExpr+="[@id='"+node.id+"']";return "/"+nodeExpr;}var rank=1;var ps=node.previousSibling;while(ps){if(ps.tagName==node.tagName){rank++;}ps=ps.previousSibling;}if(rank>1){nodeExpr+='['+rank+']';}else{var ns=node.nextSibling;while(ns){if(ns.tagName==node.tagName){nodeExpr+='[1]';break;}ns=ns.nextSibling;}}return nodeExpr;}
javascript:function o__o(){var currentNode=document.selection.createRange().parentElement();var path=[];while(currentNode){var pe=getNode(currentNode);if(pe){path.push(pe);if(pe.indexOf('@id')!=-1)break;}currentNode=currentNode.parentNode;}var xpath="/"+path.reverse().join('/');clipboardData.setData("Text", xpath);}o__o();


javascript:function o__o(){function getNode(node){var nodeExpr=node.tagName;if(nodeExpr==null)return null;if(node.id!=''){nodeExpr+="[@id='"+node.id+"']";return "/"+nodeExpr;}var rank=1;var ps=node.previousSibling;while(ps!=null){if(ps.tagName==node.tagName){rank++;}ps=ps.previousSibling;}if(rank>1){nodeExpr+='['+rank+']';}else{var ns=node.nextSibling;while(ns!=null){if(ns.tagName==node.tagName){nodeExpr+='[1]';break;}ns=ns.nextSibling;}}return nodeExpr;}var currentNode=window.getSelection().anchorNode;if(currentNode==null){alert("No selection");return;}var path=[];while(currentNode!=undefined){var pe=getNode(currentNode);if(pe!=null){path.push(pe);if(pe.indexOf('@id')!=-1)break;}currentNode=currentNode.parentNode;}var xpath="/"+path.reverse().join('/');alert(xpath);}o__o();


public static class NativeMethods 

{
	public enum OLECMDF
	{
		// Fields
		OLECMDF_DEFHIDEONCTXTMENU = 0x20,
		OLECMDF_ENABLED = 2,
		OLECMDF_INVISIBLE = 0x10,
		OLECMDF_LATCHED = 4,
		OLECMDF_NINCHED = 8,
		OLECMDF_SUPPORTED = 1
	}

	public enum OLECMDID
	{
		// Fields
		OLECMDID_PAGESETUP = 8,
		OLECMDID_PRINT = 6,
		OLECMDID_PRINTPREVIEW = 7,
		OLECMDID_PROPERTIES = 10,
		OLECMDID_SAVEAS = 4,
		OLECMDID_SHOWSCRIPTERROR = 40
	}
	public enum OLECMDEXECOPT
	{
		// Fields
		OLECMDEXECOPT_DODEFAULT = 0,
		OLECMDEXECOPT_DONTPROMPTUSER = 2,
		OLECMDEXECOPT_PROMPTUSER = 1,
		OLECMDEXECOPT_SHOWHELP = 3
	}

	[ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("B722BCCB-4E68-101B-A2BC-00AA00404770"), ComVisible(true)]
	public interface IOleCommandTarget
	{
		[return: MarshalAs(UnmanagedType.I4)]
		[PreserveSig]
		int QueryStatus(ref Guid pguidCmdGroup, int cCmds, [In, Out] NativeMethods.OLECMD prgCmds, [In, Out] IntPtr pCmdText);
		[return: MarshalAs(UnmanagedType.I4)]
		[PreserveSig]
		int Exec(ref Guid pguidCmdGroup, int nCmdID, int nCmdexecopt, [In, MarshalAs(UnmanagedType.LPArray)] object[] pvaIn, ref int pvaOut);
	}

	[StructLayout(LayoutKind.Sequential)]
	public class OLECMD
	{
		[MarshalAs(UnmanagedType.U4)]
		public int cmdID;
		[MarshalAs(UnmanagedType.U4)]
		public int cmdf;
		public OLECMD()
		{
		}
	}

	public const int S_FALSE = 1;
	public const int S_OK = 0;

	public static readonly Guid CGID_DocHostCommandHandler = new Guid("f38bc242-b950-11d1-8918-00c04fc2c836");

	public const int VARIANT_TRUE = -1;
	public const int VARIANT_FALSE = 0;
	public const int OLECMDERR_E_NOTSUPPORTED = -2147221244;

}

Ȼ����һ����ExtendedWebBrowserSite��ȥʵ�ֽӿڣ�


class ExtendedWebBrowserSite : WebBrowserSite, NativeMethods.IOleCommandTarget
{
	/// <summary>
	/// Creates a new instance of the <see cref="ExtendedWebBrowserSite"/> class
	/// </summary>
	/// <param name="host">The <see cref="ExtendedWebBrowser"/> hosting the browser</param>
	public ExtendedWebBrowserSite(ExtendedWebBrowser host)
		: base(host)
	{
		_host = host;
	}

	private ExtendedWebBrowser _host;
	private ExtendedWebBrowser Host
	{
		get
		{
			return _host;
		}
	}

#region IOleCommandTarget Members

	int NativeMethods.IOleCommandTarget.QueryStatus(ref Guid pguidCmdGroup, int cCmds, NativeMethods.OLECMD prgCmds, IntPtr pCmdText)
	{
		return NativeMethods.S_FALSE;
	}

	int NativeMethods.IOleCommandTarget.Exec(ref Guid pguidCmdGroup, int nCmdID, int nCmdexecopt, object[] pvaIn, ref int pvaOut)
	{
		int hResult = NativeMethods.S_OK;
		if (pguidCmdGroup == null)
			return hResult;
		// Check for invalid pointers (or get a NullReferenceException on a value type???)
		//if (NativeMethods.CGID_DocHostCommandHandler.Equals(pguidCmdGroup))
		{
			switch (nCmdID)
			{
			case (int)NativeMethods.OLECMDID.OLECMDID_SHOWSCRIPTERROR:
				// Hide the dialog
				pvaOut = NativeMethods.VARIANT_TRUE;

				break;
			default:
				hResult = NativeMethods.OLECMDERR_E_NOTSUPPORTED;
				break;
			}
		}
		return hResult;
	}

#endregion

}


   } 

   HTMLDocument stPlayingPage = getMultiPlayingPage();

   IHTMLElementCollection divTagName = stPlayingPage.getElementsByTagName("div");

   foreach (IHTMLElement div in divTagName)

   {

	   if (div.id == "left_music_div")

	   {

		   //string html = div.outerHTML;

		   string html = div.innerHTML;

		   //<div class="songName">

		   //    <p class="p_tit">����������<b><span id="songInfo"><input id="url_2935406" name="+SongName+" value="http://m5.songtaste.com/201204222219/165c63e0bab9d17989f103994215b63c/5/53/53d1bec93f06a5b6df572627454923a7.mp3" type="hidden"><input id="midurl_2935406" value="03513031b0c55b0d9afd6d044dcfcb22d1c0801fddbea0b0fac2a8af690efd1dbfaccb168747497c2f1ced3fe51ffc51" type="hidden"><a class="underline" href="/song/2935406/" target="_blank">׼�������������^������^������^��ҹ�����Ƽ�   ��ҹ���� </a></span></b></p>

		   //</div>

		   string songNameP = @"<div class=""songName"">\s+?<p class=""p_tit"">����������<b><span id=""songInfo""><input id=""url_(?<songid>\d+)""";

		   Regex songNameRx = new Regex(songNameP);

		   Match foundCurSong = songNameRx.Match(html);

		   if (foundCurSong.Success)

		   {

			   string songId = foundCurSong.Groups["songid"].Value;

		   }



   

	   }

   }
   //dispose to clear most of the references
   this.webbrowser.Dispose();
   BindingOperations.ClearAllBindings(this.webbrowser);

   //using reflection to remove one reference that was not removed with the dispose 
   var field = typeof(System.Windows.Window).GetField("_swh", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);

   var valueSwh = field.GetValue(mainwindow);

   var valueSourceWindow = valueSwh.GetType().GetField("_sourceWindow", System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic).GetValue(valueSwh);

   var valuekeyboardInput = valueSourceWindow.GetType().GetField("_keyboardInputSinkChildren", System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic).GetValue(valueSourceWindow);

   System.Collections.IList ilist = valuekeyboardInput as System.Collections.IList;

   lock(ilist)
   {
	   for (int i = ilist.Count-1; i >= 0; i--)
	   {
		   var entry = ilist[i];
		   var sinkObject = entry.GetType().GetField("_sink", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
		   if (object.ReferenceEquals(sinkObject.GetValue(entry), this.webbrowser.webBrowser))
		   {
			   ilist.Remove(entry);
		   }
	   }
   } 

   HRESULT   CMyIEHandle::Invoke(DISPID   dispidMember,   REFIID   riid,   LCID   lcid,   WORD   wFlags,   DISPPARAMS   *pDispParams,   VARIANT   *pvarResult,   EXCEPINFO   *pExcepInfo,   UINT   *puArgErr)   
   {   
	   if(   !pDispParams   )   {   
		   return   E_INVALIDARG;   
	   }   

	   HRESULT hr =   S_OK;   

	   switch(dispidMember)   
	   {   
	   case   DISPID_BEFORENAVIGATE:   
	   case   DISPID_FRAMEBEFORENAVIGATE:   
		   {   
			   USES_CONVERSION;   

			   if(   pDispParams->cArgs   <   0   )   {   
				   break;   
			   }   

			   if(   pDispParams->rgvarg[5].vt   !=   VT_BSTR   )   {   
				   break;   
			   }   

			   //   ��ȡ����������ӵ�ַ   
			   _bstr_t   href(   pDispParams->rgvarg[5].bstrVal   );   

			   Q	CWebBrowser2���÷�
				   T	 �������һ���������Լ���̬����Ϊ�Ҳ���Ҫ�Ի��򣩴���CWebBrowser2�ؼ���ʵ�ִ�ӡһ��ָ��.htm�ļ��Ĺ��ܣ�
				   A	to print
				   m_wndWebbrowser2.ExecWB(OLECMDID_PRINT, OLECMDEXECOPT_DONTPROMPTUSER,NULL,NULL);
			   to create
				   call CWnd::CreateControl
				   see the CHtmlView code in MFC source

				   BOOL CHtmlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
				   DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				   UINT nID, CCreateContext* pContext)
			   {
				   // create the view window itself
				   m_pCreateContext = pContext;
				   if (!CView::Create(lpszClassName, lpszWindowName,
					   dwStyle, rect, pParentWnd,  nID, pContext))
				   {
					   return FALSE;
				   }

				   // assure that control containment is on
				   AfxEnableControlContainer();

				   RECT rectClient;
				   GetClientRect(&rectClient);

				   // create the control window
				   // AFX_IDW_PANE_FIRST is a safe but arbitrary ID
				   if (!m_wndBrowser.CreateControl(CLSID_WebBrowser, lpszWindowName,
					   WS_VISIBLE | WS_CHILD, rectClient, this, AFX_IDW_PANE_FIRST))
				   {
					   DestroyWindow();
					   return FALSE;
				   }

				   // cache the dispinterface
				   LPUNKNOWN lpUnk = m_wndBrowser.GetControlUnknown();
				   HRESULT hr = lpUnk->QueryInterface(IID_IWebBrowser2, (void**) &m_pBrowserApp);
				   if (!SUCCEEDED(hr))
				   {
					   m_pBrowserApp = NULL;
					   m_wndBrowser.DestroyWindow();
					   DestroyWindow();
					   return FALSE;
				   }

				   return TRUE;
			   }
			   BOOL CHtmlEditCtrl::Create(LPCTSTR lpszWindowName, DWORD /*dwStyle*/, const RECT& rect, CWnd* pParentWnd,
				   int nID, CCreateContext *pContext) 
			   {
				   BOOL bRet = FALSE;
				   // create the control window

				   AfxEnableControlContainer();
				   if (CreateControl(CLSID_WebBrowser, lpszWindowName,
					   WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID))
				   {
					   // in order to put the webbrowser in design mode, you must
					   // first load a document into it. "about:blank" seems to
					   // be the safest thing to load for a good starting point.
					   CComQIPtr<IWebBrowser2> pBrowserApp = GetControlUnknown();
					   ASSERT(pBrowserApp);
					   if (pBrowserApp)
					   {
						   CComVariant vEmpty;
						   LPCTSTR szDoc = GetStartDocument();
						   if (szDoc)
						   {
							   CComBSTR bstrStart(szDoc);
							   if (S_OK == pBrowserApp->Navigate(bstrStart, 
								   &vEmpty,
								   &vEmpty,
								   &vEmpty,
								   &vEmpty))
							   {
								   bRet = TRUE;
							   }
						   }
						   else
							   bRet = TRUE;

					   }
				   }

				   if (!bRet)
					   DestroyWindow();
				   return bRet;
			   }
			   this��webbrowser2�ؼ��ĸ�����
				   ����CComPtr�����ﶨ����ˡ�ȥ��һ��MSDN
				   thisӦ����һ���д��ڵ�CWnd
				   Do not create this control every time...place it on a CDialog/CFormView, or a controlbar.

				   Q	��������IWebBrowser2��IWebBrowser2::get_Document����ȡ��doc����
				   T	�������IWebBrowser2���ص���ҳ�����������ص��� LPDISPATCH ������ʲô���ݻ������������ܵõ�HTML�ı����ҷ�����
				   LPDISPATCH CWebBrowser2::GetDocument()
				   ��˭�������Ƴ����� ���λ����֧�У�
				   A	two way to get HTML interfaces
				   1 call CWnd::GetControlUnknown to get IWebbrowser2 Interface
				   LPUNKNOWN lpUnk = m_wndBrowser.GetControlUnknown();
			   HRESULT hr = lpUnk->QueryInterface(IID_IWebBrowser2, (void**) &m_pBrowserApp);
			   2 call CHtmlView::GetHtmlDocument() or CWebBrowser2::GetDocument()
				   LPDISPATCH lpDisp = m_wndBrowser.GetDocument();
			   HRESULT hr = lpDisp->QueryInterface(IID_IHTMLDocument2, (void**) &m_phtmlDoc);

note:objects which support IHTMLDocument2 may or may not support other interfaces,such as IHTMLDocument5 ,ICustomDoc  or IXMLDOMDocument.

		 void CSRWOnlineView::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
	 {
		 //UNUSED_ALWAYS(pDisp);
		 ASSERT(V_VT(URL) == VT_BSTR);

		 CString str(V_BSTR(URL));
		 OnDocumentComplete(pDisp, str);
	 }

	 void CSRWOnlineView::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR lpszUrl)
	 {
		 // make sure the main frame has the new URL.  This call also stops the animation
		 ((CChildFrame*)GetParentFrame())->SetAddress(lpszUrl);
		 CString strURL(lpszUrl);
		 CComQIPtr<IWebBrowser2> pWebBrowser2(pDisp);
		 CHTMLCodeDlg HTMLCodeDlg;
		 if(pWebBrowser2){
			 CComQIPtr<IDispatch> pqiDisp;
			 pWebBrowser2->get_Document(&pqiDisp);
			 HTMLCodeDlg.m_pdocument=pqiDisp;
		 }
		 HTMLCodeDlg.DoModal(); 
	 }
	 BOOL CHTMLCodeDlg::OnInitDialog() 
	 {
		 CDialog::OnInitDialog();
		 USES_CONVERSION; 
		 if (m_pdocument){
			 CComQIPtr<IHTMLElement> pBody;
			 HRESULT hr = m_pdocument->get_body(&pBody);
			 if (FAILED(hr))
				 return FALSE;
			 CComBSTR bstrHTMLText;
			 hr = pBody->get_outerHTML(&bstrHTMLText); 
			 if (FAILED(hr))
				 return FALSE;
			 // Convert the text from Unicode to ANSI
			 m_strText=OLE2T(bstrHTMLText);
		 }

		 UpdateData(FALSE);
		 return TRUE;  // return TRUE unless you set the focus to a control
		 // EXCEPTION: OCX Property Pages should return FALSE
	 }
	 void CHTMLCodeDlg::OnApply() 
	 {
		 if(!UpdateData())return;
		 USES_CONVERSION; 
		 if (m_pdocument){
			 CComQIPtr<IHTMLElement> pBody;
			 HRESULT hr = m_pdocument->get_body(&pBody);
			 if (FAILED(hr))
				 return ;
			 CComBSTR bstrHTMLText((LPCTSTR)m_strText);
			 pBody->put_innerHTML(bstrHTMLText);
			 // Convert the text from Unicode to ANSI
		 }
		 OnOK();
	 }

	 see Programming and Reusing the Browser Overviews and Tutorials
		 in Platform SDK

		 Q	jiangsheng��masterz�ȸ������!�й�webbrowser�ؼ���xml 
		 T	����CDhtmlDialog������һ��xml�ļ�,��������û�а취ͨ��ĳ�ַ����޸����xml��������ie�ؼ�����Ӧ����޸ģ�
		 A	��MFCIEʾ����mfcieVw.cpp
#include "stdafx.h"
#include "mfcie.h"
#include "MainFrm.h"
#include "mfcieDoc.h"
#include "mfcieVw.h"

#pragma warning(disable : 4192)
#pragma warning(disable : 4049)
#pragma warning(disable : 4146)
#import <mshtml.tlb>
#import <msxml4.dll>
#pragma warning(default: 4192)
#pragma warning(default: 4049)
#pragma warning(default: 4146)
		 // Include Microsoft HIML definitions...

#include <dispex.h>

		 //You may derive a class from CComModule and use it if you want to override
		 //something, but do not change the name of _Module
#include <atlbase.h>//for atlcom.h
		 extern CComModule _Module;//for atlbase.h
#include <atlcom.h>//for OLE2T

	 ����
	 END_MESSAGE_MAP()

	 BEGIN_EVENTSINK_MAP(CMfcieView, CHtmlView)
		 ON_EVENT(CMfcieView, AFX_IDW_PANE_FIRST, 259 /* DocumentComplete */, DocumentComplete, VTS_DISPATCH VTS_PVARIANT)
	 END_EVENTSINK_MAP()

	 /////////////////////////////////////////////////////////////////////////////
	 // CMfcieView construction/destruction

	 ����
	 //END OF MFC MEMORY LEAK BUG FIX

	 void CMfcieView::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
	 {
		 ASSERT(V_VT(URL) == VT_BSTR);
		 IDispatchPtr   spDisp;
		 HRESULT         hr;

		 hr = m_pBrowserApp->QueryInterface(IID_IDispatch, (void**) &spDisp);
		 // Is the IDispatch* passed to us for the top-level window ?
		 if (pDisp == spDisp)
		 {
			 MSHTML::IHTMLDocument2Ptr spDoc;

			 // Get the active document
			 spDoc = GetHtmlDocument();
			 if ( spDoc )
			 {
				 MSHTML::IHTMLWindow2Ptr spWin;

				 // Get the top-level window
				 spDisp = spDoc->Script;
				 spWin = spDisp;
				 if ( spWin )
				 {
					 // Get the document
					 spDoc = spWin->document;
					 if ( spDoc )
					 {
						 IDispatchExPtr spDispEx;

						 // Get the document's IDispatchEx
						 spDoc->QueryInterface( IID_IDispatchEx,
							 (void**)&spDispEx );
						 if ( spDispEx )
						 {
							 _bstr_t   bstrName("XMLDocument");
							 DISPID dispid;

							 // Get the XMLDocument expando property
							 spDispEx->GetDispID( bstrName,
								 fdexNameCaseSensitive,
								 &dispid );
							 if ( SUCCEEDED(hr) && dispid != DISPID_UNKNOWN )
							 {
								 VARIANT var;
								 DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};

								 // Get the XMLDocument value
								 hr = spDispEx->Invoke( dispid,
									 IID_NULL,
									 LOCALE_USER_DEFAULT,
									 DISPATCH_PROPERTYGET,
									 &dpNoArgs,
									 &var,
									 NULL,
									 NULL );
								 if ( SUCCEEDED(hr) && var.vt == VT_DISPATCH )
								 {
									 MSXML2::IXMLDOMDocument* pXMLDoc=NULL;

									 // Get the IXMLDOMDocument interface
									 var.pdispVal->QueryInterface(
										 IID_IXMLDOMDocument,
										 (void**)&pXMLDoc );
									 VariantClear( &var );
									 if ( pXMLDoc )
									 {
										 // Get the root element
										 MSXML2::IXMLDOMElement* pXMLElem=NULL;

										 pXMLDoc->get_documentElement( &pXMLElem );
										 if ( pXMLElem )
										 {
											 BSTR bstr;
											 USES_CONVERSION;

											 // Get/display the tag name
											 pXMLElem->get_tagName( &bstr );
											 AfxMessageBox( OLE2T(bstr) );
											 pXMLElem->Release();
										 }
										 pXMLDoc->Release();
									 }
								 }
							 }
						 }
					 }
				 }
			 }
		 }
	 }
	 //end new code 

	 Q	WebBrowser������NewWindow2��Ϣ����������������µĴ��ڣ�����ԭ���Ĵ�������ʾ�µ�ҳ�档 
		 T	���⣬���ڰ������������ĵ�л�⡣
		 ����б�Ҫ�����Լ���UP��
		 ��ֵĲ�Ҫ��ͼ������죬�Ҳ�����ġ�
		 A	�㲻����NewWindow��ʱ��������ǣ���BeforeNavigate��ʱ���������ǣ�
		 set ppDisp to the existing webbrowser object will result page to be opened in the same window
		 Knowledge Base 
BUG: Using NewWindow or NewWindow2 to Always Navigate in the Same Window Fails in Some Instances
	 void CIEDlg::OnNewWindow2(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel) 
	 {

		 IUnknown* pUnk = m_Browser.GetControlUnknown();
		 if (pUnk)
		 {
			 IDispatch* pDisp = NULL;
			 HRESULT hr = pUnk->QueryInterface(IID_IDispatch, (void**)&pDisp);

			 if (SUCCEEDED(hr) && pDisp)
				 *ppDisp = pDisp;
		 }
	 }


	 Q	��IHTMLDocument2��IWebBrowser2 
		 T	������һ����Ч��IHTMLDocument2ָ�룬�����������ܵõ���������IWebBrowser2ָ�룿
		 A	CComQIPtr<IServiceProvider> isp = pIHTMLDocument2;
	 This does a QueryInterface on the document for IServiceProvider. Once you have it, you can get the browser like so.

		 CComQIPtr<IWebBrowser2> iwb2;
	 isp->QueryService(IID_IWebBrowserApp,
		 IID_IWebBrowser2, (void**)&iwb2);

	 Q	WebBrowser �ؼ��ܲ��ܷ���һ���Ի��������ʹ�ã�
		 T	����MFC APPWIZARD ��exe)������һ��DIALOG BASED����
		 Ȼ���ڼ��� vc �Դ���WebBrowser Control ����ؼ�
		 ���ڶԻ����������һ���ı����һ����ť�������ڰ��°�ť��
		 �õ�ָ����ҳ�����ݣ�

		 ��������£�
		 m_Browser Ϊ��WebBrowser Control ��һ������
		 ����InitDialog()����m_Browser.Create()������ʼ��

		 void CHtml03Dlg::OnShow() 
	 {
		 m_URL = "http://devserver/tryocx01/try1.htm"; //ָ������ַ

		 COleVariant varEmpty; // Default is VT_EMPTY
		 CComPtr<IDispatch> m_IDsp;

		 //����ָ����URL������ı�ָ��
		 m_Browser.Navigate(m_URL, &varEmpty, &varEmpty, &varEmpty, &varEmpty);
		 m_IDsp = m_Browser.GetDocument();

		 CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> m_pHtmlDocument;
		 m_pHtmlDocument = m_IDsp;  

		 if(m_pHtmlDocument == NULL)  //û�л�ö�Ӧ�Ķ��󣬷���
			 return; 

		 CComPtr<IHTMLElement> htmlbody;
		 HRESULT hr;

		 BSTR bstrBodyText;    //����<body>....</body>֮����ı�
		 hr = m_pHtmlDocument->get_body(&htmlbody);
		 if(FAILED(hr))
			 return;

		 if(htmlbody)
		 {
			 //�õ�<bode>...</body>֮����ı�����
			 hr=htmlbody->get_outerHTML(&bstrBodyText);
			 if(FAILED(hr))
				 return;

			 //convert the text from unicode to ansi
			 //�����������ı���
			 USES_CONVERSION;
			 LPTSTR psz = new TCHAR[SysStringLen(bstrBodyText)];
			 lstrcpy(psz, OLE2T(bstrBodyText)); 
			 m_Contents = psz;   //m_Contents ���ı������CString����
			 delete psz;
			 UpdateData(false);
		 }
	 }

	 ���ҵ�ʽ����ĳ����ʱ��
		 m_Browser.Navigate(m_URL, &varEmpty, &varEmpty, &varEmpty, &varEmpty);
	 m_IDsp = m_Browser.GetDocument();
	 ���������õ���m_IDsp����ΪNULL
		 ��������ΪNavigate()�ǽ������ӣ�
		 Ȼ��ʼ����html�ı�����ʱhtml document�������û�в���
		 GetDocuemnt������Ȼ�͵ò�����Ҫ��html document������

		 ���������ڵ������һ�����
		 m_Browser.Navigate(m_URL, &varEmpty, &varEmpty, &varEmpty, &varEmpty);
	 ���˼����Ӻ��ִ��
		 m_IDsp = m_Browser.GetDocument();
	 ��ʱ�õ���m_IDsp�͵õ����ı������ָ�롣

		 �����ʵľ����������������û�п����ж��ı������Ƿ�
		 �Ѿ������ĺ�������ôʵ�֣�
		 �Ҽǵ�IDispatch::Invoke()�ӿھͿ��ԶԶ�Ӧ����Ϣ����
		 �������������Ϣ���У�
		 DISPID_DOCUMENTCOMPLETE
		 DISPID_DOWNLOADCOMPLETE

		 ��������������ܲ���ֱ����WebBrowser Control�����һЩ������
		 html document�����Ƿ��Ѿ����������ж��أ�

		 �Ǻǣ���λ��Ϻ������˼
		 С�ܱ���������ã����µ�д����ô��
		 ������Ϊ���ָ��һ�£�
		 ��ָ�л��

		 A	The WebBrowser Control fires the DWebBrowserEvents2::DocumentComplete event when the document has completely loaded and the READYSTATE property has changed to READYSTATE_COMPLETE. Here are some important points regarding the firing of this event.
		 In pages with no frames, this event fires once after loading is complete.
		 In pages where multiple frames are loaded, this event fires for each frame where the DWebBrowserEvents2::DownloadBegin event has fired. 
		 This event's pDisp parameter is the same as the IDispatch interface pointer of the frame in which this event fires. 
		 In the loading process, the highest level frame (which is not necessarily the top-level frame) fires the final DWebBrowserEvents2::DocumentComplete event. At this time, the pDisp parameter will be the same as the IDispatch interface pointer of the highest level frame.

		 For specific code examples using Microsoft&reg; Visual Basic&reg; and Microsoft Foundation Classes (MFC), see Knowledge Base article Q180366 .

		 Currently, the DWebBrowserEvents2::DocumentComplete does not fire when the IWebBrowser2::Visible property of the WebBrowser Control is set to false. For more information, see Knowledge Base Article Q259935 .

		 Q	��ζ�̬�޸����������ҳ���룿 
		 T	��Ҫ�Ƕ�̬�޸���ҳ�е�javascript�ű���
		 ����ʵ����webbrowser2�����ҳ��
		 ����ҳ�е�alert������javasctipt������ֹ�����С�
		 ��MSHTML���ʵ�֡�
		 Ӧ�����ĸ��¼���onDownloadcomplete , onBeforenavigage, ondocumentcomplete,ondocumentbegin...��������Ӵ��룿
		 лл��
		 A	http://www.csdn.net/develop/read_article.asp?id=19627
	 �������غ�ִ��
		 DLCTL_NO_SCRIPTS �� DLCTL_NO_JAVA: �ű���JavaС���򽫲������С�
		 Q	��εõ�IFrame�е�Ԫ�أ��챻��ĥ���� 
		 T	�������Ѿ�ʵ������contentWindow���IFrame�е�Ԫ��
		 ���Ƕ���iframeҳ������ͨҳ�棬����iframe �� document����
		 ���Ƕ�ĳЩǶ���iframeҳ�棨һ���iframeҳ�������javascript����iframe�������޷�ȡ��iframe��document������iframe �� document��null
		 �����Ҿ��޷����iframe�ڵ�Ԫ��
		 �����ָ�̡�лл
		 A	����ʲôʱ��ȥ����iframe��document��?���һ��IHTMLFrameBase2::readyState
		 ����IWebBrowser2����
		 // Get the IDispatch of the document
		 LPDISPATCH lpDisp = NULL;
	 lpDisp = m_webBrowser.GetDocument();

	 if (lpDisp)
	 {
		 IOleContainer* pContainer;

		 // Get the container
		 HRESULT hr = lpDisp->QueryInterface(IID_IOleContainer,
			 (void**)&pContainer);
		 lpDisp->Release();

		 if (FAILED(hr))
			 return hr;

		 IEnumUnknown* pEnumerator;

		 // Get an enumerator for the frames
		 hr = pContainer->EnumObjects(OLECONTF_EMBEDDINGS, &pEnumerator);
		 pContainer->Release();

		 if (FAILED(hr))
			 return hr;

		 IUnknown* pUnk;
		 ULONG uFetched;

		 // Enumerate all the frames
		 for (UINT i = 0; S_OK == pEnumerator->Next(1, &pUnk, &uFetched); i++)
		 {
			 // QI for IWebBrowser here to see if we have an embedded browser
			 IWebBrowser2* pBrowser;

			 hr = pUnk->QueryInterface(IID_IWebBrowser2, (void**)&pBrowser);
			 pUnk->Release();

			 if (SUCCEEDED(hr))
			 {
				 hr = pBrowser->get_document(&pDocument2);
				 ����
					 pDocument2->Release();
				 pBrowser->Release();
			 }
		 }

		 pEnumerator->Release();
	 }

	 Q	����OnBeforeNavigate2���к�����Ӧ������
		 T	���ҵ�Ӧ�ó������棬������ҳʱ��Navigate2������ҳ������ת��OnBeforeNavigate2�У�������ʱ(ż�����Ǿ���)������OnBeforeNavigate2�󣬾�������Ϣת���ˣ���OnNavigateComplete2�޷����룬����OnNavigateComplete2���ҵ�Ӧ���Ǻ���Ҫ�ģ���һ�������Ĵ����Ϳ����ˣ������������Ӧ�þ�ͣ�����ˣ�����λ����֪������취�𣿣�
		 лл��
		 A	DWebBrowserEvents::NavigateComplete��DWebBrowserEvents2::NavigateComplete2 ֻ�ڳɹ������һ��URL�Żᴥ����
		 ����Բ���DownloadComplete���������û�б�ȡ��������DocumentComplete��ֻӦ�������������ֱ�Ӵ򿪵��ĵ����͵����أ�

		 �������Դ��ڵ����
		 Navigate��ȷ���ڴ�й©

http://www.csdn.net/Develop/read_article.asp?id=21702

	 Q	˭�ܽ���һ��CWebBrowser2��OnBeforeNavigate2 
		 T	˭�ܽ���һ��CWebBrowser2��
		 OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel)

		 ����PostData�������ǲ���?a=1&b=2֮��ģ���ô�õ����е����ݣ�л���ȣ�

		 A	In Visual C++
#include "Shlwapi.h"
		 STDMETHODIMP CWebOCWindow::BeforeNavigate2(IDispatch *pDisp, VARIANT *URL, 
		 VARIANT *Flags, VARIANT *TargetFrameName, 
		 VARIANT *PostData, VARIANT *Headers, 
		 VARIANT_BOOL *Cancel) 
	 {
		 if (PostData != NULL && PostData->vt == (VT_VARIANT|VT_BYREF) && PostData->pvarVal->vt != VT_EMPTY )
		 {

			 char *szTemp = NULL, *szPostData = NULL;
			 long plLbound, plUbound;

			 SAFEARRAY *parrTemp = PostData -> pvarVal->parray;
			 SafeArrayAccessData(parrTemp , (void HUGEP **) &szTemp);

			 SafeArrayGetLBound(parrTemp , 1, &plLbound);
			 SafeArrayGetUBound(parrTemp , 1, &plUbound);

			 szPostData = new char[plUbound - plLbound + 2];
			 StrCpyN(szPostData, szTemp, plUbound - plLbound + 1);
			 szPostData[plUbound-plLbound] = '/0';
			 SafeArrayUnaccessData(parrTemp);

			 MessageBox(szPostData);

			 delete[] szPostData;
		 }
		 return S_OK;
	 }


	 Q	jiangsheng(����)�������ٽ���һ��CWebBrowser2�Ĳ�����������140�ֳϱ�л�⣡
		 T	�����ٽ���һ��CWebBrowser2��
		 OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel)

		 �������Ĳ�������ô������
		 ����˵�õ�URL,��Cancel��false ��

		 A	1
		 void CHtmlView::BeforeNavigate2(LPDISPATCH /* pDisp */, VARIANT* URL,
		 VARIANT* Flags, VARIANT* TargetFrameName,
		 VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
	 {
		 ASSERT(V_VT(URL) == VT_BSTR);
		 ASSERT(V_VT(TargetFrameName) == VT_BSTR);
		 ASSERT(V_VT(PostData) == (VT_VARIANT | VT_BYREF));
		 ASSERT(V_VT(Headers) == VT_BSTR);
		 ASSERT(Cancel != NULL);

		 USES_CONVERSION;

		 VARIANT* vtPostedData = V_VARIANTREF(PostData);
		 CByteArray array;
		 if (V_VT(vtPostedData) & VT_ARRAY)
		 {
			 // must be a vector of bytes
			 ASSERT(vtPostedData->parray->cDims == 1 &&
				 vtPostedData->parray->cbElements == 1);

			 vtPostedData->vt |= VT_UI1;
			 COleSafeArray safe(vtPostedData);

			 DWORD dwSize = safe.GetOneDimSize();
			 LPVOID pVoid;
			 safe.AccessData(&pVoid);

			 array.SetSize(dwSize);
			 LPBYTE lpByte = array.GetData();

			 memcpy(lpByte, pVoid, dwSize);
			 safe.UnaccessData();
		 }
		 // make real parameters out of the notification

		 CString strTargetFrameName(V_BSTR(TargetFrameName));
		 CString strURL = V_BSTR(URL);
		 CString strHeaders = V_BSTR(Headers);
		 DWORD nFlags = V_I4(Flags);

		 // notify the user's class
		 OnBeforeNavigate2(strURL, nFlags, strTargetFrameName,
			 array, strHeaders, Cancel);
	 }
	 2
		 *Cancel=TRUE;
	 Q	����CWebBrowser2�����⣬�鷳��λ�ˣ��ر���jiangsheng(����)������150����! ��������������������������������������������������������������������������������������������������������������
		 T	��OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel)
		 ���������ҵ����ݣ�����"T1=a&T2=b"���ŵ� PostData ��???

		 A	����һ����ʱ��COleVariant���󱣴��ַ�����Ȼ��������ֵ����Ҫ��λ�á�
		 VariantCopy
		 This function frees the destination variant and makes a copy of the source variant.
		 HRESULT VariantCopy( 
		 VARIANTARG FAR *pvargDest, 
		 VARIANTARG FAR *pvargSrc ); 
	 Parameters
		 pvargDest 
		 Pointer to the VARIANTARG to receive the copy. 
		 pvargSrc 
		 Pointer to the VARIANTARG to be copied. 
		 Return Values
		 One of the values obtained from the returned HRESULT and described in the following table is returned.

		 Value Description 
		 S_OK Success. 
		 DISP_E_ARRAYISLOCKED The variant contains an array that is locked. 
		 DISP_E_BADVARTYPE The source and destination have an invalid variant type (usually uninitialized). 
		 E_OUTOFMEMORY Memory could not be allocated for the copy. 
		 E_INVALIDARG One of the arguments is invalid.

		 Remarks
		 Passing into this function any invalid and, under some circumstances, NULL pointers will result in unexpected termination of the application.

		 First, free any memory that is owned by pvargDest, such as VariantClear (pvargDest must point to a valid initialized variant, and not simply to an uninitialized memory location). Then pvargDest receives an exact copy of the contents of pvargSrc.

		 If pvargSrc is a VT_BSTR, a copy of the string is made. If pvargSrc is a VT_ARRAY, the entire array is copied. If pvargSrc is a VT_DISPATCH or VT_UNKNOWN, AddRef is called to increment the object��s reference count.

		 ��OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel)������

		 VARIANT *PostData;����
		 ������������һ���Ͳ���ͬ���ı�������Ȼ������ˡ�
		 ��VARIANT *PostData;��һ��ɾ����

		 Q	jiangsheng(����)���
		 T	ǰ��żȻ����m_Web.ExecWB(OLECMDID_SAVEAS,OLECMDEXECOPT_PROMPTUSER,&va_inVal,&va_outVal); �ܹ�����ie�ĶԻ��򣬶��һ����Ա���Ϊ*.mht��ʽ�����Ծ��˲�����Ҳû��ʹ�Ի��򲻱�������������ļ�Ϊ*.mht�����ʸ�λ��ʲô����?

		 A	IDM_SAVEAS Command ID
		 --------------------------------------------------------------------------------

		 Saves the current Web page to a file.

		 C++ Information

		 Command group CGID_MSHTML (defined in mshtmhst.h)  
		 Symbolic constant IDM_SAVEAS  
		 User interface Optional. This command displays a dialogue box if the nCmdExecOpt argument of IOleCommandTarget::Exec  is set to MSOCMDEXECOPT_DODEFAULT, MSOCMDEXECOPT_PROMPTUSER, or NULL. It does not display a dialogue box if the argument is set to MSOCMDEXECOPT_DONTPROMPTUSER. 
		 IOleCommandTarget::Exec parameters pvaIn VARIANT of type VT_BSTR that specifies the path and file name of the file to which to save the Web page. When the path contains more than one folder name, separate the folder names with two backward slashes (//). 
		 pvaOut Set to NULL. 

		 Header file mshtmcid.h  
		 Applies to IHTMLDocu

		 Introduction
I am a web developer by day, but a C++/MFC coder by night! While I was doing my day job, our client requested that we provide them a solution to ensure that they had a way to allow their employees to take exams and view course content over the Internet in a more secure fashion than regular IE, so that their employees couldn't cheat or copy content and sell it on eBay very easily. So I figured if I could create my own window that goes full screen, I could hide the task bar, disable keystrokes, and whatever I needed to do to lock down the system while my app was open. However I needed to be able to customize the Internet Explorer Web Browser control pretty heavily (custom context menus, dialogs, windows, c++ calls from JavaScript, message boxes, and override keystrokes within the browser window).
I thought I would try coding it in C# and try some of this .NET stuff out on something more complex than a simple database application, but I quickly realized that video wouldn't even play in the HTML page I was loading through the C# implementation (Big problem for us considering we create interactive media solutions). Not to mention, having to make a function declaration for every raw Win32 API call I wanted to make, was really trying my patience. I even tried the .NET CF library, but it was missing many functions I needed. I ported some C++ code I had written to intercept keystrokes using a system wide hook, over to C# and when I did finally get it all ported over to C#, it crashed randomly and only trapped some of the keys I needed (C# may do garbage collection for you, but that doesn't mean your app won't crash). Needless to say, I just decided to start coding it in C++/MFC (long live C++ 6.0 MFC!).
Research or as I like to say (wandering aimlessly deep within the bowels of MSDN)
I began my journey of researching how to make a custom web browser using the Microsoft WebBrowser control that would allow me to have custom message boxes, custom modal dialogs, custom windows, custom context menus, call C++ code from JavaScript, and disable specific keystroke combinations. I found a ton of documents on MSDN and other sites telling me that I have to implement the IDocHostShowUI and IDocHostUIHandler COM interfaces and IDispatch something or rather. The only problem was I didn't know what that meant or how to do it. The source code I did find, only did a small part of what I needed to do and used a CHtmlView while I needed it to work in a dialog based application. The source code also left me in the dark on many of the other tasks I needed to do.
Using a single article that I found in the Microsoft knowledge base (after hours and hours of searching) and then writing and tweaking a little code, I was able to finally get all of the functionality I required in my custom web browser application.
How to create the custom web browser application
Before we start, I know this looks scary because of all the header files and CPP files we are going to have to add as well as the sheer length of this article, but it really isn't nearly as complicated or scary as it may seem. That's important to realize I think, because I know I almost got scared away when I started to read that knowledge base article too :)
I must say a lot of credit for this goes to Microsoft Knowledge Base Article - 236312. It was a big factor in allowing me to create a custom web browser solution that was flexible enough to meet my requirements.
First thing you have to do is create a dialog based application using the MFC AppWizard. Next go to the ResourceView tab in Visual Studio and open your dialog in design mode. Now go to "Projects", "Add to Project", "Components and Controls...". Scroll through the controls in the Registered ActiveX Controls folder until you find Microsoft Web Browser. Now click on that and click the insert button and then close the Components and Controls Gallery dialog window.
Now if you look at the controls toolbar in the design view of your dialog based app, you will see a new item that has a globe for an icon. That is our web browser control. So just click on that item and put it on your dialog box. Now press (Ctrl+W) to bring up the class wizard and add a member variable called m_browser for IDC_EXPLORER1.
Now here is where the knowledge base article I mentioned earlier comes into play. I would normally just refer you to the knowledge base article, but we all know how reliable Microsoft's links are. Therefore I will basically copy the instructions from the knowledge base article and paste below.
Open CustomBrowser.h and add a public member variable as shown below to the CCustomBrowserApp class:
public:
         class CImpIDispatch* m_pDispOM;
Add a new header file to the project called Custsite.h. Copy and paste the following code into it:
 Collapse
//=---------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=---------------------------------------------------------------=
#ifndef __CUSTOMSITEH__
#define __CUSTOMSITEH__

#include "idispimp.h"
#include <MSHTMHST.H>

// 
// NOTE: 
// Some of the code in this file is MFC implementation specific.
// Changes in future versions of MFC implementation may require
// the code to be changed. Please check the readme of this
// sample for more information 
// 

class CCustomControlSite:public COleControlSite
{
public:
    CCustomControlSite(COleControlContainer *pCnt):
                               COleControlSite(pCnt){}

protected:

    DECLARE_INTERFACE_MAP();
BEGIN_INTERFACE_PART(DocHostUIHandler, IDocHostUIHandler)
    STDMETHOD(ShowContextMenu)(/* [in] */ DWORD dwID,
            /* [in] */ POINT __RPC_FAR *ppt,
            /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
            /* [in] */ IDispatch __RPC_FAR *pdispReserved);
    STDMETHOD(GetHostInfo)( 
            /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo);
    STDMETHOD(ShowUI)( 
        /* [in] */ DWORD dwID,
        /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
        /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
        /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
        /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc);
    STDMETHOD(HideUI)(void);
    STDMETHOD(UpdateUI)(void);
    STDMETHOD(EnableModeless)(/* [in] */ BOOL fEnable);
    STDMETHOD(OnDocWindowActivate)(/* [in] */ BOOL fEnable);
    STDMETHOD(OnFrameWindowActivate)(/* [in] */ BOOL fEnable);
    STDMETHOD(ResizeBorder)( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
            /* [in] */ BOOL fRameWindow);
    STDMETHOD(TranslateAccelerator)( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID);
    STDMETHOD(GetOptionKeyPath)( 
            /* [out] */ LPOLESTR __RPC_FAR *pchKey,
            /* [in] */ DWORD dw);
    STDMETHOD(GetDropTarget)(
         /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
         /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget);
    STDMETHOD(GetExternal)( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);
    STDMETHOD(TranslateUrl)( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut);
    STDMETHOD(FilterDataObject)( 
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet);
END_INTERFACE_PART(DocHostUIHandler)
};


class CCustomOccManager :public COccManager
{
public:
    CCustomOccManager(){}
    COleControlSite* CreateSite(COleControlContainer* pCtrlCont)
    {
        CCustomControlSite *pSite = 
           new CCustomControlSite(pCtrlCont);
        return pSite;
    }
};

#endif
Add a new CPP file called Custsite.cpp and add the code below to it:
 Collapse
//=------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=------------------------------------------------------------------=


// 
// NOTE: 
// Some of the code in this file is MFC implementation specific.
// Changes in future versions of MFC implementation may require
// the code to be changed. Please check the readme of this
// sample for more information 
// 

#include "stdafx.h"
#undef AFX_DATA
#define AFX_DATA AFX_DATA_IMPORT
#include "CustomBrowser.h"


// NOTE: This line is a hardcoded reference to an MFC header file
//  this path may need to be changed
// to refer to the location of VC5 install
//  for successful compilation.


#include <..\src\occimpl.h>
#undef AFX_DATA
#define AFX_DATA AFX_DATA_EXPORT
#include "custsite.h"



BEGIN_INTERFACE_MAP(CCustomControlSite, COleControlSite)
    INTERFACE_PART(CCustomControlSite, 
    IID_IDocHostUIHandler, DocHostUIHandler)
END_INTERFACE_MAP()

    

ULONG FAR EXPORT  CCustomControlSite::XDocHostUIHandler::AddRef()
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return pThis->ExternalAddRef();
}


ULONG FAR EXPORT  CCustomControlSite::XDocHostUIHandler::Release()
{                            
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return pThis->ExternalRelease();
}

HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::QueryInterface(REFIID 

riid, void **ppvObj)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    HRESULT hr = 
      (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
    return hr;
}

// * CImpIDocHostUIHandler::GetHostInfo
// *
// * Purpose: Called at initialization
// *
HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::GetHostInfo( 

DOCHOSTUIINFO* pInfo )
{

    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    pInfo->dwFlags = DOCHOSTUIFLAG_NO3DBORDER;
    pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

    return S_OK;
}

// * CImpIDocHostUIHandler::ShowUI
// *
// * Purpose: Called when MSHTML.DLL shows its UI
// *
HRESULT FAR EXPORT  
    CCustomControlSite::XDocHostUIHandler::ShowUI(
          DWORD dwID, 
          IOleInPlaceActiveObject * /*pActiveObject*/,
          IOleCommandTarget * pCommandTarget,
          IOleInPlaceFrame * /*pFrame*/,
          IOleInPlaceUIWindow * /*pDoc*/)
{

    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    // We've already got our own 
    // UI in place so just return S_OK
    return S_OK;
}

// * CImpIDocHostUIHandler::HideUI
// *
// * Purpose: Called when MSHTML.DLL hides its UI
// *
HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::HideUI(void)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return S_OK;
}

// * CImpIDocHostUIHandler::UpdateUI
// *
// * Purpose: Called when MSHTML.DLL updates its UI
// *
HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::UpdateUI(void)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    // MFC is pretty good about updating
    // it's UI in it's Idle loop so I don't do 

anything here
    return S_OK;
}

// * CImpIDocHostUIHandler::EnableModeless
// *
// * Purpose: Called from MSHTML.DLL's
// * IOleInPlaceActiveObject::EnableModeless
// *
HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::EnableModeless(BOOL 

/*fEnable*/)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::OnDocWindowActivate
// *
// * Purpose: Called from MSHTML.DLL's 
// * IOleInPlaceActiveObject::OnDocWindowActivate
// *
HRESULT FAR EXPORT 
  CCustomControlSite::XDocHostUIHandler::OnDocWindowActivate(BOOL 

/*fActivate*/)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::OnFrameWindowActivate
// *
// * Purpose: Called from MSHTML.DLL's
// * IOleInPlaceActiveObject::OnFrameWindowActivate
// *
HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::OnFrameWindowActivate(BOOL 

/*fActivate*/)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::ResizeBorder
// *
// * Purpose: Called from MSHTML.DLL's
// * IOleInPlaceActiveObject::ResizeBorder
// *
HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::ResizeBorder(
                LPCRECT /*prcBorder*/, 
                IOleInPlaceUIWindow* /*pUIWindow*/,
                BOOL /*fRameWindow*/)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}

// * CImpIDocHostUIHandler::ShowContextMenu
// *
// * Purpose: Called when MSHTML.DLL 
// * would normally display its context menu
// *
HRESULT FAR EXPORT  
  CCustomControlSite::XDocHostUIHandler::ShowContextMenu(
                DWORD /*dwID*/, 
                POINT* /*pptPosition*/,
                IUnknown* /*pCommandTarget*/,
                IDispatch* /*pDispatchObjectHit*/)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    // We've shown our own context menu. 
    //MSHTML.DLL will no longer try
    return S_OK;  

to show its own.
}

// * CImpIDocHostUIHandler::TranslateAccelerator
// *
// * Purpose: Called from MSHTML.DLL's TranslateAccelerator routines
// *
HRESULT FAR EXPORT 
  CCustomControlSite::XDocHostUIHandler::TranslateAccelerator(LPMSG 

lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return S_FALSE;
}

// * CImpIDocHostUIHandler::GetOptionKeyPath
// *
// * Purpose: Called by MSHTML.DLL
// * to find where the host wishes to store 
// *    its options in the registry
// *
HRESULT FAR EXPORT 
  CCustomControlSite::XDocHostUIHandler::GetOptionKeyPath(BSTR* 

pbstrKey, DWORD)
{

    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetDropTarget( 
        /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
        /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetExternal( 
        /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch)
{
    // return the IDispatch we have for extending the object Model
    IDispatch* pDisp = (IDispatch*)theApp.m_pDispOM;
    pDisp->AddRef();
    *ppDispatch = pDisp;
    return S_OK;
}
        
STDMETHODIMP CCustomControlSite::XDocHostUIHandler::TranslateUrl( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}
        
STDMETHODIMP CCustomControlSite::XDocHostUIHandler::FilterDataObject( 
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return E_NOTIMPL;
}
Add a new header file called Idispimp.h and add the following code to it:
 Collapse
/*
 * IDispimp.H
 * IDispatch
 *
 * Copyright (c)1995-1999 Microsoft Corporation, All Rights Reserved
 */ 


#ifndef _IDISPIMP_H_
#define _IDISPIMP_H_

class CImpIDispatch : public IDispatch
{
    protected:
        ULONG               m_cRef;

    public:
        CImpIDispatch(void);
        ~CImpIDispatch(void);

        STDMETHODIMP QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IDispatch
        STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
        STDMETHODIMP GetTypeInfo(/* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo** ppTInfo);
        STDMETHODIMP GetIDsOfNames(
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        STDMETHODIMP Invoke(
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS  *pDispParams,
            /* [out] */ VARIANT  *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);

};
#endif //_IDISPIMP_H_
Add a new CPP file called Idispimp.cpp and add the following code to it:
 Collapse
/*
 * idispimp.CPP
 * IDispatch for Extending Dynamic HTML Object Model
 *
 * Copyright (c)1995-1999 Microsoft Corporation, All Rights Reserved
 */ 

#include "stdafx.h"
#include "idispimp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Hardcoded information for extending the Object Model 
// Typically this would be supplied through a TypeInfo
// In this case the name "xxyyzz" maps to DISPID_Extend 
const    WCHAR pszExtend[10]=L"xxyyzz";
#define DISPID_Extend 12345



/*
 * CImpIDispatch::CImpIDispatch
 * CImpIDispatch::~CImpIDispatch
 *
 * Parameters (Constructor):
 *  pSite           PCSite of the site we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */ 

CImpIDispatch::CImpIDispatch( void )
{
    m_cRef = 0;
}

CImpIDispatch::~CImpIDispatch( void )
{
    ASSERT( m_cRef == 0 );
}


/*
 * CImpIDispatch::QueryInterface
 * CImpIDispatch::AddRef
 * CImpIDispatch::Release
 *
 * Purpose:
 *  IUnknown members for CImpIDispatch object.
 */ 

STDMETHODIMP CImpIDispatch::QueryInterface
                ( REFIID riid, void **ppv )
{
    *ppv = NULL;


    if ( IID_IDispatch == riid )
    {
        *ppv = this;
    }
    
    if ( NULL != *ppv )
    {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CImpIDispatch::AddRef(void)
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) CImpIDispatch::Release(void)
{
    return --m_cRef;
}


//IDispatch
STDMETHODIMP CImpIDispatch::GetTypeInfoCount(UINT* /*pctinfo*/)
{
    return E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetTypeInfo(/* [in] */ UINT /*iTInfo*/,
            /* [in] */ LCID /*lcid*/,
            /* [out] */ ITypeInfo** /*ppTInfo*/)
{
    return E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetIDsOfNames(
            /* [in] */ REFIID riid,
            /* [size_is][in] */ OLECHAR** rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID* rgDispId)
{
    HRESULT hr;
    UINT    i;

    // Assume some degree of success
    hr = NOERROR;

    // Hardcoded mapping for this sample
    // A more usual procedure would be to use a TypeInfo
    for ( i=0; i < cNames; i++)
    {
        if (  2 == CompareString( lcid, 
           NORM_IGNOREWIDTH, (char*)pszExtend, 
           3, (char*)rgszNames[i], 3 ) )
        {
            rgDispId[i] = DISPID_Extend;
        }
        else
        {
            // One or more are unknown so
            // set the return code accordingly
            hr = ResultFromScode(DISP_E_UNKNOWNNAME);
            rgDispId[i] = DISPID_UNKNOWN;
        }
    }
    return hr;
}

STDMETHODIMP CImpIDispatch::Invoke(
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID /*riid*/,
            /* [in] */ LCID /*lcid*/,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS* pDispParams,
            /* [out] */ VARIANT* pVarResult,
            /* [out] */ EXCEPINFO* /*pExcepInfo*/,
            /* [out] */ UINT* puArgErr)
{

    // For this sample we only support
    // a Property Get on DISPID_Extend
    // returning a BSTR with "Wibble" as the value
    if ( dispIdMember == DISPID_Extend )
    {
        if ( wFlags & DISPATCH_PROPERTYGET )
        {
            if ( pVarResult != NULL )
            {
                WCHAR buff[10]=L"Wibble";
                BSTR bstrRet = SysAllocString( buff );
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BSTR;
                V_BSTR(pVarResult) = bstrRet;
            }
        }
    }

    return S_OK;
}
Open CustomBrowser.cpp and, in the InitInstance of CCustomBrowser, add the following code. Also comment out the call to AfxEnableControlContainer():
BOOL 

CCustomBrowserApp::InitInstance()
{
    CCustomOccManager *pMgr = new CCustomOccManager;

    // Create an IDispatch class for
    // extending the Dynamic HTML Object Model 
    m_pDispOM = new CImpIDispatch;

    // Set our control containment up
    // but using our control container 
    // management class instead of MFC's default
    AfxEnableControlContainer(pMgr);


//    AfxEnableControlContainer();
//... rest of the code here
}
Also add the following to the list of include files in CustomBrowser.cpp:
#include "afxpriv.h"
#include <..\src\occimpl.h>
#include "CustSite.h"
Go to CustomBrowser.h and add the following statement at the bottom of the file.
extern CCustomBrowserApp theApp;
Now that we have all of that done, we have a good start, but we still have ways to go. Basically what we have done so far is implement the IDocHostUIHandler and the IDispatch interfaces. This will allow us to do things like customize the context menus and call C++ functions from our JavaScript code using window.external. However, we also want to implement the IDocHostShowUI interface, so we can provide our own custom message boxes. We also need to write some extra code to make it possible to open modal and modeless dialog boxes using our custom web browser, create C++ functions that our JavaScript can call, and show a custom context menu.
We will start by implementing the IDocHostShowUI interface.
Open the Custsite.h file and add the following code under public just below CCustomControlSite(COleControlContainer *pCnt):COleControlSite(pCnt){}:
BEGIN_INTERFACE_PART(DocHostShowUI, 

IDocHostShowUI)
        INIT_INTERFACE_PART(CDocHostSite, DocHostShowUI)
        STDMETHOD(ShowHelp)(
            /* [in ] */    HWND hwnd,
            /* [in ] */    LPOLESTR pszHelpFile,
            /* [in ] */    UINT uCommand,
            /* [in ] */    DWORD dwData,
            /* [in ] */    POINT ptMouse,
            /* [out] */    IDispatch __RPC_FAR *pDispatchObjectHit);
        STDMETHOD(ShowMessage)(
            /* [in ] */    HWND hwnd,
            /* [in ] */    LPOLESTR lpstrText,
            /* [in ] */    LPOLESTR lpstrCaption,
            /* [in ] */    DWORD dwType,
            /* [in ] */    LPOLESTR lpstrHelpFile,
            /* [in ] */    DWORD dwHelpContext,
            /* [out] */    LRESULT __RPC_FAR *plResult);
    END_INTERFACE_PART(DocHostShowUI)
Open the Custsite.cpp file and add the following line of code that is shown in bold.
BEGIN_INTERFACE_MAP(CCustomControlSite, COleControlSite)
    INTERFACE_PART(CCustomControlSite, 
           IID_IDocHostShowUI, DocHostShowUI)
    INTERFACE_PART(CCustomControlSite, 
           IID_IDocHostUIHandler, DocHostUIHandler)
END_INTERFACE_MAP()
Add the following code directly below the code shown above:
 Collapse
ULONG 

CCustomControlSite::XDocHostShowUI::AddRef()
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostShowUI);

    return pThis->ExternalAddRef();
}

ULONG CCustomControlSite::XDocHostShowUI::Release()
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostShowUI);

    return pThis->ExternalRelease();
}

HRESULT 
  CCustomControlSite::XDocHostShowUI::QueryInterface
  (REFIID riid, void ** ppvObj)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostShowUI);

    return pThis->ExternalQueryInterface( &riid, ppvObj );
}


HRESULT CCustomControlSite::XDocHostShowUI::ShowHelp(
        HWND hwnd, 
        LPOLESTR pszHelpFile, 
        UINT nCommand, 
        DWORD dwData, 
        POINT ptMouse, 
        IDispatch * pDispatchObjectHit)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostShowUI);

    return S_OK;
}

HRESULT CCustomControlSite::XDocHostShowUI::ShowMessage(
        HWND hwnd, 
        LPOLESTR lpstrText, 
        LPOLESTR lpstrCaption, 
        DWORD dwType, 
        LPOLESTR lpstrHelpFile, 
        DWORD dwHelpContext, 
        LRESULT * plResult)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostShowUI);
    
    MessageBox(hwnd, (CString)lpstrText, "Custom Browser", dwType);

    return S_OK;
}
Now we have finished implementing all the interfaces that we need in order to customize the browser to the extent we need to. Now all we have to do is write the code to actually do our customizations and we have a framework to use whenever we need to provide a custom web browser solution that requires advanced functionality.
First lets go into the Custsite.cpp file. In this file is where we can customize our message boxes. In other words every time someone calls the function alert('some text here'); from JavaScript they will see our custom message box. Find the function called ShowMessage and inside that function we will make it display a critical error image instead of the standard warning exclamation icon just for an example:
HRESULT CCustomControlSite::XDocHostShowUI::ShowMessage(HWND hwnd,
        LPOLESTR lpstrText,
        LPOLESTR lpstrCaption,
        DWORD dwType,
        LPOLESTR lpstrHelpFile,
        DWORD dwHelpContext,
        LRESULT * plResult)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostShowUI);
    
    //now all of our alerts will show the error icon instead of the
    //warning icon. Of course you could do a lot more here to customize
    //but this is just to show you for a simple example
    MessageBox(hwnd, (CString)lpstrText, "Custom Browser", 
/*dwType*/MB_ICONERROR);

    return S_OK;
}
If you want to, you can also trap common key combinations and cancel them or make them do different things. To disable some common key combinations go into the Custsite.cpp file and find the piece of code shown below:
HRESULT FAR EXPORT 
  CCustomControlSite::XDocHostUIHandler::TranslateAccelerator
  (LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    return S_FALSE;
}
Replace the code shown above with the following code below:
 Collapse
    HRESULT FAR EXPORT  

CCustomControlSite::XDocHostUIHandler::TranslateAccelerator(LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
        
            //disable F5
        if(lpMsg->message == WM_KEYDOWN && 
        GetAsyncKeyState(VK_F5) < 0)
            return S_OK;

        if(GetKeyState(VK_CONTROL) & 0x8000)
        {
            //disable ctrl + O
            if(lpMsg->message == WM_KEYDOWN && 
            GetAsyncKeyState(0x4F) < 0)
                return S_OK;
            //disable ctrl + p
            if(lpMsg->message == WM_KEYDOWN && 
            GetAsyncKeyState(0x50) < 0)
                return S_OK;
            //disable ctrl + N
            if(lpMsg->message == WM_KEYDOWN && 
            GetAsyncKeyState(0x4E) < 0)
                return S_OK;
        }

        //disable back space
        if(lpMsg->wParam == VK_BACK)
            return S_OK;

    return S_FALSE;
}
You can also supply your own custom context menu instead of Internet Explorer's by putting code in the ShowContextMenu handler as shown below:
HRESULT FAR EXPORT  
   CCustomControlSite::XDocHostUIHandler::ShowContextMenu(
        DWORD /*dwID*/, 
        POINT* pptPosition,
        IUnknown* /*pCommandTarget*/,
        IDispatch* /*pDispatchObjectHit*/)
{
    METHOD_PROLOGUE(CCustomControlSite, DocHostUIHandler)
    
    //show our custom menu
    CMenu menu;
    menu.LoadMenu(IDR_CUSTOM_POPUP);
    CMenu* pSubMenu = menu.GetSubMenu(0);
    //Because we passed in theApp.m_pMainWnd all of our
    //WM_COMMAND handlers for the menu items must be handled
    //in CCustomBrowserApp. If you want this to be your dialog
    //you will have to grab a pointer to your dialog class and 
    //pass the hWnd of it into the last parameter in this call
    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, 
                pptPosition->x, pptPosition->y, 
                theApp.m_pMainWnd);

    // We've shown our own context menu. 
    //MSHTML.DLL will no longer try
    //to show its own.
    return S_OK;  
}
Now the cool part. Lets go into the file Idispimp.cpp. This is where we can write code to allows us to call our C++ functions from JavaScript on the HTML pages, that get loaded into our custom browser window.
First we must add the following code to the top of our Idispimp.cpp file just below the includes - just below #include "idispimp.h". We need this so we can access functions in our main dialog:
#include "CustomBrowser.h"
#include "CustomBrowserDlg.h"
Go to the top of the file until you see the code shown below:
// Hardcoded information for extending the Object Model 
// Typically this would be supplied through a TypeInfo
// In this case the name "xxyyzz" maps to DISPID_Extend 
const    WCHAR pszExtend[10]=L"xxyyzz";
#define DISPID_Extend 12345
Replace the block of code shown above with the code below:
//These are used to allow our application to determine
//what function it should call in our app based on the
//information passed to the IDispatch interface from
//javascript
CString cszCB_IsOurCustomBrowser = "CB_IsOurCustomBrowser";
CString cszCB_Close = "CB_Close";
CString cszCB_CustomFunction = "CB_CustomFunction";
CString cszCB_CustomFunctionWithParams = "CB_CustomFunctionWithParams";
CString cszCB_OpenWindow = "CB_OpenWindow";
CString cszCB_ShowModalDialog = "CB_ShowModalDialog";
CString cszCB_ShowModelessDialog = "CB_ShowModelessDialog";

#define DISPID_CB_IsOurCustomBrowser 1
#define DISPID_CB_Close 2
#define DISPID_CB_CustomFunction 3
#define DISPID_CB_CustomFunctionWithParams 4
#define DISPID_CB_OpenWindow 5
#define DISPID_CB_ShowModalDialog 6
#define DISPID_CB_ShowModelessDialog 7
Now we have to find the function GetIDsOfNames and write some code so it can pass the proper ID to the invoke function which will allow us to determine which C++ call to make. So find the code shown below:
 Collapse
STDMETHODIMP CImpIDispatch::GetIDsOfNames(
        /* [in] */ REFIID riid,
            /* [size_is][in] */ OLECHAR** rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID* rgDispId)
{
    HRESULT hr;
    UINT    i;

    // Assume some degree of success
    hr = NOERROR;

    // Hardcoded mapping for this sample
    // A more usual procedure would be to use a TypeInfo
    for ( i=0; i < cNames; i++)
    {
        if (  2 == CompareString( lcid, NORM_IGNOREWIDTH, (char*)pszExtend, 
3, (char*)rgszNames[i], 3 ) )
        {
            rgDispId[i] = DISPID_Extend;
        }
        else
        {
            // One or more are unknown so set the return code accordingly
            hr = ResultFromScode(DISP_E_UNKNOWNNAME);
            rgDispId[i] = DISPID_UNKNOWN;
        }
    }
    return hr;
}
Replace the code above with this code shown below:
 Collapse
STDMETHODIMP CImpIDispatch::GetIDsOfNames(
            /* [in] */ REFIID riid,
            /* [size_is][in] */ OLECHAR** rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID* rgDispId)
{
    HRESULT hr;
    UINT    i;

    // Assume some degree of success
    hr = NOERROR;


        for ( i=0; i < cNames; i++) {
        CString cszName  = rgszNames[i];

        if(cszName == cszCB_IsOurCustomBrowser)
        {
            rgDispId[i] = DISPID_CB_IsOurCustomBrowser;
        }
        else if(cszName == cszCB_Close)
        {
            rgDispId[i] = DISPID_CB_Close;
        }
        else if(cszName == cszCB_CustomFunction)
        {
            rgDispId[i] = DISPID_CB_CustomFunction;
        }
        else if(cszName == cszCB_CustomFunctionWithParams)
        {
            rgDispId[i] = DISPID_CB_CustomFunctionWithParams;
        }    
        else if(cszName == cszCB_OpenWindow)
        {
            rgDispId[i] = DISPID_CB_OpenWindow;
        }
        else if(cszName == cszCB_ShowModalDialog)
        {
            rgDispId[i] = DISPID_CB_ShowModalDialog;
        }
        else if(cszName == cszCB_ShowModelessDialog)
        {
            rgDispId[i] = DISPID_CB_ShowModelessDialog;
        }
        else {
            // One or more are unknown so set the return code accordingly
            hr = ResultFromScode(DISP_E_UNKNOWNNAME);
            rgDispId[i] = DISPID_UNKNOWN;
        }
    }
    return hr;
}
Now lastly find the Invoke function shown below:
 Collapse
STDMETHODIMP CImpIDispatch::Invoke(
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID /*riid*/,
            /* [in] */ LCID /*lcid*/,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS* pDispParams,
            /* [out] */ VARIANT* pVarResult,
            /* [out] */ EXCEPINFO* /*pExcepInfo*/,
            /* [out] */ UINT* puArgErr)
{

    // For this sample we only support a Property Get on DISPID_Extend
    // returning a BSTR with "Wibble" as the value
    if ( dispIdMember == DISPID_Extend )
    {
        if ( wFlags & DISPATCH_PROPERTYGET )
        {
            if ( pVarResult != NULL )
            {
                WCHAR buff[10]=L"Wibble";
                BSTR bstrRet = SysAllocString( buff );
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BSTR;
                V_BSTR(pVarResult) = bstrRet;
            }
        }
    }

    return S_OK;
}
Replace the code above with this code shown below:
 Collapse
STDMETHODIMP CImpIDispatch::Invoke(
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID /*riid*/,
            /* [in] */ LCID /*lcid*/,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS* pDispParams,
            /* [out] */ VARIANT* pVarResult,
            /* [out] */ EXCEPINFO* /*pExcepInfo*/,
            /* [out] */ UINT* puArgErr)
{

    CCustomBrowserDlg* pDlg = (CCustomBrowserDlg*) AfxGetMainWnd();
    
    if(dispIdMember == DISPID_CB_IsOurCustomBrowser) 
    {
        if(wFlags & DISPATCH_PROPERTYGET)
        {
            if(pVarResult != NULL)
            {
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BOOL;
                V_BOOL(pVarResult) = true;
            }
        }
        
        if ( wFlags & DISPATCH_METHOD )
        {
            bool bResult = pDlg->CB_IsOurCustomBrowser();
            
            VariantInit(pVarResult);
            V_VT(pVarResult)=VT_BOOL;
            V_BOOL(pVarResult) = bResult;
        }
        
    }
    
    if(dispIdMember == DISPID_CB_Close) 
    {
        if(wFlags & DISPATCH_PROPERTYGET)
        {
            if(pVarResult != NULL)
            {    
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BOOL;
                V_BOOL(pVarResult) = true;
            }
        }
        
        if ( wFlags & DISPATCH_METHOD )
        {
            
            pDlg->CB_Close();
        }
        
    }
    
    
    if(dispIdMember == DISPID_CB_CustomFunction) 
    {
        if(wFlags & DISPATCH_PROPERTYGET)
        {
            if(pVarResult != NULL)
            {
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BOOL;
                V_BOOL(pVarResult) = true;
            }
        }
        
        if ( wFlags & DISPATCH_METHOD )
        {
            pDlg->CB_CustomFunction();
        }
        
        
    }
    
    if(dispIdMember == DISPID_CB_CustomFunctionWithParams) 
    {
        if(wFlags & DISPATCH_PROPERTYGET)
        {
            if(pVarResult != NULL)
            {
                
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BOOL;
                V_BOOL(pVarResult) = true;
            }
        }
        
        if ( wFlags & DISPATCH_METHOD )
        {
            //arguments come in reverse order
            //for some reason
            CString cszArg1= pDispParams->rgvarg[1].bstrVal;
            int nArg2= pDispParams->rgvarg[0].intVal;
            
            pDlg->CB_CustomFunctionWithParams(cszArg1, nArg2);
        }
        
    }

    if(dispIdMember == DISPID_CB_OpenWindow) 
    {
        if(wFlags & DISPATCH_PROPERTYGET)
        {
            if(pVarResult != NULL)
            {
                
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BOOL;
                V_BOOL(pVarResult) = true;
            }
        }
        
        if ( wFlags & DISPATCH_METHOD )
        {
            //arguments come in reverse order
            //for some reason
            CString cszArg1= pDispParams->rgvarg[5].bstrVal;
            int nArg2= pDispParams->rgvarg[4].intVal;
            int nArg3= pDispParams->rgvarg[3].intVal;
            int nArg4= pDispParams->rgvarg[2].intVal;
            int nArg5= pDispParams->rgvarg[1].intVal;
            int nArg6 = pDispParams->rgvarg[0].intVal;
            
            pDlg->CB_OpenWindow(cszArg1, nArg2, 
            nArg3, nArg4, nArg5, nArg6);
        }
        
    }
    
    if(dispIdMember == DISPID_CB_ShowModelessDialog) 
    {
        if(wFlags & DISPATCH_PROPERTYGET)
        {
            if(pVarResult != NULL)
            {
                
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BOOL;
                V_BOOL(pVarResult) = true;
            }
        }
        
        if ( wFlags & DISPATCH_METHOD )
        {
            //arguments come in reverse order
            //for some reason
            CString cszArg1= pDispParams->rgvarg[4].bstrVal;
            int nArg2= pDispParams->rgvarg[3].intVal;
            int nArg3= pDispParams->rgvarg[2].intVal;
            int nArg4= pDispParams->rgvarg[1].intVal;
            int nArg5= pDispParams->rgvarg[0].intVal;
            
            pDlg->CB_ShowModelessDialog(cszArg1, nArg2,
            nArg3, nArg4, nArg5);
        }
        
    }
    
    if(dispIdMember == DISPID_CB_ShowModalDialog) 
    {
        if(wFlags & DISPATCH_PROPERTYGET)
        {
            if(pVarResult != NULL)
            {
                
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_BOOL;
                V_BOOL(pVarResult) = true;
            }
        }
        
        if ( wFlags & DISPATCH_METHOD )
        {
            //arguments come in reverse order
            //for some reason
            CString cszArg1= pDispParams->rgvarg[4].bstrVal;
            int nArg2= pDispParams->rgvarg[3].intVal;
            int nArg3= pDispParams->rgvarg[2].intVal;
            int nArg4= pDispParams->rgvarg[1].intVal;
            int nArg5= pDispParams->rgvarg[0].intVal;
            
            pDlg->CB_ShowModalDialog(cszArg1, nArg2,
            nArg3, nArg4, nArg5);
        }
        
    }

    return S_OK;
}
Now we just need to add all these functions to our CCustomBrowserDlg class. So go into the CustomBrowserDlg.h file and add the following public function declarations as shown below:
    void CB_ShowModelessDialog(CString cszURL, 
    int nLeft, int nTop, int nWidth, int nHeight);

    void CB_ShowModalDialog(CString cszURL, 
    int nLeft, int nTop, int nWidth, int nHeight);

    void CB_OpenWindow(CString cszURL,
     int nLeft, int nTop, int nWidth, int nHeight, int nResizable);

    void CB_CustomFunctionWithParams(CString cszString, int nNumber);

    void CB_CustomFunction();

    void CB_Close();

    BOOL CB_IsOurCustomBrowser();
Now go into the CustomBrowserDlg.cpp file and add the following functions as shown below:
Note: The functions shown below just show a message box with all the parameters passed in just for simplicity sake. In the demo project, there is actually code to open a window, modal dialog, and modeless dialog. I just didn't want to explain how to create windows, modal, and modeless dialog boxes, as it is out of scope for this article. Of course you can see how all this code actually works in the demo project.
 Collapse
void CCustomBrowserDlg::CB_Close()
{
    AfxMessageBox("Close the browser here or the current window");

    //This is one way you can determine whether or not
    //to close a dialog or the main application depending
    //on if you call the CB_Close method from an html page
    //in a dialog/window or from an html page in the main app
    
    //for example if you launch a modal dialog from your javascript code
    //and you want to have your own close button in your html page as
    //an alternative to using the x button, then you can just call
    //window.external.CB_Close(); rather than window.close(); and this
    //function will determine which window to close based on which
    //window is currently active using the code below.
    
    /*
    CWnd* pWnd = GetActiveWindow();

    if(pWnd == this)
    {
        
        EndDialog(0);
    }
    else
    {
        CDialog* pWin = (CDialog*)pWnd;
        pWin->EndDialog(1);
    }
    */
}

void CCustomBrowserDlg::CB_CustomFunction()
{

    AfxMessageBox("Do whatever you like here!");
}

void CCustomBrowserDlg::CB_CustomFunctionWithParams
                     (CString cszString, int nNumber)
{
    CString cszParameters;
    cszParameters.Format
      ("parameter 1: %s\nparameter 2:  %d", cszString, nNumber);
    AfxMessageBox(cszParameters);
}

void CCustomBrowserDlg::CB_OpenWindow(CString cszURL, 
      int nLeft, int nTop, int 
      nWidth, int nHeight, int nResizable)
{
    //you could launch a normal window from here
    //I won't show how, but it is pretty easy.
    //I just wanted to show you how to pass parameters
    CString cszParameters;
    cszParameters.Format("URL=%s LEFT=%d TOP=%d 
    WIDTH=%d HEIGHT=%d RESIZABLE=%d", 
    cszURL, nLeft, nTop, nWidth, nHeight, nResizable);

    AfxMessageBox(cszParameters);
}

void CCustomBrowserDlg::CB_ShowModalDialog(CString cszURL, 
                int nLeft, int nTop, 
                int nWidth, int nHeight)
{
    //you could launch a modal dialog from here
    //I won't show how, but it is pretty easy.
    //I just wanted to show you how to pass parameters
    CString cszParameters;
    cszParameters.Format("URL=%s LEFT=%d TOP=%d
    WIDTH=%d HEIGHT=%d RESIZABLE=%d", 
    cszURL, nLeft, nTop, nWidth, nHeight);

    AfxMessageBox(cszParameters);
}

void CCustomBrowserDlg::CB_ShowModelessDialog
        (CString cszURL, int nLeft, int nTop, 
        int nWidth, int nHeight)
{
    //you could launch a modeless dialog from here
    //I won't show how, but it is pretty easy.
    //I just wanted to show you how to pass parameters
    CString cszParameters;
    cszParameters.Format("URL=%s LEFT=%d TOP=%d
    WIDTH=%d HEIGHT=%d RESIZABLE=%d", 
    cszURL, nLeft, nTop, nWidth, nHeight);

    AfxMessageBox(cszParameters);
}
All of these functions that we have added to our CCustomBrowserDlg class are now accessible from JavaScript! as shown below. The code shown below is from the CustomTest.html file that is included in the sample project.


  STDMETHODIMP CMyBrowser::Exec( const GUID* pguidCmdGroup, DWORD nCmdID,
   DWORD nCmdexecopt, VARIANTARG* pvaIn, VARIANTARG* pvaOut )
{

HRESULT hr = S_OK;

if (pguidCmdGroup && IsEqualGUID(*pguidCmdGroup, CGID_DocHostCommandHandler))
   {



  switch (nCmdID)

  {



  case OLECMDID_SHOWSCRIPTERROR:

 {

    IHTMLDocument2*

   pDoc = NULL;

    IHTMLWindow2*


pWindow = NULL;

    IHTMLEventObj*

    pEventObj = NULL;

    BSTR



    rgwszNames[5] =







   {








 SysAllocString(L"errorLine"),








SysAllocString(L"errorCharacter"),








SysAllocString(L"errorCode"),








SysAllocString(L"errorMessage"),








SysAllocString(L"errorUrl")







  };

    DISPID



  rgDispIDs[5];

    VARIANT



 rgvaEventInfo[5];

    DISPPARAMS


   params;

    BOOL



    fContinueRunningScripts = true;

    int




i;


 params.cArgs = 0;

    params.cNamedArgs = 0;


 // Get the document that is currently being viewed.

    hr = pvaIn->punkVal->QueryInterface(IID_IHTMLDocument2, (void **) &pDoc);


   // Get document.parentWindow.

    hr = pDoc->get_parentWindow(&pWindow);

    pDoc->Release();

    // Get the window.event object.

    hr = pWindow->get_event(&pEventObj);

    // Get the error info from the window.event object.

    for (i = 0; i < 5; i++)


{


    // Get the property's dispID.


  hr = pEventObj->GetIDsOfNames(IID_NULL, &rgwszNames[i], 1,




 LOCALE_SYSTEM_DEFAULT, &rgDispIDs[i]);


  // Get the value of the property.


  hr = pEventObj->Invoke(rgDispIDs[i], IID_NULL,  LOCALE_SYSTEM_DEFAULT,




DISPATCH_PROPERTYGET, &params, &rgvaEventInfo[i],  NULL, NULL);


  SysFreeString(rgwszNames[i]);

    }


 // At this point, you would normally alert the user with


// the information about the error, which is now contained

    // in rgvaEventInfo[]. Or, you could just exit silently.


 (*pvaOut).vt = VT_BOOL;

    if (fContinueRunningScripts)

    {


  // Continue running scripts on the page.


  (*pvaOut).boolVal = VARIANT_TRUE;

    }

    else

    {


  // Stop running scripts on the page.


  (*pvaOut).boolVal = VARIANT_FALSE;


  }


break;

 }

 default:

    hr = OLECMDERR_E_NOTSUPPORTED;

    break;

 }
   }
   else
   {

 hr = OLECMDERR_E_UNKNOWNGROUP;
   }
   return (hr);
} 

#include "stdafx.h" 
#include <iostream> 
#include <sstream> 
using namespace std; 
#include <assert.h> 
#include <windows.h> 
#include <mshtml.h> 
#include <atlbase.h> 
#include <atlconv.h> 
#include "ftl.h" 
using namespace ftl; 
CComContext g_ComContext; 
CExceptionHandler<CConsoleProvider> g_ExceptionHandler; 
CMsgTracer<CConsoleProvider> log; 
void printElement(const CComPtr<IHTMLElement>& spElement, int nLevel) 
{   
	CComBSTR bstrTagName, bstrClassName, bstrID; 
	ComCheck(spElement->get_tagName(&bstrTagName));   
	ComCheck(spElement->get_className(&bstrClassName));  
	ComCheck(spElement->get_id(&bstrID));   
	USES_CONVERSION; 
	string strIndent(nLevel * 2, ' '),  
		strTagName(W2A(bstrTagName)), strClassName, strID; 
	if(bstrClassName) 
	{ 
		strClassName = " class=\""; 
		strClassName += W2A(bstrClassName); 
		strClassName += "\""; 
	} 
	else 
		strClassName = ""; 

	if(bstrID) 
	{ 
		strID = " id=\""; 
		strID += W2A(bstrID); 
		strID += "\""; 
	} 
	else 
		strID = ""; 
	CComPtr<IDispatch> spDispatch; 
	CComPtr<IHTMLElementCollection> spHTMLElementCollection; 
	ComCheck(spElement->get_children(&spDispatch)); 
	ComCheck(spDispatch.QueryInterface(&spHTMLElementCollection)); 
	long lLength = 0; 
	ComCheck(spHTMLElementCollection->get_length(&lLength)); 
	cout << strIndent << '<' << strTagName << strClassName << strID; 
	if(!lLength) 
	{    
		CComBSTR bstrInnerText; 
		ComCheck(spElement->get_innerText(&bstrInnerText)); 
		if(bstrInnerText) 
		{ 
			cout << '>' << endl  
				<< strIndent << "  " << W2A(bstrInnerText) << endl 
				<< strIndent << "</" << strTagName << '>' << endl; 
		} 
		else 
		{ 
			cout << "/>" << endl;       
		} 
	} 
	else 
	{  
		cout << '>' << endl; 
		CComVariant varName, varIndex; 
		CComPtr<IHTMLElement> spChildElement; 
		for(int i=0; i<lLength; i++, varName = varIndex = i) 
		{ 
			spDispatch.Release(); 
			ComCheck(spHTMLElementCollection->item(varName, varIndex, &spDispatch)); 

			spChildElement.Release(); 
			ComCheck(spDispatch.QueryInterface(&spChildElement)); 
			if(spChildElement) 
				printElement(spChildElement, nLevel+1); 
		}     
		cout << strIndent << "</" << strTagName << '>' << endl; 
	}   
} 
void print(const CComPtr<IMarkupContainer>& spMarkupContainer) 
{ 
	log << "-+ Enter print @ " << tmd::timestamp << " +-" << endl << endm; 
	CComPtr<IHTMLDocument2> spHTMLDocument2; 
	ComCheck(spMarkupContainer.QueryInterface(&spHTMLDocument2)); 
	log << "Query interface IHTMLDocument2 from IMarkupContainer OK!" << endl << 
		endm; 
	CComPtr<IHTMLElement> spBody; 
	ComCheck(spHTMLDocument2->get_body(&spBody)); 
	printElement(spBody, 0); 
	log << "-+ Leave print @ " << tmd::timestamp << " +-" << endl << endm; 
} 
void parse(const char *szFileName) 
{ 
	log << "-+ Enter parse @ " << tmd::timestamp << " +-" << endl << endm; 
	CComPtr<IHTMLDocument2> spHTMLDocument2; 
	ComCheck(spHTMLDocument2.CoCreateInstance(CLSID_HTMLDocument)); 
	log << "Create interface IHTMLDocument2 from CLSID_HTMLDocument OK!" << endl 
		<< endm; 
	CComPtr<IPersistStreamInit> spPersistStreamInit; 
	ComCheck(spHTMLDocument2.QueryInterface(&spPersistStreamInit)); 
	log << "Query interface IPersistStreamInit from IHTMLDocument2 OK!" << endl  
		<< endm; 
	ComCheck(spPersistStreamInit->InitNew()); 
	log << "Initialize interface IPersistStreamInit OK!" << endl << endm; 
	CComPtr<IMarkupServices> spMarkupServices; 
	ComCheck(spPersistStreamInit->QueryInterface(&spMarkupServices)); 
	log << "Query interface IMarkupServices from IPersistStreamInit OK!" << endl 
		<< endm; 
	CComPtr<IMarkupPointer> spMkStart, spMkFinish; 
	ComCheck(spMarkupServices->CreateMarkupPointer(&spMkStart)); 
	ComCheck(spMarkupServices->CreateMarkupPointer(&spMkFinish)); 
	log << "Create interface IMarkupPointer with IMarkupServices OK!" << endl << 
		endm; 
	ifstream is(szFileName); 
	stringstream ss; 
	ss << is.rdbuf(); 
	log << "Read the HTML from " << szFileName << " [size:" << ss.tellp() << "]  
		file OK!" << endl << endm; 
		CComPtr<IMarkupContainer> spMarkupContainer; 
	ComCheck(spMarkupServices->ParseString(CComBSTR(ss.str().c_str()), 0,  
		&spMarkupContainer, spMkStart, spMkFinish)); 
	log << "ParseString HTML from " << szFileName << " with IMarkupServices OK!" 
		<< endl << endm; 
	print(spMarkupContainer); 
	log << "-+ Leave parse @ " << tmd::timestamp << " +-" << endl << endm; 
}  
int main(int argc, char* argv[]) 
{ 
	log << "-= begin @ " << tmd::timestamp << " OK =-" << endl << endm; 
	if(argc == 1) 
	{ 
		cout << ExtractFileName(string(argv[0])) << " [html filename]" << endl; 
		return 1; 
	} 
	parse(argv[1]); 
	log << "-= end @ " << tmd::timestamp << " OK =-" << endl << endm; 
	return 0; 
} 



//�ڶԻ����ͷ�ļ��м��룺
#include "wininet.h"#include "UrlHist.h"#define SWEEP_BUFFER_SIZE 10000public:enum DEL_CACHE_TYPE //Ҫɾ�������͡�{File,//��ʾinternet��ʱ�ļ�Cookie //��ʾCookie};
//����ΪһЩ�������� ( ���������ľ���ʵ�ֲμ�Դ������.����ƪ�����ٸ��� )
BOOL DeleteUrlCache(DEL_CACHE_TYPE type);BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE, BOOL bWipeIndexDat = FALSE);//���һ��Ŀ¼BOOL IsWindowsNT();//�ж�ϵͳBOOL IsWindows2k();BOOL GetUserSid(PSID* ppSid);void GetSidString(PSID pSid, LPTSTR szBuffer);BOOL GetOldSD(HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD);BOOL CreateNewSD(PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl);BOOL RegSetPrivilege(HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive);BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile); 
//�������ǿ��Էֱ�ʵ��ÿ��������ܡ�

1�����IE��ʱ�ļ�

TCHAR szPath[MAX_PATH];
DeleteUrlCache(File);
if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_INTERNET_CACHE, FALSE))
{ //�õ���ʱĿ¼���������.
	EmptyDirectory(szPath);
}

���IE��ʱ�ļ�������һ��;����ֱ�ӵ���Wininet�������뿴�����������IE��ʱ�ļ��ĺ���

BOOL DelTempFiles() { BOOL bResult = FALSE; BOOL bDone = FALSE; LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL; DWORD dwTrySize, dwEntrySize = 4096; // start buffer size HANDLE hCacheDir = NULL; DWORD dwError = ERROR_INSUFFICIENT_BUFFER; do { switch (dwError) { // need a bigger buffer case ERROR_INSUFFICIENT_BUFFER: delete [] lpCacheEntry; lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize]; lpCacheEntry->dwStructSize = dwEntrySize; dwTrySize = dwEntrySize; BOOL bSuccess; if (hCacheDir == NULL) bSuccess = (hCacheDir = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwTrySize)) != NULL; else bSuccess = FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize); if (bSuccess) dwError = ERROR_SUCCESS; else { dwError = GetLastError(); dwEntrySize = dwTrySize; // use new size returned } break; // we are done case ERROR_NO_MORE_ITEMS: bDone = TRUE; bResult = TRUE; break; // we have got an entry case ERROR_SUCCESS: // don''''''''''''''''t delete cookie entry if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY)) DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName); // get ready for next entry dwTrySize = dwEntrySize; if (FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize)) dwError = ERROR_SUCCESS; else { dwError = GetLastError(); dwEntrySize = dwTrySize; // use new size returned } break; // unknown error default: bDone = TRUE; break; } if (bDone) { delete [] lpCacheEntry; if (hCacheDir) FindCloseUrlCache(hCacheDir); } } while (!bDone); return bResult;} 
2��Cookie�����


TCHAR szPath[MAX_PATH];DeleteUrlCache(Cookie);if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_COOKIES, FALSE)){//�õ�Ŀ¼������� EmptyDirectory(szPath);} 
	3���������ַ����ʷ��ַ�����

		SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\TypedURLs")); 
	4��������Զ������ʷ��¼

		CString sKey;DWORD dwRet;if (IsWindows2k() || IsWindowsNT())//���ж�ϵͳ{CString sBaseKey;SECURITY_DESCRIPTOR NewSD;BYTE* pOldSD;PACL pDacl = NULL;PSID pSid = NULL;TCHAR szSid[256];if (GetUserSid(&pSid)){//get the hiden key nameGetSidString(pSid, szSid);sKey = _T("Software\\Microsoft\\Protected Storage System Provider\\");sKey += szSid;//get old SDsBaseKey = sKey;GetOldSD(HKEY_CURRENT_USER, sBaseKey, &pOldSD);//set new SD and then clearif (CreateNewSD(pSid, &NewSD, &pDacl)){RegSetPrivilege(HKEY_CURRENT_USER, sKey, &NewSD, FALSE);sKey += _T("\\Data");RegSetPrivilege(HKEY_CURRENT_USER, sKey, &NewSD, FALSE);sKey += _T("\\e161255a-37c3-11d2-bcaa-00c04fd929db");RegSetPrivilege(HKEY_CURRENT_USER, sKey, &NewSD, TRUE);dwRet = SHDeleteKey(HKEY_CURRENT_USER, sKey);}if (pDacl != NULL)HeapFree(GetProcessHeap(), 0, pDacl);//restore old SDif (pOldSD){RegSetPrivilege(HKEY_CURRENT_USER, sBaseKey, (SECURITY_DESCRIPTOR*)pOldSD, FALSE);delete pOldSD;}}if (pSid)HeapFree(GetProcessHeap(), 0, pSid);}//win9xDWORD dwSize = MAX_PATH;TCHAR szUserName[MAX_PATH];GetUserName(szUserName, &dwSize);sKey = _T("Software\\Microsoft\\Protected Storage System Provider\\");sKey += szUserName;sKey += _T("\\Data\\e161255a-37c3-11d2-bcaa-00c04fd929db");dwRet = SHDeleteKey(HKEY_LOCAL_MACHINE, sKey);

		5������Զ�������ʷ��¼


		SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\IntelliForms")); 
	6�����ղؼ��е�����
		TCHAR szPath[MAX_PATH]; 
	if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_FAVORITES, FALSE))
	{ //�õ�Ŀ¼������� 
		EmptyDirectory(szPath);
	}

	7����RAS�Զ�������ʷ��¼

		SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\RAS Autodial\\Addresses")); 
	8����ϵͳ��ʱ�ļ���

		TCHAR szPath[MAX_PATH];if (GetTempPath(MAX_PATH, szPath))//�õ�ϵͳ��ʱĿ¼{ EmptyDirectory(szPath, TRUE);} 
		9����ջ���վ

		SHEmptyRecycleBin(NULL, NULL, 
		SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND); 
	10�����"����"�е��Զ�ƥ����ʷ��¼

		SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU")); 
	11����"�ĵ�"�е���ʷ��¼

		TCHAR szPath[MAX_PATH];if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_RECENT, FALSE)){ EmptyDirectory(szPath);} SHDeleteKey(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs")); 
	12������ϴε�½�û���¼


		SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), _T("DefaultUserName"));SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), _T("AltDefaultUserName"));SHDeleteValue(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Winlogon"), _T("DefaultUserName")); 
	13�����"�����ļ�"�Զ�ƥ����ʷ��¼


		SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Doc Find Spec MRU"));SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\ContainingTextMRU"));SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\FilesNamedMRU")); 
	14�����"���Ҽ����"�Զ�ƥ����ʷ��¼

		SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FindComputerMRU"));SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\ComputerNameMRU")); 
	15���������������ʷ��¼

		TCHAR szPath[MAX_PATH];if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_NETHOOD, FALSE)){ //�õ�Ŀ¼������� EmptyDirectory(szPath);} 
			16����Զ�̵�¼��ʷ��¼

				CString sKey;for (int i=1; i<=8; i++){ sKey.Format(_T("Machine%d"), i); SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Telnet"), sKey); sKey.Format(_T("Service%d"), i); SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Telnet"), sKey); sKey.Format(_T("TermType%d"), i); SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Telnet"), sKey);}SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Telnet"), _T("LastMachine"));SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Telnet"), _T("LastService"));SHDeleteValue(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Telnet"), _T("LastTermType")); 
			17���������ַ��ʷ��¼
				������������������������ַ��ʷ��¼
#include "SHLGUID.H"HRESULT ClearHistory() {HRESULT hr;CoInitialize(NULL);{ IUrlHistoryStg2* pUrlHistoryStg2 = NULL; hr= CoCreateInstance(CLSID_CUrlHistory,NULL,1, IID_IUrlHistoryStg2,(void**)&pUrlHistoryStg2); if (SUCCEEDED(hr)) { hr = pUrlHistoryStg2->ClearHistory(); pUrlHistoryStg2->Release(); }}CoUninitialize(); return hr;} 

				// ���������벻����
				// ��������ģ������������ܹ���.

				TCHAR szPath[MAX_PATH];GetWindowsDirectory(szPath, MAX_PATH);_tcscat(szPath, _T("\\History"));EmptyDirectory(szPath, FALSE, TRUE); if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_HISTORY, FALSE)){ EmptyDirectory(szPath, FALSE, TRUE);}