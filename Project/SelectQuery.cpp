// SelectQuery.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "SelectQuery.h"
#include "ViewDlg.h"


// SelectQuery 대화 상자

IMPLEMENT_DYNAMIC(SelectQuery, CDialogEx)

SelectQuery::SelectQuery(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Select, pParent),
	parent(NULL),
	itemCount(0),
	tableName("")
{

}

SelectQuery::~SelectQuery()
{
}

void SelectQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_Table, table);
	DDX_Control(pDX, IDC_LIST_Column, checkList);
}


BEGIN_MESSAGE_MAP(SelectQuery, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_Table, &SelectQuery::OnCbnSelchangeComboTable)
	ON_BN_CLICKED(IDC_BUTTON_LoadTable, &SelectQuery::OnBnClickedButtonLoadtable)
	ON_BN_CLICKED(IDC_BUTTON_Cancle, &SelectQuery::OnBnClickedButtonCancle)
END_MESSAGE_MAP()


// SelectQuery 메시지 처리기
BOOL SelectQuery::OnInitDialog() {
	CDialogEx::OnInitDialog();

	table.AddString(_T("카테고리"));
	table.AddString(_T("회사"));
	table.AddString(_T("상품"));
	table.AddString(_T("관련상품"));
	table.AddString(_T("사용자 평가"));

	return TRUE;
}



void SelectQuery::OnCbnSelchangeComboTable()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	switch (table.GetCurSel()) {
	case 0:
		tableName = "CATEGORY";
		break;
	case 1:
		tableName = "COMPANY";
		break;
	case 2:
		tableName = "PRODUCT";
		break;
	case 3:
		tableName = "LINK";
		break;
	case 4:
		tableName = "REVIEW";
		break;
	}
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];

	SQLSMALLINT numCols = -1;// number of columns
	SQLCHAR columnName[50][31];
	SQLSMALLINT columnNameLen[50];
	SQLSMALLINT columnDataType[50];
	SQLULEN columnDataSize[50];
	SQLSMALLINT columnDataDecimalDigits[50];
	SQLSMALLINT columnDataNullable[50];
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT * FROM %s",tableName);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLNumResultCols(hStmt, &numCols);
		for (int i = 0; i < itemCount; i++)
			checkList.DeleteString(0);
		itemCount = 0;
		for (int i = 0; i < numCols; ++i)
		{
			SQLDescribeCol(hStmt, i + 1, columnName[i], 30, &columnNameLen[i], &columnDataType[i],
				&columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);

			checkList.InsertString(i, (LPCTSTR)columnName[i]);
			checkList.SetCheck(i, 1);
			itemCount++;
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void SelectQuery::OnBnClickedButtonLoadtable()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ViewDlg view(this);
	view.sParent = this;
	view.DoModal();
}


void SelectQuery::OnBnClickedButtonCancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
