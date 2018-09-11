
FROM debian

MAINTAINER aperesad

ENV TS3SERVER_LICENSE=accept

EXPOSE 9987/udp 10011 30033

WORKDIR /home/TS3

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y wget && \
	apt-get install -y bzip2 && \
    wget http://dl.4players.de/ts/releases/3.3.0/teamspeak3-server_linux_amd64-3.3.0.tar.bz2 && \
    tar -xvf teamspeak3-server_linux_amd64-3.3.0.tar.bz2
	
WORKDIR teamspeak3-server_linux_amd64

ENTRYPOINT ["sh", "ts3server_minimal_runscript.sh"]

#docker build -t ex01
#docker run --rm -p 9987:9987/udp -p 10011:10011 -p 30033:30033 ex01
#https://github.com/overshard/docker-teamspeak
#https://www.hostinger.com/tutorials/how-to-make-a-teamspeak-3-server/
