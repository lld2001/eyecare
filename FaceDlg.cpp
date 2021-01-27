// FaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eyecare.h"
#include "FaceDlg.h"
#include "eyecaredlg.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CFaceDlg dialog

int CFaceDlg::TimerId = 1; 
CFaceDlg::CFaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFaceDlg::IDD, pParent),m_rcClip(0,0,0,0)
{
	//{{AFX_DATA_INIT(CFaceDlg)
	//}}AFX_DATA_INIT
	m_bCenterText=FALSE;
}


void CFaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaceDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFaceDlg, CDialog)
	//{{AFX_MSG_MAP(CFaceDlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDlg message handlers


BOOL CFaceDlg::OnInitDialog() 
{	
	CDialog::OnInitDialog();
	m_BitmapBack.LoadBitmap(IDB_BACK);
	m_font.CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, 
		PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "����" );
	m_nCount = restTime * MINUTE;

LONG lStyle=::GetWindowLong(this->m_hWnd,GWL_STYLE);
lStyle &= ~WS_CAPTION;
::SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
#ifdef _DEBUG
//	SetWindowPos(&wndTop,0, 0, 400, 300, SWP_SHOWWINDOW);
	SetWindowPos(&wndTop,0, 0, cx, cy, SWP_SHOWWINDOW);
#else
	SetWindowPos(&wndTop,0, 0, cx, cy, SWP_SHOWWINDOW);
	ShowWindow(SW_SHOWMAXIMIZED);
	//�ö�
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
#endif
	ShowCursor(FALSE);
	SetTimer(TimerId, SECOND, NULL);
	
	Enable(FALSE);//����
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CFaceDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor){
 //Draw red text for all edit controls .
	pDC->SetBkColor(RGB(0,255,0));
	pDC->SetTextColor(RGB(255,0,0));

// 	if (nCtlColor==CTLCOLOR_STATIC)
// 	{
// 		LOGBRUSH lb={BS_HOLLOW,0,0};
// 		CBrush br;
// 		br.CreateBrushIndirect(&lb);
// 		pDC->SetBkMode(TRANSPARENT);
// 		return br;
// 	}

	return NULL;
}


void CFaceDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	Enable(TRUE);//�������
	ShowCursor(TRUE);


	time(&lastTime);
	CEyecareDlg *main=(CEyecareDlg*)::AfxGetApp()->GetMainWnd();
	main->UpdateLastRest();
	
	//��Ϣ�����˳�
	if((exitAfterRest == 1) || (runOnce == 1)){
		TRACE("exit app \n");
		::PostMessage(::AfxGetApp()->GetMainWnd()->GetSafeHwnd(), WM_DESTROY, 0, 0);
		//PostQuitMessage(0);
	}

	CDialog::PostNcDestroy();
	delete this;
}

void CFaceDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bt;
	CRect rectClient;
	GetClientRect(rectClient);
	bt.CreateCompatibleBitmap(&dc,rectClient.right,rectClient.bottom);
	memDC.SelectObject(&bt);
	CBrush brush;
	brush.CreatePatternBrush(&m_BitmapBack);  
	memDC.SelectObject(&brush);
	CRect rcClip;
	dc.GetClipBox(rcClip);
	memDC.FillRect(rcClip,&brush);

	CFont*pFont=memDC.SelectObject(&m_font);
	memDC.SetBkMode(TRANSPARENT);
	CSize size=memDC.GetTextExtent(m_strOutText);
	memDC.TextOut((rectClient.right-size.cx)/2,(rectClient.bottom-size.cy)/2,
		m_strOutText);
	memDC.SetBkMode(OPAQUE);
	memDC.SelectObject(pFont);
	dc.BitBlt(0,0,rectClient.Width(),rectClient.Height(),&memDC,0,0,SRCCOPY);
}

void CFaceDlg::OnTimer(UINT nIDEvent) 
{	
	TRACE1( "���� = %d\n", m_nCount );
	if(m_nCount < 0){
		KillTimer(TimerId);
		DestroyWindow();
		return;
	}else{
		m_strOutText.Format("��Ϣ����ʱ��%2d��%2d��",m_nCount / 60, m_nCount % 60);
		Invalidate(FALSE);
		UpdateWindow();		
	}
	m_nCount--;

	CDialog::OnTimer(nIDEvent);
}

BOOL CFaceDlg::PreTranslateMessage(MSG* pMsg) 
{
	/*
	����control+q
	if(pMsg->wParam=='Q'&&(GetKeyState(VK_CONTROL))) 
	*/
	if   (pMsg->message   == WM_KEYDOWN)   
	{   
		TRACE("ֱ�ӷ���CFaceDlg::PreTranslateMessage");
		return   TRUE;   

		int   nVirtKey   =   (int)pMsg->wParam;           
		if   (nVirtKey==VK_RETURN)   
		{   
			//����ǻس�����������Ҫ��������,����ʲôҲ����   
			return   TRUE;   
		}   
		if   (nVirtKey==VK_ESCAPE)   
		{   
			//�����ESC����������Ҫ��������,����ʲôҲ���� 
			TRACE("CFaceDlg::PreTranslateMessageVK_ESCAPE");
			return   TRUE;   
		}   
		
	}   	
	if(pMsg->message==WM_SYSKEYDOWN) {
		TRACE("CFaceDlg::PreTranslateMessageVK_F4%d",pMsg->message);	
		int nVKey = (int)pMsg->wParam;
		if(nVKey == VK_F4)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
