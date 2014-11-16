#ifndef __ASTAR_H__
#define __ASTAR_H__

#include "cocos2d.h"

USING_NS_CC;

struct AStar
{
    enum __STATUS
    {
        NONE,
        OPEN,
        CLOSED,
    };
    __STATUS status; // ステータス
    int cost;        // 移動コスト
    int heuristic;   // ヒューリスティックコスト
    AStar *parent;   // 親A*のポインタ
    Vec2 pos;       // 座標
    // スコア取得
    int GetScore()
    {
        return cost + heuristic;
    }
    
};
//
//class AStar
//{
//public:
//    // returning the class instance pointer
//    static AStar* create();
//    virtual bool init();  
//    
//};

#endif // __ASTAR_H__
