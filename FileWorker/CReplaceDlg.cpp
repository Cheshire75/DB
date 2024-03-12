// CReplaceDlg.cpp: 구현 파일
//

#include "pch.h"
#include "FileWorker.h"
#include "afxdialogex.h"
#include "CReplaceDlg.h"
#include "FileWorkerDlg.h"


// CReplaceDlg 대화 상자

IMPLEMENT_DYNAMIC(CReplaceDlg, CDialog)

CReplaceDlg::CReplaceDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_REPLACE, pParent)
	, findEdit(_T(""))
	, replaceEdit(_T(""))
	, parent(NULL)
	, strIndex(0)
{

}

CReplaceDlg::~CReplaceDlg()
{
}

void CReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIND, findEdit);
	DDX_Text(pDX, IDC_EDIT_REPLACE, replaceEdit);
}


BEGIN_MESSAGE_MAP(CReplaceDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE, &CReplaceDlg::OnBnClickedButtonReplace)
	ON_BN_CLICKED(IDC_BUTTON_cancle, &CReplaceDlg::OnBnClickedButtoncancle)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CReplaceDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CReplaceDlg 메시지 처리기


void CReplaceDlg::OnBnClickedButtonReplace()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString editedStr = ((CFileWorkerDlg*)GetParent())->strEdit;
	editedStr.Replace(findEdit, replaceEdit);
	((CFileWorkerDlg*)GetParent())->strEdit = editedStr;
	GetParent()->UpdateData(FALSE);
}


void CReplaceDlg::OnBnClickedButtoncancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CReplaceDlg::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strEdit = parent->strEdit;
	int startIndexOfTarget = strEdit.Find(findEdit, strIndex);
	int endIndexOfTarget = startIndexOfTarget + strlen(findEdit);
	if (startIndexOfTarget == -1 && strIndex == 0) {
		MessageBox("검색결과가 없습니다.");
	}
	else {
		if (startIndexOfTarget == -1) {
			MessageBox("더 이상 검색 결과가 없습니다. 처음부터 다시 검색을 실행합니다.");
			strIndex = 0;
			startIndexOfTarget = strEdit.Find(findEdit, strIndex);
			endIndexOfTarget = startIndexOfTarget + strlen(findEdit);
		}
		parent->mainEditorBox.SetFocus();
		parent->mainEditorBox.SetSel(startIndexOfTarget, endIndexOfTarget, TRUE);
		if (strIndex + 1 >= strlen(strEdit)) {
			strIndex = 0;
		}
		else {
			strIndex = startIndexOfTarget + 1;
		}
	}
}
