
#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Printer.H>
#include <FL/Fl_Browser.H>
//#include <FL/Fl_Table.H>
#include <FL/Fl_Tile.H>

#include <Flx_Calendar/Flx_Calendar.h>
#include <Flx_Calendar/SimpleTable.h>
#include <Flx_Calendar/Fl_Table_Copy.h>

#include <my/TableData.h>
#include <my/CharBuffer.h>
#include <my/datetime.h>

using namespace my;

void onPrint( Fl_Widget *, void *pUserdata ) {
//    Flx_Table *pTbl = (Flx_Table*)pUserdata;
////    pTbl->color( FL_WHITE );
//    Fl_Printer printer;
//    
//   
//    int nPages = 1;
//        if( printer.start_job( nPages ) == 0 ) {
//            int rc = printer.start_page();
//            int w=0, h=0;
//            printer.printable_rect( &w, &h );
//            float scale_x = (float)w / (float)pTbl->w();
//            float scale_y = (float)h / (float)pTbl->h();
//            printer.scale( scale_x, scale_y );
//            printer.origin( 0, 0 );
//            printer.print_widget( pTbl, 0, 0 );
//            printer.end_page();
//            printer.end_job();
//        }
}

void onOpenCalendar( Fl_Widget *pBtn, void *pWin ) {
    Flx_Calendar *pCal = new Flx_Calendar();
    pCal->setDate( MyDate( 4, 5, 2016 ));
    MyDate dt = pCal->show( pBtn->x() + 25, pBtn->y() + pBtn->h() + 25 );
    fprintf( stderr, "selected: %s\n", dt.ToIsoString().c_str() );
    delete pCal;
}

void onSimpleTableTest( Fl_Widget *pBtn, void * ) {
    Fl_Window *pWin = new Fl_Window( 100, 100, 500, 500, "SIMPLETABLETEST" );
    SimpleTable *pTbl = new SimpleTable( 5, 5, 490, 490 );
    TableData *pData = new TableData();
    pData->addColumn( "Spalte 0" );
    pData->addColumn( "Spalte 1" );
    pData->addColumn( "Spalte 2" );
    pData->addColumn( "Spalte 3" );
    for( int r = 0; r < 100; r++ ) {
        pData->addRow();
        for( int c = 0; c < 4; c++ ) {
            CharBuffer buf;
            buf.addInt( r );
            buf.add( '/' );
            buf.addInt( c );
            pData->setValue( buf.get(), r, c );
        }
    }
    pTbl->setTableData( pData );
    //pTbl->hideColumn( "Spalte 1" );
//    pTbl->hideColumn( "Spalte 3" );
//    pTbl->hideColumn( "Spalte 0" );
    //pTbl->hideColumn( "Spalte 2" );
    
    pTbl->row_header( 1 );
    
    pTbl->setAlternatingRowColor();
    
    pWin->end();
    pWin->resizable( pTbl );
    
    pWin->show();

}

void onRightTableScroll( char c, int scrollVal, void *pUserData ) {
    fprintf( stderr, "scrollVal: %d\n", scrollVal );
    SimpleTable *pLeftTable = ((SimpleTable*)pUserData);
    pLeftTable->setScrollValue( c, scrollVal );
    pLeftTable->redraw();
}

void onLeftResize( int x, int y, int w, int h, void *pUserData ) {
    SimpleTable *pLeft = (SimpleTable*)pUserData;
    pLeft->makeColumnsFit();
    //int acw = pLeft->getAllColumnsWidth() - pLeft->row_header_width();
//    if( pLeft->isVScrollbarVisible() ) {
//        acw -= pLeft->scrollbar_size();
//    }
//    if( acw < w ) {
//        int cw = w / pLeft->cols();
//        for( int c = 0, cmax = pLeft->cols(); c < (cmax-1); c++ ) {
//            pLeft->col_width( c, cw );
//            acw -= cw;
//        }
//        pLeft->col_width( pLeft->cols() - 1, acw );
//        pLeft->redraw();
//    }
}


void onLeftSelection( Fl_Table_Copy::TableContext context, int r1, int c1, int r2, int c2, void *pUserData ) {
    SimpleTable *pRight = (SimpleTable*)pUserData;
    if( context == Fl_Table_Copy::CONTEXT_ROW_HEADER ) {
        pRight->set_selection( r1, 0, r2, pRight->cols() - 1 );
    } else {
        pRight->set_selection( -1, -1, -1, -1 );
    }
}

void onRightSelection( Fl_Table_Copy::TableContext context, int r1, int c1, int r2, int c2, void *pUserData ) {
    SimpleTable *pLeft = (SimpleTable*)pUserData;
    pLeft->set_selection( -1, -1, -1, -1 );
}

void autowidth( Fl_Widget *, void *pUserData ) {
    SimpleTable *pTbl = (SimpleTable*)pUserData;
    pTbl->makeColumnsFit();
}

void on2Tables( Fl_Widget *pBtn, void * ) {
    Fl_Double_Window *pWin = new Fl_Double_Window( 450, 100, 500, 500, "2 SimpleTables" );
    
    TableData *pData = new TableData();
    pData->addColumn( "Spalte 0" );
    pData->addColumn( "Spalte 1" );
    pData->addColumn( "Spalte 2" );
    pData->addColumn( "Spalte 3" );
    for( int r = 0; r < 50; r++ ) {
        pData->addRow();
        for( int c = 0; c < 4; c++ ) {
            CharBuffer buf;
            buf.addInt( r );
            buf.add( '/' );
            buf.addInt( c );
            pData->setValue( buf.get(), r, c );
        }
    }
    
    Fl_Tile *pTile = new Fl_Tile( 5, 5, 490, 490 );
    SimpleTable *pLeft = new SimpleTable( pTile->x(), pTile->y(), 200, 490 );
    pLeft->setTableData( pData );
    pLeft->hideColumn( "Spalte 1" );
    pLeft->hideColumn( "Spalte 2" );
    pLeft->row_header( 1 );
    pLeft->setAlternatingRowColor();
    
    int W = pLeft->getAllColumnsWidth();
    if( pLeft->isVScrollbarVisible() ) {
        W += Fl::scrollbar_size();
    }
    pLeft->size( W, pLeft->h() );
    
    pLeft->showVScrollbar( false );
    pLeft->makeColumnsFit();
    
//    int x2 = pLeft->x() + pLeft->w();
//    if( pLeft->isVScrollbarVisible() ) {
//        x2 -= Fl::scrollbar_size();
//    }
    SimpleTable *pRight = 
            new SimpleTable( pLeft->x() + pLeft->w(), pLeft->y(),
                             280, pLeft->h() );
    pRight->setTableData( pData );
    pRight->row_header( 0 );
    pRight->hideColumn( "Spalte 0" );
    pRight->hideColumn( "Spalte 3" );
    pRight->setAlternatingRowColor();
    pRight->setScrollCallback( onRightTableScroll, pLeft );
    
    pTile->end();

    pLeft->setSelectionCallback( onLeftSelection, pRight );
    pRight->setSelectionCallback( onRightSelection, pLeft );
  
    pLeft->setResizeCallback( onLeftResize, pLeft );
    
    pLeft->set_selection( 0, 0, 0, 0 );
    
    pWin->end();
    
    pWin->show();

}

void onTestResizeSimpleTable( Fl_Widget *, void * ) {
    Fl_Double_Window *pWin = new Fl_Double_Window( 100, 100, 500, 500, "Resizing" );
    SimpleTable *pTbl = new SimpleTable( 5, 5, 490, 400 );
    TableData *pData = new TableData();
    pData->addColumn( "Spalte 0" );
    pData->addColumn( "Spalte 1" );
    pData->addColumn( "Spalte 2" );
    pData->addColumn( "Spalte 3" );
    for( int r = 0; r < 10; r++ ) {
        pData->addRow();
        for( int c = 0; c < 4; c++ ) {
            CharBuffer buf;
            buf.addInt( r );
            buf.add( '/' );
            buf.addInt( c );
            pData->setValue( buf.get(), r, c );
        }
    }
    pTbl->setTableData( pData );
 
    pTbl->row_header( 1 );
    
    pTbl->setAlternatingRowColor();
    
    pTbl->hideColumn( "Spalte 2" );
    
    Fl_Button *pBtn = new Fl_Button( 10, 420, 90, 25, "Autowidth" );
    pBtn->callback( autowidth, pTbl );
    
    pWin->end();
    pWin->resizable( pTbl );
    
    pWin->show();
}

void onOpenDialog( Fl_Widget*pBtn, void * ) {
    Fl_Double_Window *pWin = new Fl_Double_Window( pBtn->x() + 25, pBtn->y() + pBtn->h() + 25, 300, 300 );
    pWin->end();
    pWin->show();
    
    while( pWin->shown() ) {
        Fl::wait();
    }
}

int main( ) {
//    Fl::scheme( "gleam" );
    Fl::scheme( "gtk+" );
    Fl_Double_Window *win = new Fl_Double_Window( 1000, 50, 200, 200, "Flx Tests" );
 
    Fl_Button btn( 10, 10, 100, 25, "Calendar" );
    btn.callback( onOpenCalendar, win );
    
    Fl_Button btn2( 10, 50, 100, 25, "SimpleTable" );
    btn2.callback( onSimpleTableTest );
    
    Fl_Button btn3( 10, 90, 100, 25, "2 Tables" );
    btn3.callback( on2Tables );
    
    Fl_Button btn4( 10, 130, 100, 25, "Resizing" );
    btn4.callback( onTestResizeSimpleTable );
    
    win->show( );

    return Fl::run( );
}

int main__( ) {
    Fl_Double_Window *win = new Fl_Double_Window( 100, 50, 1050, 800, "Flx Tests" );
    
    Fl_Browser browser( 10, 10, 1030, 700 );
    static int widths[] = { 250, 150, 50, 0 };
    browser.column_widths(widths);
    browser.column_char( '\t' ); // use tab as the column character
    browser.add( "Zeile 1\tSpalte2\t\t@r50.00" );
    browser.add( "@bZeile 2" );
    browser.add( "@m@bZeile 3" );
    browser.add( "@l@r@_Zeile 4" );
    browser.add( "\t\t@_underline\t" );
    browser.add( "SUMME" );
    browser.end();
    
    Fl_Button btn( 10, browser.y() + browser.h() + 10, 90, 25, "Drucken" );
    //btn.callback( onPrint, &tbl );
    
    
    win->show( );

    return Fl::run( );
}

int main_( ) {
    Fl_Double_Window *win = new Fl_Double_Window( 100, 50, 1050, 800, "Flx Tests" );
    
//    Flx_Table tbl( 10, 10, 1030, 700 );
//    tbl.col_header_height( 40 );
//    
//    my::TableData data;
//    data.addColumn( "" );
//    data.addColumn("Betrag\nje Stück" );
//    data.addColumn("Menge");
//    data.addColumn("Summe\nVertrag");
//    data.addColumn("ertrags-\nwirksam" );
//    data.addColumn("steuer-\nwirksam" );
//    data.addColumn("Summe\nDepot");
//    data.addColumn("Kommentar" );
//    
//    int r = data.addRow();
//    data.setValue( "LF 12345 (11 Stück, 12.03.2011 - 12.03.2016)", r, 0 );
//    
//    r = data.addRow();
//    data.setValue( "Laufzeit in Jahren", r, 0 );
//    
//    r = data.addRow();
//    data.setValue( "Kaufpreis", r, 0 );
//    
//    r = data.addRow();
//    data.setValue( "Rückkauf 2016", r, 0 );
//    
//    r = data.addRow();
//    data.setValue( "Tägl. Wertverlust ((Kaufpreis - Rückkauf) / Laufzeit in Tagen)", r, 0 );
//    data.setValue( "((Kaufpreis - Rückkauf) / Laufzeit in Tagen)", r, 7 );
//    
//    tbl.end();
//    
//    tbl.setTableData( data );
//    
//    Fl_Button btn( 10, tbl.y() + tbl.h() + 10, 90, 25, "Drucken" );
//    btn.callback( onPrint, &tbl );
//    
    
    win->show( );

    return Fl::run( );
}