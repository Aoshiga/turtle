#!/bin/bash

cd /root/TravelJournal
output=$(git pull)
WEBHOOK='https://discordapp.com/api/webhooks/653993632214548480/xnTuhn3mCd5LouXDR5HERM2SvsjJOm76HsAcNSnt7E7wtbpwJfVFHrLWe5YY9GX8cNlh'
 /root/discord.sh-1.3/discord.sh \
 --webhook-url=$WEBHOOK \
  --username "JMH the Builder" \
  --avatar "http://ntg.nl/bijeen/fotos/44/Jean-Michel%20Hufflen.jpg" \
  --text "$(date +%F_%H:%M:%S) - Build Started "


echo $output > ./log.log 2>&1
echo " $(date +%F_%H:%M:%S) - git update ended starting build " >> ../log.log 2>&1

if [ "$output" = "Already up-to-date." ]; then
/root/discord.sh-1.3/discord.sh \
  --webhook-url=$WEBHOOK \
  --username "JMH the Builder" \
  --avatar "http://ntg.nl/bijeen/fotos/44/Jean-Michel%20Hufflen.jpg" \
  --text "all is up to date building any way"
fi
    cd ./myApp
    echo " $(date +%F_%H:%M:%S) - Client Build started " >> ../log.log 2>&1
    npm i >> ../log.log 2>&1
    npm run build >>../log.log 2>&1
    echo " $(date +%F_%H:%M:%S) - Client Build finished " >> ../log.log 2>&1
    echo " $(date +%F_%H:%M:%S) - copying the clients files " >> ../log.log 2>&1

    cd build
    cp -r * /var/www/html
    cd ../../
    echo " $(date +%F_%H:%M:%S) - finished copying the clients files " >> ../log.log 2>&1

    cd Server
    echo "$(date +%F_%H:%M:%S) - Server update Started" >> ../log.log 2>&1
    npm i >> ../log.log 2>&1
    /root/discord.sh-1.3/discord.sh \
  --webhook-url=$WEBHOOK \
  --username "JMH the Builder" \
  --avatar "http://ntg.nl/bijeen/fotos/44/Jean-Michel%20Hufflen.jpg" \
  --text "$(date +%F_%H:%M:%S) - Build finished" \
  --file ../log.log \