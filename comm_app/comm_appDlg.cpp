
// comm_appDlg.cpp : ʵ���ļ�
//CONTROL         IDB_BLACKLED, IDC_PictureLED, "Static", SS_BITMAP, 19, 112, 11, 11, NOT WS_GROUP

#include "stdafx.h"
#include "comm_app.h"
#include "comm_appDlg.h"
#include "afxdialogex.h"
/////////////////////////////////////////////////////////////////////////////////////////////
//#include "mscomm1.h"
#include <locale.h>
/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ccomm_appDlg �Ի���



Ccomm_appDlg::Ccomm_appDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ccomm_appDlg::IDD, pParent)
	, m_editReceive(_T(""))
	, m_editSend(_T(""))
	, m_editRXNumber(_T(""))
	, m_editTXNumber(_T(""))
	, m_editPeriod(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccomm_appDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	DDX_Text(pDX, IDC_EDIT1, m_editReceive);
	DDX_Text(pDX, IDC_EDIT2, m_editSend);
	DDX_Control(pDX, IDC_PictureLED, m_picLED);
	DDX_Text(pDX, IDC_EDIT_RECEIVENUMBER, m_editRXNumber);
	DDX_Text(pDX, IDC_EDIT_SENDNUMBER, m_editTXNumber);
	DDX_Text(pDX, IDC_EDIT_PERIOD, m_editPeriod);
	DDV_MinMaxLong(pDX, m_editPeriod, 10, LONG_MAX);
}

BEGIN_MESSAGE_MAP(Ccomm_appDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &Ccomm_appDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &Ccomm_appDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &Ccomm_appDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_CHECK_DTR, &Ccomm_appDlg::OnBnClickedCheckDtr)
	ON_BN_CLICKED(IDC_CHECK_RTS, &Ccomm_appDlg::OnBnClickedCheckRts)
	ON_BN_CLICKED(IDC_BUTTON_TXCLEAR, &Ccomm_appDlg::OnBnClickedButtonTxclear)
	ON_BN_CLICKED(IDC_BUTTON_RXCLEAR, &Ccomm_appDlg::OnBnClickedButtonRxclear)
	ON_CBN_SELCHANGE(IDC_COMBO_COM, &Ccomm_appDlg::OnCbnSelchangeComboCom)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, &Ccomm_appDlg::OnCbnSelchangeComboBaud)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, &Ccomm_appDlg::OnCbnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_PARITY, &Ccomm_appDlg::OnCbnSelchangeComboParity)
	ON_CBN_SELCHANGE(IDC_COMBO_STOPBIT, &Ccomm_appDlg::OnCbnSelchangeComboStopbit)
	ON_BN_CLICKED(IDC_BUTTON_CLEARNUMBER, &Ccomm_appDlg::OnBnClickedButtonClearnumber)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, &Ccomm_appDlg::OnBnClickedCheckAutosend)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Ccomm_appDlg ��Ϣ�������

BOOL Ccomm_appDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������



	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//���ڿ�ʼ�����ʼ��
	//���ں������б�
	CString strTemp;
	wchar_t seriou[10];
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->ResetContent();//����������������
	for (int i = 1; i <= 15; i++)
	{		
		_ltow_s(i, seriou, 10);//�������ΪWORD���ͣ�longת���ɿ��ַ�wchar
		strTemp = seriou;
		((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString(_T("COM") + strTemp);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->SetCurSel(0);
	//���ڲ����������б�
	wchar_t baudbuffer[][7] = { _T("300"),   _T("600"),   _T("1200"),  _T("2400"),  _T("4800"),  _T("9600"),
		                        _T("19200"), _T("38400"), _T("43000"), _T("56000"), _T("57600"), _T("115200") };
	for (int i = 0; i<12; i++)
	{
		int judge_tf = ((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString(baudbuffer[i]);
		if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			MessageBox(_T("build baud error!"));
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->SetCurSel(5);
	//����У��λ�����б�
	wchar_t jiaoyan[][7] = { _T("N"), _T("O"), _T("E") };
	for (int i = 0; i<3; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->AddString(jiaoyan[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->SetCurSel(0);
	//��������λ�����б�
	wchar_t data[][2] = { _T("8"), _T("7"), _T("6") };
	for (int i = 0; i<3; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->AddString(data[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->SetCurSel(0);
	//����ֹͣλ�����б�
	wchar_t stop[][2] = { _T("1"), _T("2") };
	for(int i=0;i<2;i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->AddString(stop[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->SetCurSel(0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//��ʾ״̬��
	GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(_T("COM1 �ѹر�, 9600, n, 8, 1"));
	//�޸�ͼƬ�ؼ�����Ϊλͼ��vs2013 bug
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_PictureLED); // �õ� Picture Control ���
	pWnd->ModifyStyle(0, SS_BITMAP); // �޸���������Ϊλͼ
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//�����������б�
	wchar_t endchar[][8] = { _T("��"), _T("�ۼӺ�"), _T("����") };
	for (int i = 0; i<3; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_ENDCHAR))->AddString(endchar[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_ENDCHAR))->SetCurSel(0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//�������ʾ
	m_editSend = _T("01 01 02");
	//GetDlgItem(IDC_EDIT_SEND)->SetWindowTextW(_T("01 01 02"));
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//ʮ�����Ʒ��͡����ո�ѡ���ʼ��Ϊ��Ч
	CButton *p_check;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXRECEIVE);
	p_check->SetCheck(TRUE);
	p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXSEND);
	p_check->SetCheck(TRUE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//ͨѶ״̬��ʾ
	m_editRXNumber = _T("RX:0");
	m_editTXNumber = _T("TX:0");
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//�Զ�����������ʾ
	m_editPeriod = 1000;



	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Ccomm_appDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ccomm_appDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ccomm_appDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//////////////////////////////////////////////////////////////////////////////////////////////
void Ccomm_appDlg::OnBnClickedButtonOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	CString setstr, setstr1;
	/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->GetWindowTextW(str);
	if (str == _T("�򿪴���"))
	{
		if (m_mscomm.get_PortOpen())
		{
			m_mscomm.put_PortOpen(FALSE);
		}
		int comm = ((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel();
		m_mscomm.put_CommPort(((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel()+1); //ѡ��COM1
		m_mscomm.put_InBufferSize(1024); //���ջ�����
		m_mscomm.put_OutBufferSize(1024);//���ͻ�����
		m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
		m_mscomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д���ݡ�1:comInputModeBinary�����Ʒ�ʽ,0:comInputModeText�ı���ʽ
		m_mscomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�
		
		((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetWindowTextW(setstr);
		setstr1 = setstr;
		((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetWindowTextW(setstr);
		setstr1 += ','+ setstr;
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetWindowTextW(setstr);
		setstr1 += ',' + setstr;
		((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetWindowTextW(setstr);
		setstr1 += ',' + setstr;
		m_mscomm.put_Settings(setstr1);//������9600 �޼���λ��8������λ��1��ֹͣλ
		//m_mscomm.put_Settings(_T("9600,n,8,1"));//������9600 �޼���λ��8������λ��1��ֹͣλ
		m_mscomm.put_OutBufferCount(0);	 //��շ��ͻ�����
		m_mscomm.put_InBufferCount(0);	 //��ս��ջ�����
		

		if (!m_mscomm.get_PortOpen())//�������û�д����
		{
			try
			{
				m_mscomm.put_PortOpen(true);//�򿪴���
			}
			//��ʾ����3
			catch (COleDispatchException *e)
			{
				CString strError = _T("�򿪴���ʧ�ܣ�\n\r�����ţ�");
				wchar_t a[10];
				_ltow_s(e->m_wCode, a, 10);//�������ΪWORD���ͣ�longת���ɿ��ַ�wchar
				strError += a;
				strError += _T("\n\r������Ϣ��");
				strError += e->m_strDescription;//������ϢΪcstring����
				MessageBoxW(strError, _T("������ʾ"), MB_ICONERROR);

				//��ʾ״̬��
				int u = (((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel() + 1);
				setstr.Format(_T("%d"), u);
				//((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
				GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
					+_T("COM") +
					setstr
					+ _T(" �ѹر�, ")
					+ m_mscomm.get_Settings()
					);
				return;
			}
			//��ʾ����2
			/*catch (COleDispatchException *e)
			{
				CString strError = _T("�򿪴���ʧ�ܣ�\n\r������Ϣ��\n\r");
				    strError += e->m_strDescription;//������ϢΪcstring����
					MessageBoxW(strError, _T("������ʾ"), MB_ICONERROR);
					return;
			}*/
			//��ʾ����1
			/*catch (...)
			{
				MessageBoxW(_T("�ô����ѱ�ռ�ã���ѡ����������"), _T("������ʾ"), MB_ICONERROR);
				return ;
			}*/
			
			//m_mscomm.put_PortOpen(TRUE);//�򿪴���
			m_mscomm.put_RThreshold(1);//ÿ�����ջ�������һ���������ַ�����մ�������
			m_mscomm.put_InputLen(0);//���õ�ǰ����������Ϊ��0��ʾ��ȡȫ������
			m_mscomm.get_Input();	 //Ԥ���������������������
			/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("�رմ���"));
			//�ı�picLEDΪ��ɫ
			CBitmap bitmap; // CBitmap �������ڼ���λͼ 
			HBITMAP hBmp; // ���� CBitmap ���ص�λͼ��� 
			bitmap.LoadBitmap(IDB_REDLED); // ��λͼ IDB_REDLED ���ص� bitmap
			hBmp = (HBITMAP )bitmap.GetSafeHandle(); // ��ȡ bitmap ����λͼ�ľ��
			m_picLED.SetBitmap(hBmp); // ����ͼƬ�ؼ�m_picLED ��λͼƬΪ  IDB_REDLED
			//��ʾ״̬��
			((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
			GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
				setstr
				+ _T(" �Ѵ�, ")
				+ m_mscomm.get_Settings()
				);
			
			MessageBoxW(_T("���ڴ򿪳ɹ�"));
		}
		else
		{
			MessageBoxW(_T("���ڴ�ʧ��"));
		}
	}
	else
	{
		m_mscomm.put_PortOpen(FALSE);
		/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("�򿪴���"));
		//�ı�picLEDΪ��ɫ
		CBitmap bitmap; // CBitmap �������ڼ���λͼ 
		HBITMAP hBmp; // ���� CBitmap ���ص�λͼ��� 
		bitmap.LoadBitmap(IDB_BLACKLED); // ��λͼ IDB_REDLED ���ص� bitmap
		hBmp = (HBITMAP)bitmap.GetSafeHandle(); // ��ȡ bitmap ����λͼ�ľ��
		m_picLED.SetBitmap(hBmp); // ����ͼƬ�ؼ�m_picLED ��λͼƬΪ  IDB_BLACKLED
		//��ʾ״̬��
		((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
		GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
			setstr
			+ _T(" �ѹر�, ")
			+ m_mscomm.get_Settings()
			);
		MessageBoxW(_T("���ڹرճɹ�"));
	}
	

}

///////////////////////////

void Ccomm_appDlg::OnBnClickedButtonSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (!m_mscomm.get_PortOpen())//����δ�򿪴���
	{
		//m_mscomm.put_PortOpen(FALSE);
		MessageBoxW(_T("����δ�򿪣�"));
		return ;
	}
    CommSend();
}

void Ccomm_appDlg::OnBnClickedCheckAutosend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CButton*)GetDlgItem(IDC_CHECK_AUTOSEND))->GetCheck() == TRUE)//δ��ѡ��
	{
		SetTimer(1, m_editPeriod, NULL);
		((CEdit*)GetDlgItem(IDC_EDIT_PERIOD))->SetReadOnly(TRUE);
	}
	else
	{
		KillTimer(1);
		((CEdit*)GetDlgItem(IDC_EDIT_PERIOD))->SetReadOnly(FALSE);
	}
}


void Ccomm_appDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_mscomm.get_PortOpen())//����δ�򿪴���
	{
		KillTimer(1);
		((CEdit*)GetDlgItem(IDC_EDIT_PERIOD))->SetReadOnly(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_AUTOSEND))->SetCheck(FALSE);
		MessageBoxW(_T("����δ�򿪣�"));
	}
	else
	{
        CommSend();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

int Ccomm_appDlg::CommSend()
{
	UpdateData(true); //��ȡ�༭������

	CString temp_str;
	char temp_char[1024];
	unsigned char temp_hex[1024];
	int strlen;
	int i, j;
	CByteArray sendArr;


	_wsetlocale(LC_ALL, _T("")); //�������������õ������Ϣ�����õ�ǰ����ʹ�õı��ػ���Ϣ//�������û��

	//if (!m_mscomm.get_PortOpen())
	//{
	//	//m_mscomm.put_PortOpen(FALSE);
	//	MessageBoxW(_T("����δ�򿪣�"));
	//	return -1;
	//}

	CButton* p_check;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXSEND);
	if (p_check->GetCheck() == FALSE)
	{
		////ASCIIģʽ����//////////////////////////////////////////////////////////////////////////////
		if (m_editSend.GetLength() == 0)
		{
			MessageBoxW(_T("����������..."));
			return -1;
		}
		else
		{
		}
		m_mscomm.put_Output(COleVariant(m_editSend));//��������
		//m_editSend.Empty(); //���ͺ���������

		//ͨѶ״̬��ʾ
		//m_editRXNumber = _T("RX:0");
		GetDlgItem(IDC_EDIT_SENDNUMBER)->GetWindowTextW(temp_str);
		temp_str = temp_str.Mid(3);//�ӵ�4���ַ���ʼ��ȡ�ַ�������󣬲������ܴ����ַ�������
		int num = _ttoi(temp_str);
		num += m_editSend.GetLength();
		temp_str.Format(_T("%d"), num);
		m_editTXNumber = _T("TX:") + temp_str;
	}
	else
	{
		////HEXģʽ����//////////////////////////////////////////////////////////////////////////////
		//���͵Ļ�������ַ���CString��ֱ����m_mscom.put_Output(COleVariant(m_send)); �����ˡ�
		//ת���������͵Ļ���byte����
		//byte inst[9];
		//CByteArray sendArr;
		//sendArr.SetSize(9);
		//for (int j = 0; j<9; j++)
		//{
		//	sendArr.SetAt(j, inst[j]);
		//}
		//m_mscom.put_Output(COleVariant(sendArr));


		////////////cstring  ת����  hex����	
		temp_str = m_editSend;
		temp_str = temp_str.Trim();//ȥ��chr��β�Ŀո�
		wcstombs_s((size_t*)(&strlen), temp_char, 1024, (const wchar_t*)temp_str, _TRUNCATE);//strlen=�����ַ������ͽ����� �����ַ���2��
		//strlen = wcstombs(temp_char, temp_str, 100);//�ַ�CString   chr�ģ����Ƶ�char���� temp_char�� strlen=�����ַ������������������������ַ���2��
		//�Ͼ䱾������win8.1 64λ���� ����ʹ������
		if (strlen == 1)//û�������ַ� 
		{
			MessageBoxW(_T("����������..."));
			return -1;
		}
		else
		{
		}

		for (j = 0, i = 0; i < strlen; i++)//�ַ�������ո�
		{
			if (temp_char[i] != ' ')
			{
				temp_char[j] = temp_char[i];
				j++;
			}
			else
			{
			}
		}
		temp_char[j] = '\0';//�ַ�������

		for (i = 0; temp_char[i] != '\0'; i++)//�ж��Ƿ�Ϊ16�����ַ�
		{
			if (!(((temp_char[i] >= '0') && (temp_char[i] <= '9')) || ((temp_char[i] >= 'A') && (temp_char[i] <= 'F')) || ((temp_char[i] >= 'a') && (temp_char[i] <= 'f'))))
			{
				MessageBoxW(_T("�з�ʮ�������ַ�������������"));
				return -1;
			}
		}


		for (j = 0, i = 0; temp_char[i] != '\0'; i += 2)//ת��Ϊ16����  ��"ef"ת��Ϊ0xef
		{
			if (temp_char[i + 1] == '\0')
			{
				MessageBoxW(_T("�������ݸ�������ȷ������������"));
				return -1;
			}

			temp_hex[j] = (unsigned char)(ascii2hex(temp_char[i]) * 16 + ascii2hex(temp_char[i + 1]));
			j++;
		}

		GetDlgItem(IDC_COMBO_ENDCHAR)->GetWindowTextW(temp_str);
		if (_T("��") == temp_str)
		{

		}
		else if (_T("�ۼӺ�") == temp_str)
		{
			temp_hex[j] = 0;
			for (i = 0; i < j; i++)
			{
				temp_hex[j] += temp_hex[i];
			}
			j += 1;
		}
		else if (_T("����") == temp_str)
		{
			temp_hex[j] = 0;
			for (i = 0; i < j; i++)
			{
				temp_hex[j] ^= temp_hex[i];
			}
			j += 1;
		}
		else{}

		///////////hex����	 ת����  CByteArray
		sendArr.SetSize(j);
		for (i = 0; i < j; i++)
		{
			sendArr.SetAt(i, temp_hex[i]);
		}
		m_mscomm.put_Output(COleVariant(sendArr));//��������

		//ͨѶ״̬��ʾ
		//m_editRXNumber = _T("RX:0");
		GetDlgItem(IDC_EDIT_SENDNUMBER)->GetWindowTextW(temp_str);
		temp_str = temp_str.Mid(3);//�ӵ�4���ַ���ʼ��ȡ�ַ�������󣬲������ܴ����ַ�������
		int num = _ttoi(temp_str);
		num += j;
		temp_str.Format(_T("%d"), num);
		m_editTXNumber = _T("TX:") + temp_str;

	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	UpdateData(FALSE); //���±༭������
	return 0;
}


void Ccomm_appDlg::OnBnClickedButtonClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int result;
	result = MessageBoxW(_T("ȷ��Ҫ�˳�����"), _T("�˳�����"), IDOK);
	switch (result)/*ע�⣡ʹ��UnicodeӦ��TEXT��Χ�ִ�*/
	{
	    case IDOK:
			//MessageBoxW(_T("��ѡ���ˡ�ȷ����"), _T("ȷ��"));
			CDialog::OnCancel();
		break;
		case IDCANCEL:
			//MessageBoxW(_T("��ѡ���ˡ�ȡ����"), _T("ȡ��"));
		break;
	}
	//CDialog::OnClose();//���򲻹ر�
}



///////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_EVENTSINK_MAP(Ccomm_appDlg, CDialogEx)
	ON_EVENT(Ccomm_appDlg, IDC_MSCOMM1, 1, Ccomm_appDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

void Ccomm_appDlg::OnCommMscomm1()
{
	// TODO:  �ڴ˴������Ϣ����������
	static unsigned int cnt = 0;
	VARIANT variant_inp;//����VARIANT�ͱ��������ڴ�Ž��յ�������
	COleSafeArray safearray_inp;//����safearray�ͱ���
	long len, k;
	byte rxdata[1024]; //���� BYTE ����
	wchar_t strtemp[1024];
	CString strtemp1;
	CButton* p_check;
	CEdit* p_edit;
	//_wsetlocale(LC_ALL, _T("")); //�������������õ������Ϣ�����õ�ǰ����ʹ�õı��ػ���Ϣ

	switch (m_mscomm.get_CommEvent())
	{
	case 1: //comEvSend://ֵΪ 1 
		MessageBoxW(_T("���仺������"));
		break;
	case 2://comEvReceive://ֵΪ 2 ��ʾ���ջ����������ַ�
		cnt++;
		Sleep(100);
		variant_inp = m_mscomm.get_Input(); //�ѽ��յ������ݴ�ŵ�VARIANT�ͱ�����
		safearray_inp = variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
		len = safearray_inp.GetOneDimSize(); //�õ���Ч�����ݳ���
		for (k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);//�õ����յ������ݷŵ�BYTE������rxdata��
		}
		rxdata[k] = '\0';

		//ͨѶ״̬��ʾ
		GetDlgItem(IDC_EDIT_RECEIVENUMBER)->GetWindowTextW(strtemp1);
		strtemp1 = strtemp1.Mid(3);//�ӵ�4���ַ���ʼ��ȡ�ַ�������󣬲������ܴ����ַ�������
		k = _ttoi(strtemp1);
		k += len;
		strtemp1.Format(_T("%d"), k);
		m_editRXNumber = _T("RX:") + strtemp1;

		p_check = (CButton*)GetDlgItem(IDC_CHECK_STOPDISPLAY);//ֹͣ��ʾ
		if (p_check->GetCheck() == FALSE)
		{
			p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXRECEIVE);
			if (p_check->GetCheck() == FALSE)
			{//ASCII��ʾ��������
				//k=�����ַ������ͽ����� �����ַ���2��������ת���������⣺
				//����0��\null����Ч�ַ������ַ��ȣ���ֹͣת��
				mbstowcs_s((size_t*)(&k), strtemp, len + 1, (const char*)rxdata, _TRUNCATE);//��rxdata�е��ַ���ת��Ϊ���ַ�strtemp
				m_editReceive += strtemp;
			}
			else
			{//ʮ��������ʾ��������

				for (k = 0; k < len; k++) //������ת��Ϊ CString �ͱ���
				{
					//��һ����䣬��ʾ2���ַ�һ���ո�
					strtemp1.Format(_T("%-3.2x"), *(rxdata + k));
					m_editReceive += strtemp1;
				}
			}
			m_editReceive += _T("\r\n");//����
		}
		break;
	case 3://comEvCTS
		MessageBoxW(_T("Clear To Send �ߵ�״̬�����仯"));
		break;
	case 4://comEvDSR
		MessageBoxW(_T("Data Set Ready �ߵ�״̬�����仯"));
		break;
	case 5://comEvCD
		MessageBoxW(_T("Carrier Detect �ߵ�״̬�����仯"));
		break;
	case 6://comEvRing
		MessageBoxW(_T("��⵽�����ź�"));
		break;
	case 7://comEvRing
		MessageBoxW(_T("�յ��ļ�������ASCII �ַ�Ϊ 26���ַ�"));
		break;
	default:
		break;
	}

	UpdateData(FALSE); //���±༭������
	p_edit = (CEdit*)GetDlgItem(IDC_EDIT_RECEIVE);
	p_edit->LineScroll(p_edit->GetLineCount() - 1); //�Զ����������һ����ʾ
}


void Ccomm_appDlg::OnBnClickedCheckDtr()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CButton* p_check;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_DTR);
	if (p_check->GetCheck() == FALSE)
	{
		//MessageBoxW(_T("false"));
		m_mscomm.put_DTREnable(FALSE);//δʹ��DTR�ź�
		
	}
	else
	{
		//MessageBoxW(_T("true"));
		m_mscomm.put_DTREnable(TRUE);//ʹ��DTR�ź�
	}
}

void Ccomm_appDlg::OnBnClickedCheckRts()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CButton* p_check;
	BOOL a;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_RTS);
	a = m_mscomm.get_RTSEnable();//�õ�RTS�ź�
	a = m_mscomm.get_DTREnable();//�õ�DTR�ź�
	if (p_check->GetCheck() == FALSE)
	{
		m_mscomm.put_RTSEnable(FALSE);//δʹ��RTS�ź�
	}
	else
	{
		m_mscomm.put_RTSEnable(TRUE);//ʹ��RTS�ź�
	}
}


void Ccomm_appDlg::OnBnClickedButtonTxclear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_editSend.Empty(); //���ͺ���������
	UpdateData(FALSE); //���±༭������
}


void Ccomm_appDlg::OnBnClickedButtonRxclear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_editReceive.Empty(); //���ͺ���������
	UpdateData(FALSE); //���±༭������
}


int Ccomm_appDlg::ascii2hex(char ch)
{
	int hex = 0;
	/*if (ch == ' ')
	{
	}
	else */
	if ((ch >= '0') && (ch <= '9'))
	{
		hex = ch - '0';
	}
	else if ((ch >= 'A') && (ch <= 'F'))
	{
		hex = ch - 'A' + 10;
	}
	else if ((ch >= 'a') && (ch <= 'f'))
	{
		hex = ch - 'a' + 10;
	}
	else
	{
		hex = -1;
	}
	return hex;
}


void Ccomm_appDlg::OnCbnSelchangeComboCom()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboBaud()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboData()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboParity()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboStopbit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CommSet();
}



int Ccomm_appDlg::CommSet()
{
	CString str;
	//UpdateData(TRUE); //���±༭������
	//UpdateData(FALSE); //���±༭������
	/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->GetWindowTextW(str);
	if (str == _T("�رմ���"))
	{
		if (m_mscomm.get_PortOpen())
		{
			m_mscomm.put_PortOpen(FALSE);
		}
		m_mscomm.put_CommPort(((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel() + 1); //ѡ��COM1
		m_mscomm.put_InBufferSize(1024); //���ջ�����
		m_mscomm.put_OutBufferSize(1024);//���ͻ�����
		m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
		m_mscomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д���ݡ�1:comInputModeBinary�����Ʒ�ʽ,0:comInputModeText�ı���ʽ
		m_mscomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�
		CString setstr, setstr1;
		//((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetWindowTextW(setstr);//ʹ����䲻�ܵõ����ĺ��ֵ
		((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetCurSel(), setstr);
		setstr1 = setstr;
		//((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetWindowTextW(setstr);//ʹ����䲻�ܵõ����ĺ��ֵ
		((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetCurSel(), setstr);
		setstr1 += ',' + setstr;
		//((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetWindowTextW(setstr);//ʹ����䲻�ܵõ����ĺ��ֵ
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetCurSel(), setstr);
		setstr1 += ',' + setstr;
		//((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetWindowTextW(setstr);//ʹ����䲻�ܵõ����ĺ��ֵ
		((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetCurSel(), setstr);
		setstr1 += ',' + setstr;
		m_mscomm.put_Settings(setstr1);//������9600 �޼���λ��8������λ��1��ֹͣλ
		//m_mscomm.put_Settings(_T("9600,n,8,1"));//������9600 �޼���λ��8������λ��1��ֹͣλ
		m_mscomm.put_OutBufferCount(0);	 //��շ��ͻ�����
		m_mscomm.put_InBufferCount(0);	 //��ս��ջ�����

		if (!m_mscomm.get_PortOpen())//�������û�д����
		{
			try
			{
				m_mscomm.put_PortOpen(true);//�򿪴���
			}
			catch (COleDispatchException *e)
			{
				CString strError = _T("�򿪴���ʧ�ܣ�\n\r�����ţ�");
				wchar_t a[10];
				_ltow_s(e->m_wCode, a, 10);//�������ΪWORD���ͣ�longת���ɿ��ַ�wchar
				strError += a;
				strError += _T("\n\r������Ϣ��");
				strError += e->m_strDescription;//������ϢΪcstring����
				MessageBoxW(strError, _T("������ʾ"), MB_ICONERROR);


				//m_mscomm.put_PortOpen(FALSE);
				/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("�򿪴���"));
				//�ı�picLEDΪ��ɫ
				CBitmap bitmap; // CBitmap �������ڼ���λͼ 
				HBITMAP hBmp; // ���� CBitmap ���ص�λͼ��� 
				bitmap.LoadBitmap(IDB_BLACKLED); // ��λͼ IDB_REDLED ���ص� bitmap
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); // ��ȡ bitmap ����λͼ�ľ��
				m_picLED.SetBitmap(hBmp); // ����ͼƬ�ؼ�m_picLED ��λͼƬΪ  IDB_BLACKLED
				//��ʾ״̬��
				int u = (((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel() + 1);
				setstr.Format(_T("%d"), u);
				//((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
				GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
					+_T("COM")+
					setstr
					+ _T(" �ѹر�, ")
					+ m_mscomm.get_Settings()
					);
				return -1;
			}
			m_mscomm.put_RThreshold(1);//ÿ�����ջ�������һ���������ַ�����մ�������
			m_mscomm.put_InputLen(0);//���õ�ǰ����������Ϊ��0��ʾ��ȡȫ������
			m_mscomm.get_Input();	 //Ԥ���������������������
			/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("�رմ���"));
			//��ʾ״̬��
			((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
			GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
				setstr
				+ _T(" �Ѵ�, ")
				+ m_mscomm.get_Settings()
				);
			MessageBoxW(_T("���ڴ򿪳ɹ�"));
		}
		else
		{
			MessageBoxW(_T("���ڴ�ʧ��"));
		}
	}
	return 0;
}


void Ccomm_appDlg::OnBnClickedButtonClearnumber()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ͨѶ״̬��ʾ
	m_editRXNumber = _T("RX:0");
	m_editTXNumber = _T("TX:0");

	UpdateData(FALSE);
}

