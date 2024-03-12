﻿
// FileWorkerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FileWorker.h"
#include "FileWorkerDlg.h"
#include "afxdialogex.h"
#include "CReplaceDlg.h"
#include "CDeleteDlg.h"
#include "CFindDlg.h"
#include "CInsertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileWorkerDlg 대화 상자



CFileWorkerDlg::CFileWorkerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEWORKER_DIALOG, pParent)
	, strEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileWorkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, strEdit);
	DDX_Control(pDX, IDC_EDIT, mainEditorBox);
}

BEGIN_MESSAGE_MAP(CFileWorkerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FileSave, &CFileWorkerDlg::OnBnClickedButtonFilesave)
	ON_BN_CLICKED(IDC_BUTTON_FileLoad, &CFileWorkerDlg::OnBnClickedButtonFileload)
	ON_BN_CLICKED(IDC_BUTTON_FilePrint, &CFileWorkerDlg::OnBnClickedButtonFileprint)
	ON_BN_CLICKED(IDC_BUTTON_FileUpdate, &CFileWorkerDlg::OnBnClickedButtonFileupdate)
	ON_BN_CLICKED(IDC_BUTTON_FileDelete, &CFileWorkerDlg::OnBnClickedButtonFiledelete)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CFileWorkerDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_FileFind, &CFileWorkerDlg::OnBnClickedButtonFilefind)
ON_BN_CLICKED(IDC_BUTTON_INSERT, &CFileWorkerDlg::OnBnClickedButtonInsert)
ON_EN_CHANGE(IDC_EDIT, &CFileWorkerDlg::OnChangeEdit)
END_MESSAGE_MAP()


// CFileWorkerDlg 메시지 처리기

BOOL CFileWorkerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	fileTitle = "";
	strEdit = "";

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFileWorkerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFileWorkerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFileWorkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileWorkerDlg::OnBnClickedButtonFileload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog DlgFileLoad(TRUE, "TXT", NULL, OFN_FILEMUSTEXIST, "*.txt||*.hwp||*.doc||모든파일(*.*)||", FALSE);
	
	if (DlgFileLoad.DoModal() == IDOK) {
		CString FileName;
		FileName = DlgFileLoad.GetFileName();
		CFile loadedFile;
		loadedFile.Open(FileName, CFile::modeRead);
		unsigned int textLength = loadedFile.GetLength();
		char* text = new char[textLength + 1];
		text[textLength] = { 0 };
		loadedFile.Read(text, textLength * sizeof(char));
		strEdit.Format("%s", text);
		loadedFile.Close();
		MessageBox("파일을 성공적으로 불러왔습니다.", "성공");
	}
	else {
		MessageBox("파일을 여는 중 취소 또는 오류가 발생했습니다.", "실패");
	}
}


void CFileWorkerDlg::OnBnClickedButtonFileprint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
}

void CFileWorkerDlg::OnBnClickedButtonFilesave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog DlgFileSave(FALSE, "txt", NULL, OFN_EXPLORER, "*.txt||*.hwp||*.doc||모든파일(*.*)||", FALSE);
	
	if (DlgFileSave.DoModal() == IDOK) {
		CFile MyFile;
		MyFile.Open(DlgFileSave.GetFileName(), CFile::modeCreate | CFile::modeWrite);
		MyFile.Write(strEdit, strlen(strEdit));
		MyFile.Close();
	}
	else {
		MessageBox("취소 되거나 오류가 발생했습니다.", "실패");
	}

}



void CFileWorkerDlg::OnBnClickedButtonFileupdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CReplaceDlg DlgReplace;
	DlgReplace.DoModal();
}




void CFileWorkerDlg::OnBnClickedButtonFiledelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDeleteDlg DlgDelete;
	DlgDelete.DoModal();
}


void CFileWorkerDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CFileWorkerDlg::OnBnClickedButtonFilefind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFindDlg* DlgFind = new CFindDlg;
	DlgFind->parent = this;
	DlgFind->Create(IDD_DIALOG_FIND);
	DlgFind->ShowWindow(SW_SHOW);
}



void CFileWorkerDlg::OnBnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CInsertDlg* DlgInsert = new CInsertDlg;
	DlgInsert->parent = this;

	DlgInsert->Create(IDD_DIALOG_INSERT);
	DlgInsert->ShowWindow(SW_SHOW);
}


void CFileWorkerDlg::OnChangeEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}