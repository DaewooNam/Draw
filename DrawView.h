
// DrawView.h: CDrawView 클래스의 인터페이스
//

#pragma once
enum DRAWTYPE {DT_RECTANGEL, DT_ELLIPSE, DT_LINE};

struct st_Line
{
	CPoint start;
	CPoint end;

};

struct st_Rect
{
	CPoint start;
	CPoint end;

};

struct st_Ellipse
{
	CPoint start;
	CPoint end;

};


class CDrawView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// 특성입니다.
public:
	CDrawDoc* GetDocument() const;

// 작업입니다.
public:

	list<CRect>  m_ListRects;
	list<CRect>  m_ListEllipses;
	list<CRect>  m_ListLine;

	
	st_Line		 m_StLine;
	st_Ellipse	 m_StEllipse;
	st_Rect		 m_StRect;
	
	DRAWTYPE	 m_enDrawType;
	CString		 strType;




// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // DrawView.cpp의 디버그 버전
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }
#endif

