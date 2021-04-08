
FROM python:3.8.5
WORKDIR /server
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt
COPY . .
CMD [ "python3", "app/server.py" ]