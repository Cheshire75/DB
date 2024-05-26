#pragma once
#include "afxdialogex.h"
#include "ProjectDlg.h"


// SchemaCheckDia 대화 상자

class SchemaCheckDia : public CDialogEx
{
	DECLARE_DYNAMIC(SchemaCheckDia)

public:
	SchemaCheckDia(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SchemaCheckDia();

	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SchemaCheck };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CProjectDlg* parent;
private:
	CComboBox table;
};
