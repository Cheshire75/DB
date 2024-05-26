#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// ReviewingDlg 대화 상자

class ReviewingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ReviewingDlg)

public:
	ReviewingDlg(CProjectDlg* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ReviewingDlg();
	CProjectDlg* parent;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Review };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox proName;
	afx_msg void OnBnClickedOk();
	CComboBox scoreCombo;
	afx_msg void OnCbnSelchangeCombo1();
};
