#include "stdafx.h"
#include "ImageProcessing.h"

#include "DlgCompositeOption.h"

#include "ImageProcessingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_PROCESS_COMPOSITE, &CImageProcessingDoc::OnProcessComposite)
END_MESSAGE_MAP()


// CImageProcessingDoc Contruction/Destuction

CImageProcessingDoc::CImageProcessingDoc()
{
	//// TODO: Add an one-time generating code here
	m_pImage = NULL;
}

CImageProcessingDoc::~CImageProcessingDoc()
{
	if (NULL != m_pImage)
		delete m_pImage;
}

BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: load imagefile // DONE
	m_pImage = new CxImage;
	m_pImage->Load(lpszPathName, FindType(lpszPathName));

	CalculateHistogram();

	return TRUE;
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}


// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//// TODO: Add a saving code here
	}
	else
	{
		//// TODO: Add a loading code here
	}
}


// CImageProcessingDoc diagnosis

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc command

CString CImageProcessingDoc::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}

CString CImageProcessingDoc::RemoveExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(0,i);
		}
	}
	return name;
}

int CImageProcessingDoc::FindType(const CString& ext)
{
	return CxImage::GetTypeIdFromName(ext);
}

void CImageProcessingDoc::CalculateHistogram()
{
	// TODO: Add a calculating histogram code here
	if (m_pImage) {
		// Histogram function, which is implemented in Cximage
		 //m_histogramMax = m_pImage->Histogram(m_histogramRed, m_histogramGreen, m_histogramBlue, m_histogramGray);

		 
		// 가짜코드
		for (int i = 0; i < 256; i++){
			m_histogramRed[i]   = rand() % 200;
			m_histogramGreen[i] = rand() % 200;
			m_histogramBlue[i]  = rand() % 200;
			m_histogramGray[i]  = rand() % 200;
		}

		m_histogramMax = 0;
		for (int i = 0; i < 256; i++){
			m_histogramMax = max(m_histogramMax, m_histogramRed[i]  );
			m_histogramMax = max(m_histogramMax, m_histogramGreen[i]);
			m_histogramMax = max(m_histogramMax, m_histogramBlue[i] );
			m_histogramMax = max(m_histogramMax, m_histogramGray[i] );
		}
		//////////////////////////////////////////////////////////////
	}
}

void CImageProcessingDoc::OnProcessComposite() // for term project #1
{
	if (m_pImage) {
		DlgCompositeOption dlg;

		if (dlg.DoModal() == IDOK) {
			int nOperatorID = dlg.GetCompositeOperatorID();
			CxImage* pSecondImage = dlg.GetSecondImage();

			DWORD width = m_pImage->GetWidth();
			DWORD height = m_pImage->GetHeight();

			RGBQUAD firstColor, secondColor, newColor;

			for (DWORD y = 0; y < height; y++) {
				for (DWORD x = 0; x < width; x++) {
					firstColor = m_pImage->GetPixelColor(x, y);
					secondColor = pSecondImage->GetPixelColor(x, y);

					switch (nOperatorID) {
					case 0: // +
						newColor.rgbRed = min(255, firstColor.rgbRed + secondColor.rgbRed);
						newColor.rgbGreen = min(255, firstColor.rgbGreen + secondColor.rgbGreen);
						newColor.rgbBlue = min(255, firstColor.rgbBlue + secondColor.rgbBlue);
						break;

					case 1: // - (neagtive prevented)
						newColor.rgbRed = max(0, firstColor.rgbRed - secondColor.rgbRed);
						newColor.rgbGreen = max(0, firstColor.rgbGreen - secondColor.rgbGreen);
						newColor.rgbBlue = max(0, firstColor.rgbBlue - secondColor.rgbBlue);
						break;

					case 2: // average	composite
						newColor.rgbRed = (firstColor.rgbRed + secondColor.rgbRed) / 2;
						newColor.rgbGreen = (firstColor.rgbGreen + secondColor.rgbGreen) / 2;
						newColor.rgbBlue = (firstColor.rgbBlue + secondColor.rgbBlue) / 2;
						break;

					default: // default
						newColor = firstColor;
						break;
					}

					newColor.rgbReserved = 0;
					m_pImage->SetPixelColor(x, y, newColor);
				}
			}
		}
	}

	CalculateHistogram();
	UpdateAllViews(NULL);
}