
if ! [[ -f /usr/bin/android_nonline ]] ; then sudo ln -sf /home/kaumi/android_nonline.sh /usr/bin/android_nonline ; fi

for blocked_ip in "$@"
do
     sudo iptables  -I FORWARD  -i enp1s0  -o  wlan0  -s 192.168.31.$blocked_ip  -j DROP  ;
     sudo iptables  -I FORWARD  -i  wlan0  -o enp1s0  -d 192.168.31.$blocked_ip  -j DROP  ;
done

bash /home/kaumi/check.sh
