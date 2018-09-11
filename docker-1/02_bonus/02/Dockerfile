FROM alpine:3.5

RUN apk add --update py2-pip

COPY requirements.txt /usr/src/app/
RUN pip install --no-cache-dir -r /usr/src/app/requirements.txt

COPY 1.py /usr/src/app/
COPY html/index.html /usr/src/app/templates/

EXPOSE 5000

CMD ["python", "/usr/src/app/1.py"]

# docker run -p 8888:5000 b02
# http://localhost:8888
