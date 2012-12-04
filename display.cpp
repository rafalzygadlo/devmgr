#include <wx/wx.h>
#include <wx/mstream.h>
#include "conf.h"
#include "tools.h"
#include "display.h"
#include "item.h"
#include "config.h"
#include "warning.h"

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
	EVT_TREE_ITEM_MENU(ID_TREE, OnTreeMenu)
	EVT_MENU(ID_STOP,OnStop)
	EVT_MENU(ID_START,OnStart)
	EVT_MENU(ID_CONFIGURE,OnConfigure)
	EVT_MENU(ID_ADD,OnAdd)
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	m_SelectedDevice = NULL;
	SetDisplayID(NDS_GPS);
	m_Broker = NULL;
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_Devices = new wxTreeCtrl(this,ID_TREE,wxDefaultPosition,wxDefaultSize);

	ImageListSmall = new wxImageList(16, 16, true);
		
	
	//wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_1);

	//wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    //wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_2);
	
	wxMemoryInputStream in_3((const unsigned char*)warning,warning_size);
    wxImage myImage_3(in_3, wxBITMAP_TYPE_PNG);
    ImageListSmall->Add(myImage_3);
	

	m_Devices->AssignImageList(ImageListSmall);

	m_Root = m_Devices->AddRoot(_("Devices"));
	Sizer->Add(m_Devices,1,wxALL|wxEXPAND);
	this->SetSizer(Sizer);
	m_FirstTime = true;
	m_SelectedItem = NULL;

};

CDisplayPlugin::~CDisplayPlugin()
{

}

void CDisplayPlugin::OnTreeMenu(wxTreeEvent &event)
{
		
	m_SelectedItem = (CItem*)m_Devices->GetItemData(event.GetItem());

	if(m_SelectedItem == NULL)
	{
		wxMenu *Menu = new wxMenu();
		Menu->Append(ID_ADD,_("Add device"));
		PopupMenu(Menu);
		delete Menu;
		return;
	}

	
	CMySerial *Serial = m_SelectedItem->GetSerial();
	m_SelectedDevice = Serial;
	wxMenu *Menu = new wxMenu();
		
	if(Serial->IsRunning())
		Menu->Append(ID_STOP,_("Stop"));
	else
		Menu->Append(ID_START,_("Start"));
	
	//Menu->Append(ID_CONFIGURE,_("Configure"));
	Menu->Append(ID_REMOVE,_("Remove"));

	PopupMenu(Menu);
	
	delete Menu;

}

void CDisplayPlugin::OnStop(wxCommandEvent &event)
{
	m_SelectedDevice->Stop();
	m_Devices->SetItemImage(m_SelectedItem,0, wxTreeItemIcon_Normal);
	m_Devices->Refresh();
	
}

void CDisplayPlugin::OnStart(wxCommandEvent &event)
{
	m_SelectedDevice->Start();
}

void CDisplayPlugin::OnRemove(wxCommandEvent &event)
{
	//m_SelectedDevice->Stop();
}

void CDisplayPlugin::OnConfigure(wxCommandEvent &event)
{
	CMyConfig *Config = new CMyConfig();
//	if(m_SelectedDevice != NULL)
//	{
		//Config->SetPort();
		//Config->SetBaud();
		//Config->SetDeviceName();
	//}
	
	if(Config->ShowModal() == wxID_OK)
	{
		Config->GetDeviceName();
		Config->GetPort();
		Config->GetBaud();
		
		
		
		
	}	
	
	
	delete Config;
}

void CDisplayPlugin::OnAdd(wxCommandEvent &event)
{
	CMyConfig *Config = new CMyConfig();
	
	if(Config->ShowModal() == wxID_OK)
	{
		Config->GetDeviceName();
		Config->GetPort();
		Config->GetBaud();
		CMySerial *serial = CreateNewDevice(Config->GetDeviceName(), Config->GetPort().char_str(),	Config->GetBaud(),true);
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_AddDevice",serial);
	}	
	
	delete Config;
}


void CDisplayPlugin::DrawData(wxGCDC &dc, wxString caption, wxString text)
{
	
	Caption = caption;
	int Size;
	
	wxFont Font;
	if(GetWidth() < GetHeight())
		Size = GetWidth() / 2;
	else
		Size = GetHeight() / 2;
	
	wxSize FontSize;

	Font.SetPointSize( GetHeight() / 4 * 2 ) ;
	dc.SetTextForeground(wxColor(0,0,0));  
	dc.SetFont( Font );

	FontSize = dc.GetTextExtent(text);

	if( FontSize.GetWidth() > GetWidth() ) 
	{
		do 
		{
			Font.SetPointSize( Font.GetPointSize() - 1 );
			dc.SetFont( Font );
			FontSize = dc.GetTextExtent(text);
		} 
		while ( FontSize.GetWidth() > GetWidth() );
	}

	dc.DrawText( text, GetWidth()/2 - FontSize.GetWidth()/2, GetHeight() * 0.625 - FontSize.GetHeight() / 2 );
	
}



bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) {

	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST && m_Broker == NULL)
	{
		m_Broker = (CNaviBroker*)SignalID->GetData();
		m_MapPlugin = (CMapPlugin*)m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_GetParentPtr",NULL);
		if(m_MapPlugin != NULL)
			InitDisplay();
		return false;
	}

	if(SignalID->GetSignalID() == NDS_DEVICE_MANAGER)
	{
		m_MapPlugin = (CMapPlugin*)SignalID->GetData();
		m_SignalType = m_MapPlugin->GetDisplaySignalType();
		m_DeviceId = m_MapPlugin->GetDeviceId();
		GetSignal();
		InitDisplay();
		return false;
	}
	
	return false;
}

void CDisplayPlugin::GetSignal()
{
	int a = m_MapPlugin->GetDisplaySignalType();
	
	if(a == CLEAR_DISPLAY)
	{
		//wxMessageBox(_("clear signal"));
		//m_MapPlugin = NULL;
		//m_Broker = NULL;
		m_FirstTime = true;
		//m_Devices->DeleteChildren(m_Root);
	}

	if(a == INIT_SIGNAL)
		InitDisplay();
}


void CDisplayPlugin::InitDisplay()
{
	if(m_FirstTime)
	{
		m_FirstTime = false;
		SetData();
	}

}

void CDisplayPlugin::SetData() 
{
	for(size_t i = 0; i < m_MapPlugin->GetDevicesCount(); i++)
	{
		CMySerial *Serial = m_MapPlugin->GetDevice(i);
		wxTreeItemId id = m_Devices->AppendItem(m_Root,wxString::Format(_("%s"),Serial->GetDeviceName()));
		CItem *Item = new CItem();
		Item->SetSerial(Serial);
		m_Devices->SetItemData(id,Item);
	}
}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{
	DrawData(dc,wxString::Format(_("dev id:%d"),m_DeviceId),wxString::Format(_("signal id%d"),m_SignalType));
}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
		
	Refresh();
	wxMilliSleep(50);

}

void CDisplayPlugin::AfterWork(CDisplaySignal *Signal)
{
	
}

void CDisplayPlugin::BeforeWork(CDisplaySignal *Signal)
{
	
}

const wchar_t *NaviDisplayIntroduce(int LanguageID) 
{

	switch( LanguageID ) 
	{

		case 0: 
			return L"devmgr";
			break;

		default:
			return L"devmgr";
	}

}

const int NaviDisplayID()
{
	return NDS_GPS;
}

CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID,int LangID) 
{
	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
	return SimplePlugin;
}