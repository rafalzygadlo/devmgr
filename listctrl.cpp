#include "listctrl.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include <algorithm>
#include <wx/mstream.h>
#include "ais_html.h"
#include "options.h"
#include "images/up_sort.img"
#include "images/down_sort.img"

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CListCtrl,wxListCtrl)
	EVT_LIST_ITEM_ACTIVATED(ID_LIST,CListCtrl::OnActivate)
	EVT_CONTEXT_MENU(CListCtrl::OnContextMenu)
	EVT_LIST_ITEM_SELECTED(ID_LIST,CListCtrl::OnSelected)
	//EVT_PAINT(CListCtrl::OnPaint)
	//EVT_ERASE_BACKGROUND(CListCtrl::OnEraseBackground)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,CListCtrl::OnSetItem)
	EVT_LIST_COL_CLICK(ID_LIST,CListCtrl::OnColClick)
	//EVT_LIST_CACHE_HINT(ID_LIST, CListCtrl::OnCacheHint)
END_EVENT_TABLE()
 
CListCtrl::CListCtrl( wxWindow *Parent,CAisList *AisList, int style )
:wxListCtrl( Parent, ID_LIST, wxDefaultPosition, wxDefaultSize, style )
{
	
	//SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	//SetDoubleBuffered(true);
	_AisList = AisList;
		
	error.SetTextColour(*wxRED);
	
	selected.SetBackgroundColour(*wxBLUE);
	selected.SetTextColour(*wxWHITE);
		
	installed.SetTextColour(wxColor(100,0,200));
		
	queued.SetTextColour(wxColor(100,200,0));
		
	selected_and_installed.SetBackgroundColour(wxColor(100,0,200));
	selected_and_installed.SetTextColour(*wxWHITE);

	selected_and_queued.SetBackgroundColour(wxColor(100,200,0));
	selected_and_queued.SetTextColour(*wxWHITE);
		
	last_selected_item = -1;
	
	SetItemCount(0);
	m_FromSearch = false;
	ImageListSmall = new wxImageList(10, 10, true);
		
	wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    ImageListSmall->Add(myImage_1);

	wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    ImageListSmall->Add(myImage_2);
		
	SetImageList(ImageListSmall, wxIMAGE_LIST_SMALL);
	
}

CListCtrl::~CListCtrl()
{
	delete ImageListSmall;
}


void CListCtrl::SetSearch(bool val)
{
	m_FromSearch = val;
}

void CListCtrl::OnSetItem(wxCommandEvent &event)
{
	int i = event.GetInt();
	wxString str = event.GetString();
		
	long item = InsertItem(i,str);
	SetItemPtrData(item,(wxUIntPtr)event.GetClientData());
}

void CListCtrl::OnContextMenu(wxContextMenuEvent &event)
{
	
}

void CListCtrl::OnEraseBackground(wxEraseEvent &event)
{
	// to prevent flickering, erase only content *outside* of the 
   // actual list items stuff

   if(GetItemCount() > 0) {
       wxDC * dc = event.GetDC();
       assert(dc);

       // get some info
       wxCoord width = 0, height = 0;
       GetClientSize(&width, &height);

       wxCoord x, y, w, h;
       dc->SetClippingRegion(0, 0, width, height);
       dc->GetClippingBox(&x, &y, &w, &h); 

       long top_item = GetTopItem();
       long bottom_item = top_item + GetCountPerPage();
       if(bottom_item >= GetItemCount()) {
           bottom_item = GetItemCount() - 1;
       }                

       // trick: we want to exclude a couple pixels
       // on the left side thus use wxLIST_RECT_LABEL
       // for the top rect and wxLIST_RECT_BOUNDS for bottom
       // rect
       wxRect top_rect, bottom_rect;
       GetItemRect(top_item, top_rect, wxLIST_RECT_LABEL);
       GetItemRect(bottom_item, bottom_rect, wxLIST_RECT_BOUNDS);

       // set the new clipping region and do erasing
       wxRect items_rect(top_rect.GetLeftTop(), bottom_rect.GetBottomRight());
       wxRegion reg(wxRegion(x, y, w, h)); 
       reg.Subtract(items_rect);
       dc->DestroyClippingRegion();
       dc->SetClippingRegion(reg);

       // do erasing
       dc->SetBackground(wxBrush(GetBackgroundColour(), wxSOLID));
       dc->Clear();

       // restore old clipping region
       dc->DestroyClippingRegion();
       dc->SetClippingRegion(wxRegion(x, y, w, h));
   } else {
       event.Skip();
  
  }
  
}

/*
void CListCtrl::OnPaint(wxPaintEvent &event)
{
	event.Skip();
}
*/
void CListCtrl::Menu()
{
	
	wxMenu *Menu = new wxMenu();
	
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if(n_item == -1)
		return;
	
	bool queue = true;
	Menu->Append(ID_DELETE_FROM_INSTALLED,GetMsg(MSG_UNINSTALL));
	//Menu->Append(ID_ADD_CATEGORY,GetMsg()

	
			
	//Menu->AppendSeparator();
	//Menu->Append(ID_PROPERTIES,GetMsg(MSG_PROPERTIES));
	
	
	PopupMenu(Menu);
	
	delete Menu;
}

void CListCtrl::OnSelected(wxListEvent &event)
{
	
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	
	ais_t *ais = NULL;

	wxMutexLocker locker(*GetSearchMutex());
	ais = ais_get_search_item(n_item);
	
	
	if(ais)
	{
		_AisList->ClearHtml();
		_AisList->SetHtml(_("<a name='top'></a><br>"));
		_AisList->SetHtml(PrintHtmlAnchors(ais));
	
		for(size_t i = 1; i < AIS_MESSAGES_LENGTH; i++)
		{
			if(ais->valid[i])
			{
				_AisList->SetHtml(PrintHtmlMsg(ais,i));
				
			}
		}
		
		fprintf(stdout,"%d\n",ais->buffer_id);
		SAisData *data = ais_buffer_exists(ais->mmsi);
		
		SetSelectedAnimPtr(data); // inna funkcja musi byæ wp³ywa to na timer w frame
		SetStartAnimation(true);
	
	}


}


void CListCtrl::OnActivate(wxListEvent &event)
{

	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	
	ais_t *ais = NULL;

	wxMutexLocker locker(*GetSearchMutex());
	ais = ais_get_search_item(n_item);
			
	_AisList->ClearHtml();
	_AisList->SetHtml(_("<a name='top'></a><br>"));
	_AisList->SetHtml(PrintHtmlAnchors(ais));
	
	for(size_t i = 1; i < AIS_MESSAGES_LENGTH; i++)
	{
		if(ais->valid[i])
		{
			_AisList->SetHtml(PrintHtmlMsg(ais,i));
			_AisList->ShowHtmlPanel();
		}
	
	}

/*
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	ais_t *ais = ais_get_item(n_item);
	
	for(size_t i = 0; i < AIS_MESSAGES_LENGTH; i++)
	{
		if(ais->valid[i])
		{
			_AisList->ClearHtml();
			_AisList->SetHtml(PrintHtmlMsg(ais,i));
		}
	
	}
*/
}

void CListCtrl::ClearList()
{
	SetItemCount(0);
}

//void CListCtrl::SetSelection(CNaviGeometry *geometry)
//{
	//if(geometry == NULL)
		//return;
			
	//long n_item = -1;
	//last_selected_item = -1;	
	/*
	for(size_t i = 0; i < CatalogGeometryGroup->Length();i++)
	{ 
		CNaviGeometry *Geometry = CatalogGeometryGroup->GetGeometry(i);
		if(Geometry != NULL)
		{
		
			if(wcsstr(Geometry->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_1),geometry->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_1)) != NULL && wcsstr(Geometry->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_4),geometry->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_4)) != NULL)
			{
				EnsureVisible(i);
				Refresh();
				last_selected_item = i;
				return;
				
			}
		
		}
	}
	*/
	//last_selected_item = -1;
	//Refresh();
//}


long CListCtrl::GetLastSelectedItem()
{
	return last_selected_item;
}

void CListCtrl::OnCacheHint(wxListEvent& event)
{
    m_From = event.GetCacheFrom();
	m_To = event.GetCacheTo();
	fprintf(stdout,"from:%d to:%d\n",m_From,m_To);
	event.Skip();
}

long CListCtrl::_GetFrom()
{
	return m_From;
}

long CListCtrl::_GetTo()
{
	return m_To;
}

wxString CListCtrl::OnGetItemText(long item, long column) const
{
		
	if(GetSearchMutex() == NULL)
		return _("N/A"); 
	
	GetSearchMutex()->Lock();
	
	if(item > ais_get_search_item_count())
	{
		GetSearchMutex()->Unlock();
		return _("N/A"); 
	}
	GetSearchMutex()->Unlock();
	
	wxString str;
	wxString name;
	wxString callsign(_("N/A"));
	wxString imo(_("N/A"));

	ais_t *ais = NULL;
	ais = ais_get_search_item(item);
		
	wxString mes;
	for(size_t i = 1; i < AIS_MESSAGES_LENGTH;i++)
	{
		if(ais->valid[i])
			mes.Append(wxString::Format(_("[%d]"),i));
	}
	
	if(ais->valid[AIS_MSG_5])
	{
		wxString name5(ais->type5.shipname,wxConvUTF8);
		name = name5;
		wxString _callsign(ais->type5.callsign,wxConvUTF8);
		callsign = _callsign;
		imo = wxString::Format(_("%d"),ais->type5.imo);
	}
	
	if(ais->valid[AIS_MSG_19])
	{
		wxString name19(ais->type5.shipname,wxConvUTF8);
		name = name19;
	}
	
	if(ais->valid[AIS_MSG_21])
	{
		wxString name21(ais->type21.name,wxConvUTF8);
		name = name21;
	}
	
	if(ais->valid[AIS_MSG_24])
	{
		wxString name24(ais->type24.shipname,wxConvUTF8);
		name = name24;
		wxString _callsign(ais->type24.callsign,wxConvUTF8);
		callsign = _callsign;
	}
	
	wxString lon(_("N/A"));
	wxString lat(_("N/A"));
	
	double _lon,_lat;
	
	int seconds = (GetTickCount() - ais->timeout)/1000;
		
	int minutes = seconds/60;
	div_t _div = div(seconds,60);

	switch (column)
	{
		case 0:	str = mes;												break;
		case 1:	str = wxString::Format(_("%d"),ais->mmsi);				break;
		case 2:	str = wxString::Format(_("%s"),name.wc_str());			break;
		case 3: str = wxString::Format(_("%s"),callsign.wc_str());		break;
		case 4: str = wxString::Format(_("%s"),imo.wc_str());			break;
		case 5: str = wxString::Format(_("%d:%02d"),minutes,_div.rem);	break;
	}

	return str;
}

/*
wxListItemAttr *CListCtrl::OnGetItemAttr(long item) const
{
	
	//if(Plugin->IsLoading())
		return NULL;
	
	//if(GetMutex()->TryLock())
//		return NULL;
	
	//if(CatalogGeometryGroup->Length() == 0 || CatalogGeometryGroup->Length() < item )
		//return NULL;
	
	//CNaviGeometry *Geometry = CatalogGeometryGroup->GetGeometry(item);
	
	 //je¿eli geometria zainstalowana to sprawdz czy plik geometri istnieje 
	//CNaviGeometry *Installed = Plugin->IsInstalled(Geometry); 
	//GetMutex()->Unlock();
	
	//if(Installed != NULL)
	//{
		//if(!wxFileExists(Installed->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_9)))
			//return (wxListItemAttr *)&error;
	//}
		

//	if(Installed && Plugin->ChartCheckUpdate(Installed) != NULL)				// geometria potrzebuje update
		//return (wxListItemAttr *)&error;
	
	//if (last_selected_item == item && Installed)								// zainstalowana
		//return (wxListItemAttr *)&selected_and_installed;				
		
	if (last_selected_item == item)
		return (wxListItemAttr *)&selected;
		
	//if(Installed && Type == LIST_TYPE_ALL)
		//return (wxListItemAttr *)&installed;
		    

    return NULL;
}
*/

int wxCALLBACK
MyCompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
    // inverse the order
    if (item1 < item2)
        return 1;
    if (item1 > item2)
        return -1;

    return 0;
}

void CListCtrl::OnColClick(wxListEvent& event)
{
	
	static bool x = false;
    x = !x;

	for(size_t i = 0; i < GetColumnCount(); i++)
	{
		int col = event.GetColumn();
		if(event.GetColumn() == i)
			SetColumnImage(i, x ? 0 : 1);
		else
			SetColumnImage(i, -1 );
	}			
			
	ais_set_sort_order(x);
	ais_set_sort_column(event.GetColumn());
	
}

void CListCtrl::SetColumnImage(int col, int image)
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_IMAGE);
    item.SetImage(image);
    SetColumn(col, item);
}

bool CListCtrl::GetSortOrder()
{
	return Order;
}

const char *CListCtrl::GetSelectedColumn()
{
	return SelectedColumn;
}

/*
bool CListCtrl::Compare(CNaviGeometry *g1, CNaviGeometry * g2)
{

	int a = wcscmp(g1->GetAttributes()->GetValueAsString(SelectedColumn), g2->GetAttributes()->GetValueAsString(SelectedColumn));

	if(a < 0)
		return true;
	else
		return false;

}
*/

void CListCtrl::Sort()
{
//	CatalogGeometryGroup->First();	
//	std::vector<CNaviGeometry*> *it = (std::vector<CNaviGeometry*>*)CatalogGeometryGroup;
//	myCompareClass a(this);
//	std::sort(it->begin(),it->end(),a);
	Refresh();
}

int CListCtrl::OnGetItemColumnImage(long item, long column) const
{
	//CNaviGeometry *Geometry = CatalogGeometryGroup->GetGeometry(item);
	//CNaviGeometry *Installed = Plugin->IsInstalled(Geometry);
	//if(Installed && column == 0)
	//{
		//if(!wxFileExists(Installed->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_9)))
			//return 0;
	//}
	
	return -1;
}


int CListCtrl::OnGetItemImage(long item) const
{
	return -1;
}

 myCompareClass::myCompareClass(CListCtrl *parent) 
{
	Parent = parent;
}
 
 /*
bool myCompareClass::operator() (CNaviGeometry *g1, CNaviGeometry *g2) 
{ 
		
     int a = wcscmp(g1->GetAttributes()->GetValueAsString(Parent->GetSelectedColumn()), g2->GetAttributes()->GetValueAsString(Parent->GetSelectedColumn()));

	 if(Parent->GetSortOrder())
	 {
		if(a < 0)
			return true;
		else
			return false;
	 
	 }else{
	 	
		 if(a > 0)
			return true;
		else
			return false;
	 }
    
  }
    
  */