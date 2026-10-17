#!/bin/sh
echo Enter password to check
read pass
passes=`grep -i $pass /etc/passwd | cut -d: -f1`
echo "All users with the word $pass in their passwd"
echo "Entries are: "
echo "$passes" | tr ' ' '\012' | tr '[a-z]' '[A-Z]'
