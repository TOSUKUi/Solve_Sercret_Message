#!/bin/sh

set -ue



echo nmaping...
PORTFILE="./Port.txt"
PORT=(`nmap -p 1024-65535 $@ | sed -e "s|\([0-9]*\).*|\1|g" | grep -v -e '^\s*$'`)
echo "空いているポートの数 = "${#PORT[@]}

for i in ${PORT[@]}
do
    ./Protocol2.out $@ ${i}
    
done    

