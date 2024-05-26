// InsertDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "InsertDlg.h"
#include "InsertTuple.h"


// InsertDlg 대화 상자

IMPLEMENT_DYNAMIC(InsertDlg, CDialogEx)

InsertDlg::InsertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Insert, pParent),
	columnCount(0),
	tableName(""),
	tupleCount(0)
{

}

InsertDlg::~InsertDlg()
{
}

void InsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, table);
	DDX_Control(pDX, IDC_LIST1, inserting);
}


BEGIN_MESSAGE_MAP(InsertDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &InsertDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(ID_addTuple, &InsertDlg::OnBnClickedaddtuple)
	ON_BN_CLICKED(ID_delTuple, &InsertDlg::OnBnClickeddeltuple)
	ON_BN_CLICKED(IDOK, &InsertDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// InsertDlg 메시지 처리기

BOOL InsertDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	table.AddString(_T("카테고리"));
	table.AddString(_T("회사"));
	table.AddString(_T("상품"));
	table.AddString(_T("관련상품"));
	table.AddString(_T("사용자 평가"));
	inserting.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	return TRUE;
}

void InsertDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	inserting.DeleteAllItems();
	for (int i = 0; i < columnCount; i++) {
		inserting.DeleteColumn(0);
	}
	columnCount = 0;
	tupleCount = 0;

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
	CRect size;
	inserting.GetWindowRect(&size);
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT * FROM %s", tableName);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLNumResultCols(hStmt, &numCols);
		for (int i = 0; i < numCols; ++i)
		{
			SQLDescribeCol(hStmt, i + 1, columnName[i], 30, &columnNameLen[i], &columnDataType[i],
				&columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);

			inserting.InsertColumn(i, (CString)columnName[i], LVCFMT_LEFT, size.Width() / numCols );
		}
		columnCount = numCols;
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void InsertDlg::OnBnClickedaddtuple()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 0; i < columnCount; i++) {
		LVCOLUMN col;
		TCHAR name[50];
		col.mask = LVCF_TEXT;
		col.pszText = name;
		col.cchTextMax = 50;

		inserting.GetColumn(i, &col);
		InsertTuple insertTuple(col.pszText);
		insertTuple.parent = this;
		insertTuple.DoModal();
		if (i == 0)
			inserting.InsertItem(inserting.GetItemCount(), attrInput);
		else
			inserting.SetItemText(inserting.GetItemCount()-1, i, attrInput);
	}
	tupleCount++;
}


void InsertDlg::OnBnClickeddeltuple()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	inserting.DeleteItem(inserting.GetSelectionMark());
	tupleCount--;
}


void InsertDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;

	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{

		for (int i = 0; i < tupleCount; i++) {
			CString values="";
			for (int j = 0; j < columnCount; j++) {
				values += '\''+inserting.GetItemText(0, j)+'\'';
				if (j < columnCount - 1) values += ',';
			}
			sprintf_s((char*)query, 101, "insert into %s values(%s)",tableName,values);
			retCode = SQLExecDirect(hStmt, query, SQL_NTS);
			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
			{
				MessageBox("Query execution error!");
				break;
			}
			inserting.DeleteItem(0);
		}
		tupleCount = 0;
		MessageBox("Query execution success");
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

}
