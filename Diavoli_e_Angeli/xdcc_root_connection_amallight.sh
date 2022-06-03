
ssh 192.168.31.1 -t  " \
\
sudo iptables  -I  OUTPUT  -o  wlan0  -s  172.20.10.0/28  -p  tcp  --match  multiport  --dports  6660,6666,6667,6668,6697,6999 -j  ACCEPT ; \
sudo iptables  -I  OUTPUT  -o  wlan0  -s  172.20.10.0/28  -p  tcp  --match  multiport  --sports  1024:5000                     -j  ACCEPT ; \
sudo iptables  -I  INPUT   -i  wlan0  -d  172.20.10.0/28  -p  tcp  --match  multiport  --sports  6660,6666,6667,6668,6697,6999 -j  ACCEPT ; \
sudo iptables  -I  INPUT   -i  wlan0  -d  172.20.10.0/28  -p  tcp  --match  multiport  --dports  1024:5000                     -j  ACCEPT ; \
\
sudo iptables  -I  FORWARD  -i  enp1s0  -o  wlan0   -p  tcp  --match  multiport  --dports  6660,6666,6667,6668,6697,6999  -j  ACCEPT ; \
sudo iptables  -I  FORWARD  -i  enp1s0  -o  wlan0   -p  tcp  --match  multiport  --sports  1024:5000                      -j  ACCEPT ; \
sudo iptables  -I  FORWARD  -i  wlan0   -o  enp1s0  -p  tcp  --match  multiport  --sports  6660,6666,6667,6668,6697,6999  -j  ACCEPT ; \
sudo iptables  -I  FORWARD  -i  wlan0   -o  enp1s0  -p  tcp  --match  multiport  --dports  1024:5000                      -j  ACCEPT ; \
\
sudo bash check.sh ; "

echo ''
read -sp 'Waiting for input to Reset and Check... '
echo ''

bash $HOME/reset_root_connection.sh
