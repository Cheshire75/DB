#pragma once
#include "afxdialogex.h"
#include "FileWorkerDlg.h"


// CReplaceDlg 대화 상자

class CReplaceDlg : public CDialog
{
	DECLARE_DYNAMIC(CReplaceDlg)

public:
	CReplaceDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CReplaceDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REPLACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString findEdit;
	CString replaceEdit;
	CFileWorkerDlg* parent;
	int strIndex;
	afx_msg void OnBnClickedButtonReplace();
	afx_msg void OnBnClickedButtoncancle();
	afx_msg void OnBnClickedButtonSearch();
};
