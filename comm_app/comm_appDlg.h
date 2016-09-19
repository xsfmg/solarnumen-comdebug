
// comm_appDlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"


// Ccomm_appDlg �Ի���
class Ccomm_appDlg : public CDialogEx
{
// ����
public:
	Ccomm_appDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMM_APP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
