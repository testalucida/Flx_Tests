#ifndef _FLX_CALENDAR_H_
#define _FLX_CALENDAR_H_

#include <FL/Fl_Double_Window.H>

#include <my/TableData.h>
#include <my/datetime.h>
#include "SimpleTable.h"

class DayTable;
class CalendarController;

class Fl_Choice;
class Fl_Button;
class Fl_Return_Button;

/**
	A calendar widget for selecting a date.
*/
class Flx_Calendar : public Fl_Window {
public:

    Flx_Calendar();

	/** sets the initially selected date */
    void setDate(const my::MyDate &date);

	/** sets the initially selected date */
	void setDate( const char *date );

	/** shows this dialog at the given position and returns 
     the selected date. 
     If Cancel is pressed, the returned date will be not set.
     (MyDate::IsSet() == false) */
	my::MyDate show( int x, int y );
    
    ~Flx_Calendar();
 
protected:
	/** handles the dragging of this Flx_Calendar window */
    int handle(int event);

private:
    /** called by Ok and Cancel buttons */
    static void staticOnOkCancel( Fl_Widget *pWi, void* pUserdata ) ;
	void onOkCancel( bool ok );


private:
	Fl_Return_Button *_pBtnOk;
	Fl_Button  *_pBtnCancel;
    Fl_Choice *_pMoCho;
    Fl_Choice *_pYCho;
    int _xMouse, _yMouse;
    bool _isDragging;
    my::MyDate _selectedDate;
	DayTable *_pDayTable;
	CalendarController *_pCalCtrl;
};


#endif