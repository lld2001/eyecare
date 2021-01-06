#if !defined(AFX_FACEDLG_H__757A8CA5_D396_4797_8159_DDD15A132D91__INCLUDED_)
#define AFX_FACEDLG_H__757A8CA5_D396_4797_8159_DDD15A132D91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FaceDlg.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CFaceDlg dialog

class CFaceDlg : public CDialog
{
// Construction
public:
	CFaceDlg(CWnd* pParent = NULL);   // standard constructor

private: int m_nCount;
	CFont m_font;
	CRect m_rcClip;
	CString m_strOutText;
	CBitmap m_BitmapBack;
	BOOL m_bCenterText;
public:
// Dialog Data
	//{{AFX_DATA(CFaceDlg)
	enum { IDD = IDD_FACEDLG_DIALOG };
	CStatic	m_Time;
	//}}AFX_DATA

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_FACEDLG_H__757A8CA5_D396_4797_8159_DDD15A132D91__INCLUDED_)
