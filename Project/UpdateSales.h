#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// UpdateSales 대화 상자

class UpdateSales : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateSales)

public:
	UpdateSales(CProjectDlg* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UpdateSales();
	CProjectDlg* parent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Sales };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox proCombo;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
};
