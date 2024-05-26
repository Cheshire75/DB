#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// InsertDlg 대화 상자

class InsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InsertDlg)

public:
	InsertDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InsertDlg();
	CProjectDlg* parent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Insert };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox table;
	CListCtrl inserting;
	afx_msg void OnCbnSelchangeCombo1();
	int columnCount;
	CString tableName;
	int tupleCount;
	afx_msg void OnBnClickedaddtuple();
	CString attrInput;
	afx_msg void OnBnClickeddeltuple();
	afx_msg void OnBnClickedOk();
};
