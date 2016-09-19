
// comm_appDlg.h : 头文件
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"


// Ccomm_appDlg 对话框
class Ccomm_appDlg : public CDialogEx
{
// 构造
public:
	Ccomm_appDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMM_APP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	CMscomm1 m_mscomm;
	afx_msg void OnEnChangeEdit1();
	CString m_editReceive;
	CString m_editSend;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClose();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnBnClickedCheckDtr();
	afx_msg void OnBnClickedCheckRts();
	afx_msg void OnBnClickedButtonTxclear();
	afx_msg void OnBnClickedButtonRxclear();
	static int ascii2hex(char ch);
	afx_msg void OnCbnSelchangeComboCom();
	afx_msg void OnCbnSelchangeComboBaud();
	afx_msg void OnCbnSelchangeComboData();
	afx_msg void OnCbnSelchangeComboParity();
	afx_msg void OnCbnSelchangeComboStopbit();
	virtual int CommSet();
	CStatic m_picLED;
//	CString m_editCommState;
	CString m_editRXNumber;
	CString m_editTXNumber;
	afx_msg void OnBnClickedButtonClearnumber();
	long m_editPeriod;
	afx_msg void OnBnClickedCheckAutosend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	virtual int CommSend();
};
