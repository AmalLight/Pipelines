
ssh 192.168.31.1 -t ' sudo iptables -F ; sudo bash check.sh '

echo ''
read -sp 'Waiting for input to Reset and Check... '
echo ''

bash $HOME/reset_root_connection.sh
