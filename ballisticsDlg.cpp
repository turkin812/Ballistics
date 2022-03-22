
// maiatnicDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "ballistics.h"
#include "ballisticsDlg.h"
#include "afxdialogex.h"
#include <math.h>

#define M_PI 3.14159265358979323846
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//X
//- (Cd*r0*exp(-M*g*y / R*T*S) / 2.0 * m) * pow(x00_*x00_ + y_00*y_00, 0.5)*x00_
//
//Y
//- (Cd*r0*exp(-M*g*y / R*T*S) / 2.0 * m) * pow(x00_*x00_ + y_00*y_00, 0.5)*y00_ - g












double X__(double y, double y_00, double x_00, double Cd, double m, double S, double R){
	return(-(Cd*R*exp(-0.029*9.81*y / (8.31*253.))*S*S*M_PI / (2.0 * m)) * pow(x_00*x_00 + y_00*y_00, 0.5)*x_00);
}
double Y__(double y, double y_00, double x_00, double Cd, double m, double S, double R){
	return(-(Cd*R*exp(-0.029*9.81*y /( 8.31*253.))*S*S*M_PI / (2.0 * m)) * pow(x_00*x_00 + y_00*y_00, 0.5)*y_00 - 9.81);

} 


// диалоговое окно CmaiatnicDlg

void CballisticsDlg::p(){

	UpdateData(TRUE);
	
		y00_ = L*sin(M_PI*alfa / 180);
		x00_ = L*cos(M_PI*alfa / 180);
	
	double y0 = 0;
	double x0 = 0;
	double y_0 = y00_;
	double x_0 = x00_;
	double Xk1
		, Yk1
		, Xk2
		, Yk2
		, Xk3
		, Yk3
		, Xk4
		, Yk4;
	n = 0;
	m_DrawArea.RedrawWindow();
	Anim_area.RedrawWindow();
	energe.RedrawWindow();
	EN.RedrawWindow();
	EN1.RedrawWindow();
	
	//for (int i = 0; i < endt / dT + 2; i++)
	//{
	//	x[i] = -5;
	//	y[i] = -5;
	//	T[i] = 0;
	//	U[i] = 0;
	//	E[i] = 0;
	//}

	for (double t = 0; (t < endt); t = t + dT){


			x[n] = x0;
			y[n] = y0;
			T[n] = (pow(x_0, 2) + pow(y_0, 2)) * m / 2;//energe
			U[n] = (y0) * m * 9.81;//potencial energe
			E[n] = T[n] + U[n];
			v[n] = pow((pow(x_0, 2) + pow(y_0, 2)), 0.5);

			/*!check_nit || (y[n] >= ((pow(x00_, 2) + pow(y00_, 2)) / (3 * g) + 2 * y0_ / 3)) || (y[n] * y[n] + x[n] * x[n] >= L*L*/




			/*if (  !(  (  ((y0 * y0 + x0 * x0 < L*L-5)) ||     (y[n] >= ((pow(x00_, 2) + pow(y00_, 2)) / (3 * g) + 2 * y0_ / 3)))    &&    check_nit))
		/*	{X__(y, y_00, x_00, Cd, m)	Y__(y, y_00, x_00, Cd, m);*/
				/*Y__(double y, double L, double y00_, double x00_, double y0_, double Cd, double m)*/
			Xk1 = X__(y0, y_0, x_0, Cd, m, SSS, RRR)*dT;
			Yk1 = Y__(y0, y_0, x_0, Cd, m, SSS, RRR)*dT;

			Xk2 = X__((y0 + y_0 * dT / 2), y_0 + Yk1 / 2, x_0 + Xk1 / 2, Cd, m, SSS, RRR)*dT;
			Yk2 = Y__((y0 + y_0 * dT / 2), y_0 + Yk1 / 2, x_0 + Xk1 / 2, Cd, m, SSS, RRR)*dT;

			Xk3 = X__((y0 + y_0 * dT / 2 + Yk1 *dT / 4), y_0 + Yk2 / 2, x_0 + Xk2 / 2, Cd, m, SSS, RRR)*dT;
			Yk3 = Y__((y0 + y_0 * dT / 2 + Yk1 *dT / 4), y_0 + Yk2 / 2, x_0 + Xk2 / 2, Cd, m, SSS, RRR)*dT;

			Xk4 = X__((y0 + y_0 * dT + Yk2*dT / 2), y_0 + Yk3, x_0 + Xk3, Cd, m, SSS, RRR)*dT;
			Yk4 = Y__((y0 + y_0 * dT + Yk2*dT / 2), y_0 + Yk3, x_0 + Xk3, Cd, m,SSS,RRR)*dT;

			x0 = x0 + x_0 * dT + (Xk1 + Xk2 + Xk3)*dT / 6.;
			x_0 = x_0 + (Xk1 + 2 * Xk2 + 2 * Xk3 + Xk4) / 6.;

			y0 = y0 + y_0 * dT + (Yk1 + Yk2 + Yk3)*dT / 6.;
			y_0 = y_0 + (Yk1 + 2 * Yk2 + 2 * Yk3 + Yk4) / 6.;
			
			if (y[n] < 0)break;
			n++;

		}

	
	/*int x_min1 = 0;
	for (int i = 0; i < n; i++)
	{
		if ((abs(x[i + 1]) < abs(x[i])) && (abs(x[i + 2]) > abs(x[i + 1])) && (abs(x[i + 1]) < 0.1)){
			x_min1 = i + 1;
		}

	}
	int x_min2 = 0;
	for (int i = 0; i < x_min1 - 1; i++)
	{
		if ((abs(x[i + 1]) < abs(x[i])) && (abs(x[i + 2]) > abs(x[i + 1])) && (abs(x[i + 1]) < 0.1)){
			x_min2 = i + 1;
		}
	}*/
	/*t_pract =2*(x_min1 - x_min2)*dT;*/
	paint( "v,km/c",1000, v, 100, 100, 100, m_DrawArea);
	paint_energe(E[0], E, 20, 20, 200, energe);
	paint( "T,kДж",1, T, 20, 20, 200, EN);
	paint( "U,kДж",1, U, 200, 20, 200, EN1);
	//if (chek_garmonik)
	//{
	//	double y_max = x[0];
	//	double y_min=x[0];
	//	CClientDC dc(&m_DrawArea);
	//	RECT size;
	//	m_DrawArea.GetClientRect(&size);
	//	CPen aPen;
	//	aPen.CreatePen(PS_SOLID, 2, RGB(0, 100, 100));
	//	CPen *pOldPen = dc.SelectObject(&aPen);
	//	for (int i = 0; i < n; i++)//����� ������������� � ������������ ��������
	//	{
	//		if ((x[i])>y_max)
	//		{
	//			y_max = (x[i]);
	//		}
	//		if ((x[i])<y_min)
	//		{
	//			y_min = (x[i]);
	//		}


	//	}
	//	for (int i = 0; (30 + i*float(size.right - 50) / n <size.right); i++)
	//	{
	//		SetPixel(dc, int(15 + i*float(size.right - 50) / n), int((size.bottom / 2) - x0_*cos(i*dT*pow(g / L, 0.5)) * float(size.bottom-60) / (y_max - y_min)), RGB(0, 100, 56));
	//	}
	//	dc.SelectObject(pOldPen);
	//	t_teor = 2 * M_PI*pow(L / g, 0.5);
	//}
	UpdateData(FALSE);
}
void CballisticsDlg::paint(char *name, double y, double *x, int R, int G, int B, CStatic &Area)
{		

	double kx,ky;
	CString r;
	CString Nam(name);
	CClientDC dc(&Area);
	RECT size;
	Area.GetClientRect(&size);
	CPen aPen;
	aPen.CreatePen(PS_SOLID, 2, RGB(R,G , B));
	CPen *pOldPen = dc.SelectObject(&aPen);
	double y_min = x[0];
	double y_max = x[0];


	for (int i = 0; i < n; i++)//����� ������������� � ������������ ��������
	{
		if ((x[i])>y_max)
		{
			y_max = (x[i]);
		}
		if ((x[i])<y_min)
		{
			y_min = (x[i]);
		}


	}
	ky = double(size.bottom-50) / (y_max - y_min);
	/* int x0_pix = (30);
	 int y0_pix = (size.bottom / 2);*/
	kx = double(size.right - 50) / n;
	int y0_pix = (size.bottom / 2) + ((y_max + y_min) / 2)*ky;
	/*int x0_pix = -((a + b) / 2)*(kx) + ((size.right) / 2);*/
	int x0_pix = -(n / 2)*(kx)+((size.right) / 2) + 15;
	if (y0_pix<size.bottom - 10){
		dc.MoveTo(size.left, y0_pix);
		dc.LineTo(size.right, y0_pix);
	}

	dc.MoveTo(x0_pix, size.top);
	dc.LineTo(x0_pix, size.bottom);

	for (int i = 0; (i < n)&&(x0_pix+i*kx<size.right); i++)
	{
		
			SetPixel(dc, int(x0_pix + i*kx), int(y0_pix - x[i] * ky), RGB(200, 0, 56));
		




	}
	dc.TextOutW((x0_pix - 30), size.top, Nam);
	
	double v = 1 / dT;
	int f1 = 10;
	if (y0_pix -4>size.bottom){

		r = "t,c";
		dc.TextOutW((size.right - 20), size.bottom-30, r);

		
		for (int i = 0; (x0_pix + f1*v*kx*i<size.right - 30); i++)//������� �
		{
			CString r = 0;
			dc.MoveTo(x0_pix + f1*v* i*kx, size.bottom- 34);
			dc.LineTo(x0_pix + f1*v* i*kx, size.bottom - 26);
			r.Format(_T("%d"), f1*i);
			dc.TextOutW((x0_pix + f1*v*i*kx), size.bottom - 20, r);
		}
	
	
	}
	else{
		r = "t,c";
		dc.TextOutW((size.right - 20), y0_pix + 2, r);
		for (int i = 0; (x0_pix + f1*v*kx*i < size.right - 30); i++)//������� �
		{
			CString r = 0;
			dc.MoveTo(x0_pix + f1*v* i*kx, y0_pix - 4);
			dc.LineTo(x0_pix + f1*v* i*kx, y0_pix + 4);
			r.Format(_T("%d"), f1*i);
			dc.TextOutW((x0_pix + f1*v*i*kx), y0_pix + 10, r);
		}
	}

	float f =25/ky;
	
	for (float i =(-y0_pix+30)/(ky*f); (f*i*ky < size.bottom - y0_pix-30); i++)//������� �
	{
		CString r = 0;
		dc.MoveTo(x0_pix - 4, y0_pix + f*i*ky);
		dc.LineTo(x0_pix + 4, y0_pix + f*i*ky);
		r.Format(_T("%.f"), -y*f*i/1000);
		if (i != 0)
		{
			dc.TextOutW((x0_pix - 35), y0_pix + f*i*ky, r);
		}


	}





	/*if (chek_garmonik&&Area == m_DrawArea)t_teor = 2 * M_PI*pow(L / g, 0.5);*/

	dc.SelectObject(pOldPen);


}




void CballisticsDlg::paint_energe(double y, double *x, int R, int G, int B, CStatic &Area)
{

	float kx;
	float ky;
	CString r = 0;
	CClientDC dc(&Area);
	RECT size;
	Area.GetClientRect(&size);
	CPen aPen;
	aPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen *pOldPen = dc.SelectObject(&aPen);

	double y_min = x[0];
	double y_max = x[0];


	for (int i = 0; i < n-2; i++)//����� ������������� � ������������ ��������
	{
		if ((x[i])>y_max)
		{
			y_max = (x[i]);
		}
		if ((x[i])<y_min)
		{
			y_min = (x[i]);
		}


	}
	/* int x0_pix = (30);
	int y0_pix = (size.bottom / 2);*/
	kx = float(size.right - 50) / n;
	ky = float(size.bottom/2)/(y_max-y_min);
	int y0_pix = (size.bottom / 2) + int(((y_max + y_min) / 2-y)*ky);
	/*int x0_pix = -((a + b) / 2)*(kx) + ((size.right) / 2);*/
	int x0_pix = -(n / 2)*(kx)+((size.right) / 2) + 40;
	
	dc.MoveTo(size.left, size.bottom-30);
	dc.LineTo(size.right, size.bottom - 30);
	dc.MoveTo(x0_pix, size.top);
	dc.LineTo(x0_pix, size.bottom);

	for (int i = 0; (i < n) && (x0_pix + i*kx<size.right); i++)
	{
		SetPixel(dc, int(x0_pix + i*kx), int(y0_pix - x[i] * ky + y*ky), RGB(R, G, B));
	}
	r = "t,c";
	dc.TextOutW((size.right - 20), size.bottom - 30 + 10, r);
	r = "E,Дж";
	dc.TextOutW((x0_pix - 30), size.top, r);
	double v = 1 / dT;
	int f1 = 20;
	for (int i = 0; (x0_pix + f1*v*kx*i<size.right - 30); i++)//������� �
	{
		CString r = 0;
		dc.MoveTo(x0_pix + f1*v* i*kx, size.bottom - 30 - 4);
		dc.LineTo(x0_pix + f1*v* i*kx, size.bottom - 30 + 4);
		r.Format(_T("%d"), f1*i);
		dc.TextOutW((x0_pix + f1*v*i*kx), size.bottom - 30 + 10, r);
	}


	int f = 2;
	r = "";
	dc.MoveTo(x0_pix - 4, int(y0_pix - y_max * ky + y*ky) - 5);
	dc.LineTo(x0_pix + 4, int(y0_pix - y_max * ky + y*ky) - 5);
	r.Format(_T("%f"), y+5/ky);
	dc.TextOutW((x0_pix - 40), int(y0_pix - y_max * ky + y*ky) - 30, r);

	dc.MoveTo(x0_pix - 4, int(y0_pix - y_min * ky + y*ky) + 5);
	dc.LineTo(x0_pix + 4, int(y0_pix - y_min * ky + y*ky) + 5);
	r.Format(_T("%f"),y-5/ky);
	dc.TextOutW((x0_pix - 40), int(y0_pix - y_min * ky + y*ky) + 10, r);

	//for (int i = (-y0_pix) / (ky*f) -y*ky; (f*i*ky < size.bottom - y0_pix); i++)//������� �
	//{
	//	CString r = 0;
	//	dc.MoveTo(x0_pix - 4, size.bottom - 30 + f*i*10);
	//	dc.LineTo(x0_pix + 4, size.bottom - 30 + f*i*10);
	//	r.Format(_T("%d"), -f*i - y*ky);
	//	if (i != 0)
	//	{
	//		dc.TextOutW((x0_pix - 25), size.bottom - 30 + f*i*ky, r);
	//	}


	//}
	dc.SelectObject(pOldPen);


}
double y_max;
void CballisticsDlg::Anim(){
	/*UpdateData(TRUE);*/
	Anim_area.RedrawWindow();
	ntimeout = int(dT*10/*00*/);
	
	I = 0;

	y_max = 0;

	for (int i = 0; i < n - 2; i++)//����� ������������� � ������������ ��������
	{
		if ((y[i])>y_max)
		{
			y_max = (y[i]);
		}
		


	}
	nTimer = SetTimer(ID_TIMER1, ntimeout, NULL);

}

void CballisticsDlg::OnTimer(UINT){

	CClientDC dc(&Anim_area);
	RECT size;
	Anim_area.GetClientRect(&size);
	CPen aPen;
	aPen.CreatePen(PS_SOLID, 2, RGB(0, 0,0));
	CPen *pOldPen = dc.SelectObject(&aPen);
	CString r;
	/*Anim_area.RedrawWindow();*/
	int x0_pix = 30;
	int y0_pix = (size.bottom -60);
	dc.MoveTo(size.left, y0_pix);
	dc.LineTo(size.right, y0_pix);
	dc.MoveTo(x0_pix, size.top);
	dc.LineTo(x0_pix, size.bottom);
	float ky = float(size.bottom-70) / (y_max);
	float kx = float(size.right - 70) / x[n-1];;
	/*for (int i = 0; (i < n) && (x0_pix + i*0.2<size.right); i++)
	{*/
	int H = 2;
	if (I >= n){
			I = 0;
		}
	Ellipse(dc,
		int(x0_pix + x[I] * kx) - H - 2,
		int(y0_pix - y[I] *ky) - H - 2,
		int(x0_pix + x[I] * kx) + H + 2,
		int(y0_pix - y[I] * ky) + H + 2);

		/*SetPixel(dc, int(x0_pix + x[I-1] * 15), int(y0_pix - y[I-1] * 15),RGB());*/
		/*SetPixel(dc, int(x0_pix + x[I]*15), int(y0_pix - y[I] * 15), RGB(200, 0, 56));*/
	//}
	Ellipse(dc,
		int(x0_pix )  - 2,
		int(y0_pix)  - 2,
		int(x0_pix)  + 2,
		int(y0_pix )  + 2);
	
	/*int ky = 18;*/
	double f1 = 30;
	for (int i = (0); ( f1*i<size.right-20-x0_pix); i++)//������� �
	{
		
		dc.MoveTo(x0_pix + f1* i, y0_pix - 4);
		dc.LineTo(x0_pix + f1* i, y0_pix + 4);
		r.Format(_T("%.f"), i*f1/kx/1000);
		dc.TextOutW((x0_pix + f1*i), y0_pix + 10, r);
	}


	double f = 30;
	for (int i = (0); (f*i <y0_pix-20); i++)//������� �
	{
		
		dc.MoveTo(x0_pix - 4, y0_pix - f*i);
		dc.LineTo(x0_pix + 4, y0_pix - f*i);
		r.Format(_T("%.f"), i *f/ ky/1000.);
		if (i != 0)
		{
			dc.TextOutW((x0_pix - 25), y0_pix - f*i, r);
		}


	}

	r = "x,km";
	dc.TextOutW((size.right - 25), y0_pix +30, r);
	r = "y,km";
	dc.TextOutW((x0_pix - 30), size.top+5, r);
	
		I++;
		
		dc.SelectObject(pOldPen);
}
CballisticsDlg::CballisticsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CballisticsDlg::IDD, pParent),

	 Cd(0.315)
	, L(655)
	, x00_(0)
	, y00_(0)
	, m(43.56)
	, y0_(0)

	, dT(0.2)
	, endt(100)
	, chek_garmonik(FALSE)
	, alfa(45)
	, t_pract(0)
	, t_teor(0)
	, check_nit(FALSE)
	, SSS(0.076)
	, RRR(1.29)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CballisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPH, m_DrawArea);
	DDX_Text(pDX, IDC_G, Cd);

	DDX_Text(pDX, IDC_X0, m);
	DDX_Text(pDX, IDC_SSS,SSS);
	DDX_Text(pDX, IDC_RRR, RRR);
	DDX_Text(pDX, IDC_L, L);
	DDX_Text(pDX, IDC_DT, dT);
	DDX_Text(pDX, IDC_ENDT, endt);

	DDX_Control(pDX, IDC_ANIM, Anim_area);
	DDX_Text(pDX, IDC_ALFA, alfa);
	DDV_MinMaxInt(pDX, alfa, 0, 180);
	DDX_Control(pDX, IDC_ENERGE, energe);


	DDX_Control(pDX, IDC_EN, EN);
	DDX_Control(pDX, IDC_EN1, EN1);
}

BEGIN_MESSAGE_MAP(CballisticsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(But, CballisticsDlg::p)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUT_ANIM, &CballisticsDlg::Anim)
	ON_BN_CLICKED(IDCANCEL, &CballisticsDlg::OnBnClickedCancel)
	ON_STN_CLICKED(IDC_T_TEOR, &CballisticsDlg::OnStnClickedTTeor)
	ON_STN_CLICKED(IDC_T_PRACT, &CballisticsDlg::OnStnClickedTPract)
END_MESSAGE_MAP()


// обработчики сообщений CmaiatnicDlg

BOOL CballisticsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	// TODO: добавьте дополнительную инициализацию
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CballisticsDlg::OnPaint()
{

	if (IsIconic())
	{
		
		p();

	}
	else
	{

		CDialogEx::OnPaint();



	}
	
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CballisticsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CballisticsDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений

	KillTimer(nTimer);
}


void CballisticsDlg::OnStnClickedTTeor()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CballisticsDlg::OnStnClickedTPract()
{
	// TODO: добавьте свой код обработчика уведомлений
}
