# cloudwatch_alert
AWSのCloudWatchのアラートをArduinoで表現する
![Alt text](http://blog.picomon.jp/tech/wp-content/uploads/sites/5/2015/08/2015-08-03-20.23.40.jpg)

## インストール
direnvとNode.js 0.10系、Arduino IDEを用意する

* このリポジトリをgit cloneする
```
git clone git@github.com:kitadesign/cloudwatch_alert.git && cd cloudwatch_alert
```

* direnvを編集し、有効にする
```
direnv edit .
direnv allow
```

* cloudwatch_alert.inoを編集し、Arduinoに書き込む

* Node.jsを実行する
```
npm install
npm start
```


[Blog](http://blog.picomon.jp/tech/?p=580)
