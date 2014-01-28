#ifndef __LIST
#define __LIST

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "NaviBroker.h"
#include "display.h"
#include "ais_dialog.h"
#include "ais.h"

class CDisplayPlugin;
class CAisDialog;
class CListCtrl: public wxListCtrl
{
	//wxImageList *ImageListSmall;
	bool Order;
	const char *SelectedColumn;
	CMyFrame *Frame;
	CListCtrl *ThisPtr;
	int VisibleChartType;
	int Type;
	long last_selected_item;
	wxMutex mutex;
	int item_count;
	//wxMenu *Menu;
	wxListItemAttr selected, installed, queued, selected_and_installed, selected_and_queued, error;
	CDisplayPlugin *Plugin;	
	CAisDialog *AisDialog;
	void PrintMsg(ais_t *ais, int type);

	
	wxString CatalogPath;
	void MenuInstalled();
	void MenuVisible();
	void Menu();
	void OnActivate(wxListEvent &event);
	//void OnEraseBackground(wxEraseEvent &event);
	void OnProperties(wxCommandEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	void OnChartQueue(wxCommandEvent &event);
	void OnSelected(wxListEvent &event);
	//void OnPaint(wxPaintEvent &event);
	void OnDeleteFromQueue(wxCommandEvent &event);
	void OnDeleteFromInstalled(wxCommandEvent &event);
	void OnOpenChart(wxCommandEvent &event);
	void OnSetItem(wxCommandEvent &event);
	void OnColClick(wxListEvent& event);
	long GetLastSelectedItem();
	void SetColumnImage(int col, int image);
	
	void Sort();
	
	wxString OnGetItemText(long item, long column) const;
	//wxListItemAttr *OnGetItemAttr(long item) const;
	//int OnGetItemColumnImage(long item, long column) const; 
	//int OnGetItemImage(long item) const;

public:
	
	
	CListCtrl(wxWindow *Parent, CDisplayPlugin *DspPlugin, int style);
	~CListCtrl();

	void ClearList();
	void Insert();
	wxString GetItemValue(long item, long column);
	const char *GetSelectedColumn();
	bool GetSortOrder();
	void SetList();
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LIST,
		ID_PROPERTIES,
		ID_DELETE_FROM_QUEUE,
		ID_DELETE_FROM_INSTALLED,
		ID_QUEUE_CHART,
		ID_DOWNLOAD_CHART_START,
		ID_DOWNLOAD_CHART_STOP,
		ID_UPDATE_CHART,
		ID_SET_ITEM,
		ID_OPEN_CHART,
	};

};

class myCompareClass 
{
	CListCtrl *Parent;
  
public:
	
	myCompareClass(CListCtrl *parent);
//	bool operator() (CNaviGeometry *g1, CNaviGeometry *g2); 
	  
};


#endif