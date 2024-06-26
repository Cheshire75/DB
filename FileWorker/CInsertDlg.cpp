﻿// CInsertDlg.cpp: 구현 파일
//

#include "pch.h"
#include "FileWorker.h"
#include "afxdialogex.h"
#include "CInsertDlg.h"
#include "FileWorkerDlg.h"


// CInsertDlg 대화 상자

IMPLEMENT_DYNAMIC(CInsertDlg, CDialog)

CInsertDlg::CInsertDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_INSERT, pParent)
	, insertEdit(_T(""))
{

}

CInsertDlg::~CInsertDlg()
{
}

void CInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INSERT, insertEdit);
}


BEGIN_MESSAGE_MAP(CInsertDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CInsertDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_cancle, &CInsertDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CInsertDlg 메시지 처리기



void CInsertDlg::OnBnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*CString strEdit = parent->strEdit;
	UpdateData(TRUE);
	strEdit.Insert(strEdit.GetLength(), insertEdit);


	parent->strEdit = strEdit;
	parent->UpdateData(FALSE);*/

	UpdateData(TRUE);
	int i = parent->mainEditorBox.GetWindowTextLengthA();
	parent->mainEditorBox.SetSel(i, i);
	parent->mainEditorBox.ReplaceSel(insertEdit+"\r\n");
	parent->UpdateData(FALSE);
	int nLineCount = parent->mainEditorBox.GetLineCount();
	parent->mainEditorBox.LineScroll(nLineCount);
}


void CInsertDlg::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->DestroyWindow();
	delete(this);
}


//BOOL CInsertDlg::PreTranslateMessage(MSG* pMsg)
//{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	if (pMsg->message == WM_KEYDOWN && pMsg->message == VK_RETURN)
//	{
//		return true;
//	}
//	return CDialog::PreTranslateMessage(pMsg);
//}
