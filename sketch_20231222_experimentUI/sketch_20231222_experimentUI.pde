import controlP5.*;
import java.util.*;
ControlP5 cp5;

int State;
int cone=0;
int nd_length = 0;

String filename0 = "result.txt";
String filename = filename0.replace("\n", "");


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
  println(filename);
}

void AddCone()
{
	println("linesの要素数=" + nd_length);

  cone++;
	if(cone > nd_length-3){
    cone = 0;
  }
}


void RemoveCone()
{
	println("linesの要素数=" + nd_length);
	
	if(cone == 0){
    cone = nd_length - 2;
  }
	cone--;
}


void draw()
{
	background(#F5FFFE); //背景色
  //
	String[] ex_data = loadStrings(filename);
  List<String> new_data = new ArrayList<String>();
  for(int i = 0; i < ex_data.length; i++){
    if(ex_data[i] != ""){
      new_data.add(ex_data[i]);
    }else{
      println("a");
    }
  }
  nd_length = new_data.size();
	//println("there are" + lines.length + " lines");
	//for (int i = 0 ; i < lines.length; i++){
	//println(lines[i] + "(by loadStrings)");
	//}
	
	switch(0){
		case 0 : 
		  text(new_data.get(cone), 590, 300); //フォント位置
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
