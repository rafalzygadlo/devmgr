#include "conf.h"
#include "tools.h"
#include <wx/stdpaths.h>

wxMutex *mutex = new wxMutex;

wxMutex *GetMutex()
{
	return mutex;
}


double DD( float DM ) 
{

	int ddeg = ( int )(DM / 100);
	double min =  ( double )( DM / 100 - ddeg);
	double x = double ( min / 60 ) * 100;
	double a = ( double ) ddeg + x;

	return a;

}

wxString ConvertDegree(float degree) 
{
	int decimal = (int)degree;
    float minutes = (float)(degree - decimal) *100;
    return wxString::Format(_("%02d %02.2f'"),decimal, minutes);

}

wxString FormatLongitude(float x) 
{
      wxString str;

      if (x > 0.0f) {
        if (x <= 180.0f)
			str = wxString::Format(_("%s E"), ConvertDegree(x).wc_str());
        else
			str = wxString::Format(_("%s W"), ConvertDegree(360 - x).wc_str());
      } else {
        if (x >= -180.0f)
			str = wxString::Format(_("%s W"), ConvertDegree(-x).wc_str());
        else
			str = wxString::Format(_("%s E"), ConvertDegree(x+360).wc_str());
            
      }
      return str;
}



wxString FormatLatitude(float y) 
{
	
	wxString str;

    if (y > 0)
		str = wxString::Format(_("%s N"), ConvertDegree(y).wc_str());
    else
		str = wxString::Format(_("%s S"), ConvertDegree(-y).wc_str());

    return str;

}

void PrintInfo(CNaviBroker *Broker,wchar_t *text)
{
	// 9 id chart_catalogu
	if(Broker != NULL)
		Broker->PrintInfoBlock(Broker->GetParentPtr(), 13 , text, 10);

}

char *gen_random(const int len) 
{
	char *s = (char*)malloc(len + 1);

	srand( (unsigned int) time(NULL));

	for (int i = 0; i < len; ++i) {
         int randomChar = rand()%(26+26+10);
         if (randomChar < 26)
             s[i] = 'a' + randomChar;
         else if (randomChar < 26+26)
             s[i] = 'A' + randomChar - 26;
         else
             s[i] = '0' + randomChar - 26 - 26;
     }
	 s[len] = 0;

	 return s;
}

wxString GenerateRandomFileName(wxString dir, wxString ext, int len)
{
	// genarate random name
	static wxString DestinationPath;
	wxString RandomName;
	char *random;
	
	do
	{
		random = gen_random(len);
		wxString RandomUTF8(random, wxConvUTF8);
		RandomName = RandomUTF8;
		RandomUTF8.Clear();
		DestinationPath.Printf(wxT("%s%s%s.%s"),dir.wc_str(),wxT(DIR_SEPARATOR),RandomName.wc_str(),ext.wc_str());
	}
	while(wxFileExists(DestinationPath));

	free( random );
	return DestinationPath;
}

wxString GetWorkDir(void)
{
	static wxString buffer;
	wxStandardPaths *Paths = new wxStandardPaths();
 	buffer.Printf(wxT("%s%s%s%s"), Paths->GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR), wxT(DIR_SEPARATOR) );
	delete Paths;
	return buffer;
}
