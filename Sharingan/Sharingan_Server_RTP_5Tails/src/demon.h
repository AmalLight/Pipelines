#ifndef DEMON_H_
#define DEMON_H_

#include <iostream>
#include <string>

using namespace::std ;

// -------------------------

const int width  = 1920 ;
const int height = 1080 ;

const int dim = 2 ;

// const int quality = 30 ;

const int wdim  = width  / dim ;
const int hdim  = height / dim ;
const int wdim2 =   wdim / 2   ;
const int hdim2 =   hdim / 2   ;

const std::string str_wdim  = std::to_string ( wdim  ) ;
const std::string str_hdim  = std::to_string ( hdim  ) ;
const std::string str_wdim2 = std::to_string ( wdim2 ) ;
const std::string str_hdim2 = std::to_string ( hdim2 ) ;

const int max_bytes = 0 ;

const std::string home =        "/home/kaumi/"      ;
const std::string live = home + "Sharingan-Live"    ;
const std::string work = home + "Sharingan-Working" ;

const double correctionX = double (  width ) / 1440.0 ;
const double correctionY = double ( height ) /  630.0 ;

// -------------------------

const int keyb1 = 23        ; // iClever Bluethoot Keyboard init
const int keyb2 = keyb1 + 1 ; // iClever Bluethoot Keyboard + 1
const int keyb3 = keyb2 + 1 ; // iClever Bluethoot Keyboard + 2

const int ctrl = 37 ;

const std::string str_keyb1 = std::to_string ( keyb1 ) ;
const std::string str_keyb2 = std::to_string ( keyb2 ) ;
const std::string str_keyb3 = std::to_string ( keyb3 ) ;

const std::string str_ctrl = std::to_string ( ctrl ) ;

// -------------------------

void initDemon () ;

#endif /* DEMON_H_ */
