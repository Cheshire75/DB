// CDeleteDlg.cpp: 구현 파일
//

#include "pch.h"
#include "FileWorker.h"
#include "afxdialogex.h"
#include "CDeleteDlg.h"
#include "FileWorkerDlg.h"


// CDeleteDlg 대화 상자

IMPLEMENT_DYNAMIC(CDeleteDlg, CDialog)

CDeleteDlg::CDeleteDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_DELETE, pParent)
	, deleteEdit(_T(""))
{

}

CDeleteDlg::~CDeleteDlg()
{
}

void CDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELETE, deleteEdit);
}


BEGIN_MESSAGE_MAP(CDeleteDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDeleteDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_cancle, &CDeleteDlg::OnBnClickedButtoncancle)
END_MESSAGE_MAP()


// CDeleteDlg 메시지 처리기


void CDeleteDlg::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString editedStr = ((CFileWorkerDlg*)GetParent())->strEdit;
	editedStr.Replace(deleteEdit, "");
	((CFileWorkerDlg*)GetParent())->strEdit = editedStr;
	GetParent()->UpdateData(FALSE);
}


void CDeleteDlg::OnBnClickedButtoncancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
