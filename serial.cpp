#include <wx/wx.h>
#include <wx/statline.h>
#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"



CMySerial::CMySerial()
	:CSerial()
{
	m_DeviceId = -1;
    m_RunOnStart = false;
	m_IsRunning = false;
	m_LineBufLen = 0;
	m_SignalType = -1;
	m_Broker = NULL;
	m_ConfigPanel = NULL;
}

CMySerial::~CMySerial()
{
	
}

void CMySerial::SetRunOnStart(bool val)
{
	m_RunOnStart = val;
}

bool CMySerial::RunOnStart()
{
	return m_RunOnStart;
}

void CMySerial::SetBroker(CNaviBroker *broker)
{
	m_Broker = broker;
}

void CMySerial::SetDeviceId(size_t id)
{
	m_DeviceId = id;
}

size_t CMySerial::GetDeviceId()
{
	return m_DeviceId;
}

void CMySerial::SetDeviceName(wxString name)
{
	m_DeviceName = name;
}

wxString CMySerial::GetDeviceName()
{
	return m_DeviceName;
}

bool CMySerial::IsRunning()
{
	return m_IsRunning;
}

void CMySerial::OnConnect()
{

}

void CMySerial::OnDisconnect()
{
   
}

void CMySerial::OnData(unsigned char *buffer, int length)
{
	m_SignalType = SERIAL_SIGNAL_ONDATA;
    m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
}

void CMySerial::OnExit()
{
}

void CMySerial::OnStart()
{
	m_IsRunning = true;
}

void CMySerial::OnStop()
{
	m_IsRunning = false;
}

void CMySerial::OnReconnect()
{
	m_SignalType = SERIAL_SIGNAL_RECONNECT;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
}

void CMySerial::OnAfterMainLoop()
{
	bool flag = true;
}

void CMySerial::OnBeforeMainLoop()
{
}

void CMySerial::OnLine(unsigned char* buffer,int length)
{
	Parse(buffer);
}

void CMySerial::OnNewSignal()
{
	m_SignalType = SERIAL_SIGNAL_NEW_SIGNAL;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
	
}

void CMySerial::OnNoSignal()
{
	m_SignalType = SERIAL_SIGNAL_NO_SIGNAL;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
	
}


int CMySerial::GetSignalType()
{
	return m_SignalType;
}

void CMySerial::AddMarker(TDataDefinition marker)
{
	m_DataDefinitionTable.push_back(marker);
}

int CMySerial::GetMarkersLength()
{
	return m_DataDefinitionTable.size();
}

TDataDefinition *CMySerial::GetMarkerItem(int id)
{
	return &m_DataDefinitionTable[id];
}

TDataDefinition *CMySerial::GetMarker(int marker_id)
{
	for(size_t i = 0; i < m_DataDefinitionTable.size();i++)
	{
		if(marker_id == m_DataDefinitionTable[i].DataID)
			return &m_DataDefinitionTable[i];

	}	
	return NULL;
}

/*
void CMySerial::CreateDataDefinitionTable(char *data) 
{
	wxString str(data,wxConvUTF8);
	m_DataDefinitionString = str;
	
	int ListSize;
	char **DataDefinitionList = ExplodeStr(data, ";", &ListSize );
	
	if( ListSize % 5 ) {

		FreeStrList( DataDefinitionList, ListSize );
		//if( !SilentMode )
			//wxMessageBox(MSG_008, MSG_007, wxICON_ERROR );
		return;
	};

	//if( DDTProtector->Lock() != wxMUTEX_NO_ERROR ) {

		//FreeStrList( DataDefinitionList, ListSize );
		//return;
	//};

	m_DataDefinitionTable.clear();
	TDataDefinition DefBuf;
	for(int i = 0; i < ListSize; i+=5 ) {

		memset( &DefBuf, 0, sizeof(TDataDefinition) );
		memset( &DefBuf.Position, -1, MAX_DATA_POSITIONS * sizeof(int) );	// wszystkie pozycje do wycinania na pocz¹tku -1

		DefBuf.DataID = atoi( DataDefinitionList[ i + 0] );
		strcpy( DefBuf.Name, DataDefinitionList[ i + 1] );		// oczyt nazwy parametru oraz markera sentencji NMEA
		strcpy( DefBuf.Marker, DataDefinitionList[ i + 2] );

		if( DataDefinitionList[ i + 3] != NULL ) {	// odczyt listy pozycji do wyciêcia z sentencji NMEA. Zazwyczaj jedna pozycja. Maksymalna iloœæ pozycji zawarta w MAX_DATA_POSITIONS

			int PositionsSize;
			char **Positions = ExplodeStr( DataDefinitionList[ i + 3], ",", &PositionsSize);

			if( (PositionsSize > 0) && (PositionsSize < MAX_DATA_POSITIONS) ) {

				for( int p = 0; p < PositionsSize; p++ ) {

					
					DefBuf.Position[p] = atoi( Positions[p] );
				};
			};
			FreeStrList( Positions, PositionsSize );
		};
		DefBuf.Average = (bool)(atoi( DataDefinitionList[ i + 4] ) != 0 );

		m_DataDefinitionTable.push_back( DefBuf );
	};
	FreeStrList( DataDefinitionList, ListSize );

	if( m_DataDefinitionTable.size() == 0 ) {

		//if( !SilentMode )
			//wxMessageBox(MSG_008, MSG_007, wxICON_ERROR );

	};

	//DDTProtector->Unlock();
};
*/
void CMySerial::Parse(unsigned char *line)
{

	//sygna³ nowej lini
			
	TDataDefinition *DataDefinition;
	for( size_t d = 0; d < m_DataDefinitionTable.size() ; d++ ) 
	{

		DataDefinition = &m_DataDefinitionTable[d];

		if( (MemPos( (const unsigned char*)line, (int)strlen((char*)line), (const unsigned char*)DataDefinition->Marker, (int)strlen( DataDefinition->Marker ), 0 ) != -1 ) ) {	// linia zawiera dane, które nale¿y wyci¹æ

			char *ValidLine = GetSentenceFromLine((char*)line, DataDefinition->Marker );	
			int Size;
			char **StrList = ExplodeStr(ValidLine, ",", &Size);
			free( ValidLine );


			TData Data;
			memset( &Data, 0, sizeof(TData) );
			strcpy(Data.Marker, DataDefinition->Marker);

			// Obliczanie czasu uniwersalnego
			//Data.DateTime = GetUTCTimeNow();	// nie brane pod uwagê
			Data.DataID = DataDefinition->DataID;
			Data.Average = DataDefinition->Average;
			// odczyt kolumn na podstawie definicji odczytu
			size_t WriteStrPor = 0;	// pozycja sk³adania ³añcucha wynikowego

			bool ValidData = true;	// flaga wa¿noœci danych 
			for(size_t i = 0; i < MAX_DATA_POSITIONS; i++ ) {

				if( DataDefinition->Position[i] == -1 )	// pozycja niezdefiniowana, przerywamy 
					break;

				if( DataDefinition->Position[i] < Size ) {

					char *MarkerValue = StrList[ DataDefinition->Position[i] ];
					if( MarkerValue != NULL ) {
	
						size_t MarkerValueSize = strlen( MarkerValue );
						memcpy( Data.Value + WriteStrPor, MarkerValue, MarkerValueSize );
						WriteStrPor += MarkerValueSize;
					};

				} else {

					ValidData = false;	// próba odczytu parametru poza zakresem
					break;
				};
			};

			if( ValidData )
			{
				m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevData",&Data);
				// sygna³ danych
			}	
			FreeStrList( StrList, Size );
		};

	};

}


// config panel
BEGIN_EVENT_TABLE(CPanel,wxPanel)
END_EVENT_TABLE()

CPanel::CPanel(wxWindow *Parent,CMySerial *Serial)
	:wxPanel(Parent,wxID_ANY,wxDefaultPosition,wxDefaultSize )
{
	
	this->SetBackgroundColour(*wxRED);
	m_Serial = Serial;

	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *CenterSizer = new wxBoxSizer(wxVERTICAL);
	//wxBoxSizer *BottomSizer = new wxBoxSizer(wxHORIZONTAL);

	MainSizer->Add(TopSizer,0,wxALL,0);
	MainSizer->Add(CenterSizer,0,wxEXPAND,0);
	//MainSizer->Add(BottomSizer,0,wxALL,0);

	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_PortComboBox = new wxComboBox(this,ID_PORTS,wxEmptyString,wxDefaultPosition,wxDefaultSize, NULL);
	//m_PortComboBox->Disable();
	ButtonSizer->Add(m_PortComboBox,0,wxALL,2);
	
	m_BaudComboBox = new wxComboBox(this,ID_PORTS,wxEmptyString,wxDefaultPosition,wxDefaultSize, NULL);
	//m_BaudComboBox->Disable();
	ButtonSizer->Add(m_BaudComboBox,0,wxALL,2);

	//button start
	m_StartButton = new wxButton(this,ID_START,_("+"),wxDefaultPosition,wxDefaultSize);
	m_StartButton->Disable();
	ButtonSizer->Add(m_StartButton,0,wxALL,2);

	// button stop
	m_StopButton = new wxButton(this,ID_STOP,_("-"),wxDefaultPosition,wxDefaultSize);
	m_StopButton->Disable();
	ButtonSizer->Add(m_StopButton,0,wxALL,2);
	
	TopSizer->Add(ButtonSizer,0,wxALL,2);
	
	//wxStaticLine *Line1 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
	//CenterSizer->Add(Line1,0,wxALL|wxEXPAND,2);

	//wxBoxSizer *LeftSizer = new wxBoxSizer(wxHORIZONTAL);
	//CenterSizer->Add(LeftSizer,0,wxALL|wxEXPAND,5);
	
	// log window check
	//bool chk_log;
	//m_CheckLogBox = new wxCheckBox(this,ID_CHECK_LOG,_("Show log window"),wxDefaultPosition,wxDefaultSize);
	//CheckLogBox->SetValue(chk_log);
	//CenterSizer->Add(m_CheckLogBox,0,wxALL,5);

	// Log Window on center
	m_LogText = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	//m_LogText->Show(chk_log);
	m_LogText->SetMinSize(wxSize(-1,200));
	CenterSizer->Add(m_LogText,1,wxALL|wxEXPAND,5);

/*	
	if(Serial != NULL)
	{
        if(Serial->IsRunning())
		{
            m_StopButton->Enable();
			m_PortComboBox->Disable();
			m_BaudComboBox->Disable();
		}else{
            m_StartButton->Enable();
			m_PortComboBox->Enable();
			m_BaudComboBox->Enable();
		}
	}

*/
	// static horizontal line
	//wxStaticLine *Line3 = new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL);
	//CenterSizer->Add(Line3,0,wxALL|wxEXPAND,2);

	// plugin name
	//wxStaticText *PluginName = new wxStaticText(this,wxID_ANY,wxString::Format(_("%s \n%s"),_(PRODUCT_NAME),_(PRODUCT_COPYRIGHT)));
	//BottomSizer->Add(PluginName,1,wxALL|wxEXPAND,5);

	// button close
	//wxButton *ButtonClose = new wxButton(this,ID_CLOSE,_("Close"),wxDefaultPosition,wxDefaultSize);
	//BottomSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);

	
	//MainSizer->Add(this,1,wxALL|wxEXPAND,0);
	this->SetSizer(MainSizer);

	//RefreshPortsList();
	//RefreshBaudList();
	
	
	//_SetStatusText(wxString::Format(_(MSG_2),_MapPlugin->GetMySerial()->GetPortNumber(),_MapPlugin->GetMySerial()->GetBaudRate()));
	if(Serial != NULL)
	{
		
		//Serial->ScanPorts();

		//for(size_t i = 0; i < Serial->GetPortInfoLength();i++)
		//{
			//wxString port(Serial->GetPortInfo(i).port_name,wxConvUTF8);
			//m_PortComboBox->Append(port);
		//}
		
		wxString buf(Serial->GetPortName(),wxConvUTF8);
		m_PortComboBox->SetValue(buf);
		
		//for(size_t i = 0; i < Serial->GetPortInfoLength();i++)
		//{
			//wxString port(Serial->GetPortInfo(i).port_name,wxConvUTF8);
			//m_PortComboBox->Append(port);
		//}



		m_BaudComboBox->SetValue(wxString::Format(_("%d"),Serial->GetBaudRate()));
	}
	
	//m_PortComboBox->SetDoubleBuffered(true);
	
	//if(GetSizer())
	//	GetSizer()->SetSizeHints(this);

	
	//Center();
		
}


CPanel::~CPanel()
{

}


void CPanel::OnComboBox(wxCommandEvent &event)
{
	PortSelection = event.GetSelection();
//	MapPlugin->GetMySerial()->SetPortIndex(event.GetSelection());
}

void CPanel::OnStartButton(wxCommandEvent &event)
{
	wxString port = m_PortComboBox->GetValue();
	wxString baud = m_BaudComboBox->GetValue();
	m_StartButton->Disable();
	
	m_StopButton->Enable();
	m_PortComboBox->Disable();
	m_BaudComboBox->Disable();
	m_PortComboBox->SetValue(port);
	m_BaudComboBox->SetValue(baud);
	m_Serial->_SetPort(m_PortComboBox->GetValue().char_str());
	long _baud;
	m_BaudComboBox->GetValue().ToLong(&_baud);
	m_Serial->SetBaud(_baud);
		
	m_Serial->Start();
}

void CPanel::OnStopButton(wxCommandEvent &event)
{
	
	wxString value = m_PortComboBox->GetValue();
	m_PortComboBox->SetValue(value);
	m_StopButton->Disable();
	m_PortComboBox->Enable();
	m_BaudComboBox->Enable();
	m_Serial->Stop();
	m_StartButton->Enable(true);
	
}

void CPanel::OnCheckLog(wxCommandEvent &event)
{
	m_LogText->Show(event.IsChecked());
	//FileConfig->Write(_(KEY_CHECK_LOG),event.IsChecked());
	if(GetSizer())
		GetSizer()->SetSizeHints(this);

}


//void CPanel::SetPortEvent(wxString str)
//{
	//wxCommandEvent evt(nvEVT_SET_PORT,ID_SET_PORT);
	//evt.SetString(str);
	//wxPostEvent(this,evt);
//}

//void CPanel::SetBaudEvent(wxString str)
//{
	//wxCommandEvent evt(nvEVT_SET_BAUD,ID_SET_BAUD);
	//evt.SetString(str);
	//wxPostEvent(this,evt);
//}

//void CPanel::SetLogEvent(wxString str)
//{
	//wxCommandEvent evt(nvEVT_SET_LOG,ID_SET_LOG);
	//evt.SetString(str);
	//wxPostEvent(this,evt);
//}

//void CPanel::OnSetLog(wxCommandEvent &event)
//{
  //  if(!_Close)
   // {
    //    m_LogText->AppendText(event.GetString());
   // }
//}


//void CPanel::SetDevice(CSerial *dev)
//{
	//m_Serial = dev;
//}

