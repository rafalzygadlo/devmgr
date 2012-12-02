#ifndef __SERIAL
#define __SERIAL

#include "serial_port.h"
#include <wx/wx.h>
#include "conf.h"
#include "NaviMapIOApi.h"

class CMySerial :public CSerial
{
		bool _IsRunning;
		wxString DeviceName;
		CNaviBroker *_Broker;
		bool _ValidGPS;								// valid gps ale mo¿e byæ nie zsynchronizowany
		//bool _Exit;
		bool _ValidData;							// from parser
		unsigned char _LineBuffer[BUFFER_LENGTH];
		int _LineBufLen;
		void FoldLine( unsigned char *Buffer, int BufferLength );
		void BuildPortList();						// buduje liste portów
		void SendInfoEvent(wxString info_text);     // wysylaj event do okienka informacyjnego

public:
		CMySerial(CNaviBroker *_Broker);
		~CMySerial();
		bool IsValidGPS();					// zwraca flagê czy prawid³owy sygna³ gps (mo¿e byæ nie z synchronizowany)

		bool IsRunning();
		void SetDeviceName(wxString name);
		wxString GetDeviceName();

		virtual void OnConnect();
		virtual void OnDisconnect();
		virtual void OnData(unsigned char *buffer, int length);
		virtual void OnLine(unsigned char* line);
		virtual void OnStart();
		virtual void OnStop();
		virtual void OnAfterMainLoop();
		virtual void OnBeforeMainLoop();
		virtual void OnExit();			// no gps found plugin ends working
		virtual void OnReconnect();
		virtual void OnNewSignal();
};




#endif
