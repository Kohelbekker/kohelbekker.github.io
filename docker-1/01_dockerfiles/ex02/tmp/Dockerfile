FROM ruby:latest

MAINTAINER aperesad 

RUN apt-get update -y && apt-get install -y build-essential libpq-dev nodejs
RUN gem install rails

ONBUILD COPY app/ /opt/app
ONBUILD WORKDIR /opt/app

ONBUILD EXPOSE 3000

ONBUILD RUN bundle install
ONBUILD RUN rake db:migrate
ONBUILD RUN rake db:seed


#https://docs.docker.com/compose/rails/#define-the-project
