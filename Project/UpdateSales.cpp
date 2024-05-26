// UpdateSales.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "UpdateSales.h"


// UpdateSales 대화 상자

IMPLEMENT_DYNAMIC(UpdateSales, CDialogEx)

UpdateSales::UpdateSales(CProjectDlg* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Sales, NULL),
	parent(pParent)
{

}

UpdateSales::~UpdateSales()
{
}

void UpdateSales::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, proCombo);
}


BEGIN_MESSAGE_MAP(UpdateSales, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &UpdateSales::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &UpdateSales::OnBnClickedOk)
END_MESSAGE_MAP()


// UpdateSales 메시지 처리기

BOOL UpdateSales::OnInitDialog() {
	CDialogEx::OnInitDialog();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT PRONAME FROM PRODUCT");
		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCHAR name[15];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, name, 15, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			proCombo.AddString((CString)name);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	return TRUE;
}

void UpdateSales::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	CString proName;
	proCombo.GetLBText(proCombo.GetCurSel(), proName);
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT DOWNLOADS FROM PRODUCT WHERE PRONAME = '%s'",proName);
		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCHAR sales[20];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, sales, 20, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			SetDlgItemText(IDC_EDIT1, (CString)sales);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void UpdateSales::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	CString proName;
	SQLRETURN resCode;
	proCombo.GetLBText(proCombo.GetCurSel(), proName);
	CString sales;
	GetDlgItemTextA(IDC_EDIT1, sales);
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "UPDATE PRODUCT SET DOWNLOADS = '%s' WHERE PRONAME = '%s'",sales, proName);
		resCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (resCode == SQL_ERROR || resCode == SQL_NO_DATA_FOUND) {
			MessageBox("Failed");
		}
		MessageBox("Success");
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}
