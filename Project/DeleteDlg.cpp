// DeleteDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "DeleteDlg.h"
#include "resource.h"


// DeleteDlg 대화 상자

IMPLEMENT_DYNAMIC(DeleteDlg, CDialogEx)

DeleteDlg::DeleteDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Delete, pParent),
	itemCount(0),
	columnCount(0),
	parent(NULL),
	key(""),
	dParent(NULL)
{

}

DeleteDlg::DeleteDlg(DeleteDlg* Parent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Delete, NULL),
	itemCount(0),
	columnCount(0),
	parent(NULL),
	key(""),
	dParent(Parent)
{
}

DeleteDlg::~DeleteDlg()
{
}

void DeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo);
	DDX_Control(pDX, IDC_LIST1, list);
}


BEGIN_MESSAGE_MAP(DeleteDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DeleteDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_Button_Del, &DeleteDlg::OnBnClickedButtonDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &DeleteDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// DeleteDlg 메시지 처리기

BOOL DeleteDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	

	list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	if (dParent != NULL) {
		combo.AddString("사용자평가");
		combo.SetCurSel(0);
	}
	else {
		combo.AddString("카테고리");
		combo.AddString("회사");
		combo.AddString("상품");
	}
	if(dParent !=NULL) OnCbnSelchangeCombo1();
	return TRUE;
}

void DeleteDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (combo.GetCurSel()) {
	case 0:
		tableName = "CATEGORY";
		key = "CATNUM";
		break;
	case 1:
		tableName = "COMPANY";
		key = "CMPNUM";
		break;
	case 2:
		tableName = "PRODUCT";
		key = "PRONUM";
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
	GetWindowRect(&size);
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		if(dParent != NULL) sprintf_s((char*)query, 101, "SELECT * FROM REVIEW WHERE PRONUM = '%s'", dParent->list.GetItemText(dParent->list.GetSelectionMark(),0));
		else sprintf_s((char*)query, 101, "SELECT * FROM %s", tableName);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLNumResultCols(hStmt, &numCols);
		list.DeleteAllItems();
		for (int i = 0; i < columnCount; i++)
			list.DeleteColumn(0);
		itemCount = 0;
		columnCount = 0;
		for (int i = 0; i < numCols; ++i)
		{
			SQLDescribeCol(hStmt, i + 1, columnName[i], 30, &columnNameLen[i], &columnDataType[i],
				&columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);

			list.InsertColumn(i, (LPCTSTR)columnName[i],LVCFMT_LEFT,size.Width()/numCols);
			columnCount++;
		}

		SQLCHAR** data = new SQLCHAR * [columnCount];
		for (int i = 0; i < columnCount; i++)
			data[i] = new SQLCHAR[30];
		for (int i = 0; i < columnCount; i++) {
			SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], 50, NULL);
		}


		while (SQLFetch(hStmt) != SQL_NO_DATA)
		{
			int num = list.GetItemCount();
			int itemNum = list.InsertItem(num, (CString)data[0]);
			for (int i = 1; i < columnCount; i++) {
				list.SetItemText(itemNum, i, (CString)data[i]);
			}
		}


		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void DeleteDlg::OnBnClickedButtonDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		for (int i = 0; i < list.GetItemCount(); i++) {
			if (list.GetCheck(i)) {
				CString target = list.GetItemText(i, 1);
				if (dParent != NULL) {
					sprintf_s((char*)query, 101, "DELETE FROM REVIEW WHERE PRONUM = '%s' and SEQ = '%s'", 
						dParent->list.GetItemText(dParent->list.GetSelectionMark(),0), target);
					
				}
				else sprintf_s((char*)query, 101, "DELETE FROM %s WHERE %s = '%s'", tableName, key, target);
				retCode = SQLExecDirect(hStmt, query, SQL_NTS);
				if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
				{
					MessageBox("Query execution error!");
					break;
				}
				list.DeleteItem(i);
				i--;
			}
		}
		

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void DeleteDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (tableName == "PRODUCT") {
		DeleteDlg reviewDel(this);
		reviewDel.parent = parent;
		reviewDel.DoModal();
	}
	*pResult = 0;
}
