#pragma once
#include "afxdialogex.h"
#include "FileWorkerDlg.h"

// CInsertDlg 대화 상자

class CInsertDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertDlg)

public:
	CInsertDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString insertEdit;
	CFileWorkerDlg* parent;
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonOk();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
