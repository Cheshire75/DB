#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// ProductEnroll 대화 상자

class ProductEnroll : public CDialogEx
{
	DECLARE_DYNAMIC(ProductEnroll)

public:
	ProductEnroll(CProjectDlg* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ProductEnroll();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ProductEnroll };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox categoryCombo;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox typeCombo;
	CProjectDlg* parent;
	CComboBox cmpCombo;
	CEdit proNum;
	CEdit proName;
	CEdit proPrice;
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedOk();
};
