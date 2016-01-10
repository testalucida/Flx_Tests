#include <Flx_Calendar/DayTable.h>
#include <my/TableData.h>

using namespace my;

DayTable::DayTable( int x, int y, int w, int h ) : SimpleTable( x, y, w, h ) {
    _r = _c = -1;
    	
    _weekendColor = fl_rgb_color( 193, 211, 255 );
	col_resize( 0 );
    enableDragging( false );
    
}

bool DayTable::canSelectCell( int row, int col )  {
	if( row < 0 || col < 0 ) return false; //
    const char* val = getTableData()->getValue( row, col );
    return val[0] > ' ' || val[1] > ' ';
}

/** overrides Flx_Table::getCellBackground(..) */
Fl_Color DayTable::getCellBackground( int row, int col, bool isSelected ) const {
    if ( _rowToday == row && _colToday == col ) {
        return isSelected ? FL_YELLOW : FL_GRAY;
    }

    return isSelected ? FL_YELLOW :
            (col == 5 || col == 6) ? _weekendColor : FL_WHITE;
}

void DayTable::setToday( int row, int col ) { 
	//clearSelection();
	_rowToday = row; _colToday = col; 
}
