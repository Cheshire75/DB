#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// SelectQuery 대화 상자

class SelectQuery : public CDialogEx
{
	DECLARE_DYNAMIC(SelectQuery)

public:
	SelectQuery(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SelectQuery();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Select };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL SelectQuery::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox table;
	CCheckListBox checkList;
	afx_msg void OnCbnSelchangeComboTable();
	CProjectDlg* parent;
	CString tableName;
	int itemCount;
	afx_msg void OnBnClickedButtonLoadtable();
	afx_msg void OnBnClickedButtonCancle();
};
