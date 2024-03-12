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
	, strIndex(0)
	, startIndexOfTarget(0)
	, endIndexOfTarget(0)
	, parent(NULL)
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
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDeleteDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDeleteDlg::OnBnClickedButtonDel)
	ON_EN_CHANGE(IDC_EDIT_DELETE, &CDeleteDlg::OnChangeEditDelete)
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
	this->DestroyWindow();
	delete(this);
}


void CDeleteDlg::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strEdit = parent->strEdit;
	startIndexOfTarget = strEdit.Find(deleteEdit, strIndex);
	endIndexOfTarget = startIndexOfTarget + strlen(deleteEdit);
	if (startIndexOfTarget == -1 && strIndex == 0) {
		MessageBox("검색결과가 없습니다.");
	}
	else {
		if (startIndexOfTarget == -1) {
			MessageBox("더 이상 검색 결과가 없습니다. 처음부터 다시 검색을 실행합니다.");
			strIndex = 0;
			startIndexOfTarget = strEdit.Find(deleteEdit, strIndex);
			endIndexOfTarget = startIndexOfTarget + strlen(deleteEdit);
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


void CDeleteDlg::OnBnClickedButtonDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strEdit = parent->strEdit;
	if (startIndexOfTarget == endIndexOfTarget) {
		MessageBox("다음 찾기를 눌러 지울 단어를 선택해주세요");
	}
	else {
		strEdit = strEdit.Left(startIndexOfTarget) + strEdit.Mid(endIndexOfTarget);
		parent->strEdit = strEdit;
		parent->UpdateData(FALSE);
		if(strIndex>0) strIndex--;
	}
}


void CDeleteDlg::OnChangeEditDelete()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	strIndex = 0;
	startIndexOfTarget = 0;
	endIndexOfTarget = 0;
}
