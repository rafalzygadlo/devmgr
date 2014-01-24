#include "listctrl.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include <algorithm>
#include <wx/mstream.h>
#include "ais.h"

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CListCtrl,wxListCtrl)
	EVT_LIST_ITEM_ACTIVATED(ID_LIST,CListCtrl::OnActivate)
	EVT_CONTEXT_MENU(CListCtrl::OnContextMenu)
	EVT_MENU(ID_QUEUE_CHART,CListCtrl::OnChartQueue)
	EVT_MENU(ID_PROPERTIES,CListCtrl::OnProperties)
	EVT_MENU(ID_DELETE_FROM_QUEUE,CListCtrl::OnDeleteFromQueue)
	EVT_MENU(ID_DELETE_FROM_INSTALLED,CListCtrl::OnDeleteFromInstalled)
	EVT_MENU(ID_OPEN_CHART,CListCtrl::OnOpenChart)
	EVT_LIST_ITEM_SELECTED(ID_LIST,CListCtrl::OnSelected)
	EVT_LIST_ITEM_ACTIVATED(ID_LIST,CListCtrl::OnActivate)
	//EVT_PAINT(CListCtrl::OnPaint)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,CListCtrl::OnSetItem)
	EVT_LIST_COL_CLICK(ID_LIST,CListCtrl::OnColClick)
END_EVENT_TABLE()
 
CListCtrl::CListCtrl( wxWindow *Parent,CDisplayPlugin *DspPlugin, int style )
:wxListCtrl( Parent, ID_LIST, wxDefaultPosition, wxDefaultSize, style )
{
	ThisPtr = this;
	//Menu = NULL;
	Plugin = DspPlugin;
		
	error.SetTextColour(*wxRED);
	
	selected.SetBackgroundColour(*wxBLUE);
	selected.SetTextColour(*wxWHITE);
		
	installed.SetTextColour(wxColor(100,0,200));
		
	queued.SetTextColour(wxColor(100,200,0));
		
	selected_and_installed.SetBackgroundColour(wxColor(100,0,200));
	selected_and_installed.SetTextColour(*wxWHITE);

	selected_and_queued.SetBackgroundColour(wxColor(100,200,0));
	selected_and_queued.SetTextColour(*wxWHITE);

	SetDoubleBuffered(true);
	last_selected_item = -1;
	
	SetItemCount(0);
	//ImageListSmall = new wxImageList(20, 20, true);
		
	
	//wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_1);

	//wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    //wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_2);
		
	//SetImageList(ImageListSmall, wxIMAGE_LIST_SMALL);
	
}

CListCtrl::~CListCtrl()
{
	//delete ImageListSmall;
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


void CListCtrl::OnOpenChart(wxCommandEvent &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	
	if(n_item == -1)
		return;

//	CNaviGeometry *Installed = Plugin->IsInstalled(Geometry);
		
}

void CListCtrl::OnProperties(wxCommandEvent  &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	//	Plugin->ShowProperties(Geometry);	
}

void CListCtrl::OnDeleteFromQueue(wxCommandEvent &event)
{
	
	long n_item = -1;
	Disable();
	wxArrayPtrVoid GeometryList;
	
	for(;;)
	{
		n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (n_item < 0)	break;
	}
	
//	for(size_t i =0; i < GeometryList.size(); i++)
//		Plugin->RemoveQueueGeometry((CNaviGeometry*)GeometryList.Item(i));
	
	Enable();
	//Plugin->SendQueueInsertSignal();
}

void CListCtrl::OnChartQueue(wxCommandEvent &event)
{	
	
	long n_item = -1;
//	wchar_t *name,*type,*edtn,*updn;
	
	for(;;)
	{
		n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

        if (n_item < 0)	break;
		//Plugin->AddToQueue(Geometry);
	}
	
//	Plugin->SendQueueInsertSignal();

}



void CListCtrl::OnDeleteFromInstalled(wxCommandEvent &event)
{

	long n_item = -1;
	Disable();
	wxArrayPtrVoid GeometryList;
	
	for(;;)
	{
		n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (n_item < 0)	break;
		
	}
	
	//for(size_t i =0; i < GeometryList.size(); i++)
		//Plugin->RemoveInstalledGeometry((CNaviGeometry*)GeometryList.Item(i));
	
	
	Enable();
	//Plugin->SendLibraryInsertSignal();
		
}

void CListCtrl::OnSelected(wxListEvent &event)
{
	
	long n_item = -1;
	for(;;)
	{
		n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);

        if (n_item < 0)	break;
		
		//if(GetMutex()->TryLock())
			//break;
		//Plugin->SetSelectedGeometryLine(Geometry);
		//GetMutex()->Unlock();
	}
	
		
}

void CListCtrl::OnActivate(wxListEvent &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
//	CNaviGeometry *Geometry = CatalogGeometryGroup->GetGeometry(n_item);
	
	//Plugin->ShowProperties(Geometry);
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

wxString CListCtrl::OnGetItemText(long item, long column) const
{

	wxString str;
	wxString name;	
	
	ais_t *ais = ais_get_item(item);		
	if(ais->type5.valid)
	{
		wxString name5(ais->type5.shipname,wxConvUTF8);
		name = name5;
	}
	
	if(ais->type19.valid)
	{
		wxString name19(ais->type5.shipname,wxConvUTF8);
		name = name19;
	}
	
	if(ais->type24.valid)
	{
		wxString name24(ais->type5.shipname,wxConvUTF8);
		name = name24;
	}
	
	switch (column)
	{
		case 0:	str = wxString::Format(_("%d"),ais->mmsi);					break;
		case 1:	str = wxString::Format(_("%s"),name.wc_str());				break;
		case 2: str = wxString::Format(_("%4.2f"),(float)(ais->type1.lat/10000));	break;
		case 3: str = wxString::Format(_("%4.2f"),(float)(ais->type1.lon/10000));	break;
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
void CListCtrl::OnColClick(wxListEvent& event)
{
	
	static bool x = false;
    x = !x;

	//for(size_t i = 0; i < GetColumnCount(); i++)
	//{
		//int col = event.GetColumn();
		//if(event.GetColumn() == i)
			//SetColumnImage(i, x ? 0 : 1);
		//else
			//SetColumnImage(i, -1 );
	//}			
	
	Order = x;
	switch(event.GetColumn())
	{
		//case 0:	SelectedColumn = GEOMETRY_ATTRIBUTE_1; break;
		//case 1:	SelectedColumn = GEOMETRY_ATTRIBUTE_2; break;
		//case 2: SelectedColumn = GEOMETRY_ATTRIBUTE_13; break;
	}
	
	Sort();

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
/*
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
*/
/*
int CListCtrl::OnGetItemImage(long item) const
{
	return -1;
}
*/
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