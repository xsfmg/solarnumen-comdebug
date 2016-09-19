
// comm_appDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Ccomm_appDlg 对话框



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


// Ccomm_appDlg 消息处理程序

BOOL Ccomm_appDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码



	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//串口开始界面初始化
	//串口号下拉列表
	CString strTemp;
	wchar_t seriou[10];
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->ResetContent();//消除现有所有内容
	for (int i = 1; i <= 15; i++)
	{		
		_ltow_s(i, seriou, 10);//错误编码为WORD类型，long转换成宽字符wchar
		strTemp = seriou;
		((CComboBox*)GetDlgItem(IDC_COMBO_COM))->AddString(_T("COM") + strTemp);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_COM))->SetCurSel(0);
	//串口波特率下拉列表
	wchar_t baudbuffer[][7] = { _T("300"),   _T("600"),   _T("1200"),  _T("2400"),  _T("4800"),  _T("9600"),
		                        _T("19200"), _T("38400"), _T("43000"), _T("56000"), _T("57600"), _T("115200") };
	for (int i = 0; i<12; i++)
	{
		int judge_tf = ((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->AddString(baudbuffer[i]);
		if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			MessageBox(_T("build baud error!"));
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->SetCurSel(5);
	//串口校验位下拉列表
	wchar_t jiaoyan[][7] = { _T("N"), _T("O"), _T("E") };
	for (int i = 0; i<3; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->AddString(jiaoyan[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->SetCurSel(0);
	//串口数据位下拉列表
	wchar_t data[][2] = { _T("8"), _T("7"), _T("6") };
	for (int i = 0; i<3; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->AddString(data[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->SetCurSel(0);
	//串口停止位下拉列表
	wchar_t stop[][2] = { _T("1"), _T("2") };
	for(int i=0;i<2;i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->AddString(stop[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->SetCurSel(0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//显示状态栏
	GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(_T("COM1 已关闭, 9600, n, 8, 1"));
	//修改图片控件属性为位图，vs2013 bug
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_PictureLED); // 得到 Picture Control 句柄
	pWnd->ModifyStyle(0, SS_BITMAP); // 修改它的属性为位图
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//结束符下拉列表
	wchar_t endchar[][8] = { _T("无"), _T("累加和"), _T("异或和") };
	for (int i = 0; i<3; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_ENDCHAR))->AddString(endchar[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_ENDCHAR))->SetCurSel(0);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//输入框显示
	m_editSend = _T("01 01 02");
	//GetDlgItem(IDC_EDIT_SEND)->SetWindowTextW(_T("01 01 02"));
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//十六进制发送、接收复选框初始化为有效
	CButton *p_check;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXRECEIVE);
	p_check->SetCheck(TRUE);
	p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXSEND);
	p_check->SetCheck(TRUE);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//通讯状态显示
	m_editRXNumber = _T("RX:0");
	m_editTXNumber = _T("TX:0");
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//自动发送周期显示
	m_editPeriod = 1000;



	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ccomm_appDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ccomm_appDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//////////////////////////////////////////////////////////////////////////////////////////////
void Ccomm_appDlg::OnBnClickedButtonOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	CString setstr, setstr1;
	/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->GetWindowTextW(str);
	if (str == _T("打开串口"))
	{
		if (m_mscomm.get_PortOpen())
		{
			m_mscomm.put_PortOpen(FALSE);
		}
		int comm = ((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel();
		m_mscomm.put_CommPort(((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel()+1); //选择COM1
		m_mscomm.put_InBufferSize(1024); //接收缓冲区
		m_mscomm.put_OutBufferSize(1024);//发送缓冲区
		m_mscomm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取
		m_mscomm.put_InputMode(1);//以二进制方式读写数据。1:comInputModeBinary二进制方式,0:comInputModeText文本方式
		m_mscomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件
		
		((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetWindowTextW(setstr);
		setstr1 = setstr;
		((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetWindowTextW(setstr);
		setstr1 += ','+ setstr;
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetWindowTextW(setstr);
		setstr1 += ',' + setstr;
		((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetWindowTextW(setstr);
		setstr1 += ',' + setstr;
		m_mscomm.put_Settings(setstr1);//波特率9600 无检验位，8个数据位，1个停止位
		//m_mscomm.put_Settings(_T("9600,n,8,1"));//波特率9600 无检验位，8个数据位，1个停止位
		m_mscomm.put_OutBufferCount(0);	 //清空发送缓冲区
		m_mscomm.put_InBufferCount(0);	 //清空接收缓冲区
		

		if (!m_mscomm.get_PortOpen())//如果串口没有打开则打开
		{
			try
			{
				m_mscomm.put_PortOpen(true);//打开串口
			}
			//提示方法3
			catch (COleDispatchException *e)
			{
				CString strError = _T("打开串口失败！\n\r错误编号：");
				wchar_t a[10];
				_ltow_s(e->m_wCode, a, 10);//错误编码为WORD类型，long转换成宽字符wchar
				strError += a;
				strError += _T("\n\r错误信息：");
				strError += e->m_strDescription;//错误信息为cstring类型
				MessageBoxW(strError, _T("错误提示"), MB_ICONERROR);

				//显示状态栏
				int u = (((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel() + 1);
				setstr.Format(_T("%d"), u);
				//((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
				GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
					+_T("COM") +
					setstr
					+ _T(" 已关闭, ")
					+ m_mscomm.get_Settings()
					);
				return;
			}
			//提示方法2
			/*catch (COleDispatchException *e)
			{
				CString strError = _T("打开串口失败！\n\r错误信息：\n\r");
				    strError += e->m_strDescription;//错误信息为cstring类型
					MessageBoxW(strError, _T("错误提示"), MB_ICONERROR);
					return;
			}*/
			//提示方法1
			/*catch (...)
			{
				MessageBoxW(_T("该串口已被占用，请选择其他串口"), _T("错误提示"), MB_ICONERROR);
				return ;
			}*/
			
			//m_mscomm.put_PortOpen(TRUE);//打开串口
			m_mscomm.put_RThreshold(1);//每当接收缓冲区有一个及以上字符则接收串口数据
			m_mscomm.put_InputLen(0);//设置当前缓冲区长度为，0表示读取全部数据
			m_mscomm.get_Input();	 //预读缓冲区以清除残留数据
			/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("关闭串口"));
			//改变picLED为红色
			CBitmap bitmap; // CBitmap 对象，用于加载位图 
			HBITMAP hBmp; // 保存 CBitmap 加载的位图句柄 
			bitmap.LoadBitmap(IDB_REDLED); // 将位图 IDB_REDLED 加载到 bitmap
			hBmp = (HBITMAP )bitmap.GetSafeHandle(); // 获取 bitmap 加载位图的句柄
			m_picLED.SetBitmap(hBmp); // 设置图片控件m_picLED 的位图片为  IDB_REDLED
			//显示状态栏
			((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
			GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
				setstr
				+ _T(" 已打开, ")
				+ m_mscomm.get_Settings()
				);
			
			MessageBoxW(_T("串口打开成功"));
		}
		else
		{
			MessageBoxW(_T("串口打开失败"));
		}
	}
	else
	{
		m_mscomm.put_PortOpen(FALSE);
		/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("打开串口"));
		//改变picLED为黑色
		CBitmap bitmap; // CBitmap 对象，用于加载位图 
		HBITMAP hBmp; // 保存 CBitmap 加载的位图句柄 
		bitmap.LoadBitmap(IDB_BLACKLED); // 将位图 IDB_REDLED 加载到 bitmap
		hBmp = (HBITMAP)bitmap.GetSafeHandle(); // 获取 bitmap 加载位图的句柄
		m_picLED.SetBitmap(hBmp); // 设置图片控件m_picLED 的位图片为  IDB_BLACKLED
		//显示状态栏
		((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
		GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
			setstr
			+ _T(" 已关闭, ")
			+ m_mscomm.get_Settings()
			);
		MessageBoxW(_T("串口关闭成功"));
	}
	

}

///////////////////////////

void Ccomm_appDlg::OnBnClickedButtonSend()
{
	// TODO:  在此添加控件通知处理程序代码

	if (!m_mscomm.get_PortOpen())//串口未打开处理
	{
		//m_mscomm.put_PortOpen(FALSE);
		MessageBoxW(_T("串口未打开！"));
		return ;
	}
    CommSend();
}

void Ccomm_appDlg::OnBnClickedCheckAutosend()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK_AUTOSEND))->GetCheck() == TRUE)//未被选中
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_mscomm.get_PortOpen())//串口未打开处理
	{
		KillTimer(1);
		((CEdit*)GetDlgItem(IDC_EDIT_PERIOD))->SetReadOnly(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_AUTOSEND))->SetCheck(FALSE);
		MessageBoxW(_T("串口未打开！"));
	}
	else
	{
        CommSend();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

int Ccomm_appDlg::CommSend()
{
	UpdateData(true); //读取编辑框内容

	CString temp_str;
	char temp_char[1024];
	unsigned char temp_hex[1024];
	int strlen;
	int i, j;
	CByteArray sendArr;


	_wsetlocale(LC_ALL, _T("")); //本函数用来配置地域的信息，设置当前程序使用的本地化信息//本程序好没用

	//if (!m_mscomm.get_PortOpen())
	//{
	//	//m_mscomm.put_PortOpen(FALSE);
	//	MessageBoxW(_T("串口未打开！"));
	//	return -1;
	//}

	CButton* p_check;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXSEND);
	if (p_check->GetCheck() == FALSE)
	{
		////ASCII模式发送//////////////////////////////////////////////////////////////////////////////
		if (m_editSend.GetLength() == 0)
		{
			MessageBoxW(_T("请输入数据..."));
			return -1;
		}
		else
		{
		}
		m_mscomm.put_Output(COleVariant(m_editSend));//发送数据
		//m_editSend.Empty(); //发送后清空输入框

		//通讯状态显示
		//m_editRXNumber = _T("RX:0");
		GetDlgItem(IDC_EDIT_SENDNUMBER)->GetWindowTextW(temp_str);
		temp_str = temp_str.Mid(3);//从第4个字符开始截取字符串到最后，参数不能大于字符串长度
		int num = _ttoi(temp_str);
		num += m_editSend.GetLength();
		temp_str.Format(_T("%d"), num);
		m_editTXNumber = _T("TX:") + temp_str;
	}
	else
	{
		////HEX模式发送//////////////////////////////////////////////////////////////////////////////
		//发送的话如果是字符串CString，直接用m_mscom.put_Output(COleVariant(m_send)); 就行了。
		//转换数据类型的话如byte如下
		//byte inst[9];
		//CByteArray sendArr;
		//sendArr.SetSize(9);
		//for (int j = 0; j<9; j++)
		//{
		//	sendArr.SetAt(j, inst[j]);
		//}
		//m_mscom.put_Output(COleVariant(sendArr));


		////////////cstring  转换成  hex数组	
		temp_str = m_editSend;
		temp_str = temp_str.Trim();//去掉chr首尾的空格
		wcstombs_s((size_t*)(&strlen), temp_char, 1024, (const wchar_t*)temp_str, _TRUNCATE);//strlen=串中字符个数和结束符 中文字符算2个
		//strlen = wcstombs(temp_char, temp_str, 100);//字符CString   chr的，复制到char数组 temp_char中 strlen=串中字符个数，不包括结束符中文字符算2个
		//上句本程序在win8.1 64位机上 不好使，报错
		if (strlen == 1)//没有输入字符 
		{
			MessageBoxW(_T("请输入数据..."));
			return -1;
		}
		else
		{
		}

		for (j = 0, i = 0; i < strlen; i++)//字符串清除空格
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
		temp_char[j] = '\0';//字符串结束

		for (i = 0; temp_char[i] != '\0'; i++)//判断是否为16进制字符
		{
			if (!(((temp_char[i] >= '0') && (temp_char[i] <= '9')) || ((temp_char[i] >= 'A') && (temp_char[i] <= 'F')) || ((temp_char[i] >= 'a') && (temp_char[i] <= 'f'))))
			{
				MessageBoxW(_T("有非十六进制字符，请重新输入"));
				return -1;
			}
		}


		for (j = 0, i = 0; temp_char[i] != '\0'; i += 2)//转换为16进制  即"ef"转换为0xef
		{
			if (temp_char[i + 1] == '\0')
			{
				MessageBoxW(_T("输入数据个数不正确，请重新输入"));
				return -1;
			}

			temp_hex[j] = (unsigned char)(ascii2hex(temp_char[i]) * 16 + ascii2hex(temp_char[i + 1]));
			j++;
		}

		GetDlgItem(IDC_COMBO_ENDCHAR)->GetWindowTextW(temp_str);
		if (_T("无") == temp_str)
		{

		}
		else if (_T("累加和") == temp_str)
		{
			temp_hex[j] = 0;
			for (i = 0; i < j; i++)
			{
				temp_hex[j] += temp_hex[i];
			}
			j += 1;
		}
		else if (_T("异或和") == temp_str)
		{
			temp_hex[j] = 0;
			for (i = 0; i < j; i++)
			{
				temp_hex[j] ^= temp_hex[i];
			}
			j += 1;
		}
		else{}

		///////////hex数组	 转换成  CByteArray
		sendArr.SetSize(j);
		for (i = 0; i < j; i++)
		{
			sendArr.SetAt(i, temp_hex[i]);
		}
		m_mscomm.put_Output(COleVariant(sendArr));//发送数据

		//通讯状态显示
		//m_editRXNumber = _T("RX:0");
		GetDlgItem(IDC_EDIT_SENDNUMBER)->GetWindowTextW(temp_str);
		temp_str = temp_str.Mid(3);//从第4个字符开始截取字符串到最后，参数不能大于字符串长度
		int num = _ttoi(temp_str);
		num += j;
		temp_str.Format(_T("%d"), num);
		m_editTXNumber = _T("TX:") + temp_str;

	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	UpdateData(FALSE); //更新编辑框内容
	return 0;
}


void Ccomm_appDlg::OnBnClickedButtonClose()
{
	// TODO:  在此添加控件通知处理程序代码
	int result;
	result = MessageBoxW(_T("确定要退出程序？"), _T("退出程序"), IDOK);
	switch (result)/*注意！使用Unicode应用TEXT包围字串*/
	{
	    case IDOK:
			//MessageBoxW(_T("您选择了“确定”"), _T("确定"));
			CDialog::OnCancel();
		break;
		case IDCANCEL:
			//MessageBoxW(_T("您选择了“取消”"), _T("取消"));
		break;
	}
	//CDialog::OnClose();//程序不关闭
}



///////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_EVENTSINK_MAP(Ccomm_appDlg, CDialogEx)
	ON_EVENT(Ccomm_appDlg, IDC_MSCOMM1, 1, Ccomm_appDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

void Ccomm_appDlg::OnCommMscomm1()
{
	// TODO:  在此处添加消息处理程序代码
	static unsigned int cnt = 0;
	VARIANT variant_inp;//定义VARIANT型变量，用于存放接收到的数据
	COleSafeArray safearray_inp;//定义safearray型变量
	long len, k;
	byte rxdata[1024]; //设置 BYTE 数组
	wchar_t strtemp[1024];
	CString strtemp1;
	CButton* p_check;
	CEdit* p_edit;
	//_wsetlocale(LC_ALL, _T("")); //本函数用来配置地域的信息，设置当前程序使用的本地化信息

	switch (m_mscomm.get_CommEvent())
	{
	case 1: //comEvSend://值为 1 
		MessageBoxW(_T("传输缓冲区空"));
		break;
	case 2://comEvReceive://值为 2 表示接收缓冲区内有字符
		cnt++;
		Sleep(100);
		variant_inp = m_mscomm.get_Input(); //把接收到的数据存放到VARIANT型变量里
		safearray_inp = variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
		len = safearray_inp.GetOneDimSize(); //得到有效的数据长度
		for (k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);//得到接收到的数据放到BYTE型数组rxdata里
		}
		rxdata[k] = '\0';

		//通讯状态显示
		GetDlgItem(IDC_EDIT_RECEIVENUMBER)->GetWindowTextW(strtemp1);
		strtemp1 = strtemp1.Mid(3);//从第4个字符开始截取字符串到最后，参数不能大于字符串长度
		k = _ttoi(strtemp1);
		k += len;
		strtemp1.Format(_T("%d"), k);
		m_editRXNumber = _T("RX:") + strtemp1;

		p_check = (CButton*)GetDlgItem(IDC_CHECK_STOPDISPLAY);//停止显示
		if (p_check->GetCheck() == FALSE)
		{
			p_check = (CButton*)GetDlgItem(IDC_CHECK_HEXRECEIVE);
			if (p_check->GetCheck() == FALSE)
			{//ASCII显示接受数据
				//k=串中字符个数和结束符 中文字符算2个，下面转换存在问题：
				//遇到0、\null、无效字符、宽字符等，则停止转换
				mbstowcs_s((size_t*)(&k), strtemp, len + 1, (const char*)rxdata, _TRUNCATE);//将rxdata中的字符串转换为宽字符strtemp
				m_editReceive += strtemp;
			}
			else
			{//十六进制显示接受数据

				for (k = 0; k < len; k++) //将数组转换为 CString 型变量
				{
					//下一条语句，显示2个字符一个空格
					strtemp1.Format(_T("%-3.2x"), *(rxdata + k));
					m_editReceive += strtemp1;
				}
			}
			m_editReceive += _T("\r\n");//换行
		}
		break;
	case 3://comEvCTS
		MessageBoxW(_T("Clear To Send 线的状态发生变化"));
		break;
	case 4://comEvDSR
		MessageBoxW(_T("Data Set Ready 线的状态发生变化"));
		break;
	case 5://comEvCD
		MessageBoxW(_T("Carrier Detect 线的状态发生变化"));
		break;
	case 6://comEvRing
		MessageBoxW(_T("检测到振铃信号"));
		break;
	case 7://comEvRing
		MessageBoxW(_T("收到文件结束（ASCII 字符为 26）字符"));
		break;
	default:
		break;
	}

	UpdateData(FALSE); //更新编辑框内容
	p_edit = (CEdit*)GetDlgItem(IDC_EDIT_RECEIVE);
	p_edit->LineScroll(p_edit->GetLineCount() - 1); //自动滚屏到最后一行显示
}


void Ccomm_appDlg::OnBnClickedCheckDtr()
{
	// TODO:  在此添加控件通知处理程序代码
	CButton* p_check;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_DTR);
	if (p_check->GetCheck() == FALSE)
	{
		//MessageBoxW(_T("false"));
		m_mscomm.put_DTREnable(FALSE);//未使能DTR信号
		
	}
	else
	{
		//MessageBoxW(_T("true"));
		m_mscomm.put_DTREnable(TRUE);//使能DTR信号
	}
}

void Ccomm_appDlg::OnBnClickedCheckRts()
{
	// TODO:  在此添加控件通知处理程序代码
	CButton* p_check;
	BOOL a;
	p_check = (CButton*)GetDlgItem(IDC_CHECK_RTS);
	a = m_mscomm.get_RTSEnable();//得到RTS信号
	a = m_mscomm.get_DTREnable();//得到DTR信号
	if (p_check->GetCheck() == FALSE)
	{
		m_mscomm.put_RTSEnable(FALSE);//未使能RTS信号
	}
	else
	{
		m_mscomm.put_RTSEnable(TRUE);//使能RTS信号
	}
}


void Ccomm_appDlg::OnBnClickedButtonTxclear()
{
	// TODO:  在此添加控件通知处理程序代码
	m_editSend.Empty(); //发送后清空输入框
	UpdateData(FALSE); //更新编辑框内容
}


void Ccomm_appDlg::OnBnClickedButtonRxclear()
{
	// TODO:  在此添加控件通知处理程序代码
	m_editReceive.Empty(); //发送后清空输入框
	UpdateData(FALSE); //更新编辑框内容
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
	// TODO:  在此添加控件通知处理程序代码
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboBaud()
{
	// TODO:  在此添加控件通知处理程序代码
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboData()
{
	// TODO:  在此添加控件通知处理程序代码
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboParity()
{
	// TODO:  在此添加控件通知处理程序代码
	CommSet();
}


void Ccomm_appDlg::OnCbnSelchangeComboStopbit()
{
	// TODO:  在此添加控件通知处理程序代码
	CommSet();
}



int Ccomm_appDlg::CommSet()
{
	CString str;
	//UpdateData(TRUE); //更新编辑框内容
	//UpdateData(FALSE); //更新编辑框内容
	/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->GetWindowTextW(str);
	if (str == _T("关闭串口"))
	{
		if (m_mscomm.get_PortOpen())
		{
			m_mscomm.put_PortOpen(FALSE);
		}
		m_mscomm.put_CommPort(((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel() + 1); //选择COM1
		m_mscomm.put_InBufferSize(1024); //接收缓冲区
		m_mscomm.put_OutBufferSize(1024);//发送缓冲区
		m_mscomm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取
		m_mscomm.put_InputMode(1);//以二进制方式读写数据。1:comInputModeBinary二进制方式,0:comInputModeText文本方式
		m_mscomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件
		CString setstr, setstr1;
		//((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetWindowTextW(setstr);//使用这句不能得到更改后的值
		((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_BAUD))->GetCurSel(), setstr);
		setstr1 = setstr;
		//((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetWindowTextW(setstr);//使用这句不能得到更改后的值
		((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_PARITY))->GetCurSel(), setstr);
		setstr1 += ',' + setstr;
		//((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetWindowTextW(setstr);//使用这句不能得到更改后的值
		((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_DATA))->GetCurSel(), setstr);
		setstr1 += ',' + setstr;
		//((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetWindowTextW(setstr);//使用这句不能得到更改后的值
		((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT))->GetCurSel(), setstr);
		setstr1 += ',' + setstr;
		m_mscomm.put_Settings(setstr1);//波特率9600 无检验位，8个数据位，1个停止位
		//m_mscomm.put_Settings(_T("9600,n,8,1"));//波特率9600 无检验位，8个数据位，1个停止位
		m_mscomm.put_OutBufferCount(0);	 //清空发送缓冲区
		m_mscomm.put_InBufferCount(0);	 //清空接收缓冲区

		if (!m_mscomm.get_PortOpen())//如果串口没有打开则打开
		{
			try
			{
				m_mscomm.put_PortOpen(true);//打开串口
			}
			catch (COleDispatchException *e)
			{
				CString strError = _T("打开串口失败！\n\r错误编号：");
				wchar_t a[10];
				_ltow_s(e->m_wCode, a, 10);//错误编码为WORD类型，long转换成宽字符wchar
				strError += a;
				strError += _T("\n\r错误信息：");
				strError += e->m_strDescription;//错误信息为cstring类型
				MessageBoxW(strError, _T("错误提示"), MB_ICONERROR);


				//m_mscomm.put_PortOpen(FALSE);
				/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("打开串口"));
				//改变picLED为黑色
				CBitmap bitmap; // CBitmap 对象，用于加载位图 
				HBITMAP hBmp; // 保存 CBitmap 加载的位图句柄 
				bitmap.LoadBitmap(IDB_BLACKLED); // 将位图 IDB_REDLED 加载到 bitmap
				hBmp = (HBITMAP)bitmap.GetSafeHandle(); // 获取 bitmap 加载位图的句柄
				m_picLED.SetBitmap(hBmp); // 设置图片控件m_picLED 的位图片为  IDB_BLACKLED
				//显示状态栏
				int u = (((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetCurSel() + 1);
				setstr.Format(_T("%d"), u);
				//((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
				GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
					+_T("COM")+
					setstr
					+ _T(" 已关闭, ")
					+ m_mscomm.get_Settings()
					);
				return -1;
			}
			m_mscomm.put_RThreshold(1);//每当接收缓冲区有一个及以上字符则接收串口数据
			m_mscomm.put_InputLen(0);//设置当前缓冲区长度为，0表示读取全部数据
			m_mscomm.get_Input();	 //预读缓冲区以清除残留数据
			/*(CButton*)*/GetDlgItem(IDC_BUTTON_OPEN)->SetWindowTextW(_T("关闭串口"));
			//显示状态栏
			((CComboBox*)GetDlgItem(IDC_COMBO_COM))->GetWindowTextW(setstr);
			GetDlgItem(IDC_EDIT_STATE)->SetWindowTextW(
				setstr
				+ _T(" 已打开, ")
				+ m_mscomm.get_Settings()
				);
			MessageBoxW(_T("串口打开成功"));
		}
		else
		{
			MessageBoxW(_T("串口打开失败"));
		}
	}
	return 0;
}


void Ccomm_appDlg::OnBnClickedButtonClearnumber()
{
	// TODO:  在此添加控件通知处理程序代码
	//通讯状态显示
	m_editRXNumber = _T("RX:0");
	m_editTXNumber = _T("TX:0");

	UpdateData(FALSE);
}

