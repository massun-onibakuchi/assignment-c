#LABEL maintainer="Bakuchi-"

FROM alpine:latest

RUN apk add --no-cache gcc musl-dev

!
# docker build -f ./Dockerfile
# docker run -itd --name [コンテナ名] --mount type=bind,source=[ホスト上のパス],target=[コンテナ上にマウントするパス] [利用したいイメージ]:[利用したいバージョン]
# docker run -it --name Ccompiler --mount type=bind,source="$(PWD)"/practice_program,target=/practice_program -rm [IMAGE]

#docker run -it --name Ccompiler --mount type=bind,source="$(PWD)"/practice_program,target=/practice_program compiler