// CALIBdLG.cpp: 实现文件
//

#include "stdafx.h"
#include "CV.h"
#include "CALIBdLG.h"
#include "afxdialogex.h"


// CALIBdLG 对话框

IMPLEMENT_DYNAMIC(CALIBdLG, CDialogEx)

CALIBdLG::CALIBdLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALIBRATION, pParent)
	, INFO(_T(""))
{

}

CALIBdLG::~CALIBdLG()
{
}

void CALIBdLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_H, INFO);
}


BEGIN_MESSAGE_MAP(CALIBdLG, CDialogEx)
END_MESSAGE_MAP()


// CALIBdLG 消息处理程序
