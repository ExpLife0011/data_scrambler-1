private void Ocr()
{
    string datapath = System.Environment.CurrentDirectory + ��\\tessdata��; //����Ǳ���ģ����ǵ��ֿ���Ϣ�ʹ洢������
    tessnet2.Tesseract ocr = new tessnet2.Tesseract();
    ocr.Init(datapath, ��eng��, false);
    ocr.OcrDone = new tessnet2.Tesseract.OcrDoneHandler(Done);//ʹ��һ��Handler�ӹ����ʶ���Ĳ���
    ocr.DoOCR(getImage(), Rectangle.Empty);
}
void Done((List<tessnet2.Word> Words) {
    str = Words[0]; //�����str��ȫ�ֵġ�
}
��֤��ʶ������ˣ����������ǰ���������֤���������
public void write()
{
    mshtml.IHTMLDocument2 Doc;
    mshtml.IHTMLElement element;
    mshtml.IHTMLElementCollection all;
    SHDocVw.ShellWindows shellWindows = new SHDocVw.ShellWindowsClass();
    string filename;
    Bitmap Img = null;
    foreach(SHDocVw.InternetExplorer ie in shellWindows)
    {
        filename = Path.GetFileNameWithoutExtension(ie.FullName).ToLower();
        if (filename.Equals(��iexplore��))
        {
            Doc = ie.Document as mshtml.IHTMLDocument2;

            HTMLBody body = (HTMLBody)Doc.body;
            mshtml.IHTMLControlRange range = (IHTMLControlRange)body.createControlRange();
            if (Doc.domain == ��baidu.com��)
            {
                all = Doc.all;

                element = all.item(��captcha��, null) as mshtml.IHTMLElement;

                element.setAttribute(��Value��, str, 0);
            }
        }
    }
}

Private Function copyImageToClipBoard() As String
Dim doc As mshtml.IHTMLDocument2 = DirectCast(wc.Document.DomDocument, mshtml.IHTMLDocument2)
Dim imgRange As mshtml.IHTMLControlRange = DirectCast(DirectCast(doc.body, mshtml.HTMLBody).createControlRange(), mshtml.IHTMLControlRange)

For Each img As mshtml.IHTMLImgElement In doc.images
imgRange.add(DirectCast(img, mshtml.IHTMLControlElement))
If img.src.Contains("recaptcha/api/image?c=") Or img.src.Contains("seccode.php") Then
imgRange.execCommand("Copy", False, Nothing)
If isManual = True Then
Using bmp As Bitmap = DirectCast(Clipboard.GetDataObject().GetData(DataFormats.Bitmap), Bitmap)
Dim ofrmCap As New frmCaptcha(bmp)
ofrmCap.BringToFront()
ofrmCap.ShowDialog()
mCaptcha = vars.mCaptcha
vars.mCaptcha = Nothing
End Using
Else
bgwDecaptcher.RunWorkerAsync(Clipboard.GetDataObject().GetData(DataFormats.Bitmap))
End If
End If

Next
Return mCaptcha
End Function