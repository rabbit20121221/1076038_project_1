# 1076038 Project 1 - 2-bit Predictor
此檔案介紹如何使用此程式

## 執行方式
輸入 input 檔案檔名。

## 程式流程
	1. 讀入 Taken/Not Taken 序列
	2. 輸入 Predictor 初始狀態(00)
	3. 進行預測(T/N)
	4. 計算 Misprediction rate
	5. 輸出結果

## FUNCTION
bool two_bit_predictor(int index);
此 function 用來預測 Taken 或 Not Taken，並回傳下一個狀態(state)。

## INPUT FILE
輸入檔包含 T(Taken) 及 NT(Not Taken)。
* **Example:** test1.txt

		T NT T T T NT NT NT NT
		NT NT T T T T NT T NT

以上總共 5 比測試資料

## OUTPUT FILE
輸出檔包含 Prediction、Miss or not 以及 Misprediction rate。
* **Example:** output.txt
	
		State: 00 01 00 01 10 11 10 01 00 
		Input: T NT T T T NT NT NT NT 
		Prediction: N N N N T T T N N 
 		Miss or not: X O X X O X X O O 
  		Misprediction rate: 5/9
  
  		State: 00 00 00 01 10 11 11 10 11 
  		Input: NT NT T T T T NT T NT 
  		Prediction: N N N N T T T T T 
  		Miss or not: O O X X O O X O X 
  		Misprediction rate: 4/9

