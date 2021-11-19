#include <stdio.h>
#include <stdlib.h>
#define GNUPLOT_PATH "\"C:/Program Files/gnuplot/bin/gnuplot.exe\"" // gnuplot.exeのある場所
// \ではなく、/を使いましょう。
// Program FilesはPROGRA~1、Program Files(x86)はPROGRA~2に置き換えましょう


int main()
{
	FILE *gp;	// For gnuplot

	// gnuplotの起動コマンド
	if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL) {	// gnuplotをパイプで起動
		fprintf(stderr, "ファイルが見つかりません %s.", GNUPLOT_PATH);
		exit(EXIT_FAILURE);
	}

	// --- gnuplotにコマンドを送る --- //
	fprintf(gp, "set xrange [-10:10]\n"); // 範囲の指定(省略可)
	fprintf(gp, "set yrange [-1:1]\n");

	fprintf(gp, "plot sin(x)\n"); 	//sin(x)を描く
	
	fflush(gp); // バッファに格納されているデータを吐き出す（必須）
	system("pause");
	fprintf(gp, "exit\n"); // gnuplotの終了
	_pclose(gp);
}