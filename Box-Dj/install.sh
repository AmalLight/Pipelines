
chmod 755  /home/kaumi/Box-Dj/sharingan.sh
sudo ln -s /home/kaumi/Box-Dj/sharingan.sh /usr/bin/sharingan

sudo cp /home/kaumi/Box-Dj/Box-Dj.desktop /etc/xdg/autostart/Box-Dj.desktop
sudo chmod 755                            /etc/xdg/autostart/Box-Dj.desktop

sudo apt-get install -y python3-pip xclip xsel wl-clipboard xdotool

pip3 install pynput pyperclip clipboard
