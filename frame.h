#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include <vector>
#include <wx/dcbuffer.h>
#include "NaviMapIOApi.h"
#include "dll.h"


class CMyPanel;
class CMapPlugin;

class CMyFrame: public wxDialog
{
	int PortSelection;
	CMapPlugin *MapPlugin;
	wxString ConfigPath;
	wxFileConfig *FileConfig;
	wxTextCtrl *LogText;
	wxStaticText *ConfigPathText;
	wxComboBox *PortComboBox,*BaudComboBox;
	wxButton *StartButton;
	wxButton *StopButton;
	wxCheckBox *CheckLogBox,*CheckBoxHint;
	wxSpinCtrl *Spin;
	double minX, maxX, minY, maxY;						// gps area
	double old_data;
	
	bool _Start,_Stop , _Close;
	void OnCloseButton(wxCommandEvent &event);			// close click
	
	void OnClose(wxCloseEvent &event);
	void OnList(wxCommandEvent &event);
	

public:

	CMyFrame(CMapPlugin *_MapPlugin);
	~CMyFrame();
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_START = 12345,
		ID_STOP,
		ID_CLOSE,
		ID_PORTS,
		ID_TRANSPARENT,
		ID_CHECK_LOG,
		ID_CHECK_HINT,
		ID_REFRESH,
		ID_LIST,
	};
};





class CMyPanel: public wxPanel
{

	int _OldX,_OldY;
	int	_X,_Y;									// X,Y myszy
	double _Xd, _Yd;							// X,Y zaznaczenia
	int _DragX, _DragY;
	int CenterX, CenterY;						// centrum okna rysowania
	bool _Drag;
	
	int RectWidth, RectHeight;					// wysokoœæ szerokoœæ zaznaczenia
	int MinRectWidth, MinRectHeight;			// minimalna wysokoœæ zaznaczenia
	int RectCenterX, RectCenterY;				// centralne punkty zaznaczenia
	int Selection;								// id zaznaczenia hintu
	int ScreenWidth, ScreenHeight;				// wymiary ekranu rysowania
	float Zoom;									// zoom okna rysowania
	bool Start;									// flaga kreowania kontrolki
	float minX, maxX, minY, maxY;				// gps area
	wxWindow *_Parent;

	void OnPaint(wxPaintEvent &event);
	void OnMouseEvents(wxMouseEvent &event);
	void OnWindowEnter(wxMouseEvent &event);
	void OnWindowLeave(wxMouseEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnSize(wxSizeEvent &event);

	void DrawHints(wxBufferedPaintDC *dc);		// rysuj podpowiedŸ
	void DrawGps(wxBufferedPaintDC *dc);		// rysuj obrazek gpsa
	void DrawInfo(wxBufferedPaintDC *dc);		// rysuj info
	void BuildHints();							// buduj na podstawie wymiarów zaznaczenia listê podpowiedzi w postaci prostok¹tów
	void Render(wxBufferedPaintDC *dc);			// rysuj wszystko

public:
	CMyPanel(wxWindow *Parent);
	~CMyPanel();

		DECLARE_EVENT_TABLE();
};

#endif
