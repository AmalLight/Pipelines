#!/bin/bash

 width=1920
height=1080

div=2 ; quality=30

# 320x180 is 1920x1080 / 6
wdiv=$((  width / div ))
hdiv=$(( height / div ))
# ------------------------

# 160x90 is 320x180 / 2
wdiv2=$(( wdiv / 2 ))
hdiv2=$(( hdiv / 2 ))
# ------------------------

max=0 # max bytes is 7000 for 1920x1080 / 6

var='/var/www/html'

live=$var/'Sharingan-Live'
work=$var/'Sharingan-Working'

[[ ! -d $live ]] && sudo mkdir -p $live && sudo chmod 777 -R $live
[[ ! -d $work ]] && sudo mkdir -p $work && sudo chmod 777 -R $work

doing_row ()
{
    posx=$1 ; posy=$2 ; file=$3
    
    maim --geometry "$wdiv"x"$hdiv"+"$posx"+"$posy" "$work"/"$file"a.jpg ; sync
    
    # 240x105 is 1440x630 / 6
    # 160x90--is--320x180-/-2--------------------------------------------------------
    # -------------------------------------------------------------------------------
    convert "$work"/"$file"a.jpg -resize    "$wdiv2"x"$hdiv2"! \
                                 -colorspace              Gray \
            "$live"/"$file"b.jpg
    #                            -quality             $quality \
    # -------------------------------------------------------------------------------
    
    sync
    
    # tmp_max=(`wc -c /var/www/html/Sharingan/"$file"b.jpg`) ; 
    
    # (( $tmp_max >  $max )) && echo "new max: $tmp_max" ;
    # (( $tmp_max >  $max )) &&            max=$tmp_max  ;
    # (( $tmp_max == $max )) && echo "this value == max" ;
}

rm -f $work/*
rm -f $live/*

echo ''
echo "Working: $work"
echo "Live: $live"

echo ''
echo "Started and doing files..."

while true
do
    sleep 0.100 # milliseconds to seconds

    for first in `seq 1 $div` ;
    do
        for second in `seq 1 $div` ;
        do
            doing_row "$(( ( first - 1 ) * wdiv ))" "$(( ( second - 1 ) * hdiv ))" "$(( ( first - 1 ) * $div + second ))"
        
        done
    done
done
