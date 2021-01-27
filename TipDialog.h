#if !defined(AFX_TIPDIALOG_H__600913E8_4BD9_426D_A55E_A7CDDACEF917__INCLUDED_)
#define AFX_TIPDIALOG_H__600913E8_4BD9_426D_A55E_A7CDDACEF917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipDialog dialog

class CTipDialog : public CDialog
{
// Construction
static int TimerId;
private:
	int m_Tip_Count;
public:
	CTipDialog(CWnd* pParent = NULL);   // standard constructor
	~CTipDialog(){

	};
// Dialog Data
	//{{AFX_DATA(CTipDialog)
	enum { IDD = IDD_TIP_DIALOG };
	CButton	m_bOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTipDialog)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPDIALOG_H__600913E8_4BD9_426D_A55E_A7CDDACEF917__INCLUDED_)
