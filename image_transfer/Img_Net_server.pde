import processing.net.*; //ネットワークライブラリの使用宣言

Server   myServer; //サーバのデータ構造
String[] Message = new String[5]; //表示メッセージ用文字列配列
int      state   = 0;    // サーバの受信状態
PImage   RecvImg; //受信画像を格納するPImage型変数

void setup( ){
  size( 860, 580 );
  
  //日本語フォント(BIZ UDゴシック)で、サイズ16のフォントを生成
  PFont font = createFont("BIZ UDゴシック", 16, true);
  textFont(font); // 生成したフォントを設定

  //サーバの起動 (ポート番号は5554)
  myServer = new Server(this, 5554);
  
  Message[0] = "サーバ： " + myServer.ip( );
  Message[1] = " ";
  Message[2] = " ";
  Message[3] = " ";
  Message[4] = " ";
}

void stop( ){
  myServer.stop( );
}

void draw( ){
  // 画面描画(100ms毎に勝手に繰り返す)
  background(#086C52); // 緑に塗りつぶす．
  
  text(Message[0] + " :状態 " + state, 30, 30);
  text(Message[1], 30, 60); 
  text(Message[2], 30, 90);
  text(Message[3], 30, 120);
  text(Message[4], 30, 150);
  
  // 受信画像をウィンドウに表示
  if( RecvImg != null ) 
    image(RecvImg, 45, 155, RecvImg.width * 0.6, RecvImg.height * 0.5); 
}

// クライアント接続時に起動されるイベント
void serverEvent( Server ConServer, Client ConClient ){ 
  Message[1] = "クライアント(" + ConClient.ip( ) + ")と接続";
}

// マウスをクリックしたら起動されるイベント
void mousePressed( ) {
  if(state == 0){ //状態0の時のみ
    myServer.write(0); //マウスが押されたらクライアントに動作指示
  }
}

//*************************************************************************
//データを受信したら起動されるイベント(引数は送信先の情報)
//*************************************************************************
int    ImgWidth     = 0;    // 受信画像の幅
int    ImgHeight    = 0;    // 受信画像の高さ
int    NumBytes     = 0;
String whereIs = "";
String User_ID = "";
void clientEvent(Client RecvClient){
  
  //受信したデータ(受信バッファ内)のバイト数を取得
  NumBytes = RecvClient.available( );
  
  // 受信状態に応じた動作の記述(状態0: 文字列の受信, 状態1：画像の高さと幅の受信, 状態2：画像データの受信)
  switch(state){
    // -------------------------------------------------------------------------------------------------
    case 0 :
      NumBytes = RecvClient.available();
      if(NumBytes >= 3){
        whereIs = RecvClient.readString();
        Message[2] = "エリア: " + whereIs.substring(0, 3);
        state      = 1;
      }
    break;
    
    case 1 : 
      NumBytes = RecvClient.available();
      print(NumBytes);
      if(NumBytes >= 3){
        byte[] TmpBuff = RecvClient.readBytes(NumBytes); 
        int ID = (TmpBuff[0] & 0xff) << 16 | (TmpBuff[1] & 0xff) << 8 | TmpBuff[2] & 0xff;
        println(ID);
        User_ID = Integer.valueOf(ID).toString();
        Message[3] = "ID : " + User_ID;
        saveStrings("Area.txt", split(whereIs + " " + User_ID, ","));
        state = 2;
        myServer.write(1);
      }
      break;
    //--------------------------------------------------------------------------------------------------
    case 2 : // 画像の高さと幅を受信
    //--------------------------------------------------------------------------------------------------
      NumBytes = RecvClient.available( ); //受信データのバイト数を確認
      
      if( NumBytes >= 8 ){ //8バイト分、データを受信したら
        byte[] TmpBuff = RecvClient.readBytes(NumBytes); //今受け取ったバイトデータを一時バッファに保存
        
        ImgHeight  = (TmpBuff[3] & 0xff) << 24 | (TmpBuff[2] & 0xff) << 16 | (TmpBuff[1] & 0xff) << 8 | TmpBuff[0] & 0xff;
        ImgWidth   = (TmpBuff[7] & 0xff) << 24 | (TmpBuff[6] & 0xff) << 16 | (TmpBuff[5] & 0xff) << 8 | TmpBuff[4] & 0xff;
        Message[4] = "高さ= " + ImgHeight + ", 幅= " + ImgWidth;
        state      = 3; //状態遷移
        myServer.write(2); // 高さと幅の受信完了をクライアントに通知
      }
      
      break;
    //--------------------------------------------------------------------------------------------------
    case 3 : // 画像データの受信(総画素数×RGBの3バイト)
    //--------------------------------------------------------------------------------------------------
      NumBytes = RecvClient.available( ); //受信データのバイト数を確認
      if( NumBytes >= ImgHeight * ImgWidth * 3 ){ //全画像データ(RGB×高さ×幅)を受信したら
        
        Message[4] += " => 受信完了: " + NumBytes + "[バイト]";
        
        byte[] TmpBuff = RecvClient.readBytes(NumBytes);//受信バッファ内の全画像データを読み出す。
        
        //画像を格納するメモリ領域を確保
        RecvImg = createImage(ImgWidth, ImgHeight, RGB);
        int idx = 0;
        for( int i = 0; i < ImgWidth * ImgHeight; i++ ){
          //画素を詰め込む。
          RecvImg.pixels[i] = color(( TmpBuff[idx+0] & 0xff), ( TmpBuff[idx+1] & 0xff), ( TmpBuff[idx+2] & 0xff));
          idx += 3;
        }
        RecvImg.updatePixels( ); //領域のアップデート
        state = 0;   //状態遷移
        myServer.write(0); // 画像データの受信完了をクライアントに通知
        RecvImg.save("output.png");
      }
      break;

    default : break;
  }
}
