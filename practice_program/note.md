## pricf scanf
 - printf() *variable*
 - scanf() &*variable*

## 文字列と文字型
文字列とはchar型の配列char[]のこと
char[] strとする
 - char[] は%s scanf("%s", 配列名);
 - char    は scanf("%c", &変数);

strとstr[0]は別物
strは配列の銭湯番地=ポインタが格納されている．
str[0],str[1]．．．はその先頭番地からの連番で格納される
str[i]は1文字を表現する文字コードが入っている．
