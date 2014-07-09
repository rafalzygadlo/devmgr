#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/notebook.h>
#include "conf.h"
#include "tools.h"
#include "display.h"
#include "item.h"
#include "config.h"
#include "status.h"
#include "info.h"
#include "wizard.h"
#include "devices.h"
#include "options.h"
#include "signals.h"


BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
	EVT_MENU_RANGE(ID_MENU_BEGIN,ID_MENU_END,CDisplayPlugin::OnMenuRange)
	EVT_CONTEXT_MENU(CDisplayPlugin::OnMenu)
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	m_AisMonitor = NULL;
	m_SelectedDevice = NULL;
	SetDisplayID(NDS_DEVICE_MANAGER);
	m_Broker = NULL;
	m_SignalsPanel = NULL;
	m_Sizer = NULL;
	m_MapPlugin = NULL;
	m_DeviceID = -1;
	//SetDoubleBuffered(true);
		
	this->Disable();
	m_FirstTime = true;
	m_SelectedItem = NULL;
	m_DevicesList = NULL;
	m_AisList = NULL;
	m_GUI = false;

	m_Menu = new wxMenu();
	m_Menu->AppendRadioItem(0 + ID_MENU_BEGIN ,_("Device Manager - Configurator"));
	m_Menu->AppendRadioItem(1 + ID_MENU_BEGIN ,_("Ais Targets"));
	m_Menu->AppendRadioItem(2 + ID_MENU_BEGIN ,_("Ais Monitor"));
		
	m_Ticker = new CTicker(this,TICK_DISPLAY_REFRESH);
	m_Ticker->Start(DISPLAY_REFRESH);

	m_RefreshTick = 0;
	m_RefreshInterval = DISPLAY_REFRESH;
	CProtocol Protocol;
	int counter = 0;

	CDevices devices;
	
	size_t dcount = devices.GetLen();
	
	for(size_t i = 0; i < dcount; i++)
	{
		SDevices *device = devices.Get(i);
	
		SDefinition *Definition;
		Protocol.GetDefinitionById(device->id,counter,*&Definition);

		for(size_t j = 0; j < counter; j++)
		{
			int len;
			SSignals *signal_s = Protocol.GetSignalsById(Definition[j].id_signal);
			wxString name(signal_s->name,wxConvUTF8);
			m_Menu->AppendCheckItem(CONTROL_OFFSET + signal_s->id + ID_MENU_BEGIN, name);
		}

		delete Definition;
	}

	Name = parent->GetLabel();
	wxFileConfig *m_FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	if(!m_FileConfig->Read(wxString::Format(_("%s/%s"),Name.wc_str(),_(KEY_CONTROL_TYPE)),&m_ControlType))
		m_ControlType = DEFAULT_CONTROL_TYPE;

	delete m_FileConfig;
	
}

CDisplayPlugin::~CDisplayPlugin()
{
	Name = GetName();
	
	m_Ticker->Stop();
	delete m_Ticker;
	wxFileConfig *m_FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	m_FileConfig->Write(wxString::Format(_("%s/%s"),Name,_(KEY_CONTROL_TYPE)),m_ControlType);
	delete m_FileConfig;
	delete m_Menu;
}

int CDisplayPlugin::GetControlType()
{
	return m_ControlType - ID_MENU_BEGIN;
}

void  CDisplayPlugin::GetDevicesList()
{
	m_GUI = true;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	m_DevicesList = new CDevicesList(this,m_MapPlugin);
	MainSizer->Add(m_DevicesList,1,wxALL|wxEXPAND);
	this->SetSizer(MainSizer);
	this->Layout();
}

void  CDisplayPlugin::GetAisList()
{
	m_GUI = true;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	m_AisList = new CAisList(this,m_MapPlugin,this);
	MainSizer->Add(m_AisList,1,wxALL|wxEXPAND);
	this->SetSizer(MainSizer);
	this->Layout();
}

void  CDisplayPlugin::GetAisMonitor()
{	
	m_GUI = true;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	m_AisMonitor = new CAisMonitor(this);
	MainSizer->Add(m_AisMonitor,1,wxALL|wxEXPAND);
	this->SetSizer(MainSizer);
	this->Layout();
	
}

void CDisplayPlugin::RemoveControl(int type)
{
	switch(type)
	{
		case CONTROL_DEVICES_LIST:	FreeDevicesList();	break;
		case CONTROL_AIS_LIST:		FreeAisList();		break;
		case CONTROL_AIS_MONITOR:	FreeAisMonitor();	break;
	}
}

void CDisplayPlugin::FreeAisMonitor()
{
	delete m_AisMonitor;
	m_AisMonitor = NULL;
}

void CDisplayPlugin::FreeDevicesList()
{
	delete m_DevicesList;
	m_DevicesList = NULL;
}

void CDisplayPlugin::FreeAisList()
{
	delete m_AisList;
	m_AisList = NULL;
}

void CDisplayPlugin::OnMenuRange(wxCommandEvent &event)
{
	if(m_ControlType == event.GetId())
	{
		wxMessageBox(_("The same type of control ?"));
		return;
	}
		
	m_GUI = false;
	RemoveControl(m_ControlType);
		
	switch(event.GetId())
	{
		case CONTROL_DEVICES_LIST:	GetDevicesList();	break;
		case CONTROL_AIS_LIST:		GetAisList();		break;
		case CONTROL_AIS_MONITOR:	GetAisMonitor();	break;
	}
	
	m_ControlType = event.GetId(); // ustawiamy po zbudowaniu gui
	
	CProtocol Protocol;
	SSignals *signals = Protocol.GetSignalsById(GetControlId());
	if(signals)
	{
		wxString name(signals->name,wxConvUTF8);
		m_Caption = name;
		SetCaption(m_Caption);
		Refresh();
	}
	
}

void CDisplayPlugin::OnMenu(wxContextMenuEvent &event)
{
		
	if(m_ControlType != -1)
		m_Menu->Check(m_ControlType, true);
	
	PopupMenu(m_Menu);
	//delete Menu;
	
}

bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) {

	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST)
	{
		m_Broker = (CNaviBroker*)SignalID->GetData();
		m_MapPlugin = (CMapPlugin*)m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_GetParentPtr",NULL);
		if(m_MapPlugin != NULL)
			InitDisplay();
		return false;
	}

	if(SignalID->GetSignalID() == NDS_DEVICE_MANAGER)
	{
		m_SignalType = SignalID->GetTag();
		if(m_MapPlugin != NULL)
		{
			m_Broker = m_MapPlugin->GetBroker();
			InitDisplay();
		}
		// kolejnoœæ initDispaly najpierw dla sygnalu czyszcz¹cego m_firstTime przestawiany na fa³sz i InitDisplay siê inicjuje
		
		GetSignal(SignalID);
		GetGUIControl(SignalID);
		
	}
	
	return false;
}

void CDisplayPlugin::GetGUIControl(CDisplaySignal *sig)
{
	// kontrolki GUI
		
	switch(m_ControlType)
	{
		case CONTROL_DEVICES_LIST:	SetDevicesListSignal(m_SignalType,sig);	break;
		case CONTROL_AIS_LIST:		SetAisListSignal(m_SignalType);			break;
	}

}


void CDisplayPlugin::GetSignal(CDisplaySignal *sig)
{
		
	switch(m_SignalType)
	{
		case CLEAR_DISPLAY:				ClearDisplay();		break;		// czysci listê urz¹dzeñ (np przy wy³¹czeniu plugina)
		case SIGNAL_SYNCHRO_OPTIONS:	SynchroOptions();	break;

	}

}

void CDisplayPlugin::SetDevicesListSignal(int type, CDisplaySignal *sig)
{
	if(m_DevicesList)
	{
		m_DevicesList->SetSignal(type,(CReader*)sig->GetData());
	}
}

void CDisplayPlugin::SetAisListSignal(int type)
{
	if(m_AisList)
		m_AisList->SetSignal(type);
}

void CDisplayPlugin::ClearDisplay()
{
	m_FirstTime = true;
	this->Disable();
	m_MapPlugin = NULL;
	
	if(m_DevicesList != NULL)
	{
		delete m_DevicesList;
		m_DevicesList = NULL;
	}
}

void CDisplayPlugin::InitDisplay()
{
	if(m_FirstTime)
	{
		m_FirstTime = false;
				
		switch(m_ControlType)
		{
			case CONTROL_DEVICES_LIST:	GetDevicesList();	break;
			case CONTROL_AIS_LIST:		GetAisList();		break;
			case CONTROL_AIS_MONITOR:	GetAisMonitor();	break;	
		}
	
		this->Enable();
	}

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
			if(dc.IsOk())
				FontSize = dc.GetTextExtent(text);
			else
				int a =0;
		
		} while ( FontSize.GetWidth() > GetWidth() );
	}

 	dc.DrawText( text, (int)GetWidth()/2 - FontSize.GetWidth()/2, (int)GetHeight() * 0.625 - FontSize.GetHeight() / 2 );
//	dc.EndDrawing();
	
	
}
int CDisplayPlugin::GetControlId()
{
	return m_ControlType - CONTROL_OFFSET - ID_MENU_BEGIN;
}

void CDisplayPlugin::SynchroOptions()
{
	if(m_AisList)
		m_AisList->Synchro();
			
}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{
	bool exists = false;
	size_t count = GetDeviceSignalCount();
	for(size_t i = 0; i < count; i++)
	{
		SData * ptr = GetDeviceSignal(i);
		if(ptr->id == GetControlId())
		{	
			wxString b(ptr->value,wxConvUTF8);
			DrawData(dc,m_Caption,b);
			exists = true;		
		}
	}	

	if(!exists)
		DrawData(dc,m_Caption,_("N/A"));

}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
	
}

void CDisplayPlugin::OnTickerStart()
{
}

void CDisplayPlugin::OnTickerStop()
{
}

void CDisplayPlugin::OnTickerTick()
{
	
	bool refresh = false;
	//m_RefreshTick++;
	//if( m_RefreshTick >= m_RefreshInterval)	
	//{	
	//m_RefreshTick = 0;
	
	size_t count = GetDeviceSignalCount();
	for(size_t i = 0; i < count; i++)
	{
		SData * ptr = GetDeviceSignal(i);
		if(ptr->id == GetControlId())
			refresh = true;
	}
		
	if(refresh)
		Refresh();
	//}
	
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
			return TEXT(PRODUCT_NAME);
			break;

		default:
			return TEXT(PRODUCT_NAME);
	}

}

const int NaviDisplayID()
{
	return NDS_DEVICE_MANAGER;
}

CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID,int LangID) 
{
	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
	return SimplePlugin;
}