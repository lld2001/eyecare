// TipDialog.cpp : implementation file
//

#include "stdafx.h"
#include "eyecare.h"
#include "TipDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int tipTime;
/////////////////////////////////////////////////////////////////////////////
// CTipDialog dialog

int CTipDialog::TimerId = 1; 
CTipDialog::CTipDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTipDialog::IDD, pParent)
{

	//{{AFX_DATA_INIT(CTipDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTipDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTipDialog)
	DDX_Control(pDX, IDOK, m_bOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTipDialog, CDialog)
	//{{AFX_MSG_MAP(CTipDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipDialog message handlers
int Tip_Count=0;
void CTipDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(Tip_Count >= (tipTime-1)){
		Tip_Count=0;
		KillTimer(TimerId);
		DestroyWindow();
		return;
	}
	Tip_Count++;
	CString cs;
	cs.Format("还有%2d秒!", tipTime - Tip_Count);
	GetDlgItem(IDOK)->SetWindowText(cs);
	CDialog::OnTimer(nIDEvent);
}



BOOL CTipDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetTimer(TimerId,1000,NULL);
	CString cs;
	cs.Format("还有%2d秒!", tipTime);
	m_bOK.SetWindowText(cs);
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTipDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}
