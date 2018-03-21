
// DrawView.cpp: CDrawView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CDrawView 생성/소멸

CDrawView::CDrawView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	

	strType = "DRAW TYPE : None";

}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDrawView 그리기

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	/*
	for (list<CRect>::iterator itor = m_ListRects.begin(); itor != m_ListRects.end();itor++)
	{
		int i = 0;
		CRect rc = (*itor);
		pDC->Rectangle(rc);
	}
	*/


	//line


	


	int nCnt = (int)m_ListRects.size();

	//str.Format("RectCnt : %d", nCnt);


	
	if (m_enDrawType == DT_RECTANGEL)
	{
		strType = "DRAW TYPE : Rectangle";

		for (list<CRect>::iterator itor = m_ListRects.begin(); itor != m_ListRects.end(); itor++)
		{

			CRect rc = (*itor);

			pDC->Rectangle(rc);

		
		}



	}
	
	
	if (m_enDrawType == DT_ELLIPSE)
	{
		strType = "DRAW TYPE : Ellipse";

		for (list<CRect>::iterator itor = m_ListEllipses.begin(); itor != m_ListEllipses.end(); itor++)
		{

			CRect ellipse = (*itor);

			pDC->Ellipse(ellipse);

		}



	}
	
	if(m_enDrawType == DT_LINE)
	{
		strType = "DRAW TYPE : LINE";


		for (list<CPoint>::iterator ptstart = m_ListStart.begin(); ptstart != m_ListStart.end(); ptstart++)
		{
			for (list<CPoint>::iterator ptstop = m_ListEnd.begin(); ptstop != m_ListEnd.end(); ptstop++)
			{
				CPoint start = *ptstart;
				CPoint stop = *ptstop;
				
				
				pDC->MoveTo(start);
				pDC->LineTo(stop);

			}
			

		}


	}



	pDC->TextOut(10,30,strType);


}


// CDrawView 인쇄

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDrawView 진단

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView 메시지 처리기


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	m_StLine.m_PtStart = point;
	m_StEllipse.m_PtStart = point;
	m_StRect.m_PtStart = point;
	
	


	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_StLine.m_PtEnd = point;
	m_StEllipse.m_PtEnd = point;
	m_StRect.m_PtEnd = point;


	
	//Rectangle
	CRect rc = { m_StRect.m_PtStart.x, m_StRect.m_PtStart.y, m_StRect.m_PtEnd.x, m_StRect.m_PtEnd.y };

	m_ListRects.push_back(rc);
	

	//Ellpise
	CRect ellipse = { m_StEllipse.m_PtStart.x, m_StEllipse.m_PtStart.y, m_StEllipse.m_PtEnd.x, m_StEllipse.m_PtEnd.y };

	m_ListEllipses.push_back(ellipse);
	

	//Line
	CPoint start = m_StLine.m_PtStart;
	CPoint end = m_StLine.m_PtEnd;

	m_ListStart.push_back(start);
	m_ListStart.push_back(end);



	
	
	Invalidate();



	CView::OnLButtonUp(nFlags, point);
}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);
}






void CDrawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nChar == VK_F1)
	{
		m_enDrawType = DT_RECTANGEL;

	}
	else if (nChar == VK_F2)
	{
		m_enDrawType = DT_ELLIPSE;
	}
	else if (nChar == VK_F3)
	{
		m_enDrawType = DT_LINE;

	}

	Invalidate();


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
