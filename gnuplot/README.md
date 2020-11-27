次のコマンドを実行すると./files/plot-cos.pdfが生成されます．

docker-compose build
docker-compose up
次のコマンドを実行して，

docker-compose build
docker-compose run gnuplot bash
コンテナ内でgnuplot ./plot-sinc.pltを実行すると./files/plot-sinc.pdfが生成されます．