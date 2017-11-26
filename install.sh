sudo grep "auth optional mypam.so" /etc/pam.d/common-auth
if [ "$?" = 1 ]
then
   sudo echo -e  "\nauth optional mypam.so" >> /etc/pam.d/common-auth
else
    echo "auth optional mypam.so"
fi

sudo grep "session optional mypam.so" /etc/pam.d/common-session
if [ "$?" = 1 ]
then
   sudo echo -e "\nsession optional mypam.so" >> /etc/pam.d/common-session
else
    echo "session optional mypam.so"
fi

sudo grep "password optional mypam.so" /etc/pam.d/common-password
if [ "$?" = 1 ]
then
   sudo echo -e "\npassword optional mypam.so" >> /etc/pam.d/common-password
else
   echo "password optional mypam.so"
fi
