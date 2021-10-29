#!/bin/bash
STR=/home/pi/Desktop/DQPSK/Images/image
STR_H=/home/pi/Desktop/DQPSK/Images_high_resolution/image_high
num=0
id=0

while(true); do
  
  export IMAGE="$STR$num.jpg"
  export IMAGEH="$STR_H$num.jpg"
  export NUM="$num"
  
  while(true); do
    if [ -e $IMAGE ]; then
      IMAGE="$STR$num$id.jpg"
      IMAGEH="$STR_H$num$id.jpg"
      ((id++))
    else
      break
    fi
    
  done
  
  /home/pi/Desktop/DQPSK/bin/cam
  '''while true; do
    
    /home/pi/Desktop/DQPSK/bin/listen
    debut=$(date +%s)
    #var=$(/home/pi/Desktop/DQPSK/Energy) 
    #var=$(python3 /home/pi/Desktop/Stage_asma/Energy.py) 
    #fin=$(date +%s)
    duree=$(( $fin - $debut ))
    if [ $var == 0 ]; then
      /home/pi/Desktop/DQPSK/bin/control_PA 1
      break  
    fi
  done '''
  hackrf_transfer -t /home/pi/Desktop/DQPSK/Identifiant.raw -f 1278000000 -s 5000 -x 47 -p 1 -a 1 -d 000000000000000075b068dc317bae07  
  /home/pi/Desktop/DQPSK/bin/emitter_image
  ((num++))
  /home/pi/Desktop/DQPSK/bin/control_PA 0
  sleep 1



done
