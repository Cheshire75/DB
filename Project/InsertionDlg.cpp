// InsertionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "InsertionDlg.h"
#include "ProductEnroll.h"
#include "ReviewingDlg.h"



// InsertionDlg 대화 상자

IMPLEMENT_DYNAMIC(InsertionDlg, CDialogEx)

InsertionDlg::InsertionDlg(CProjectDlg* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Insertion, NULL),
	parent(pParent)
{

}

InsertionDlg::~InsertionDlg()
{
}


void InsertionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InsertionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Enroll, &InsertionDlg::OnBnClickedButtonEnroll)
	ON_BN_CLICKED(IDC_BUTTON_Review, &InsertionDlg::OnBnClickedButtonReview)
END_MESSAGE_MAP()


// InsertionDlg 메시지 처리기




void InsertionDlg::OnBnClickedButtonEnroll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ProductEnroll pro(parent);
	pro.DoModal();
}


void InsertionDlg::OnBnClickedButtonReview()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ReviewingDlg review(parent);
	review.DoModal();
}
