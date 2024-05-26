#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// InsertionDlg 대화 상자

class InsertionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InsertionDlg)

public:
	InsertionDlg(CProjectDlg* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InsertionDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Insertion };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEnroll();
	afx_msg void OnClickedButtonEnroll();
	CProjectDlg* parent;
	afx_msg void OnBnClickedButtonReview();
};
