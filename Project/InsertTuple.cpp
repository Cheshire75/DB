// InsertTuple.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "InsertTuple.h"
#include "resource.h"


// InsertTuple 대화 상자

IMPLEMENT_DYNAMIC(InsertTuple, CDialogEx)

InsertTuple::InsertTuple(CString attr, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Tuple, pParent)
	, attribute(attr)
{

}

InsertTuple::~InsertTuple()
{
}

void InsertTuple::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, what);
	DDX_Text(pDX, IDC_TEXT, attribute);
}


BEGIN_MESSAGE_MAP(InsertTuple, CDialogEx)
	ON_BN_CLICKED(IDOK, &InsertTuple::OnBnClickedOk)
END_MESSAGE_MAP()


// InsertTuple 메시지 처리기

BOOL InsertTuple::OnInitDialog() {
	CDialogEx::OnInitDialog();

	SetDlgItemTextA(IDC_TEXT, attribute);
	return TRUE;
}

void InsertTuple::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemTextA(IDC_EDIT1, parent->attrInput);
	
	CDialogEx::OnOK();
}
