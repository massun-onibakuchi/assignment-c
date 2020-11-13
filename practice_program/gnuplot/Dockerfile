FROM ubuntu

WORKDIR /home/files
# COPY ./second-term/histo.d /home/files
RUN apt update -y && apt upgrade -y && apt install -y gnuplot 
# && apt-get install gnuplot-x11

CMD ["gnuplot", "test.plt"]