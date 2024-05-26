#pragma once
#include "afxdialogex.h"
#include "InsertDlg.h"


// InsertTuple 대화 상자

class InsertTuple : public CDialogEx
{
	DECLARE_DYNAMIC(InsertTuple)

public:
	InsertTuple(CString attr, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InsertTuple();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Tuple };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit what;
	CString attribute;
	InsertDlg* parent;
	afx_msg void OnBnClickedOk();
};
