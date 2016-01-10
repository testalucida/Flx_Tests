
#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Printer.H>
#include <FL/Fl_Browser.H>

#include <Flx_Calendar/Flx_Calendar.h>

#include <my/TableData.h>
//#include <flx/Flx_Calendar.h>
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
    //pCal->show( pBtn->x() + 25, pBtn->y() + pBtn->h() + 25);
    //((Fl_Double_Window*)pWin)->add( pCal );
    MyDate dt = pCal->show( pBtn->x() + 25, pBtn->y() + pBtn->h() + 25 );
    fprintf( stderr, "selected: %s\n", dt.ToIsoString().c_str() );
    delete pCal;
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
    Fl_Double_Window *win = new Fl_Double_Window( 100, 50, 1050, 800, "Flx Tests" );
 
    Fl_Button btn( 10, 10, 90, 25, "..." );
    btn.callback( onOpenCalendar, win );
    
    
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