
// ProjectDlg.h: 헤더 파일
//

#pragma once


// CProjectDlg 대화 상자
class CProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	SQLHDBC hDbc = NULL;
	SQLHENV hEnv = NULL;
	const char* dataSourceName = "DBProject";
	const char* serverID = "sa";
	const char* serverPw = "1234";

	bool db_connect()
	{
		SQLRETURN Ret;

		// Allocate the Environment Handle (hEnv)
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		{
			return false;
		}

		// Set attributes of the Environment Handle (hEnv)
		if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		{
			return false;
		}

		// Allocate the Connection Handle (hDbc)
		if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		{
			return false;
		}

		// Connect to the SQL Sever with ODBC name, ID, and PW
		Ret = SQLConnect(hDbc, (SQLCHAR*)dataSourceName, SQL_NTS, (SQLCHAR*)serverID, SQL_NTS, (SQLCHAR*)serverPw, SQL_NTS);

		if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
		{
			return false;
		}

		return true;
}

	void db_disconnect()
	{
		SQLDisconnect(hDbc);					// Disconnect from the SQL Server
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);	// Free the Connection Handle
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);	// Free the Environment Handle
	}

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_DIALOG };
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
	afx_msg void OnBnClickedButtonSchema();
	
	afx_msg void OnBnClickedButtonSelect();
	afx_msg void OnBnClickedButtonInsert2();
	afx_msg void OnBnClickedButtonDelete2();
	afx_msg void OnBnClickedButtonUpdate();
};
