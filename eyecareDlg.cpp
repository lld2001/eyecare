// eyecareDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eyecare.h"
#include "eyecareDlg.h"
#include "winlockdll.h"
#include "facedlg.h"
#include "TipDialog.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CONFIG_FILE	".\\Eyecare.ini"
#define USE_FIELD	"USE_TIME"
#define REST_FIELD	"REST_TIME"
#define TIP_FIELD	"TIP_TIME"
#define EXIT_AFTER_REST	"EXIT_AFTER_REST"
#define AUTORUN	"AUTORUN"
#define VALUE	"VALUE"
#ifdef	_DEBUG
	#define USE_DOWN_TIME	1
#else
	#define USE_DOWN_TIME	1
#endif	
#define USE_UP_TIME		120

int useTime;
int restTime;
int tipTime;
time_t lastTime;
int exitAfterRest;
int runOnce;

CFaceDlg *lpFace=NULL;
BOOL isEnable = TRUE;
HINSTANCE hmod;//Dllģ��
/*
_AltTab2_Enable_Disable@8
_CtrlAltDel_Enable_Disable@4
_TaskManager_Enable_Disable@4
_TaskSwitching_Enable_Disable@4
_Taskbar_Show_Hide@4
*/
//TRUE���������   FALSE������
void Enable(BOOL bEnable){//
typedef int (WINAPI*  lpTaskbar_Show_Hide)(BOOL);
typedef int (WINAPI*  lpAltTab2_Enable_Disable)(HWND, BOOL);
typedef int (WINAPI*  lpTaskSwitching_Enable_Disable)(BOOL);
typedef int (WINAPI*  lpTaskManager_Enable_Disable)(BOOL);
typedef int (WINAPI*  lpCtrlAltDel_Enable_Disable)(BOOL);

#define LINK_EXPLICIT  //��ʽ����
#ifndef LINK_EXPLICIT
	Taskbar_Show_Hide(bEnable);
	AltTab2_Enable_Disable(::AfxGetApp()->GetMainWnd()->GetSafeHwnd(), bEnable);
	TaskSwitching_Enable_Disable(bEnable);
	TaskManager_Enable_Disable(bEnable);
	//CtrlAltDel_Enable_Disable(bEnable);
#else
	hmod=LoadLibrary("WinLockDll.dll");
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ))
	if(hmod == NULL){
		::AfxMessageBox(_T("WinLockDll.dll����ʧ��"), 0, MB_OK);
	}else{
		TRACE("_____________________\r\n");
		lpTaskbar_Show_Hide p1;
		p1=(lpTaskbar_Show_Hide)GetProcAddress(hmod,"_Taskbar_Show_Hide@4");
		if(p1 != (lpTaskbar_Show_Hide)NULL){
			TRACE("����������\r\n");
			p1(bEnable);
		}

		lpAltTab2_Enable_Disable p2;
		p2=(lpAltTab2_Enable_Disable)GetProcAddress(hmod, "_AltTab2_Enable_Disable@4");
		if(p2 != (lpAltTab2_Enable_Disable)NULL){
			TRACE("AltTab");
			p2(::AfxGetApp()->GetMainWnd()->GetSafeHwnd(), bEnable);
		}
		

		lpTaskSwitching_Enable_Disable p3;
		p3=(lpTaskSwitching_Enable_Disable)GetProcAddress(hmod, "_TaskSwitching_Enable_Disable@4");
		if(p3 != (lpTaskSwitching_Enable_Disable)NULL){
			TRACE("�����л�\r\n");
			p3(bEnable);
		}

		lpTaskManager_Enable_Disable p4;
		p4=(lpTaskManager_Enable_Disable)GetProcAddress(hmod,"_TaskManager_Enable_Disable@4");
		if(p4 != (lpTaskManager_Enable_Disable)NULL){
			TRACE("���������\r\n");
			p4(bEnable);
		}

		lpCtrlAltDel_Enable_Disable p5;
		p5=(lpCtrlAltDel_Enable_Disable)GetProcAddress(hmod,"_CtrlAltDel_Enable_Disable@4");
		if(p5 != (lpCtrlAltDel_Enable_Disable)NULL){
			TRACE("CtrlAltDel\r\n");
			p5(bEnable);
		}

	//	FreeLibrary(hmod);//Ϊʲô��ע�;Ͳ����ͷŰ���
		//����TimeProc1��FreeLibrary
	}
#endif
}

void CALLBACK TipTimerProc(//���Ѷ�ʱ���Ļص�����
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
   ){
	CWnd  *wnd=CWnd::FromHandle(hWnd);
	int WAIT_DIALOG_INIT=10000;
	switch(nMsg){
	case WM_TIMER:
		lpFace = new CFaceDlg();
		lpFace->Create(IDD_FACEDLG_DIALOG);
		::SetTimer(wnd->GetSafeHwnd(), USE_TIMER, 
			WAIT_DIALOG_INIT*MINUTE*SECOND, NULL);		
		Enable(FALSE);//����
		break;
	default:
		break;
	}
}
void CALLBACK TimerProc(//��Ϣ��ʱ���Ļص�����
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
   ){
		CWnd  *wnd=CWnd::FromHandle(hWnd);
		CTipDialog *dlg;
		//	CString c;
	switch(nMsg){
	case WM_TIMER:
		//c.Format("%d����������ԣ�������׼����",tipTime);
		//TRACE(c);
		::SetTimer(wnd->GetSafeHwnd(), USE_TIMER, 
			tipTime*SECOND, TipTimerProc);
		dlg= new CTipDialog();
		dlg->Create(IDD_TIP_DIALOG);
		dlg->ShowWindow(SW_SHOW);
		//::AfxMessageBox(c, MB_OK);
		break;
	default:
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEyecareDlg dialog

CEyecareDlg::CEyecareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEyecareDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEyecareDlg)
	m_Autorun = FALSE;
	//m_TipTime = _T("");
	m_strLastRest = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	//read config from .ini
	CString c;
	int use=::GetPrivateProfileInt(USE_FIELD, VALUE,45,CONFIG_FILE);
	useTime = use;
	int rest=::GetPrivateProfileInt(REST_FIELD, VALUE,3,CONFIG_FILE);
	restTime = rest;
	int tip=::GetPrivateProfileInt(TIP_FIELD, VALUE,10,CONFIG_FILE);
	tipTime = tip;
	int ex = ::GetPrivateProfileInt(EXIT_AFTER_REST, VALUE, 0, CONFIG_FILE);
	exitAfterRest = ex;
	runOnce = 0;
	//���������-once��ֻ����һ��
	CString s(AfxGetApp()->m_lpCmdLine);
	if(s == CString(_T("-once"))){
		runOnce = 1;
		//MessageBox(s, "ע��",MB_ICONASTERISK );
	}
}
CEyecareDlg::~CEyecareDlg(){
#ifdef	_DEBUG
	GlobalDeleteAtom(m_atomId);
#endif
}
void CEyecareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEyecareDlg)
	DDX_Control(pDX, IDC_COMBOUSE, m_USE);
	DDX_Control(pDX, IDC_COMBOREST, m_REST);
	DDX_Check(pDX, IDC_CHECKAUTORUN, m_Autorun);
	//DDX_CBString(pDX, IDC_COMBOTIP, m_TipTime);
	DDX_Control(pDX, IDC_COMBOTIP, m_TIP);
	DDX_Text(pDX, IDC_LASTREST, m_strLastRest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEyecareDlg, CDialog)
	//{{AFX_MSG_MAP(CEyecareDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_SETUP, OnSetup)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECKAUTORUN, OnCheckautorun)
	ON_CBN_EDITUPDATE(IDC_COMBOUSE, OnEditupdateCombouse)
	ON_CBN_SELCHANGE(IDC_COMBOUSE, OnSelchangeCombouse)
	ON_CBN_EDITCHANGE(IDC_COMBOREST, OnEditchangeComborest)
	ON_CBN_SELCHANGE(IDC_COMBOREST, OnSelchangeComborest)
	ON_CBN_EDITCHANGE(IDC_COMBOTIP, OnEditchangeCombotip)
	ON_CBN_SELCHANGE(IDC_COMBOTIP, OnSelchangeCombotip)
	ON_BN_CLICKED(IDC_OK, OnMyOK)
	ON_BN_CLICKED(IDC_CANCEL, OnMyCancel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRAY, OnTray)
	ON_COMMAND(ID_EXIT, OnExit)
#ifdef	_DEBUG
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
#endif
END_MESSAGE_MAP()

void CEyecareDlg::Show(){//��ʾ���ô���
	isParamChanged=FALSE;
	UpdateLastRest();
	ModifyStyle(WS_POPUP, WS_CAPTION);
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_TOPMOST);
	ShowWindow(SW_SHOW);
}
void CEyecareDlg::Hide(){//�������ô���
	ShowWindow(SW_HIDE);
	ModifyStyle(WS_CAPTION, WS_POPUP);
	ModifyStyleEx(WS_EX_TOPMOST, WS_EX_TOOLWINDOW);
}
/////////////////////////////////////////////////////////////////////////////
// CEyecareDlg message handlers
BOOL CEyecareDlg::OnInitDialog()
{	
	CDialog::OnInitDialog();

//	((CEyecareApp *)AfxGetApp())->m_hwndDialog=m_hWnd;
	Enable(TRUE);//��ʱ��ֹ�ϴ����������������

#ifdef	_DEBUG
	m_atomId=GlobalAddAtom("myHotKey");
	if(!RegisterHotKey(GetSafeHwnd(),
		m_atomId,MOD_ALT,'Q'))
		m_bRegister=FALSE;
	else
		m_bRegister=TRUE;
	TRACE("ע��ϵͳ�ȼ���[%d](0ʧ�ܣ�1�ɹ�)", m_bRegister);
#endif

	isParamChanged=FALSE;
	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	char tip[] ="�����������۾�!";
	NOTIFYICONDATA tnd;
	tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=this->m_hWnd;
	tnd.uID=IDR_MAINFRAME;
	tnd.uFlags=NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnd.uCallbackMessage = WM_TRAY;
	tnd.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(tnd.szTip, tip);
	Shell_NotifyIcon(NIM_ADD, &tnd);
	//��¼����ʱ��
	time(&lastTime);
	//�ö�
	//SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,0);

	ReadConfigFile();
	UpdateData(FALSE);
	UpdateLastRest();

	if(m_Autorun)
		WriteRegister();//��ʼʱдע���

	//���ö�ʱ��
	if(runOnce == 1){
		::SetTimer(GetSafeHwnd(), USE_TIMER, 
			1, TimerProc);	
	}else{
		::SetTimer(GetSafeHwnd(), USE_TIMER, 
			useTime*MINUTE*SECOND, TimerProc);	
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEyecareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CEyecareDlg::OnPaint() 
{	
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEyecareDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


LRESULT CEyecareDlg::OnTray(WPARAM wParam, LPARAM lParam){
	UINT uID = (UINT)wParam;
	UINT uMouseMsg = (UINT)lParam;
	CMenu menu, *pMenu;
	POINT pt;
	if(uMouseMsg == WM_RBUTTONDOWN){//�Ҽ�
		switch(uID){
		case IDR_MAINFRAME:
			GetCursorPos(&pt);
			menu.LoadMenu(IDR_BEGINMENU);
			pMenu= menu.GetSubMenu(0);
			ASSERT(pMenu !=0);
			pMenu->TrackPopupMenu(TPM_RIGHTBUTTON ,pt.x,pt.y,this, NULL);
			break;
		default:
			break;
		}
	}

	if(uMouseMsg == WM_LBUTTONDBLCLK){//˫��
		BOOL isVisible= IsWindowVisible();
		switch(uID){
		case IDR_MAINFRAME:
			if(isVisible == FALSE){
				Show();
			}else{
				Hide();
			}
		default:
			break;
		}
	}
	return 0;	
}

void CEyecareDlg::OnSetup(){
		ModifyStyle(WS_POPUP, WS_CAPTION);
		ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_TOPMOST);
		ShowWindow(SW_SHOW);	
}

void CEyecareDlg::OnExit(){
	::KillTimer(this->GetSafeHwnd(), USE_TIMER);
	Enable(TRUE);//�������

	NOTIFYICONDATA tnid;//ɾ��������ͼ��
	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	tnid.uID = IDR_MAINFRAME;
	Shell_NotifyIcon(NIM_DELETE, &tnid);
	AfxPostQuitMessage(0);
}
void CEyecareDlg::OnAbout(){
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

LRESULT CEyecareDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	static i = 2; //һ��paint������update
	if(message==WM_NCPAINT)
		if(i>0)
		{
			i--;
			this->ShowWindow(SW_HIDE);
		}
	return CDialog::DefWindowProc(message, wParam, lParam);
}
void CEyecareDlg::WriteRegister(){
		HKEY hKEY;
		char CurrentPath[MAX_PATH];
		GetModuleFileName(NULL,CurrentPath,MAX_PATH);//��ȡ����·��
		LPCSTR Rgspath="Software\\Microsoft\\Windows\\CurrentVersion\\Run";		
		long ret;
		//��ע���
		ret=RegOpenKeyEx(HKEY_LOCAL_MACHINE,Rgspath,0,KEY_WRITE,&hKEY);
		if(ret!=ERROR_SUCCESS)
		{
			RegCloseKey(hKEY);
			return;
		}
		//д��ע���
		const BYTE* file=(const BYTE*)CurrentPath;
		if(m_Autorun)
			ret=RegSetValueEx(hKEY,"Eyebaby",NULL,REG_SZ,file,MAX_PATH);
		else
			ret=RegSetValueEx(hKEY,"Eyebaby",NULL,REG_SZ,(const BYTE*)"",MAX_PATH);
		if(ret!=ERROR_SUCCESS)
		{
			RegCloseKey(hKEY);
			return;
		}
		//�ر�ע���
		RegCloseKey(hKEY);		
}
void CEyecareDlg::OnOK() 
{	
//	CDialog::OnOK();
}
void CEyecareDlg::OnCancel() 
{
//	CDialog::OnCancel();
}
void CEyecareDlg::OnClose() 
{	
	// TODO: Add your message handler code here and/or call default
	isParamChanged=FALSE;
	CString cs;
	cs.Format("%d",useTime);
	m_USE.SetWindowText(cs);
	cs.Format("%d", restTime);
	m_REST.SetWindowText(cs);
	UpdateData(FALSE);
	OnTray(IDR_MAINFRAME, WM_LBUTTONDBLCLK);
}

#define	USE_DEFAULT		1
#define REST_DEFAULT	1
#define TIP_DEFAULT		10	//��
void CEyecareDlg::ReadConfigFile(){
	CString c;
	int use=::GetPrivateProfileInt(USE_FIELD, VALUE,USE_DEFAULT,CONFIG_FILE);
	int rest=::GetPrivateProfileInt(REST_FIELD, VALUE,REST_DEFAULT,CONFIG_FILE);
	int tip=::GetPrivateProfileInt(TIP_FIELD, VALUE,TIP_DEFAULT,CONFIG_FILE);

	if(use >= USE_DOWN_TIME){//�Զ���ʹ��ʱ��
		c.Format("%d", use);
		m_USE.SetWindowText(c);

		useTime = use;
	}else{
		m_USE.SetCurSel(USE_DEFAULT);
		m_USE.GetWindowText(c);
		useTime = atoi(c);
	}

	if(rest>0 ){//�Զ�����Ϣʱ��
		c.Format("%d", rest);
		m_REST.SetWindowText(c);

		restTime = rest;
	}else{
		m_REST.SetCurSel(REST_DEFAULT);	
		m_REST.GetWindowText(c);
		restTime = atoi(c);	
	}
	
	if(tip>0){//�Զ�������ʱ��
		c.Format("%d", tip);
		m_TIP.SetWindowText(c);
		tipTime = tip;	
		
	}else{
		m_TIP.SetCurSel(TIP_DEFAULT);
		m_TIP.GetWindowText(c);
		tipTime = atoi(c);
	}
	c="";
	::GetPrivateProfileString(AUTORUN,"value","TRUE",c.GetBuffer(10),10,CONFIG_FILE);
	if(c=="TRUE"){
		m_Autorun=TRUE;
	}
}

void CEyecareDlg::WriteConfigFile(){
	CString cs;
	m_USE.GetWindowText(cs);//ʹ��ʱ��
	TRACE1("cs=%s",cs);
	::WritePrivateProfileString(USE_FIELD, VALUE,
		cs,CONFIG_FILE);
	useTime=atoi(cs);

	m_REST.GetWindowText(cs);//��Ϣʱ��
	::WritePrivateProfileString(REST_FIELD, VALUE,
		cs,CONFIG_FILE);
	restTime=atoi(cs);
	
	m_TIP.GetWindowText(cs);//����ʱ��
	::WritePrivateProfileString(TIP_FIELD, VALUE,
		cs,CONFIG_FILE);
	tipTime=atoi(cs);

	if(m_Autorun==TRUE)
		cs.Format("%s","TRUE");
	else
		cs.Format("%s","FALSE");
	::WritePrivateProfileString(AUTORUN, VALUE,
		cs,CONFIG_FILE); 

}

void CEyecareDlg::OnCheckautorun() 
{
	// TODO: Add your control notification handler code here
	m_Autorun = !m_Autorun;
	UpdateData(FALSE);
	isParamChanged=TRUE;	
}
void CEyecareDlg::UpdateLastRest(){
	CString cs;
	time_t now;
	time(&now);
	long usedTime =static_cast<long>(difftime(now, lastTime));
	usedTime /= 60;//�� TO ��
	cs.Format("%5d����", usedTime);
	m_strLastRest=cs;
	UpdateData(FALSE);
}

#ifdef _DEBUG
void CEyecareDlg::OnHotKey(WPARAM wParam,LPARAM lParam){
	if(m_atomId==wParam)//�ȼ��˳�����
		OnExit();
}
#endif

void CEyecareDlg::OnEditupdateCombouse() 
{
	// TODO: Add your control notification handler code here
	isParamChanged=TRUE;	
	TRACE("ʹ��ʱ��ı�OnEditupdateCombouse\r\n");
}

void CEyecareDlg::OnSelchangeCombouse() 
{
	// TODO: Add your control notification handler code here
	isParamChanged=TRUE;	
	TRACE("ʹ��ʱ��ı�OnSelchangeCombouse\r\n");	
}

void CEyecareDlg::OnEditchangeComborest() 
{
	// TODO: Add your control notification handler code here
	isParamChanged=TRUE;	
	TRACE("��Ϣʱ��ı�OnEditchangeComborest\r\n");	
}

void CEyecareDlg::OnSelchangeComborest() 
{
	// TODO: Add your control notification handler code here
	isParamChanged=TRUE;	
	TRACE("��Ϣʱ��ı�OnSelchangeComborest\r\n");		
}


void CEyecareDlg::OnEditchangeCombotip() 
{
	// TODO: Add your control notification handler code here
	isParamChanged=TRUE;	
}

void CEyecareDlg::OnSelchangeCombotip() 
{
	// TODO: Add your control notification handler code here
	isParamChanged=TRUE;	
}
void CEyecareDlg::ShowDialog(){
	OnTray(IDR_MAINFRAME, WM_LBUTTONDBLCLK);	
}

void CEyecareDlg::OnMyOK() 
{
	UpdateData(TRUE);
	
	WriteRegister();
	if(isParamChanged){
		CString cs;
		int temp1, temp2;
		m_USE.GetWindowText(cs);
		temp1=atoi(cs);
		if(temp1<USE_DOWN_TIME || temp1 >USE_UP_TIME){
			cs.Format("Ϊ�˸��õ���Ϣ�۾���\r\nֻ�����[ʹ��ʱ��]������"
				"%d-%d����֮�䣡",USE_DOWN_TIME,USE_UP_TIME);
			MessageBox(cs, "ע��",MB_ICONASTERISK );
			return;
		}
		m_REST.GetWindowText(cs);
		temp2=atoi(cs);
		if(temp2 <= 0){
			MessageBox("��Ϣʱ�������� 0��",
				"ע��",MB_ICONASTERISK);
			return;		
		}
		if(temp1 < temp2){
			MessageBox("[ʹ��ʱ��] ������� [��Ϣʱ��]��",
				"ע��",MB_ICONASTERISK);
			return;		
		}
		m_TIP.GetWindowText(cs);
		temp2= atoi(cs);
		if(temp2 <= 0){
			MessageBox("����ʱ�������� 0��",
				"ע��",MB_ICONASTERISK);
			return;		
		}			
		isParamChanged = FALSE;
		MessageBox("���óɹ����µ��������������á�",
			"�ɹ�",MB_ICONASTERISK);
		WriteConfigFile();
	}
	OnClose();	
}

void CEyecareDlg::OnMyCancel() 
{
	OnClose();	
}

void CEyecareDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
//	((CEyecareApp *)AfxGetApp())->m_hwndDialog=NULL;

}


