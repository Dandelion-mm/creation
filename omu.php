<?php
// LINE@ アクセストークン
$accessToken = '';


//-------------------------------------------------
// Webhook Event Objectの取り込み
//-------------------------------------------------
$Event_Object = file_get_contents('php://input'); // Objectを取得
$EventObj = json_decode($Event_Object); // ObjectをJSONデコード
$type = $EventObj->{"events"}[0]->{"message"}->{"type"}; // Message Event Typeの取得
$text = $EventObj->{"events"}[0]->{"message"}->{"text"}; // テキスト内容の取得
$replyToken = $EventObj->{"events"}[0]->{"replyToken"}; // ReplyTokenの取得

//-------------------------------------------------
// Webhook Event Objectごとの処理
//-------------------------------------------------
if($type != "text"){ // もしMessage Event TypeがTextではなかったら
  exit; // プログラム終了
} else { // それ以外なら（Textなら）
  // LINE Messaging APIの仕様に沿って、返答を成形
  if($text == '問題'){
    $response = [
    [
        'type' = > 'text',
        'text' => $text
        ]
};
}

//-------------------------------------------------
// Reply Message送信　※以下、おまじない
//-------------------------------------------------
$postData = [
    "replyToken" => $replyToken,
    "messages" => $response
    ];

$ch = curl_init("https://api.line.me/v2/bot/message/reply");
curl_setopt($ch, CURLOPT_POST, true);
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'POST');
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($postData));
curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Content-Type: application/json; charser=UTF-8',
    'Authorization: Bearer ' . $accessToken
    ));
$result = curl_exec($ch);
curl_close($ch);
