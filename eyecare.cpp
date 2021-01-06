// eyecare.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "eyecare.h"
#include "eyecareDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEyecareApp

BEGIN_MESSAGE_MAP(CEyecareApp, CWinApp)
	//{{AFX_MSG_MAP(CEyecareApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEyecareApp construction

CEyecareApp::CEyecareApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
//	m_hwndDialog=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEyecareApp object

CEyecareApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEyecareApp initialization

BOOL CEyecareApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
#ifndef	_DEBUG
	CWnd *pWndPrev;//防止运行多个实例
	if((pWndPrev=CWnd::FindWindow("#32770",_T("Eyecare")))){
		CEyecareDlg *p = (CEyecareDlg*)pWndPrev;
		p->ShowDialog();
		TRACE("程序已经在运行");
		return FALSE;
	}
#endif
	

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CEyecareDlg dlg;
	m_pMainWnd = &dlg;
	//dlg.Create(CEyecareDlg::IDD);	
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
/*
BOOL CEyecareApp::PreTranslateMessage(MSG* pMsg) 
{
    if   (pMsg->message   == WM_KEYDOWN)   
	{   
		int   nVirtKey   =   (int)pMsg->wParam;           
		if   (nVirtKey==VK_RETURN)   
		{   
			//如果是回车在这里做你要做的事情,或者什么也不作   
			return   TRUE;   
		}   
		if   (nVirtKey==VK_ESCAPE)   
		{   
			//如果是ESC在这里做你要做的事情,或者什么也不作 
			TRACE("EEEEEEEEEESAPEEEEEEEEEE");
			return   TRUE;   
		}   
		
	}   
	
	return CWinApp::PreTranslateMessage(pMsg);
}
*/
/*
BOOL CEyecareApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
	// Check to see if the modal dialog box is up
	if (m_hwndDialog != NULL)
		if (lpMsg->hwnd == m_hwndDialog ||
			::IsChild(m_hwndDialog, lpMsg->hwnd))
		{
			// Use the global IsChild() function to get
			// messages destined for the dialog's controls
			// Perform customized message processing here
			if   (lpMsg->message   == WM_KEYDOWN)   
			{   
				int   nVirtKey   =   (int)lpMsg->wParam;           
				if   (nVirtKey==VK_RETURN)   
				{   
					//如果是回车在这里做你要做的事情,或者什么也不作   
					return   TRUE;   
				}   
				if   (nVirtKey==VK_ESCAPE)   
				{   
					//如果是ESC在这里做你要做的事情,或者什么也不作 
					return   TRUE;   
				}   
				
			}   
		}

	return CWinApp::ProcessMessageFilter(code, lpMsg);
}
*/