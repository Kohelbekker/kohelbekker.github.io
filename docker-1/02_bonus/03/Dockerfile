FROM ubuntu:latest

MAINTAINER aperesad <aperesad@student.unit.ua>

RUN apt-get update -y && \
	apt-get upgrade -y && \
	apt-get install -y curl

ENV MY_URL https://www.kyivpost.com/

WORKDIR /data

VOLUME /data

CMD sh -c "curl  -Lk $MY_URL > /data/results"

#https://askubuntu.com/questions/230476/how-to-solve-permission-denied-when-using-sudo-with-redirection-in-bash
# -c flag means execute the following command as interpreted by this program.
# curl -k  This option explicitly allows curl to  perform  "insecure" SSL connections and transfers.
# curl L
# docker run --rm -e MY_URL=          -v $(pwd)/vol:/data/:rw 03
