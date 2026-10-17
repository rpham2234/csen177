#!/bin/sh
#Variables
MY_MESSAGE="Hello World"
echo $MY_MESSAGE
echo "This is \" a quote and this is \\ a backslash" #Note \ is used to mark special characters
echo "What is your name?"
read USER_NAME
echo "Hello $USER_NAME"
echo "I will create you a file called ${USER_NAME}_file"
touch ${USER_NAME}_file

echo "I was called with $# parameters"
echo "My name is $0"
echo "My first parameter is $1"
echo "My second parameter is $2"
echo "All parameters are $@"

echo "I will create you a file called $1_file"
touch $1_file
