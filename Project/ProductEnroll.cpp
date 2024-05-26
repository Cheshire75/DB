// ProductEnroll.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "ProductEnroll.h"
#include "resource.h"

class product{
public:
	CString proNum;
	CString proName;
	CString category;
	CString cmp;
	CString price;
	int downloads = 0;
}newPro;
// ProductEnroll 대화 상자

IMPLEMENT_DYNAMIC(ProductEnroll, CDialogEx)

ProductEnroll::ProductEnroll(CProjectDlg* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ProductEnroll, NULL),
	parent(pParent)
{
	
}

ProductEnroll::~ProductEnroll()
{
}

void ProductEnroll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, categoryCombo);
	DDX_Control(pDX, IDC_COMBO1, typeCombo);
	DDX_Control(pDX, IDC_COMBO3, cmpCombo);
	DDX_Control(pDX, IDC_EDIT_ProNum, proNum);
	DDX_Control(pDX, IDC_EDIT1, proName);
	DDX_Control(pDX, IDC_EDIT2, proPrice);
}


BEGIN_MESSAGE_MAP(ProductEnroll, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ProductEnroll::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &ProductEnroll::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &ProductEnroll::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDOK, &ProductEnroll::OnBnClickedOk)
END_MESSAGE_MAP()


// ProductEnroll 메시지 처리기
BOOL ProductEnroll::OnInitDialog() {
	CDialogEx::OnInitDialog();

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		categoryCombo.ResetContent();
		sprintf_s((char*)query, 101, "select CMPNAME FROM COMPANY");
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		SQLCHAR cmpName[20];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, cmpName, 20, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			cmpCombo.AddString((CString)cmpName);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	return TRUE;
}


void ProductEnroll::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString type;
	typeCombo.GetLBText(typeCombo.GetCurSel(), type);

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		categoryCombo.ResetContent();
		sprintf_s((char*)query, 101, "select CATNAME from CATEGORY where PTYPE = '%s'",type);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		SQLCHAR catName[15];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, catName, 15, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			categoryCombo.AddString((CString)catName);
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void ProductEnroll::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString type, category;
	typeCombo.GetLBText(typeCombo.GetCurSel(), type);
	categoryCombo.GetLBText(categoryCombo.GetCurSel(), category);

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "select CATNUM from CATEGORY where PTYPE = '%s' AND CATNAME = '%s'", type, category);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		SQLCHAR catNum[15];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, catNum, 15, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			newPro.category = (CString)catNum;
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void ProductEnroll::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cmpName;
	cmpCombo.GetLBText(cmpCombo.GetCurSel(), cmpName);

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "select CMPNUM from COMPANY where CMPNAME = '%s'", cmpName);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		SQLCHAR cmpNum[15];
		SQLBindCol(hStmt, 1, SQL_C_CHAR, cmpNum, 15, NULL);
		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			newPro.cmp = (CString)cmpNum;
		}
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void ProductEnroll::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemTextA(IDC_EDIT2, newPro.price);
	GetDlgItemTextA(IDC_EDIT_ProNum, newPro.proNum);
	GetDlgItemTextA(IDC_EDIT1, newPro.proName);

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "insert into PRODUCT VALUES('%s','%s','%s','%s','%s',0)",newPro.proNum,newPro.proName,newPro.category,newPro.cmp,newPro.price);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		else MessageBox("Insert Success!");
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}
