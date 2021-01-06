
// eyecareDlg.h : header file
//

#if !defined(AFX_EYECAREDLG_H__103209EF_40C6_4864_9F05_8D00AE5A5730__INCLUDED_)
#define AFX_EYECAREDLG_H__103209EF_40C6_4864_9F05_8D00AE5A5730__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_TRAY (WM_USER+100)
/////////////////////////////////////////////////////////////////////////////
// CEyecareDlg dialog

class CEyecareDlg : public CDialog
{
// Construction
public:
	CEyecareDlg(CWnd* pParent = NULL);	// standard constructor
	~CEyecareDlg();
//#ifdef _DUBUG	//ÏµÍ³ÈÈ¼ü
public:
	ATOM m_atomId;
	BOOL m_bRegister;
//#endif
public:
	void ShowDialog();
	void UpdateLastRest();
private:
	void Show();
	void Hide();
	void ReadConfigFile();
	void WriteConfigFile();
	void WriteRegister();
private:
	BOOL isParamChanged;
// Dialog Data
	//{{AFX_DATA(CEyecareDlg)
	enum { IDD = IDD_EYECARE_DIALOG };
	CComboBox	m_USE;
	CComboBox	m_REST;
	BOOL	m_Autorun;
	CComboBox m_TIP;
	//CString	m_TipTime;
	CString	m_strLastRest;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEyecareDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEyecareDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetup();
	afx_msg void OnAbout();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnCheckautorun();
	afx_msg void OnEditupdateCombouse();
	afx_msg void OnSelchangeCombouse();
	afx_msg void OnEditchangeComborest();
	afx_msg void OnSelchangeComborest();
	afx_msg void OnEditchangeCombotip();
	afx_msg void OnSelchangeCombotip();
	afx_msg void OnMyOK();
	afx_msg void OnMyCancel();
	//}}AFX_MSG
	LRESULT OnTray(WPARAM wParam, LPARAM lParam);
	afx_msg void OnExit();
#ifdef _DEBUG
	afx_msg void OnHotKey(WPARAM wParam, LPARAM lParam);
#endif
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EYECAREDLG_H__103209EF_40C6_4864_9F05_8D00AE5A5730__INCLUDED_)
