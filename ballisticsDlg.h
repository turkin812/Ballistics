
// ballisticsDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"
#define ID_TIMER1 1000
// диалоговое окно CballisticsDlg
class CballisticsDlg : public CDialogEx
{
// Создание
public:
	CballisticsDlg(CWnd* pParent = NULL);
	
// Данные диалогового окна
	enum { IDD = IDD_BALLISTICS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void p();
	afx_msg void OnTimer(UINT);
	afx_msg void Anim();
	afx_msg void paint(char *name,double y, double *x, int R, int G, int B, CStatic &DC);	
	afx_msg void paint_energe( double y, double *x, int R, int G, int B, CStatic &DC);// стандартный конструктор
	CStatic m_DrawArea;
	double Cd,x00_,y00_,m,y0_,L,dT,endt;
	BOOL chek_garmonik;
	CStatic Anim_area;
	double *x = new double[4000];
	double *y = new double[4000];
	double *v = new double[4000];
	double *T = new double[4000];
	double *U = new double[4000];
	double *E = new double[4000];
	int nTimer,ntimeout;
	int I, n;

	afx_msg void OnBnClickedCancel();
	float alfa;
	CStatic energe;
	double t_pract;
	double t_teor;
	BOOL check_nit;
	afx_msg void OnStnClickedTTeor();
	afx_msg void OnStnClickedTPract();
	CStatic EN;
	CStatic EN1;
	double SSS;
	double RRR;
};
