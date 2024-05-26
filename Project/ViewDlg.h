#pragma once
#include "afxdialogex.h"
#include "SelectQuery.h"


// ViewDlg 대화 상자

class ViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ViewDlg)

public:
	ViewDlg(SelectQuery* sParent, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	ViewDlg(ViewDlg* pparent, CWnd* pParent = nullptr);
	virtual ~ViewDlg();
	SelectQuery* sParent;
	ViewDlg* vParent;
	int level;
	CString tableName;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_View };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl View;
	CComboBox searchColumn;
	CEdit target;
	afx_msg void OnBnClickedSearch();
	CString viewColumn;
	afx_msg void OnNMDblclkListView(NMHDR* pNMHDR, LRESULT* pResult);
};
