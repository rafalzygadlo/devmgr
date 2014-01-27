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

//DEFINE_EVENT_TYPE(EVT_SET_LOGGER)
//DEFINE_EVENT_TYPE(EVT_SET_ICON)
//DEFINE_EVENT_TYPE(EVT_SET_TEXT)

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
	//EVT_TREE_ITEM_MENU(ID_TREE, CDisplayPlugin::OnTreeMenu)
	//EVT_TREE_SEL_CHANGED(ID_TREE, CDisplayPlugin::OnTreeSelChanged)
	//EVT_MENU(ID_STOP,CDisplayPlugin::OnStop)
	//EVT_MENU(ID_START,CDisplayPlugin::OnStart)
	//EVT_MENU(ID_CONFIGURE_DEVICE,CDisplayPlugin::OnConfigureDevice)
	//EVT_MENU(ID_UNINSTALL,CDisplayPlugin::OnUninstall)
	//EVT_MENU(ID_NEW_DEVICE,CDisplayPlugin::OnNewDevice)
	//EVT_MENU(ID_DEVICE_WIZARD,CDisplayPlugin::OnDeviceWizard)
	//EVT_MENU(ID_STATUS,CDisplayPlugin::OnStatus)
	//EVT_MENU(ID_START,CDisplayPlugin::OnStart)
	
	//EVT_HYPERLINK(ID_STOP,CDisplayPlugin::OnStop)
	//EVT_HYPERLINK(ID_START,CDisplayPlugin::OnStart)
//	EVT_HYPERLINK(ID_CONFIGURE_DEVICE,CDisplayPlugin::OnConfigureDevice)
	//EVT_HYPERLINK(ID_MONITOR,CDisplayPlugin::OnMonitor)
	
	EVT_MENU_RANGE(ID_MENU_BEGIN,ID_MENU_END,CDisplayPlugin::OnMenuRange)
	EVT_CONTEXT_MENU(CDisplayPlugin::OnMenu)

	//EVT_COMMAND(ID_LOGGER,EVT_SET_LOGGER,CDisplayPlugin::OnSetLogger)
	//EVT_COMMAND(ID_ICON,EVT_SET_ICON,CDisplayPlugin::OnSetIcon)
	//EVT_COMMAND(ID_TEXT,EVT_SET_TEXT,CDisplayPlugin::OnSetText)
	//EVT_TOOL(ID_TOOL_STOP,
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	m_SelectedDevice = NULL;
	SetDisplayID(NDS_DEVICE_MANAGER);
	m_Broker = NULL;
	m_SignalsPanel = NULL;
	m_Sizer = NULL;
	SetDoubleBuffered(true);
		
	this->Disable();
	m_FirstTime = true;
	m_SelectedItem = NULL;
	
	m_ControlType = -1;
		
	m_DevicesList = NULL;
	m_AisList = NULL;
	m_Data = NULL;

	m_Menu = new wxMenu();
		
	m_Menu->AppendRadioItem(0 + ID_MENU_BEGIN ,_("Device Manager - Configurator"));
	m_Menu->AppendRadioItem(1 + ID_MENU_BEGIN ,_("Ais Targets list"));
		

	CProtocol Protocol;
	int counter = 0;

	SDevices *device = Protocol.GetDevice(0);
	
	SDefinition *Definition;
	Protocol.GetDefinitionById(device->id,counter,*&Definition);

	for(size_t i = 0; i < counter; i++)
	{
		int len;
		SSignals *signal_s = Protocol.GetSignalsById(Definition[i].id_signal);
		wxString name(signal_s->name,wxConvUTF8);
		m_Menu->AppendRadioItem(2 + signal_s->id + ID_MENU_BEGIN, name);
		
	}
	
	delete Definition;
	

	
	//ArrayOfTypes.Add(_("Speed"));
	//ArrayOfTypes.Add(_("Date"));
	//ArrayOfTypes.Add(_("Time"));
	//ArrayOfTypes.Add(_("Fix"));
	//ArrayOfTypes.Add(_("Direction"));
	//ArrayOfTypes.Add(_("Longitude"));
	//ArrayOfTypes.Add(_("Latitude"));
	//ArrayOfTypes.Add(_("PDOP"));
	//ArrayOfTypes.Add(_("HDOP"));
	//ArrayOfTypes.Add(_("VDOP"));
	//ArrayOfTypes.Add(_("Quality"));
	//ArrayOfTypes.Add(_("Sattelites"));
	//ArrayOfTypes.Add(_("Status"));


}

CDisplayPlugin::~CDisplayPlugin()
{
	delete m_Menu;
	//RemoveControl(m_ControlType);
}

int CDisplayPlugin::GetControlType()
{
	return m_ControlType - ID_MENU_BEGIN;
}

void  CDisplayPlugin::GetDevicesList()
{
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	m_DevicesList = new CDevicesList(this,m_MapPlugin);
	MainSizer->Add(m_DevicesList,1,wxALL|wxEXPAND);
	this->SetSizer(MainSizer);
	this->Layout();
}

void  CDisplayPlugin::GetAisList()
{
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	m_AisList = new CAisList(this,m_MapPlugin,this);
	MainSizer->Add(m_AisList,1,wxALL|wxEXPAND);
	this->SetSizer(MainSizer);
	this->Layout();
}

void CDisplayPlugin::RemoveControl(int type)
{
	switch(type)
	{
		case CONTROL_DEVICES_LIST:	FreeDevicesList();	break;
		case CONTROL_AIS_LIST:		FreeAisList();		break;
	}
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
	
	RemoveControl(m_ControlType);
		
	switch(event.GetId())
	{
		case CONTROL_DEVICES_LIST:	GetDevicesList();	break;
		case CONTROL_AIS_LIST:		GetAisList();		break;
	}
	
	m_ControlType = event.GetId(); // ustawiamy po zbudowaniu gui
	//m_Caption = ArrayOfTypes[GetControlType()];

}

void CDisplayPlugin::OnMenu(wxContextMenuEvent &event)
{
	
	
	if(m_ControlType != -1)
		m_Menu->Check(m_ControlType, true);
	
	PopupMenu(m_Menu);
	//delete Menu;
	
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
		m_SignalType = SignalID->GetTag();
		InitDisplay();
		// kolejnoœæ initDispaly najpierw dla sygnalu czyszcz¹cego m_firstTime przestawiany na fa³sz i InitDisplay siê inicjuje
		
		if(!GetGUIControl(SignalID))
		{
			if(GetSignal(SignalID))
				return true;	// dla sygnalow danych uruchom watki dla rysowania kontrolek
		}
	
	}
	
	return false;
}

bool CDisplayPlugin::GetGUIControl(CDisplaySignal *sig)
{
	// kontrolki GUI
	bool result = false;
	
	switch(m_ControlType)
	{
		case CONTROL_DEVICES_LIST:	SetDevicesListSignal(m_SignalType,sig);	result = true; break;
		case CONTROL_AIS_LIST:		SetAisListSignal(m_SignalType);			result = true; break;
	}

	return result;
}


bool CDisplayPlugin::GetSignal(CDisplaySignal *sig)
{
	bool result = false;
		
	switch(m_SignalType)
	{
		case CLEAR_DISPLAY: 			ClearDisplay(); break;		// czysci listê urz¹dzeñ (np przy wy³¹czeniu plugina)
		case INIT_SIGNAL:				InitDisplay();	break;		// inicjuje listê urzadzeñ
		case DATA_SIGNAL:				result = true;	break;		// sygna³ danych w strukturze
	}
	
	return result;
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
		this->Enable();
	}

}

void CDisplayPlugin::DrawData(wxGCDC &dc, wxString caption, wxString text)
{
	//if(IsDrawning)
//		return;
	
	//IsDrawning = true;
	
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
	//IsDrawning = false;
	
}
int CDisplayPlugin::GetControlId()
{
	return m_ControlType - 2 - ID_MENU_BEGIN;
}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{
	if(m_Data)
	{
		if(m_Data->id == GetControlId())
		{	
			wxString a(m_Data->marker,wxConvUTF8);
			wxString b(m_Data->value,wxConvUTF8);
			DrawData(dc,a,b);
		}
		//fprintf(stdout,"%s %s\n",m_Data->marker,m_Data->value);
	}

}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
	m_Data = (SData*)Signal->GetData();	
	Refresh();
	wxMilliSleep(150);

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