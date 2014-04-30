#include "combo.h"
#include "wx/combo.h"
#include "wx/odcombo.h"
#include <wx/image.h>
#include <wx/pen.h>
#include "tools.h"

CPenStyleComboBox::CPenStyleComboBox(wxWindow *parent, int id)
	:wxOwnerDrawnComboBox(parent,id,wxEmptyString, wxDefaultPosition, wxDefaultSize,NULL,wxCB_READONLY )
{
	Append(GetMsg(MSG_LINE_STYLE_SOLID));
	Append(GetMsg(MSG_LINE_STYLE_DASH));
}

void CPenStyleComboBox::OnDrawItem( wxDC& dc, const wxRect& rect, int item, int flags ) const
{
	if ( item == wxNOT_FOUND )
		return;

	wxRect r(rect);
    r.Deflate(3);
    r.height -= 2;

    int penStyle = wxSOLID;
	switch(item)
	{
		case 0:  penStyle = wxSOLID;		break;
		case 1:  penStyle = wxLONG_DASH;	break;
	}

	wxPen pen( dc.GetTextForeground(), 3, penStyle );

    // Get text colour as pen colour
    dc.SetPen( pen );

    if ( !(flags & wxODCB_PAINTING_CONTROL) )
    {
		dc.DrawText(GetString( item ), r.x + 3, (r.y + 0) + ( (r.height/2) - dc.GetCharHeight() )/2 );
		dc.DrawLine( r.x+5, r.y+((r.height/4)*3), r.x+r.width - 5, r.y+((r.height/4)*3) );
        
	}else{
           
		dc.DrawLine( r.x+5, r.y+r.height/2, r.x+r.width - 5, r.y+r.height/2 );
    }
}

void CPenStyleComboBox::OnDrawBackground( wxDC& dc, const wxRect& rect, int item, int flags ) const
{

	// If item is selected or even, or we are painting the
    // combo control itself, use the default rendering.
    if ( (flags & (wxODCB_PAINTING_CONTROL|wxODCB_PAINTING_SELECTED)) ||   (item & 1) == 0 )
	{
		wxOwnerDrawnComboBox::OnDrawBackground(dc,rect,item,flags);
		return;
	}

     // Otherwise, draw every other background with different colour.
	wxColour bgCol(240,240,250);
	dc.SetBrush(wxBrush(bgCol));
	dc.SetPen(wxPen(bgCol));
	dc.DrawRectangle(rect);

}

 wxCoord CPenStyleComboBox::OnMeasureItem( size_t item ) const
 {
        // Simply demonstrate the ability to have variable-height items
	if ( item & 1 )
		return 36;
	else
		return 24;
}

 wxCoord CPenStyleComboBox::OnMeasureItemWidth( size_t WXUNUSED(item) ) const
 {
       return -1; // default - will be measured from text width
 }

