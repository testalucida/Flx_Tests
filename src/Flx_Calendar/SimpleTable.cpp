/*
 * File: SimpleTable.cpp
 * Author: max
 *
 * Created on 22. März 2015, 16:43
 */

#include "SimpleTable.h"
#include <FL/fl_draw.H>

using namespace my;

SimpleTable::SimpleTable( int X, int Y, int W, int H, const char* L )
: Fl_Table_Row( X, Y, W, H, L )
, _headerFontsize( 12 )
, _cellFontsize( 12 ) 
, _selMode( SELECTIONMODE_CELL_SINGLE )
, _enableDragging( true )
, _isAlternatingColumnColor( false )
, _isAlternatingRowColor( false )
, _backgroundColor ( FL_WHITE )
, _alternatingColumnColor( FL_WHITE )
, _alternatingRowColor( FL_WHITE )
{
    // box( FL_FLAT_BOX );
    // color( fl_lighter( FL_LIGHT2 ) );
#if FLTK_ABI_VERSION >= 10303
    tab_cell_nav( 1 );
#endif
    col_header( 1 );
    col_resize( 1 );
    row_header_color( FL_LIGHT1 | FL_GRAY );
    col_header_color( FL_LIGHT1 | FL_GRAY );
    callback( &event_callback, (void*) this );
    //when( FL_WHEN_NOT_CHANGED | when( ) );
    when( FL_WHEN_NOT_CHANGED | FL_WHEN_RELEASE_ALWAYS | FL_WHEN_RELEASE );
    end( );
    set_selection( 0, 0, 0, 0 );
}

void SimpleTable::setTableData( my::TableData *pDataTable ) {
    _pData = pDataTable;
    rows( _pData->getRowCount( ) );
    cols( _pData->getColumnCount( ) );
    
    for( int c = 0, cmax = pDataTable->getColumnCount(); c < cmax; c++ ) {
        IndexRel rel;
        rel.viewIdx = rel.modelIdx = c;
        _indexRelations.push_back( rel );
    }
    redraw( );
}

int SimpleTable::handle( int evt ) {
    //int rc = Fl_Table::handle( evt );
    int r, c;
    ResizeFlag resizeFlag;
    TableContext context = cursor2rowcol( r, c, resizeFlag );
    switch( evt ) {
        case FL_PUSH:
            if( Fl::focus( ) != this ) {
                Fl::focus( this );
            }
            if( !canSelectCell( r, c ) ) {
                return 1;
            }
            break;
        case FL_DRAG:
            if( !_enableDragging ) {
                return 1;
            }
            break;
        default:
            break;
    }
    //return rc;
    return Fl_Table::handle( evt );
}

bool SimpleTable::isNothingSelected( ) {
    int x1, y1, x2, y2;
    get_selection( x1, y1, x2, y2 );
    return x1 < 0 && y1 < 0 && x2 < 0 && y2 < 0;
}

void SimpleTable::hideColumn( const char *pColName ) {
    //Model-Index der Spalte ermitteln...
    int modelIdx = _pData->getColumnIndex( pColName );
          //Element des Index-Relations-Vectors holen:
    
    _tmp.clear();
    int viewIndex = 0;
    for_each( _indexRelations.begin(), _indexRelations.end(), 
              [&]( IndexRel &ixrelAlt ) 
    {
        if( ixrelAlt.modelIdx != modelIdx ) {
            IndexRel ixrelNeu;
            ixrelNeu.viewIdx = viewIndex++;
            ixrelNeu.modelIdx = ixrelAlt.modelIdx;
            _tmp.push_back( ixrelNeu );
        }
    } );
    
    _indexRelations = _tmp;
    
    cols( cols( ) - 1 );
}

/** Handle drawing all cells in table */

void SimpleTable::draw_cell( TableContext context, int R, int C, int X, int Y, int W, int H ) {
    switch( context ) {
        case CONTEXT_STARTPAGE: // table about to redraw
            break;
        case CONTEXT_COL_HEADER: // table wants us to draw a column heading (C is column)
            fl_font( FL_HELVETICA, _headerFontsize ); // set font for heading to bold
            fl_push_clip( X - 1, Y, W, H ); // clip region for text
        {
            fl_draw_box( FL_FLAT_BOX, X, Y, W, H, col_header_color( ) );
            //draw a vertical line between columns and a downsided horizontal one
            fl_color( FL_GRAY );
            fl_line( X - 1, Y, X - 1, Y + H - 1, X + W, Y + H - 1 );
            if( _pData ) {
                fl_color( FL_BLACK );
                fl_draw( _pData->getColumnHeader( getModelIndex( C ) ), 
                         X, Y, W, H, FL_ALIGN_CENTER );
            }
        }
            fl_pop_clip( );
            return;
        case CONTEXT_ROW_HEADER: // table wants us to draw a row heading (R is row)
            fl_font( FL_HELVETICA, _headerFontsize ); // set font for row heading to bold
            fl_push_clip( X, Y - 1, W + 1, H );
        {
            fl_draw_box( FL_FLAT_BOX, X, Y, W, H, row_header_color( ) );
            //draw horizontal line between rows and a vertical right sided line
            fl_color( FL_GRAY );
            fl_line( X, Y - 1, X + W - 1, Y - 1, X + W - 1, Y + H );
            if( _pData ) {
                fl_color( FL_BLACK );
                fl_draw( _pData->getRowHeader( R ), X, Y, W, H, FL_ALIGN_CENTER );
            }
        }
            fl_pop_clip( );
            return;
        case CONTEXT_CELL:
        { // table wants us to draw a cell
            fl_push_clip( X - 1, Y - 1, W, H );
            // Background
            fl_draw_box( FL_THIN_UP_BOX, X - 1, Y - 1, W + 2, H + 2, 
                         getCellBackground( R, C, is_selected( R, C ) ) );
            {
                if( _pData ) {
                    fl_color( FL_BLACK );
                    fl_font( FL_HELVETICA, _cellFontsize ); // ..in regular font
                    fl_draw( _pData->getValue( R,  getModelIndex( C ) ), 
                             X + 3, Y + 3, W - 6, H - 6, FL_ALIGN_RIGHT );
                }
            }
            fl_pop_clip( );
            return;
        }
        case CONTEXT_RC_RESIZE: // table resizing rows or columns
            return;
        default:
            return;
    }
}

/** Callback whenever someone clicks on different parts of the table */
void SimpleTable::event_callback2( ) {
    int R = callback_row( );
    int C = callback_col( );
    TableContext context = callback_context( );
    //adjustSelection( context, R, C );
//    switch( context ) {
//        case CONTEXT_ROW_HEADER:
//            if( isNothingSelected( ) ) {
//                set_selection( R, 1, R, 1 );
//                redraw( );
//            }
//            break;
//        case CONTEXT_COL_HEADER:
//            break;
//        case CONTEXT_CELL:
//        { // A table event occurred on a cell
//            switch( Fl::event( ) ) { // see what FLTK event caused it
//                case FL_PUSH: // mouse click?
//                    adjustSelection( context, R, C );
//                    return;
//                case FL_KEYBOARD: // key press in table?
//                    return;
//            }
//            return;
//        }
//        case CONTEXT_TABLE: // A table event occurred on dead zone in table
//           return;
//        default:
//            return;
//    }
}

void SimpleTable::adjustSelection( TableContext context, int r, int c ) {
    switch( context ) {
        case CONTEXT_CELL:
            switch ( _selMode ) {
                case SELECTIONMODE_CELL_SINGLE:
                    int x1, y1, x2, y2;
                    get_selection( x1, y1, x2, y2 );
                    fprintf( stderr, "selected before: %d, %d, %d, %d\n", x1, y1, x2, y2 );
                    set_selection( r, c, r, c );
                    fprintf( stderr, "selected after: %d, %d, %d, %d\n", x1, y1, x2, y2 );
                    redraw();
                    break;
                case SELECTIONMODE_CELL_MULTI:
                    break;
                default:
                    break;
            }
            break;
        case CONTEXT_ROW_HEADER:
        case CONTEXT_COL_HEADER:
        case CONTEXT_TABLE:
            //TODO
            break;
        default:
            break;
    }
}

Fl_Color SimpleTable::getCellBackground( int row, int col, bool isSelected ) const {
    if( isSelected ) return FL_YELLOW;
    
    Fl_Color backColor = _backgroundColor;
    
    if( _isAlternatingColumnColor || _isAlternatingRowColor ) {        
        if( _isAlternatingColumnColor ) {
            int rem = col % 2;
            if( rem != 0 ) backColor = _alternatingColumnColor;
        }
        if( _isAlternatingRowColor ) {
            int rem = row % 2;
            if( rem != 0 ) backColor = _alternatingRowColor;
        }
    }
    return backColor;
}

int SimpleTable::getModelIndex( int viewIndex ) const {
    for( auto itr = _indexRelations.begin(); itr != _indexRelations.end(); itr++ ) {
        const IndexRel &ixRel = *itr; 
        if( ixRel.viewIdx == viewIndex ) {
            return ixRel.modelIdx;
        }
    }
    return -1;
}

void SimpleTable::setAlternatingColumnColor( Fl_Color color ) {
    _alternatingColumnColor = color;
    _isAlternatingColumnColor = color == _backgroundColor ? false : true;
}

void SimpleTable::setAlternatingRowColor( Fl_Color color ) {
    _alternatingRowColor = color;
    _isAlternatingRowColor = color == _backgroundColor ? false : true;
}