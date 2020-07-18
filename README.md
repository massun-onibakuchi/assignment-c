# C言語Docker


## Usage 
 docker run -it --name Ccompiler --mount type=bind,source="$(PWD)"/practice_program,target=/practice_program -rm [IMAGE]


 - イメージからコンテナを生成してコンテナに入る
 docker run -it --name Ccompiler --mount type=bind,source="$(PWD)"/practice_program,target=/practice_program compiler

 - 全てのコンテナを消去する
 docker rm `docker ps -a -q`