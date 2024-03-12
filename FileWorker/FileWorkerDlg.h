
// FileWorkerDlg.h: 헤더 파일
//

#pragma once


// CFileWorkerDlg 대화 상자
class CFileWorkerDlg : public CDialogEx
{
// 생성입니다.
public:
	CFileWorkerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEWORKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString strEdit;
	afx_msg void OnBnClickedButtonFilesave();
	afx_msg void OnBnClickedButtonFileload();
private:
	CString fileTitle;
public:
	afx_msg void OnBnClickedButtonFileprint();
	afx_msg void OnBnClickedButtonFileupdate();
	afx_msg void OnBnClickedButtonFiledelete();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonFilefind();
	CEdit mainEditorBox;
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnChangeEdit();
};
