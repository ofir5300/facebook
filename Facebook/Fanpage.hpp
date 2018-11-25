//
//  Fanpage.hpp
//  Facebook
//
//  Created by Ilan Kushnir on 25/11/18.
//  Copyright © 2018 Ilan Kushnir. All rights reserved.
//

#ifndef Fanpage_hpp
#define Fanpage_hpp

#include "constants.hpp"
#include "Member.hpp"
#include "Status.hpp"

using namespace std;

class Fanpage
{
private:
    char        name[NAME_MAX_SIZE];
    Member**    fans = nullptr;
    int         fansCount = 0;
    int         fansArrSize = 0;
    Status**    statuses = nullptr;
    int         statusesCount = 0;
    int         statusesArrSize =0;
    
public:
    
    Fanpage(char* name)
    {
        strcpy(this->name, name);
    }
    
    ~Fanpage()
    {
        if (fansCount != 0) {
            for (int i = 0; i < fansCount; i++) {
                delete [](fans[i]);
            }
            delete []fans;
        }
        if (statusesCount != 0) {
            for (int i = 0; i < statusesCount; i++) {
                delete [](statuses[i]);
            }
            delete []statuses;
        }
    }
    
    bool        addFan(const Member& fan);
    Member**    getFans()                   const;
    Status**    getStatuses()               const;
    char*       getName()                   const;
};

#endif /* Fanpage_hpp */
