# Name: Richard Pham
# Date: 9/22
# Title: Lab1 – Task 3
# Description: This program computes area and perimeter of a circle based in radius.
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
pi=3.14159
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "vcpham" ] #use your username instead of salagtash
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
        exit 1
fi

function area() {
        radius2=`expr $1 \* $1`  #radius squared
        area=$(echo "scale=4; $radius2 * 4*a(1)" | bc -l) #a(1) is arctan(1), which is pi/4
        echo "The area of the circle is $area"
}

function perimeter() {
        perimeter=$(echo "scale=4; $1 * 8*a(1)" | bc -l) #4a(1) is pi, circumference is 2pir, thus we use 8, see above explanation (line 28)
        echo "The perimeter of the circle is $perimeter"
}

response="Yes"
while [ $response != "No" ]
do
        echo "Enter radius of circle: " #Asks for radius
        read radius

        if [ $radius -gt 0 ]; then
                area $radius
                perimeter $radius 

        else
                echo "Positive Numbers Only!"
        fi
        
        echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done