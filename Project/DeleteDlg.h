#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// DeleteDlg 대화 상자

class DeleteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteDlg)

public:
	DeleteDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	DeleteDlg(DeleteDlg* dParent);
	virtual ~DeleteDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Delete };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox combo;
	CProjectDlg* parent;
	afx_msg void OnCbnSelchangeCombo1();
	CString tableName;
	int itemCount;
	int columnCount;
	CListCtrl list;
	CString key;
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	DeleteDlg* dParent;
};
