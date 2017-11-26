sudo grep "auth optional mypam.so" /etc/pam.d/common-auth
if [ "$?" = 0 ]
then
    sudo sed -i "/auth optional mypam.so/d" /etc/pam.d/common-auth
fi

sudo grep "session optional mypam.so" /etc/pam.d/common-session
if [ "$?" = 0 ]
then
    sudo sed -i "/session optional mypam.so/d" /etc/pam.d/common-session
fi

sudo grep "password optional mypam.so" /etc/pam.d/common-password
if [ "$?" = 0 ]
then
    sudo sed -i "/password optional mypam.so/d" /etc/pam.d/common-password
fi
