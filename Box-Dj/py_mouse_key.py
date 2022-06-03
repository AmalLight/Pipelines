from pynput.keyboard import Key , Controller

import json , os , time , pyperclip

keyboard = Controller()

# --------------------------------------------------------
# --------------------------------------------------------

def keyPress1        ( v1 , sec=0.2 ):
    keyboard.press   ( v1 )
    time.sleep ( sec )
    keyboard.release ( v1 )

def keyPress2 ( v1 , v2 , sec=0.2 ):
    with keyboard.pressed ( v1 ): keyPress1 ( v2 , sec )

def keyPress3   ( v1 , v2 , v3 , sec=0.2 ):
    keyboard.press   ( v1 )
    keyboard.press   ( v2 )
    keyboard.press   ( v3 )
    time.sleep ( sec )
    keyboard.release ( v1 )
    keyboard.release ( v2 )
    keyboard.release ( v3 )

# --------------------------------------------------------
# --------------------------------------------------------

def hack ( app , request ) :

    data = request.get_json ()

    app.logger.debug ( data )

    client_number = int ( data [ 'number' ] )
    client_input  = str ( data [ 'input'  ] )
    
    da_ritorno = 'you pressed ' +  str ( client_number ) + '\n'
    
    # --------------------------------------------------------

    if ( client_number == 1 ):

        pyperclip.copy ( client_input )

        keyPress2 ( Key.ctrl_l , 'a' )
        keyPress2 ( Key.ctrl_l , 'v' )
        keyPress1 ( Key.enter        )

        da_ritorno += "paste sel: {}".format ( pyperclip.paste () )
 
    # --------------------------------------------------------

    elif ( client_number == 2 ):

        pyperclip.copy ( client_input )

        keyPress2 ( Key.ctrl_l , 'v' )

        da_ritorno += "paste sel: {}".format ( pyperclip.paste () )

    # --------------------------------------------------------

    elif ( client_number == 3 ):

        pyperclip.copy ( client_input )

        keyPress3 ( Key.ctrl_l , Key.shift_l , 'v' )

        da_ritorno += "paste sel: {}".format ( pyperclip.paste () )

    # --------------------------------------------------------

    elif ( client_number == 4 ):

        os.system ( 'xdotool click 3' )
        
        da_ritorno += "mouse right click done."

    # --------------------------------------------------------

    elif ( client_number == 5 ):

        sel = os.popen ( 'pgrep Sharingan'  ).read   ()
        da_ritorno    += "pgrep before: {}\n".format ( sel[:-1] )

        os.system  ( 'pkill Sharingan' )
        time.sleep ( 2 )

        os.system  ( "xfce4-terminal -T Sharingan -e 'sh -c sharingan'" )
        time.sleep ( 2 )

        sel = os.popen ( 'pgrep Sharingan' ).read   ()
        da_ritorno    += "pgrep after: {}\n".format ( sel[:-1] )

    # --------------------------------------------------------

    elif ( client_number == 6 ):

        keyPress1 ( Key.ctrl_r )
        
        da_ritorno += "right ctrl done."

    # --------------------------------------------------------
    
    elif ( client_number == 7 ):

        keyPress2 ( Key.shift_l , Key.up )

        da_ritorno += "copy sel: \n{}".format ( os.popen ( 'xsel' ).read () )

    # --------------------------------------------------------

    elif ( client_number == 8 ):

        os.system ( 'xdotool click 1' )
        os.system ( 'xdotool click 1' )
        os.system ( 'xdotool click 1' )
        time.sleep ( 0.2 )

        da_ritorno += "copy sel: \n{}".format ( os.popen ( 'xsel' ).read () )

    # --------------------------------------------------------

    elif ( client_number == 9 ):

        keyPress2 ( Key.ctrl_l , 'a' )

        da_ritorno += "copy sel: \n{}".format ( os.popen ( 'xsel' ).read () )

    # --------------------------------------------------------
    # --------------------------------------------------------
    # --------------------------------------------------------
    
    elif ( client_number == 10 ):
    
        keyPress2 ( Key.ctrl_l , 's' )
        
        da_ritorno += "ctrl + s done."
    
    # --------------------------------------------------------
    
    elif ( client_number == 11 ):
    
        keyPress2 ( Key.ctrl_l , 'c' )
        
        da_ritorno += "ctrl + c done.\n"
        da_ritorno += "copy sel: \n{}".format ( pyperclip.paste () )
    
    # --------------------------------------------------------
    
    elif ( client_number == 12 ):

        keyPress2 ( Key.ctrl_l , 'v' )

        da_ritorno += "ctrl + v done.\n"
    
    # --------------------------------------------------------
    
    elif ( client_number == 13 ):

        os.system ( 'xdotool click 2' )
        
        da_ritorno += "mouse middle click done."
    
    # --------------------------------------------------------
    
    elif ( client_number == 14 ):

        os.system ( 'xdotool click 1' )
        os.system ( 'xdotool click 1' )
        
        da_ritorno += "mouse double click done.\n"
        da_ritorno += "copy sel: \n{}".format ( os.popen ( 'xsel' ).read () )
    
    # --------------------------------------------------------
    
    elif ( client_number == 15 ):

        for i in range ( 10 ): keyPress1 ( Key.backspace , 0.1 )
        
        da_ritorno += "delete x10 done."
    
    # --------------------------------------------------------
    
    elif ( client_number == 16 ):

        for i in range ( 10 ): keyPress1 ( Key.delete , 0.1 )
        
        da_ritorno += "cancel x10 done."

    # --------------------------------------------------------

    elif ( client_number == 17 ): None
    elif ( client_number == 18 ): None
    
    return da_ritorno
