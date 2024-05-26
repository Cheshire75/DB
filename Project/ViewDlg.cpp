// ViewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "ViewDlg.h"
#include "resource.h"


// ViewDlg 대화 상자

IMPLEMENT_DYNAMIC(ViewDlg, CDialogEx)

ViewDlg::ViewDlg(SelectQuery* sParent, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_View, pParent),
	viewColumn(""),
	sParent(sParent)
{
	level = 1;
	tableName = sParent->tableName;
}
ViewDlg::ViewDlg(ViewDlg* pparent, CWnd* pParent)
	:CDialogEx(IDD_DIALOG_View, pParent),
	viewColumn(""),
	vParent(pparent)
{
	level = 2;
	sParent = vParent->sParent;
	tableName=(vParent->tableName);
}

ViewDlg::~ViewDlg()
{
}

void ViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_View, View);
	DDX_Control(pDX, IDC_COMBO1, searchColumn);
	DDX_Control(pDX, IDC_EDIT1, target);
}


BEGIN_MESSAGE_MAP(ViewDlg, CDialogEx)
	ON_BN_CLICKED(ID_Search, &ViewDlg::OnBnClickedSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_View, &ViewDlg::OnNMDblclkListView)
END_MESSAGE_MAP()


// ViewDlg 메시지 처리기

BOOL ViewDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	CString columnName;
	CRect size;
	View.GetWindowRect(&size);
	View.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	switch (level) {
	case 1:
		for (int i = 0; i < sParent->itemCount; i++) {
			if (sParent->checkList.GetCheck(i)) {
				sParent->checkList.GetText(i, columnName);
				View.InsertColumn(i, columnName, LVCFMT_LEFT, size.Width() / (sParent->itemCount));
				searchColumn.AddString(columnName);
				if (viewColumn == "")
					viewColumn += columnName;
				else {
					viewColumn += (", " + columnName);
				}
			}
		}
		

		if (SQLAllocHandle(SQL_HANDLE_STMT, sParent->parent->hDbc, &hStmt) == SQL_SUCCESS)
		{
			int columnCount = sParent->itemCount;
			sprintf_s((char*)query, 101, "SELECT %s FROM %s", viewColumn, tableName);
			SQLExecDirect(hStmt, query, SQL_NTS);
			SQLCHAR** data = new SQLCHAR * [columnCount];
			for (int i = 0; i < columnCount; i++)
				data[i] = new SQLCHAR[30];
			for (int i = 0; i < columnCount; i++) {
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], 50, NULL);
			}


			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				int num = View.GetItemCount();
				int itemNum = View.InsertItem(num, (CString)data[0]);
				for (int i = 1; i < columnCount; i++) {
					View.SetItemText(itemNum, i, (CString)data[i]);
				}
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		break;
	case 2:
			View.InsertColumn(0, "No.", LVCFMT_LEFT, size.Width() * 0.1);
			View.InsertColumn(1, "Writer", LVCFMT_LEFT, size.Width() * 0.3);
			View.InsertColumn(2, "Score", LVCFMT_LEFT, size.Width() * 0.1);

			CString productNum;
			if (SQLAllocHandle(SQL_HANDLE_STMT, vParent->sParent->parent->hDbc, &hStmt) == SQL_SUCCESS)
			{
				int columnCount = 3;
				sprintf_s((char*)query, 101, "SELECT SEQ, WRITER, SCORE FROM REVIEW WHERE PRONUM = '%s'", 
					vParent->View.GetItemText(vParent->View.GetSelectionMark(),0));
				SQLExecDirect(hStmt, query, SQL_NTS);
				SQLCHAR seq[50];
				SQLCHAR writer[50];
				SQLCHAR score[2];
				SQLBindCol(hStmt, 1, SQL_C_CHAR, seq, 50, NULL);
				SQLBindCol(hStmt, 2, SQL_C_CHAR, writer, 50, NULL);
				SQLBindCol(hStmt, 3, SQL_C_CHAR, score, 2, NULL);

				while (SQLFetch(hStmt) != SQL_NO_DATA)
				{
					int num = View.GetItemCount();
					int itemNum = View.InsertItem(num, (CString)seq);
					View.SetItemText(itemNum, 1, (CString)writer);
					View.SetItemText(itemNum, 2, (CString)score);
				}

				SQLCloseCursor(hStmt);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			}
		break;
	}
	return TRUE;
}

void ViewDlg::OnBnClickedSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString targetColumn, searchValue;
	searchColumn.GetLBText(searchColumn.GetCurSel(), targetColumn);
	target.GetWindowTextA(searchValue);

	SQLHSTMT hStmt;	// Statement Handle
	SQLCHAR query[101];
	SQLRETURN retCode;
	View.DeleteAllItems();
	if (SQLAllocHandle(SQL_HANDLE_STMT, sParent->parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		int columnCount = sParent->itemCount;
		sprintf_s((char*)query, 101, "SELECT %s FROM %s WHERE %s = '%s'", viewColumn, tableName,targetColumn,searchValue);
		retCode = SQLExecDirect(hStmt, query, SQL_NTS);
		if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
		{
			MessageBox("Query execution error!");
		}
		else {
			SQLCHAR** data = new SQLCHAR * [columnCount];
			for (int i = 0; i < columnCount; i++)
				data[i] = new SQLCHAR[30];
			for (int i = 0; i < columnCount; i++) {
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], 50, NULL);
			}


			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				int num = View.GetItemCount();
				int itemNum = View.InsertItem(num, (CString)data[0]);
				for (int i = 1; i < columnCount; i++) {
					View.SetItemText(itemNum, i, (CString)data[i]);
				}
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}


void ViewDlg::OnNMDblclkListView(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (tableName == "PRODUCT") {
		ViewDlg subView(this);
		subView.DoModal();
	}
	*pResult = 0;
}
