#pragma once
#include "afxdialogex.h"
#include "FileWorkerDlg.h"


// CDeleteDlg 대화 상자

class CDeleteDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteDlg)

public:
	CDeleteDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDeleteDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString deleteEdit;
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtoncancle();
	int startIndexOfTarget;
	int endIndexOfTarget;
	CFileWorkerDlg* parent;
	afx_msg void OnBnClickedButtonSearch();
	int strIndex;
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnChangeEditDelete();
};
