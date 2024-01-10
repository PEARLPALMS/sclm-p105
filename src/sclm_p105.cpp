 /**
 * SCLM-P105
 * 2021/03/09 Tue pearlpalms@gmail.com
 * $Id:$
 *
 * SCLM-P105 <-> Arduino
 *  (VSS)  1 <-> GND
 *  (VDD)  2 <-> +5V
 *   (NC)  3 <-> ---
 * (BUSY)  4 <-> D2
 *  (CLK)  5 <-> D3
 *  (/CS)  6 <-> D4
 *  (DB0)  7 <-> D5
 *  (DB1)  8 <-> D6
 *  (DB2)  9 <-> D7
 *  (DB3) 10 <-> D8
 *  (DB4) 11 <-> D9
 *  (DB5) 12 <-> D10
 *  (DB6) 13 <-> D11
 *  (DB7) 14 <-> D12
 */

#include <sclm_p105.h>

// ピン番号
int BUSY, CLK, CS, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7;

// 送信データバッファ
byte data[27];

// ゼロ埋めフラグ
boolean fillZero = false;

// インスタンス
SCLM_P105::SCLM_P105(int busy, int clk, int cs, int db0, int db1, int db2, int db3, int db4, int db5, int db6, int db7){
    BUSY = busy;
    CLK = clk;
    CS = cs;
    DB0 = db0;
    DB1 = db1;
    DB2 = db2;
    DB3 = db3;
    DB4 = db4;
    DB5 = db5;
    DB6 = db6;
    DB7 = db7;
}

/**
 * 初期化
 */
void SCLM_P105::begin(int busy, int clk, int cs, int db0, int db1, int db2, int db3, int db4, int db5, int db6, int db7){
    BUSY = busy;
    CLK = clk;
    CS = cs;
    DB0 = db0;
    DB1 = db1;
    DB2 = db2;
    DB3 = db3;
    DB4 = db4;
    DB5 = db5;
    DB6 = db6;
    DB7 = db7;
    begin();
}

/**
 * 初期化
 */
void SCLM_P105::begin(){

  // ピン設定
  pinMode(BUSY, INPUT_PULLUP);
  pinMode( CLK, OUTPUT);
  pinMode(  CS, OUTPUT);
  pinMode( DB0, OUTPUT);
  pinMode( DB1, OUTPUT);
  pinMode( DB2, OUTPUT);
  pinMode( DB3, OUTPUT);
  pinMode( DB4, OUTPUT);
  pinMode( DB5, OUTPUT);
  pinMode( DB6, OUTPUT);
  pinMode( DB7, OUTPUT);

  // LEDピン初期化
  digitalWrite(CS, HIGH);
  digitalWrite(CLK, LOW);
  digitalWrite(DB0, LOW);
  digitalWrite(DB1, LOW);
  digitalWrite(DB2, LOW);
  digitalWrite(DB3, LOW);
  digitalWrite(DB4, LOW);
  digitalWrite(DB5, LOW);
  digitalWrite(DB6, LOW);
  digitalWrite(DB7, LOW);
  delayMicroseconds(24);

  // LED消去
  clear();
  update();
}

/**
 * ゼロ埋めフラグ設定
 * boolean b: true:ゼロ埋め有り false:ゼロ埋め無し
 */
void SCLM_P105::setFillZero(boolean b){
  fillZero = b;
}

/**
 * 上段に数字を表示
 * double d: 表示する数字
 * int c: 色
 */
void SCLM_P105::printUp(double d, int c){
  printUp(String(d, 1), c);
}

/**
 * 上段に数字を表示
 * float f: 表示する数字
 * int c: 色
 */
void SCLM_P105::printUp(float f, int c){
  printUp(String(f, 1), c);
}

/**
 * 上段に数字を表示
 * int i: 表示する数字
 * int c: 色
 */
void SCLM_P105::printUp(int i, int c){
  printUp(String(i), c);
}

/**
 * 上段に数字を表示
 * long l: 表示する数字
 * int c: 色
 */
void SCLM_P105::printUp(long l, int c){
  printUp(String(l), c);
}

/**
 * 上段に数字を表示
 * String s: 表示文字列
 * int c: 色
 */
void SCLM_P105::printUp(String s, int c){

  // コロン処理
  if(s.indexOf(":") != -1)
    markColon(c);
  else
    markColon(LED_BLACK);

  // ドットの処理
  if(s.indexOf(".") != -1)
    markUpDot(c);
  else
    markUpDot(LED_BLACK);

  // 不要文字を削除
  s.replace(":", "");
  s.replace(".", "");

  // 文字列をlongに変換
  long l = s.toInt();
  data[17] = (l / 10000) % 10 + c;
  data[18] = (l / 1000) % 10 + c;
  data[19] = (l / 100) % 10 + c;
  data[20] = (l / 10) % 10 + c;
  data[21] = (l / 1) % 10 + c;

  // ゼロ埋め無しの場合黒で8を表示
  if(!fillZero)
    if(data[17] - c == 0){
      data[17] = LED_BLACK + 8;
      if(data[18] - c == 0){
        data[18] = LED_BLACK + 8;
        if(data[19] - c == 0){
          data[19] = LED_BLACK + 8;
          if(data[20] - c == 0)
            data[20] = LED_BLACK + 8;
	}
      }
    }
}

/**
 * 下段に数字を表示
 * double d: 表示する数字
 * int c: 色
 */
void SCLM_P105::printDown(double d, int c){
  printDown(String(d, 1), c);
}

/**
 * 下段に数字を表示
 * float f: 表示する数字
 * int c: 色
 */
void SCLM_P105::printDown(float f, int c){
  printDown(String(f, 1), c);
}

/**
 * 下段に数字を表示
 * int i: 表示する数字
 * int c: 色
 */
void SCLM_P105::printDown(int i, int c){
  printDown(String(i), c);
}

/**
 * 下段に数字を表示
 * long l: 表示する数字
 * int c: 色
 */
void SCLM_P105::printDown(long l, int c){
  printDown(String(l), c);
}

/**
 * 下段に数字を表示
 * String s: 表示文字列
 * int c: 色
 */
void SCLM_P105::printDown(String s, int c){
Serial.println(s);

  // ドットの処理
  if(s.indexOf(".") != -1)
    markDownDot(c);
  else
    markDownDot(LED_BLACK);

  // 不要文字を削除
  s.replace(":", "");
  s.replace(".", "");

  // 文字列をlongに変換
  long l = s.toInt();
  data[22] = (l / 10000) % 10 + c;
  data[23] = (l / 1000) % 10 + c;
  data[24] = (l / 100) % 10 + c;
  data[25] = (l / 10) % 10 + c;
  data[26] = (l / 1) % 10 + c;

  // ゼロ埋め無しの場合黒で8を表示
  if(!fillZero)
    if(data[22] - c == 0){
      data[22] = LED_BLACK + 8;
      if(data[23] - c == 0){
        data[23] = LED_BLACK + 8;
        if(data[24] - c == 0){
          data[24] = LED_BLACK + 8;
          if(data[25] - c == 0)
            data[25] = LED_BLACK + 8;
	}
      }
    }
}

/**
 * [終了]表示
 * int c: 色
 */
void SCLM_P105::mark0(int c){
  inputMark(13, c);
}

/**
 * [閉塞]表示
 * int c: 色
 */
void SCLM_P105::mark1(int c){
  inputMark(14, c);
}

/**
 * [押子]表示
 * int c: 色
 */
void SCLM_P105::mark2(int c){
  inputMark(15, c);
}

/**
 * [電池]表示
 * int c: 色
 */
void SCLM_P105::mark3(int c){
  inputMark(16, c);
}

/**
 * [システム]表示
 * int c: 色
 */
void SCLM_P105::mark4(int c){
  inputMark(4, c);
}

/**
 * [予定]表示
 * int c: 色
 */
void SCLM_P105::mark5(int c){
  inputMark(12, c);
}

/**
 * [早送り]表示
 * int c: 色
 */
void SCLM_P105::mark6(int c){
  inputMark(11, c);
}

/**
 * [積算]表示
 * int c: 色
 */
void SCLM_P105::mark7(int c){
  inputMark(10, c);
}

/**
 * [注入量]表示
 * int c: 色
 */
void SCLM_P105::mark8(int c){
  inputMark(9, c);
}

/**
 * [時:分]表示
 * int c: 色
 */
void SCLM_P105::mark9(int c){
  inputMark(6, c);
}

/**
 * [mL]表示
 * int c: 色
 */
void SCLM_P105::mark10(int c){
  inputMark(7, c);
}

/**
 * [mL/h]表示
 * int c: 色
 */
void SCLM_P105::mark11(int c){
  inputMark(8, c);
}

/**
 * [:]表示
 * int c: 色
 */
void SCLM_P105::markColon(int c){
  inputMark(1, c);
}

/**
 * [上段.]表示
 * int c: 色
 */
void SCLM_P105::markUpDot(int c){
  inputMark(2, c);
}

/**
 * [下段.]表示
 * int c: 色
 */
void SCLM_P105::markDownDot(int c){
  inputMark(3, c);
}

/**
 * マーク表示
 * int mark: データ番地
 * int c: 色
 */
void SCLM_P105::inputMark(int mark, int c){
  data[mark] = c;
}

/**
 * 画面表示
 */
void SCLM_P105::update(){
  transferData(27);
}

/**
 * 画面消去
 */
void SCLM_P105::clear(){

  // 記号部分に黒を設定する
  for(int i = 0; i < 17; i++)
    data[i] = LED_BLACK;

  // 数字部分に黒を設定する
  for(int i = 0; i < 10; i++)
    data[i + 17] = LED_BLACK + 8;
}

/**
 * データ転送
 */
void SCLM_P105::transferData(int dataSize){

  // BUSYがLOWになるのを待つ
  waitBusy();

  // データ転送開始時に/CSをLOWにする
  digitalWrite(CS, LOW);
  delayMicroseconds(4);

  // データ転送
  for(int i = 0; i < dataSize; i++){

    // ビット毎にデータを書き込む
    delayMicroseconds(6);
    digitalWrite(DB0, data[i] & 0b00000001);
    digitalWrite(DB1, data[i] & 0b00000010);
    digitalWrite(DB2, data[i] & 0b00000100);
    digitalWrite(DB3, data[i] & 0b00001000);
    digitalWrite(DB4, data[i] & 0b00010000);
    digitalWrite(DB5, data[i] & 0b00100000);
    digitalWrite(DB6, data[i] & 0b01000000);
    digitalWrite(DB7, data[i] & 0b10000000);

    // クロックを刻む
    digitalWrite(CLK, HIGH);
    delayMicroseconds(4);
    digitalWrite(CLK, LOW);
    delayMicroseconds(4);
  }

  // データ転送終了時に/CSをHIGHにする
  digitalWrite(CS, HIGH);
}

/**
 * BUSYがLOWになるのを待つ
 */
void SCLM_P105::waitBusy(){
  while(digitalRead(BUSY))
    delay(1);
}
