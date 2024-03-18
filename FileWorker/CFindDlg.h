#pragma once
#include "afxdialogex.h"
#include "FileWorkerDlg.h"


// CFindDlg 대화 상자

class CFindDlg : public CDialog
{
	DECLARE_DYNAMIC(CFindDlg)

public:
	CFindDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFindDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtoncancle();
	afx_msg void OnBnClickedButtonFind();
	CFileWorkerDlg* parent;
private:
	CString findEdit;
	int strIndex;
public:
//	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditFind();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
