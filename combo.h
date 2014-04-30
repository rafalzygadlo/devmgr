#include <wx/wx.h>
#include <wx/odcombo.h>

class CPenStyleComboBox : public wxOwnerDrawnComboBox
{
	wxCoord OnMeasureItem( size_t item ); 
	wxCoord OnMeasureItemWidth( size_t WXUNUSED(item) );
	void OnDrawBackground( wxDC& dc, const wxRect& rect, int item, int flags );
	virtual void OnDrawItem( wxDC& dc, const wxRect& rect, int item, int flags ) const;
	virtual void OnDrawBackground( wxDC& dc, const wxRect& rect, int item, int flags ) const;
	virtual wxCoord OnMeasureItem( size_t item ) const;
	virtual wxCoord OnMeasureItemWidth( size_t WXUNUSED(item) ) const;
 

public:
	CPenStyleComboBox(wxWindow *parent, int id);
	
	
};