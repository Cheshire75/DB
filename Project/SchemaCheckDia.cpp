// SchemaCheckDia.cpp: 구현 파일
//

#include "pch.h"
#include "Project.h"
#include "afxdialogex.h"
#include "SchemaCheckDia.h"


const char* get_data_type_in_string(SQLSMALLINT dataType)
{
    switch (dataType)
    {
    case SQL_CHAR:
        return "CHAR";
        break;
    case SQL_VARCHAR:
        return "VARCHAR";
        break;
    case SQL_LONGVARCHAR:
        return "LONGVARCHAR";
        break;
    case SQL_WCHAR:
        return "WCHAR";
        break;
    case SQL_WVARCHAR:
        return "WVARCHAR";
        break;
    case SQL_WLONGVARCHAR:
        return "WLONGVARCHAR";
        break;
    case SQL_NUMERIC:
        return "NUMERIC";
        break;
    case SQL_SMALLINT:
        return "SMALLINT";
        break;
    case SQL_INTEGER:
        return "INTEGER";
        break;
    case SQL_REAL:
        return "REAL";
        break;
    case SQL_FLOAT:
        return "FLOAT";
        break;
    case SQL_DOUBLE:
        return "DOUBLE";
        break;
    case SQL_BIT:
        return "BIT";
        break;
    case SQL_TINYINT:
        return "TINYINT";
        break;
    case SQL_BIGINT:
        return "BIGINT";
        break;
    case SQL_BINARY:
        return "BINARY";
        break;
    case SQL_VARBINARY:
        return "VARBINARY";
        break;
    case SQL_LONGVARBINARY:
        return "LONGVARBINARY";
        break;
    case SQL_TYPE_DATE:
        return "TYPE_DATE";
        break;
    case SQL_TYPE_TIME:
        return "TYPE_TIME";
        break;
    case SQL_TYPE_TIMESTAMP:
        return "TYPE_TIMESTAMP";
        break;
    case SQL_INTERVAL_MONTH:
        return "INTERVAL_MONTH";
        break;
    case SQL_INTERVAL_YEAR:
        return "INTERVAL_YEAR";
        break;
    case SQL_INTERVAL_YEAR_TO_MONTH:
        return "INTERVAL_YEAR_TO_MONTH";
        break;
    case SQL_INTERVAL_DAY:
        return "INTERVAL_DAY";
        break;
    case SQL_INTERVAL_HOUR:
        return "INTERVAL_HOUR";
        break;
    case SQL_INTERVAL_MINUTE:
        return "INTERVAL_MINUTE";
        break;
    case SQL_INTERVAL_SECOND:
        return "INTERVAL_SECOND";
        break;
    case SQL_INTERVAL_DAY_TO_HOUR:
        return "INTERVAL_DAY_TO_HOUR";
        break;
    case SQL_INTERVAL_DAY_TO_MINUTE:
        return "INTERVAL_DAY_TO_MINUTE";
        break;
    case SQL_INTERVAL_DAY_TO_SECOND:
        return "INTERVAL_DAY_TO_SECOND";
        break;
    case SQL_INTERVAL_HOUR_TO_MINUTE:
        return "INTERVAL_HOUR_TO_MINUTE";
        break;
    case SQL_INTERVAL_HOUR_TO_SECOND:
        return "INTERVAL_HOUR_TO_SECOND";
        break;
    case SQL_INTERVAL_MINUTE_TO_SECOND:
        return "INTERVAL_MINUTE_TO_SECOND";
        break;
    case SQL_GUID:
        return "GUID";
        break;
    default:
        return "UNKNOWN";
    }
}

// SchemaCheckDia 대화 상자

IMPLEMENT_DYNAMIC(SchemaCheckDia, CDialogEx)

SchemaCheckDia::SchemaCheckDia(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_SchemaCheck, pParent),
    parent(NULL)
{
}

SchemaCheckDia::~SchemaCheckDia()
{
}



void SchemaCheckDia::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, table);
}




BEGIN_MESSAGE_MAP(SchemaCheckDia, CDialogEx)
	ON_BN_CLICKED(IDOK, &SchemaCheckDia::OnBnClickedOk)
END_MESSAGE_MAP()

// SchemaCheckDia 메시지 처리기

BOOL SchemaCheckDia::OnInitDialog() {
	CDialogEx::OnInitDialog();

	table.AddString(_T("카테고리"));
	table.AddString(_T("회사"));
	table.AddString(_T("상품"));
	table.AddString(_T("관련상품"));
	table.AddString(_T("사용자 평가"));
	return TRUE;
}

void SchemaCheckDia::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString tableName;
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

    CString str;
    CString col;
	if (SQLAllocHandle(SQL_HANDLE_STMT, parent->hDbc, &hStmt) == SQL_SUCCESS)
	{
		sprintf_s((char*)query, 101, "SELECT * FROM %s",tableName);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLNumResultCols(hStmt, &numCols);
		for (int i = 0; i < numCols; ++i)
		{
			SQLDescribeCol(hStmt, i + 1, columnName[i], 30, &columnNameLen[i], &columnDataType[i],
				&columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);
            col.Format("Column #%d, Name: %s, NameLength: %d, DataType: %s\nDataSize: %d, DataDecimalDigits: %d, DataNullable: %d\n\n",
                i + 1, columnName[i], columnNameLen[i], get_data_type_in_string(columnDataType[i]),
                columnDataSize[i], columnDataDecimalDigits[i], columnDataNullable[i]);
            str += col;
		}
        MessageBox(str);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}
