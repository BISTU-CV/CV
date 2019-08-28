#pragma once


// CALIBdLG 对话框

class CALIBdLG : public CDialogEx
{
	DECLARE_DYNAMIC(CALIBdLG)

public:
	CALIBdLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CALIBdLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALIBRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString INFO;
};
