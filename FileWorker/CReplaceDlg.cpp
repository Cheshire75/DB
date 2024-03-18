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
	, startIndexOfTarget(0)
	, endIndexOfTarget(0)
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
	ON_EN_CHANGE(IDC_EDIT_FIND, &CReplaceDlg::OnChangeEditFind)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CReplaceDlg::OnBnClickedButtonChange)
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
	this->DestroyWindow();
	delete(this);
}


void CReplaceDlg::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strEdit = parent->strEdit;
	startIndexOfTarget = strEdit.Find(findEdit, strIndex);
	endIndexOfTarget = startIndexOfTarget + strlen(findEdit);
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
		parent->mainEditorBox.SendMessage(EM_SCROLLCARET);
		if (strIndex + 1 >= strlen(strEdit)) {
			strIndex = 0;
		}
		else {
			strIndex = startIndexOfTarget + 1;
		}
	}
}


void CReplaceDlg::OnChangeEditFind()
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


void CReplaceDlg::OnBnClickedButtonChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (startIndexOfTarget == endIndexOfTarget) {
		MessageBox("다음 찾기를 눌러 수정할 단어를 선택해주세요");
	}
	else {
		CString strEdit = parent->strEdit;
		strEdit = strEdit.Left(startIndexOfTarget) + replaceEdit + strEdit.Mid(endIndexOfTarget);
		parent->strEdit = strEdit;
		parent->UpdateData(FALSE);
		parent->mainEditorBox.SetFocus();
		parent->mainEditorBox.SetSel(startIndexOfTarget, startIndexOfTarget + strlen(replaceEdit), TRUE);
		parent->mainEditorBox.SendMessage(EM_SCROLLCARET);
		strIndex--;
	}
}


//BOOL CReplaceDlg::PreTranslateMessage(MSG* pMsg)
//{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	if (pMsg->message == WM_KEYDOWN && pMsg->message == VK_RETURN)
//	{
//		return true;
//	}
//	return CDialog::PreTranslateMessage(pMsg);
//}
