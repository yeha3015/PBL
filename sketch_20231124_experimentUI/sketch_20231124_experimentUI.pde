import controlP5.*;
ControlP5 cp5;

int State;
int cone=0;

String filename = "accident.txt";

void setup()
{
	size(1280, 720); //UI解像度
	
	cp5 = new ControlP5(this);
	
	ControlFont cf1 = new ControlFont(createFont("BIZ UDゴシック", 16));

	cp5.addButton		("RemoveCone") //ボタン押下時の実行関数
	.setLabel			("プラス1") //確認ボタンの表示名
	.setFont			(cf1)
	.setPosition		(820,550) //確認ボタンの位置
	.setSize			(240,80) //ボタンのサイズ
	.setColorActive		(color(0,40))
	.setColorBackground	(color(#960989))
	.setColorForeground	(color(#BD0CEA))
	.setColorCaptionLabel(color(#FBF5FC));
	
	cp5.addButton		("AddCone") //ボタン押下時の実行関数
	.setLabel			("マイナス1") //確認ボタンの表示名
	.setFont			(cf1)
	.setPosition		(220,550) //確認ボタンの位置
	.setSize			(240,80) //ボタンのサイズ
	.setColorActive		(color(0,40))
	.setColorBackground	(color(#960989))
	.setColorForeground	(color(#BD0CEA))
	.setColorCaptionLabel(color(#FBF5FC));
	
	State = 0;
	
	println("初期状態□□□□□：状態=" + State);
	
	PFont font = createFont("BIZ UDゴシック", 50, true); //フォントサイズ
	textFont(font);
	fill(0); //テキストカラー
}

void AddCone()
{
	int a=0;
	
	String[] lines = loadStrings(filename);
	
	a=lines.length;
	println("linesの要素数=" + a);
	
	cone++;
	if(cone > a-1) cone = 0;
}


void RemoveCone()
{
	int a=0;
	
	String[] lines = loadStrings(filename);
	
	a=lines.length;
	println("linesの要素数=" + a);
	
	if(cone == 0) cone = a;
	cone--;
}


void draw()
{
	background(#F5FFFE); //背景色

	String[] lines = loadStrings(filename);
	//println("there are" + lines.length + " lines");
	//for (int i = 0 ; i < lines.length; i++){
	//println(lines[i] + "(by loadStrings)");
	//}
	
	switch(0){
		case 0 : 
		  text(lines[cone], 590, 300); //フォント位置
		  //cone = cone + 1;
		  break;
		  
		//case 1 :
		  //text("A1", 590, 300);
		  //break;
		  
		//case 2 :
		  //text("B2", 590, 300);
		  //break;
		
		//case 3 :
		  //text(lines[0], 590, 300);
		  //break;
		
		default :  
	}
}
