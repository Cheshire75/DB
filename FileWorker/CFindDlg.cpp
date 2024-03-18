// CFindDlg.cpp: 구현 파일
//

#include "pch.h"
#include "FileWorker.h"
#include "afxdialogex.h"
#include "CFindDlg.h"
#include "FileWorkerDlg.h"


// CFindDlg 대화 상자

IMPLEMENT_DYNAMIC(CFindDlg, CDialog)

CFindDlg::CFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_FIND, pParent)
	, findEdit(_T(""))
	, strIndex(0)
	, parent(NULL)
{
}

CFindDlg::~CFindDlg()
{
}

void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIND, findEdit);
}


BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_cancle, &CFindDlg::OnBnClickedButtoncancle)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CFindDlg::OnBnClickedButtonFind)
	ON_EN_CHANGE(IDC_EDIT_FIND, &CFindDlg::OnChangeEditFind)
END_MESSAGE_MAP()


// CFindDlg 메시지 처리기


void CFindDlg::OnBnClickedButtoncancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->DestroyWindow();
	delete(this);
}


void CFindDlg::OnBnClickedButtonFind()
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
		parent->mainEditorBox.SendMessage(EM_SCROLLCARET);
		if (strIndex + 1 >= strlen(strEdit)) {
			strIndex = 0;
		}
		else {
			strIndex=startIndexOfTarget+1;
		}
	}
}


void CFindDlg::OnChangeEditFind()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	strIndex = 0;
}


//BOOL CFindDlg::PreTranslateMessage(MSG* pMsg)
//{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	if (pMsg->message == WM_KEYDOWN && pMsg->message == VK_RETURN)
//	{
//		return true;
//	}
//	return CDialog::PreTranslateMessage(pMsg);
//}
