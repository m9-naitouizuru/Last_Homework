//
//  main.cpp
//  Homework_Last
//
//  Created by 内藤出 on 2021/07/30.
//

#include <ctime>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Player {
    
    friend class Janken;
    
    int type;  // 0:人間　1:コンピュータ
    string name; // 名前
    int hand; // 手
    int result; // 判定結果
    int win; // 勝ち数
    int lose; // 負け数
    int draw; // 引き分け
    
public:
    Player(int t, string n) {
        type = t;
        name = n;
        win = lose = draw = 0;
    }
    
    void newHand(void) {
        if (type == 0) //人間の手をキーボードから読み込む
            cin >> hand;
        else
            hand = rand() % 3; // 乱数発生
    }
    
    void  recordCount(void) {  // 勝敗回数を更新
        switch (result) {
            case 0: draw++; break;  // 引き分け
            case 1: lose++; break;  // 負け
            case 2: win++; break;  // 勝ち
        }
    }
    
    string getName(void) { // 名前を返す
        return (name);
    }
    
    void put_record(void) { // 勝敗数を表示
        cout << name << "：" << win << "勝" << lose << "負け" << draw << "引き分け\n";
    }
};


class Janken {
    static string hd[3];

public:
    Janken(void) {
        time_t t;
        srand(time(&t) % RAND_MAX);
    }
    
    void put_start_message(void) {
        cout << "CPとのじゃんけんゲーム開始\n";
    }
    
    void put_janken_message(const Player &p1) {
        cout << "\n" << p1.name;
        cout << "\n\aじゃんけんぽん";
        for (int i = 0; i < 3; i++)
            cout << "(" << i << ")" << hd[i] << " ";
        cout << "：\n";
    }
    
    void put_hands(const Player &p1, const Player &p2) { // プレーヤーの手を表示
        cout << p1.name << "は" << hd[p1.hand] << "で、" << p2.name << "は" << hd[p2.hand] << "です。\n";
    }
    
    void judge(Player &p1, Player &p2) {
        p1.result = (p1.hand - p2.hand + 3) % 3;
        p2.result = (p2.hand - p1.hand + 3) % 3;
    }
    
    void disp_result(const Player &p1) {
        switch(p1.result) {
            case 0: cout << p1.name <<"の引き分けです\n"; break;
            case 1: cout << p1.name << "の負けです\n"; break;
            case 2: cout << p1.name << "の勝ちです\n"; break;
        }
    }
    
    int retry(void) {
        int x;
        cout << "もう一度しますか・・・(0)いいえ　(1)はい：";
        cin >> x;
        
        return (x);
    }
    
};

string Janken::hd[] = {"グー", "チョキ", "パー"};

int main(void) {
    
    cout << "参加者は,\nCP, ";
    
    vector<string> v{"ないとう", "たなか", "さとう", "あいだ"};
    sort(v.begin(), v.end());
    for (auto i : v) cout << i << ", ";
    cout << "です。" << endl;
    
    Janken game;
    Player user1(0, "ないとう");
    Player user2(0, "たなか");
    Player user3(0, "さとう");
    Player user4(0, "あいだ");
    Player comp(1, "CP");
    
    game.put_start_message();
    
    do {
        comp.newHand();
        game.put_janken_message(user1);
        game.put_janken_message(user2);
        game.put_janken_message(user3);
        game.put_janken_message(user4);
        
        user1.newHand();
        user2.newHand();
        user3.newHand();
        user4.newHand();
        
        game.put_hands(user1, comp);
        game.judge(user1, comp);
        
        game.put_hands(user2,  comp);
        game.judge(user2, comp);
        
        game.put_hands(user3,  comp);
        game.judge(user3, comp);
        
        game.put_hands(user4, comp);
        game.judge(user4, comp);
        
        game.disp_result(user1);
        game.disp_result(user2);
        game.disp_result(user3);
        game.disp_result(user4);
        
        
        user1.recordCount();
        user2.recordCount();
        user3.recordCount();
        user4.recordCount();
        comp.recordCount();
    }
    
    while(game.retry());
    
    user1.put_record();
    user2.put_record();
    user3.put_record();
    user4.put_record();
    
}



