# C言語Docker


## Usage 
### Docker
 - イメージからコンテナを生成してコンテナに入る
 `docker run -it --name Ccompiler --mount type=bind,source="$(PWD)"/practice_program,target=/practice_program -rm [IMAGE]`


 - compilerという名前のイメージからCcompilerという名前のコンテナを生成してコンテナに入る
` docker run -it --name Ccompiler --mount type=bind,source="$(PWD)"/practice_program,target=/practice_program compiler`

 - 全てのコンテナを消去する
` docker rm docker ps -a -q`