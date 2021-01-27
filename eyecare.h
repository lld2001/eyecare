// eyecare.h : main header file for the EYECARE application
//

#if !defined(AFX_EYECARE_H__95AD8675_2EE7_434E_8A90_82EB54453C16__INCLUDED_)
#define AFX_EYECARE_H__95AD8675_2EE7_434E_8A90_82EB54453C16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#ifdef _DEBUG
	#define MINUTE	60//µ÷ÊÔÊ±
	#define	SECOND	50
#else
	#define MINUTE	60
	#define	SECOND	1000
#endif


/////////////////////////////////////////////////////////////////////////////
// CEyecareApp:
// See eyecare.cpp for the implementation of this class
//

class CEyecareApp : public CWinApp
{


public:
//	HWND m_hwndDialog;
	CEyecareApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEyecareApp)
	public:
	virtual BOOL InitInstance();
	//virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEyecareApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EYECARE_H__95AD8675_2EE7_434E_8A90_82EB54453C16__INCLUDED_)
