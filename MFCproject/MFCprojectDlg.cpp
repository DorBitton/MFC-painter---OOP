
// MFCprojectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCproject.h"
#include "MFCprojectDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMFCprojectDlg dialog




CMFCprojectDlg::CMFCprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	curColor = RGB(255, 2222, 0);
}

void CMFCprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, isThin);
}

BEGIN_MESSAGE_MAP(CMFCprojectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO1, &CMFCprojectDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCprojectDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCprojectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCprojectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCprojectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCprojectDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCprojectDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCprojectDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO4, &CMFCprojectDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_CHECK2, &CMFCprojectDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCprojectDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCprojectDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCprojectDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCprojectDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_RADIO5, &CMFCprojectDlg::OnBnClickedRadio5)
END_MESSAGE_MAP()


// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);


	// Reset PreSaved file to clean one
	CFile file(_T("File.$$"), CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	figs.Serialize(ar);
	ar.Close();
	file.Close();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		for (int i = 0; i < figs.GetSize(); i++)
			figs[i]->Draw(&dc);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCprojectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	start = end = point;
	isPressed = true;
	//figs.Add(new Figure(start, start));
	switch (futureFigureKind)
	{
	case 1:
		figs.Add(new RectangleF(start, start));
		break;
	case 2:
  	    figs.Add(new EllipseF(start, start));
		break;
	case 3: 
		figs.Add(new linedSquare(start, start));
		break;
	case 4:
		figs.Add(new MagenDavid(start, start));
		break;
	case 5:
		figs.Add(new StraightLine(start, start));
		break;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCprojectDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	curColor = dc.GetPixel(point);
	CDialog::OnRButtonDown(nFlags, point);
}



void CMFCprojectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	if (isPressed)
	{
		end = point;
		isPressed = false;
		figs[figs.GetSize() - 1]->Redefine(start, end);
		//Invalidate(); //simulates the WM_PAINT message to redraw window

		if (isColor == false) // Invalidate only the object
		{
			InvalidateRectFunc();
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCprojectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (isPressed)
	{
		CClientDC dc(this);

		if (!isColor)
			InvalidateRectFunc();



		if (isColor) // Paint with colors function 
			DrawOnSwitch(nFlags, point);

		end = point;
		figs[figs.GetSize() - 1]->Redefine(start, end);
		//Invalidate(); //simulates the WM_PAINT message to redraw window // Ruin paint if on
		
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCprojectDlg::OnBnClickedRadio1() // Square
{
	// TODO: Add your control notification handler code here
	futureFigureKind = 1;
}


void CMFCprojectDlg::OnBnClickedRadio2() // Circle
{
	// TODO: Add your control notification handler code here
	futureFigureKind = 2;
}


void CMFCprojectDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	             // FALSE to SAVE
	CFileDialog dlg(FALSE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
	}
}


void CMFCprojectDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
			     // TRUE to LOAD
	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}


void CMFCprojectDlg::OnBnClickedButton3() // Open color scheme
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);


	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 255; j++)
			dc.SetPixel(rect.left + i, rect.bottom - j, RGB(i, j, 0));
}


void CMFCprojectDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CFile file(_T("File.$$"), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	figs.Serialize(ar);
	ar.Close();
	file.Close();
	Invalidate();
}


void CMFCprojectDlg::OnBnClickedRadio3() // Square with a line inside
{
	// TODO: Add your control notification handler code here
	futureFigureKind = 3;

}


void CMFCprojectDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here

}


void CMFCprojectDlg::OnBnClickedRadio4() // Magen david
{
	// TODO: Add your control notification handler code here
	futureFigureKind = 4;
}


void CMFCprojectDlg::DrawOnSwitch(UINT nFlags, CPoint point) // Function to draw shapes with color and pen size
{
	CClientDC dc(this);

	// Brush settings:
	CBrush myBrush, * oldBrush;
	myBrush.CreateSolidBrush(curColor);
	oldBrush = dc.SelectObject(&myBrush);
	CPen myPen1(PS_SOLID, thickLine ? penSize : 1, RGB(0,0,0)); // Larger pen, size: 10
	CPen* oldPen;
	oldPen = dc.SelectObject(&myPen1);
	dc.SetROP2(R2_NOTXORPEN);


	//Magen David Variables:
	CPoint center = start + end;
	center.x /= 2.0; center.y /= 2.0;
	double radius = abs(start.x - end.x) < abs(start.y - end.y) ? abs(start.x - end.x) / 2.0 : abs(start.y - end.y) / 2.0;
	CPoint vertices[12];
	double two_pi = atan(1) * 8;

	switch (futureFigureKind)
	{
	case 1:
		dc.Rectangle(start.x, start.y, end.x, end.y);
		end = point;
		dc.Rectangle(start.x, start.y, end.x, end.y);
		break;
	case 2:
		dc.Ellipse(start.x, start.y, end.x, end.y);
		end = point;
		dc.Ellipse(start.x, start.y, end.x, end.y);
		break;
	case 3:
		dc.Rectangle(start.x, start.y, end.x, end.y);
		dc.MoveTo(start);
		dc.LineTo(end.x, end.y);
		end = point;
		dc.MoveTo(start);
		dc.LineTo(end.x, end.y);
		dc.Rectangle(start.x, start.y, end.x, end.y);

		break;
	case 4:
		for (int i = 0; i < 12; i++)
		{
			if (i % 2 == 0)
			{
				vertices[i].x = center.x + radius / sqrt(3) * cos(two_pi / 12 * i);
				vertices[i].y = center.y + radius / sqrt(3) * sin(two_pi / 12 * i);
			}
			else
			{
				vertices[i].x = center.x + radius * cos(two_pi / 12 * i);
				vertices[i].y = center.y + radius * sin(two_pi / 12 * i);
			}

		}

		InvalidateRectFunc();

		dc.Polygon(vertices, 12);
		break;
	case 5:
		CPen myPen1(PS_SOLID, thickLine ? penSize : 1, curColor); // Larger pen, size: 10
		oldPen = dc.SelectObject(&myPen1);
		dc.SetROP2(R2_NOTXORPEN);

		dc.MoveTo(start);
		dc.LineTo(end.x, end.y);
		end = point;
		dc.MoveTo(start);
		dc.LineTo(end.x, end.y);
		break;
	}

	// Reset
	dc.SelectObject(oldPen);
	dc.SetROP2(R2_COPYPEN);
	dc.SelectObject(oldBrush);

}

void CMFCprojectDlg::InvalidateRectFunc() { // Invalidate only the object, not entire page.
	RECT r;
	r.left = (start.x < end.x) ? start.x : end.x;
	r.top = (start.y < end.y) ? start.y : end.y;
	r.right = (start.x > end.x) ? start.x : end.x;
	r.bottom = (start.y > end.y) ? start.y : end.y;
	InvalidateRect(&r);
}

void CMFCprojectDlg::OnBnClickedCheck2() // Larger pen
{
	// TODO: Add your control notification handler code here
	if (thickLine == true)
		thickLine = false;
	else
		thickLine = true;
}


void CMFCprojectDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	penSize++;

}


void CMFCprojectDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	if (penSize >= 2)
		penSize--;
}


void CMFCprojectDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	isColor = false;
}


void CMFCprojectDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	isColor = true;
}


void CMFCprojectDlg::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	futureFigureKind = 5;
}
