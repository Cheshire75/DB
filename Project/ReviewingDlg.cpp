// ReviewingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "ReviewingDlg.h"
#include <string>

class Review {
public:
	CString proNum;
}newReview;


// ReviewingDlg 대화 상자

IMPLEMENT_DYNAMIC(ReviewingDlg, CDialogEx)

ReviewingDlg::ReviewingDlg(CProjectDlg* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Review, NULL),
	parent(pParent)
{

}

ReviewingDlg::~ReviewingDlg()
{
}

void ReviewingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, proName);
	DDX_Control(pDX, IDC_COMBO_Score, scoreCombo);
}


BEGIN_MESSAGE_MAP(ReviewingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ReviewingDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ReviewingDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// ReviewingDlg 메시지 처리기
BOOL ReviewingDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "select PRONAME FROM PRODUCT");
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		SQLCHAR proName[20];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, proName, 20, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			ReviewingDlg::proName.AddString((CString)proName);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	return TRUE;
}

void ReviewingDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString writer;
	int seq=1;
	int score = GetDlgItemInt(IDC_COMBO_Score);
	GetDlgItemText(IDC_EDIT1, writer);

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "select count(*) from REVIEW group by PRONUM HAVING PRONUM = '%s'",newReview.proNum);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		SQLCHAR SEQ[5];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, SEQ, 5, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			seq = _ttoi((CString)SEQ)+1;
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "insert into REVIEW values('%s',%d,'%s',%d)", newReview.proNum, seq, writer, score);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		MessageBox("Review Success");
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	
}


void ReviewingDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;
	CString productName;
	proName.GetLBText(proName.GetCurSel(), productName);

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "select PRONUM from PRODUCT WHERE PRONAME = '%s'",productName);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		SQLCHAR proNum[15];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, proNum, 20, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			newReview.proNum = (CString)proNum;
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}
