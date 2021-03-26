//
// Created by npchitman on 3/19/21.
//

#ifndef GSERVER_MSG_H
#define GSERVER_MSG_H

struct MsgHead{
    unsigned short size;
    unsigned short type;
    MsgHead(const unsigned short _size, const unsigned short _type){
        size = _size;
        type = _type;
    }
};

enum MsgType {
    LOGIN_C2S,
    LOGIN_S2C,
};

const int MAX_NAME 32;
const int MAX_MSG 255;

struct Msg_Login_C2S : MsgHead{
    Msg_Login_C2S()
    : MsgHead(sizeof (*this), LOGIN_C2S){}

    char szName[MAX_NAME];
};

struct Msg_Login_S2C : MsgHead{
    Msg_Login_S2C()
    : MsgHead(sizeof(*this), LOGIN_S2C){}

    unsigned short id;
};

#endif //GSERVER_MSG_H
